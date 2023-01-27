//
// Created by lkj on 2022/11/30.
//

#include "packet.h"

Packet::Packet() {}

uint16_t Packet::getId() const {
    return m_id;
}

void Packet::setId(uint16_t mId) {
    m_id = mId;
}

bool Packet::isResponse() const {
    return m_isResponse;
}

void Packet::setResponse(bool isResponse) {
    m_isResponse = isResponse;
}

OpCode Packet::getOpCode() const {
    return m_opCode;
}

void Packet::setOpCode(OpCode mOpCode) {
    m_opCode = mOpCode;
}

bool Packet::isAa() const {
    return m_aa;
}

void Packet::setAa(bool mAa) {
    m_aa = mAa;
}

bool Packet::isTc() const {
    return m_tc;
}

void Packet::setTc(bool mTc) {
    m_tc = mTc;
}

bool Packet::isRd() const {
    return m_rd;
}

void Packet::setRd(bool rd) {
    m_rd = rd;
}

bool Packet::isRa() const {
    return m_ra;
}

void Packet::setRa(bool ra) {
    m_ra = ra;
}

char Packet::getZ() const {
    return m_z;
}

void Packet::setZ(char z) {
    m_z = z;
}

char Packet::getRcode() const {
    return m_rCode;
}

void Packet::setRCode(char rCode) {
    m_rCode = rCode;
}



uint8_t Packet::getQDCount() {
    return m_queryList.size();
}

uint8_t Packet::getANCount() {
    return m_responses.size();
}

uint8_t Packet::getNSCount() {
    return m_authority.size();
}

uint8_t Packet::getARCount() {
    return m_additional.size();
}

void Packet::addQuery(QueryPtr query) {
    m_queryList.push_back(std::move(query));
}

Query *Packet::getQuery(uint16_t idx) {
    return m_queryList.at(idx).get();
}

void Packet::addResponse(ResponsePtr response) {
    m_responses.push_back(std::move(response));
}

Response *Packet::getResponse(uint16_t idx) {
    return m_responses.at(idx).get();
}

void Packet::addAuthority(ResponsePtr response) {
    m_authority.push_back(std::move(response));
}

Response *Packet::getAuthority(uint16_t idx) {
    return m_authority.at(idx).get();
}

void Packet::addAdditional(ResponsePtr response) {
    m_additional.push_back(std::move(response));
}

Response *Packet::getAdditional(uint16_t idx) {
    return m_additional.at(idx).get();
}


