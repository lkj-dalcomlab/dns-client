//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_QTYPE_H
#define DNS_CLIENT_QTYPE_H

enum class QType {
    RESERVED = 0,
    A = 1,
    NS = 2,
    CNAME = 5,
    SOA = 6,
    MX = 15,
    AAAA = 28,
    SRV = 33
};

#endif //DNS_CLIENT_QTYPE_H
