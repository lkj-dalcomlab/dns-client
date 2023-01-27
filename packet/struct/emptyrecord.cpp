//
// Created by lkj on 2023/01/18.
//

#include "emptyrecord.h"

const String &EmptyRecord::getIp() {
    return "";
}

RecordType EmptyRecord::getType() {
    return RecordType::RESERVED;
}

uint16_t EmptyRecord::getPriority() {
    return 0;
}

uint16_t EmptyRecord::getWeight() {
    return 0;
}

uint16_t EmptyRecord::getPort() {
    return 0;
}

const String &EmptyRecord::getTarget() {
    return "";
}
