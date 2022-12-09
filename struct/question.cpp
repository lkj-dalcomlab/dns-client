//
// Created by lkj on 2022/12/01.
//

#include "question.h"

Question::Question(const String &name) : m_name(name) {}

const String &Question::getName() const {
    return m_name;
}

void Question::setName(const String &name) {
    m_name = name;
}

QType Question::getQType() const {
    return m_qType;
}

void Question::setQType(QType qType) {
    m_qType = qType;
}

QClass Question::getQClass() const {
    return m_qClass;
}

void Question::setQClass(QClass qClass) {
    m_qClass = qClass;
}
