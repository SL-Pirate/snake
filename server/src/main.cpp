#include <iostream>
#include <memory>
#include <enet/enet.h>
#include <glaze/glaze.hpp>

#include "network.hpp"
#include "room.hpp"
#include "event_handler.hpp"

#define ENET_PORT 8080

int main() {
    if (enet_initialize() != 0) {
        std::cerr << "Failed to initialize. Aborting." << std::endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    ENetAddress address;
    const auto event = std::make_unique<ENetEvent>();
    address.host = ENET_HOST_ANY;
    address.port = ENET_PORT;
    const auto server = std::unique_ptr<ENetHost>(enet_host_create(&address, 0, 1, 0, 0));
    if (server == nullptr) {
        std::cerr << "Failed to create ENetHost. Aborting." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Starting server on " << address.host << ":" << address.port << std::endl;

    while (true) {
        while (enet_host_service(server.get(), event.get(), 1) > 0) {
            if (event->type == ENET_EVENT_TYPE_DISCONNECT) {
                disconnect(event);
            } else if (event->type == ENET_EVENT_TYPE_RECEIVE) {
                if (auto body = readPacket<std::string>(event); body.has_value()) {
                    switch (body.value().type) {
                        case CREATE_ROOM:
                            reply(event, createRoom(event));
                            break;
                        case JOIN_ROOM:
                            reply(event, joinRoom(event));
                            break;
                        case POLL_PLAYERS:
                            reply(event, getPlayersInRoom(event));
                            break;
                    }
                }
            }

            enet_packet_destroy(event->packet);
        }
    }
}

template<typename T>
static std::optional<NetworkPacket<T> > readPacket(const std::unique_ptr<ENetEvent> &event) {
    std::string_view data(reinterpret_cast<const char *>(event->packet->data), event->packet->dataLength);
    auto packet = NetworkPacket<T>{};
    if (glz::read<netOpts>(packet, data)) {
        return std::nullopt;
    }

    enet_packet_destroy(event->packet);
    return packet;
}

static std::optional<std::string> address_to_string(const ENetPeer *peer) {
    char ip[64];
    if (enet_address_get_host_ip(&peer->address, ip, sizeof(ip)) == 0) {
        std::string ipStr = ip; // e.g. "192.168.1.10"
        return ip;
    }
    return std::nullopt;
}

static std::string createRoom(const std::unique_ptr<ENetEvent> &event) {
    const auto room = new Room(address_to_string(event->peer).value()); // memory is managed internally. Do not delete
    return room->getRoomId();
}

static std::string joinRoom(const std::unique_ptr<ENetEvent> &event) {
    const auto data = readPacket<ConnectSessionData>(event);
    if (!data.has_value() || !data.value().data.has_value()) return "null";
    const auto roomId = data.value().data.value().roomId;
    auto room = Room::findRoom(roomId);
    if (!room.has_value()) return "ROOM_NOT_FOUND";
    room.value().joinRoom(
        std::make_shared<Player>(
            data.value().data.value().name,
            address_to_string(event->peer).value()
        )
    );

    return "OK";
}

static std::vector<std::string> getPlayersInRoom(const std::unique_ptr<ENetEvent> &event) {
    const auto data = readPacket<ConnectSessionData>(event);
    if (!data.has_value() || !data.value().data.has_value()) return std::vector<std::string>{};
    const auto roomId = data.value().data.value().roomId;
    auto room = Room::findRoom(roomId);
    if (!room.has_value()) return std::vector<std::string>{};
    return room.value().getPlayerNamesInRoom();
}

static void disconnect(const std::unique_ptr<ENetEvent> &event) {
    const auto address = address_to_string(event->peer).value();
    Room::disconnectFromRoom(address);
}

template<typename T>
static void reply(const std::unique_ptr<ENetEvent> &event, T data) {
    const std::string json = glz::write_json(data).value_or("null");
    const auto packet = std::unique_ptr<ENetPacket>(
        enet_packet_create(json.data(), json.size(), ENET_PACKET_FLAG_RELIABLE)
    );
    if (enet_peer_send(event->peer, event->channelID, packet.get()) > 0) {
        enet_packet_destroy(packet.get());
    }
}
