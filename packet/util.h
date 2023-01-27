//
// Created by lkj on 2023/01/27.
//

#ifndef DNS_CLIENT_UTIL_H
#define DNS_CLIENT_UTIL_H


#include "struct/String.h"
#include "struct/packet.h"

class Util {
public:
    static String targetToIp(Packet *packet, Record *targetRecord);
    static RecordType toRecordType(const String &recordType);
};


#endif //DNS_CLIENT_UTIL_H
