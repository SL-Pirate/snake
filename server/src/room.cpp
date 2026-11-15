#include "room.hpp"

#include <ranges>

Room::Room(const std::string &ownerAddress) {
    this->roomId = std::to_string(std::hash<std::string>{}(ownerAddress));
    this->ownerAddress = ownerAddress;
    rooms[this->roomId] = std::shared_ptr<Room>(this);
}

void Room::joinRoom(const std::shared_ptr<Player> &player) {
    this->players.push_back(player);
    playerIndex[player->address] = rooms[this->roomId];
}

std::string Room::getRoomId() {
    return this->roomId;
}

std::vector<std::string> Room::getPlayerNamesInRoom() {
    return this->players
           | std::views::transform([](const std::shared_ptr<Player> &player) { return player->name; })
           | std::ranges::to<std::vector<std::string> >();
}

void Room::disconnectFromRoom(const std::string &playerAddress) {
    if (!playerIndex.contains(playerAddress)) return;

    const auto room = playerIndex[playerAddress];
    std::erase_if(room->players, [playerAddress](const std::shared_ptr<Player> &player) {
        return player->address == playerAddress;
    });
}

std::optional<Room> Room::findRoom(const std::string &id) {
    if (rooms.contains(id)) {
        return *rooms[id];
    }

    return std::nullopt;
}

std::optional<Room> Room::findRoomByPlayerAddress(const std::string &address) {
    if (!playerIndex.contains(address)) return std::nullopt;

    const auto room = playerIndex[address];
    return *room;
}

std::unordered_map<std::string, std::shared_ptr<Room> > Room::rooms = std::unordered_map<std::string, std::shared_ptr<
    Room> >();
std::unordered_map<std::string, std::shared_ptr<Room> > Room::playerIndex = std::unordered_map<std::string,
    std::shared_ptr<Room> >();
