# pragma once

#include <memory>
#include <enet/enet.h>
#include <iostream>
#include <optional>
#include <glaze/core/opts.hpp>

constexpr long RESPONSE_TIMEOUT = 5000;

template <typename T>
struct NetworkPacket;

class Network {
    std::unique_ptr<ENetHost> client = nullptr;
    bool isInitialized = false;
    std::unique_ptr<ENetAddress> enetAddress = nullptr;
    std::unique_ptr<ENetPeer> server = nullptr;
    std::unique_ptr<ENetEvent> event = nullptr;
    static constexpr glz::opts netOpts{.null_terminated = false};

    bool connectToServer();

    template <typename T>
    void sendPacket(NetworkPacket<T> data) const;

public:
    bool initialize();

    void deinitialize() const;

    bool createClient();

    [[nodiscard]] bool connectToSession(std::string roomId, std::string name) const;

    void disconnectFromSession() const;

    [[nodiscard]] std::optional<std::string> createSession() const;

    // will block the thread for timeout milliseconds
    template <typename T>
    [[nodiscard]] std::optional<NetworkPacket<T>> readPacket(long timeout) const;

    [[nodiscard]] std::vector<std::string> discoverPlayers() const;
};

enum NetworkEventType {
    CREATE_ROOM = 0,
    JOIN_ROOM = 1,
    POLL_PLAYERS = 2
};

template <typename T>
struct NetworkPacket { // NOLINT(*-pro-type-member-init)
    NetworkEventType type;
    std::optional<T> data;
};

struct ConnectSessionData {
    std::string roomId;
    std::string name;
};
