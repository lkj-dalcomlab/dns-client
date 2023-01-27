//
// Created by lkj on 2023/01/18.
//

#ifndef DNS_CLIENT_RECORD_H
#define DNS_CLIENT_RECORD_H

#include "String.h"
#include "RecordType.h"

class Record {
public:
    virtual const String &getIp() = 0;
    virtual RecordType getType() = 0;
    virtual uint16_t getPriority() = 0;
    virtual uint16_t getWeight() = 0;
    virtual uint16_t getPort() = 0;
    virtual const String &getTarget() = 0;
};

using RecordPtr = std::unique_ptr<Record>;

#endif //DNS_CLIENT_RECORD_H
