//
// Created by lkj on 2023/01/18.
//

#ifndef DNS_CLIENT_EMPTYRECORD_H
#define DNS_CLIENT_EMPTYRECORD_H


#include "Record.h"

class EmptyRecord : public Record {
public:
    const String &getIp() override;

    RecordType getType() override;

    uint16_t getPriority() override;

    uint16_t getWeight() override;

    uint16_t getPort() override;

    const String &getTarget() override;
};
#endif //DNS_CLIENT_EMPTYRECORD_H
