# pragma once

#include <memory>
#include <enet/enet.h>
#include <iostream>
#include <optional>
#include <glaze/core/opts.hpp>

constexpr long RESPONSE_TIMEOUT = 5000;

struct NetworkPacket;

class Network {
    std::unique_ptr<ENetHost> client = nullptr;
    bool isInitialized = false;
    std::unique_ptr<ENetAddress> enetAddress = nullptr;
    std::unique_ptr<ENetPeer> server = nullptr;
    std::unique_ptr<ENetEvent> event = nullptr;
    static constexpr glz::opts netOpts{.null_terminated = false};

    bool connectToServer();

    void send_packet(NetworkPacket data) const;

public:
    bool initialize();

    void deinitialize() const;

    bool createClient();

    bool connectToSession(std::string roomId) const;

    void disconnectFromSession() const;

    [[nodiscard]] std::optional<std::string> createSession() const;

    // will block the thread for timeout milliseconds
    [[nodiscard]] std::optional<NetworkPacket> readPacket(long timeout) const;
};

enum NetworkEventType {
    CREATE_ROOM = 0,
    JOIN_ROOM = 1
};

struct NetworkPacket { // NOLINT(*-pro-type-member-init)
    NetworkEventType type;
    std::optional<std::string> data;
};
