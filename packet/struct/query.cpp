//
// Created by lkj on 2022/12/01.
//

#include "query.h"

Query::Query() {}

Query::Query(const String &name) : m_name(name) {}

const String &Query::getName() const {
    return m_name;
}

void Query::setName(const String &name) {
    m_name = name;
}

//uint16_t Query::getNameOffset() const {
//    return m_offset;
//}
//
//void Query::setNameOffset(uint16_t offset) {
//    m_offset = offset;
//}

RecordType Query::getQType() const {
    return m_qType;
}

void Query::setQType(RecordType qType) {
    m_qType = qType;
}

QClass Query::getQClass() const {
    return m_qClass;
}

void Query::setQClass(QClass qClass) {
    m_qClass = qClass;
}
