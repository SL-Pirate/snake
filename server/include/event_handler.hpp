#pragma once
#include <memory>
#include <optional>
#include <enet/enet.h>

#include "network.hpp"

template<typename T>
static std::optional<NetworkPacket<T> > readPacket(const std::unique_ptr<ENetEvent> &event);

static std::optional<std::string> address_to_string(const ENetPeer *peer);

static std::string createRoom(const std::unique_ptr<ENetEvent> &event);

static std::string joinRoom(const std::unique_ptr<ENetEvent> &event);

static std::vector<std::string> getPlayersInRoom(const std::unique_ptr<ENetEvent> &event);

static void disconnect(const std::unique_ptr<ENetEvent> &event);

template <typename T>
static void reply(const std::unique_ptr<ENetEvent> &event, T data);