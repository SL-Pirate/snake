#pragma once

#include <vector>
#include <array>
#include <optional>

inline bool isNetworkingEnabled = false;

class Payload {
    std::vector<std::array<int, 2> > snake;
    unsigned int score = 0;
    std::array<int, 2> *ateFruit = nullptr;

public:
    Payload(const std::vector<std::array<int, 2> > &snake, unsigned int score, std::array<int, 2> *ate_fruit);

    ~Payload();

    [[nodiscard]] std::vector<std::array<int, 2> > getSnake() const;

    [[nodiscard]] unsigned int getScore() const;

    [[nodiscard]] std::array<int, 2> *getAteFruit() const;
};

class INetworkInterface {
public:
    virtual ~INetworkInterface() = default;

    virtual void send(Payload payload) const = 0;

    [[nodiscard]] virtual std::optional<Payload> poll() const = 0;
};

class NetworkHost : public INetworkInterface {
public:
    void send(Payload payload) const override;

    [[nodiscard]] std::optional<Payload> poll() const override;
};

class NetworkClient : public INetworkInterface {
public:
    void send(Payload payload) const override;

    [[nodiscard]] std::optional<Payload> poll() const override;
};
