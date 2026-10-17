#include "net_base.hpp"

void NetworkHost::send(Payload payload) const {
}

std::optional<Payload> NetworkHost::poll() const {
    return std::nullopt;
}
