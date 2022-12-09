//
// Created by lkj on 2022/12/08.
//

#ifndef DNS_CLIENT_PACKETWRITELISTENER_H
#define DNS_CLIENT_PACKETWRITELISTENER_H


#include "../promise/promise.h"
#include "../struct/packet.h"

class PacketWriteListener {
public:
    virtual PromiseSPtr onWrite(PacketPtr packet) = 0;
};


#endif //DNS_CLIENT_PACKETWRITELISTENER_H
