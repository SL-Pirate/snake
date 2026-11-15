#pragma once

#include <optional>
#include <string>

static constexpr glz::opts netOpts{.null_terminated = false};

enum NetworkEventType {
    CREATE_ROOM = 0,
    JOIN_ROOM = 1,
    POLL_PLAYERS = 2
};

template<typename T>
struct NetworkPacket { // NOLINT(*-pro-type-member-init)
    NetworkEventType type;
    std::optional<T> data;
};

struct ConnectSessionData {
    std::string roomId;
    std::string name;
};
