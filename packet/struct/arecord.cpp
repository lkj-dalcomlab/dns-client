//
// Created by lkj on 2023/01/18.
//

#include "arecord.h"

ARecord::ARecord(const String &ip) : m_ip(ip) {
}

const String &ARecord::getIp() {
    return m_ip;
}

RecordType ARecord::getType() {
    return RecordType::A;
}

uint16_t ARecord::getPriority() {
    return 0;
}

uint16_t ARecord::getWeight() {
    return 0;
}

uint16_t ARecord::getPort() {
    return 80;
}

const String &ARecord::getTarget() {
    return "";
}
