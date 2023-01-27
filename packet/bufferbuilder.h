//
// Created by lkj on 2022/12/05.
//

#ifndef DNS_CLIENT_BUFFERBUILDER_H
#define DNS_CLIENT_BUFFERBUILDER_H

#include "struct/packet.h"
#include "struct/packet.h"
#include "buffer/buffer.h"

class BufferBuilder {
public:
    BufferPtr build(Packet* header);

private:
    uint16_t flagsToLong(Packet* header);
    std::vector<char> nameToQName(const String &name);
};


#endif //DNS_CLIENT_BUFFERBUILDER_H
