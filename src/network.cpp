#include "network.hpp"
#include <glaze/glaze.hpp>
#include <utility>

bool Network::initialize() {
    if (enet_initialize() != 0) {
        return false;
    }
    isInitialized = true;
    atexit(enet_deinitialize);
    return true;
}

void Network::deinitialize() const {
    if (isInitialized) {
        enet_deinitialize();
    }
}

bool Network::createClient() {
    if (isInitialized) {
        client.reset(enet_host_create(nullptr, 1, 1, 0, 0));
    }

    if (client == nullptr) {
        return false;
    }

    return true;
}

bool Network::connectToServer() {
    enet_address_set_host(enetAddress.get(), "127.0.0.1");
    enetAddress->port = 8080;
    server.reset(enet_host_connect(client.get(), enetAddress.get(), 1, 0));
    if (server == nullptr) {
        return false;
    }
    const auto evt = std::make_unique<ENetEvent>();
    if (enet_host_service(client.get(), evt.get(), 5000) > 0 && evt->type == ENET_EVENT_TYPE_CONNECT) {
        return true;
    }

    enet_peer_reset(server.get());
    return false;
}

template<typename T>
void Network::sendPacket(NetworkPacket<T> data) const {
    const std::string json = glz::write_json(data).value_or("null");
    const auto packet = std::unique_ptr<ENetPacket>(
        enet_packet_create(json.data(), json.size(), ENET_PACKET_FLAG_RELIABLE));
    enet_peer_send(server.get(), 0, packet.get());
    enet_host_flush(client.get());
}

bool Network::connectToSession(std::string roomId, std::string name) const {
    const auto data = NetworkPacket{
        .type = JOIN_ROOM, .data = std::optional{ConnectSessionData{std::move(roomId), std::move(name)}}
    };
    sendPacket(data);

    std::optional<NetworkPacket<std::string> > value = readPacket<std::string>(RESPONSE_TIMEOUT);
    return value.transform([](const NetworkPacket<std::string> &packet) {
        return packet.data == "OK";
    }).value_or(false);
}

std::optional<std::string> Network::createSession() const {
    const auto data = NetworkPacket<std::string>{.type = CREATE_ROOM, .data = std::nullopt};
    sendPacket(data);

    std::optional<NetworkPacket<std::string> > value = readPacket<std::string>(RESPONSE_TIMEOUT);
    return value.transform([](const NetworkPacket<std::string> &packet) { return packet.data; }).value_or(std::nullopt);
}

void Network::disconnectFromSession() const {
    enet_peer_disconnect(server.get(), 0);
    const auto evt = std::make_unique<ENetEvent>();

    /* Allow up to 3 seconds for the disconnect to succeed
     * and drop any packets received packets.
     */
    while (enet_host_service(client.get(), evt.get(), 3000) > 0) {
        switch (evt->type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(evt->packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");
                return;
            default: ;
        }
    }

    /* We've arrived here, so the disconnect attempt didn't */
    /* succeed yet.  Force the connection down.             */
    enet_peer_reset(server.get());
}

template<typename T>
std::optional<NetworkPacket<T> > Network::readPacket(const long timeout) const {
    if (enet_host_service(client.get(), event.get(), timeout) > 0) {
        if (event->type == ENET_EVENT_TYPE_RECEIVE) {
            std::string_view data(reinterpret_cast<const char *>(event->packet->data), event->packet->dataLength);
            auto packet = NetworkPacket<T>{};
            if (glz::read<netOpts>(packet, data)) {
                return std::nullopt;
            }

            enet_packet_destroy(event->packet);
            return packet;
        }
    }

    return std::nullopt;
}

std::vector<std::string> Network::discoverPlayers() const {
    if (!isInitialized) return std::vector<std::string>{};

    std::vector<std::string> players;

    sendPacket(NetworkPacket<std::string>{POLL_PLAYERS});
    auto packet = readPacket<std::vector<std::string> >(0);
    if (!packet || packet->data->empty()) return {};
    return std::move(packet->data).value();
}
