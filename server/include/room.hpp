#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

struct Player {
    std::string name;
    std::string address;
};

class Room {
    // rooms
    static std::unordered_map<std::string, std::shared_ptr<Room>> rooms;

    // index of players by channel id
    static std::unordered_map<std::string, std::shared_ptr<Room>> playerIndex;

    std::string roomId;
    std::string ownerAddress;
    std::vector<std::shared_ptr<Player>> players;

public:
    explicit Room(const std::string &ownerAddress);

    void joinRoom(const std::shared_ptr<Player> &player);

    std::string getRoomId();

    std::vector<std::string> getPlayerNamesInRoom();

    static void disconnectFromRoom(const std::string &playerAddress);

    static std::optional<Room> findRoom(const std::string &id);

    static std::optional<Room> findRoomByPlayerAddress(const std::string &address);
};
