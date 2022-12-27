//
// Created by lkj on 2022/12/01.
//

#include "query.h"

Query::Query(const String &name) : m_name(name) {}

const String &Query::getName() const {
    return m_name;
}

void Query::setName(const String &name) {
    m_name = name;
}

QType Query::getQType() const {
    return m_qType;
}

void Query::setQType(QType qType) {
    m_qType = qType;
}

QClass Query::getQClass() const {
    return m_qClass;
}

void Query::setQClass(QClass qClass) {
    m_qClass = qClass;
}
