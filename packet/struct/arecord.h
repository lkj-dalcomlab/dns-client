//
// Created by lkj on 2023/01/18.
//

#ifndef DNS_CLIENT_ARECORD_H
#define DNS_CLIENT_ARECORD_H


#include "Record.h"

class ARecord : public Record {
private:
    String m_ip;

public:
    ARecord(const String &ip);
    const String &getIp() override;

    RecordType getType() override;

    uint16_t getPriority() override;

    uint16_t getWeight() override;

    uint16_t getPort() override;

    const String &getTarget() override;
};

using ARecordPtr = std::unique_ptr<ARecord>;

#endif //DNS_CLIENT_ARECORD_H
