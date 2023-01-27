//
// Created by lkj on 2023/01/18.
//

#include "srvrecord.h"

const String &SrvRecord::getIp() {
    return "";
}

RecordType SrvRecord::getType() {
    return RecordType::SRV;
}

uint16_t SrvRecord::getPriority() {
    return 0;
}

uint16_t SrvRecord::getWeight() {
    return 0;
}

void SrvRecord::setIp(const String &ip) {
    m_ip = ip;
}

void SrvRecord::setPriority(uint16_t priority) {
    m_priority = priority;
}

void SrvRecord::setWeight(uint16_t weight) {
    m_weight = weight;
}

const String &SrvRecord::getTarget() {
    return m_target;
}

void SrvRecord::setTarget(const String &target) {
    m_target = target;
}

uint16_t SrvRecord::getPort() {
    return m_port;
}

void SrvRecord::setPort(uint16_t port) {
    m_port = port;
}
