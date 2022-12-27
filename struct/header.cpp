//
// Created by lkj on 2022/11/30.
//

#include "header.h"

Header::Header() {}

uint16_t Header::getId() const {
    return m_id;
}

void Header::setId(uint16_t mId) {
    m_id = mId;
}

bool Header::isResponse() const {
    return m_isResponse;
}

void Header::setResponse(bool isResponse) {
    m_isResponse = isResponse;
}

OpCode Header::getOpCode() const {
    return m_opCode;
}

void Header::setOpCode(OpCode mOpCode) {
    m_opCode = mOpCode;
}

bool Header::isAa() const {
    return m_aa;
}

void Header::setAa(bool mAa) {
    m_aa = mAa;
}

bool Header::isTc() const {
    return m_tc;
}

void Header::setTc(bool mTc) {
    m_tc = mTc;
}

bool Header::isRd() const {
    return m_rd;
}

void Header::setRd(bool rd) {
    m_rd = rd;
}

bool Header::isRa() const {
    return m_ra;
}

void Header::setRa(bool ra) {
    m_ra = ra;
}

char Header::getZ() const {
    return m_z;
}

void Header::setZ(char z) {
    m_z = z;
}

char Header::getRcode() const {
    return m_rCode;
}

void Header::setRCode(char rCode) {
    m_rCode = rCode;
}



uint8_t Header::getQDCount() {
    return m_questions.size();
}

uint8_t Header::getANCount() {
    return m_answers.size();
}

uint8_t Header::getNSCount() {
    return m_authority.size();
}

uint8_t Header::getARCount() {
    return m_additional.size();
}

void Header::addQuery(QueryPtr query) {
    m_questions.push_back(std::move(query));
}

Query *Header::getQuery(int idx) {
    return m_questions.at(idx).get();
}


