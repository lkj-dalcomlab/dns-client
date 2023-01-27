//
// Created by lkj on 2022/12/28.
//

#ifndef DNS_CLIENT_ADDRESS_H
#define DNS_CLIENT_ADDRESS_H

#include <memory>

#include "packet/struct/String.h"

class Address {
private:
    String m_ip;
    uint16_t m_port{0};
public:
    explicit Address(const String &ip, uint16_t port);

    const String &getIp() const;
    uint32_t getPort() const;

    String toString();
};

using AddressPtr = std::unique_ptr<Address>;

#endif //DNS_CLIENT_ADDRESS_H
