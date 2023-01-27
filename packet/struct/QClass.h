//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_QCLASS_H
#define DNS_CLIENT_QCLASS_H

enum class QClass {
    RESERVED = 0,
    IN = 1, //INTERNET
    UNASSIGNED = 2,
    CH = 3, // CHAOS
    HESIOD = 4, // HESIOD
    // UNASSIGNED = 5 ~ 253
};

#endif //DNS_CLIENT_QCLASS_H
