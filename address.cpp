//
// Created by lkj on 2022/12/28.
//

#include <sstream>
#include "address.h"
#include "fmt/format.h"


const String &Address::getIp() const {
    return m_ip;
}

uint32_t Address::getPort() const {
    return m_port;
}

Address::Address(const String &ip, uint16_t port) : m_ip(ip), m_port(port){}

String Address::toString() {
    std::stringstream stream;
    stream << fmt::format("ip : {}", m_ip);
    if (m_port > 0) {
        stream << fmt::format(", port : {}", m_port);
    }
    return stream.str();
}
