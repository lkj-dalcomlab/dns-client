//
// Created by lkj on 2023/01/27.
//

#include "util.h"
#include "strings.h"

String Util::targetToIp(Packet *packet, Record *targetRecord) {
    if (targetRecord->getType() == RecordType::A) {
        return targetRecord->getIp();
    }

    String ip{};
    for (auto i = 0; i < packet->getARCount(); ++i) {
        auto res = packet->getAdditional(i);
        auto record = packet->getAdditional(i)->getRecord();
        if (record->getType() != RecordType::A) {
            continue;
        }
        if (targetRecord->getTarget() == res->getQuery()->getName()) {
            return record->getIp();
        }
    }
    return "";
}

RecordType Util::toRecordType(const String &recordType) {
    auto type = Strings::trim(recordType);
    type = Strings::toUpperCase(recordType);
    if (type == "A") {
        return RecordType::A;
    } else if (type == "SRV") {
        return RecordType::SRV;
    }

    return RecordType::RESERVED;
}
