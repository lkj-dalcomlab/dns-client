//
// Created by lkj on 2023/01/19.
//

#include "srvrecordparser.h"
#include "struct/srvrecord.h"

RecordPtr SrvRecordParser::parse(Buffer *buffer) {
    m_buffer = buffer;
    while (buffer->hasNext()) {
        switch (m_state) {
            case State::RDATA_LENGTH:
                parseRdLength();
                break;
            case State::PRIORITY:
                parsePriority();
                break;
            case State::WEIGHT:
                parseWeight();
                break;
            case State::PORT:
                parsePort();
                break;
            case State::TARGET:
                parseTarget();
                break;
            case State::END:
                m_state = State::RDATA_LENGTH;
                return std::move(m_record);
        }
    }
    return m_state == State::END ? std::move(m_record) : nullptr;
}

void SrvRecordParser::parseRdLength() {
    m_bytes.push_back(m_buffer->get());
    if (m_bytes.size() < 2) {
        return;
    }

    uint32_t rdLength{0};
    rdLength += (m_bytes[0] & 0xff) << 8;
    rdLength += (m_bytes[1] & 0xff);
    m_rDataLength = rdLength;

    m_state = State::PRIORITY;
    m_bytes.clear();

    m_record = std::make_unique<SrvRecord>();
}

void SrvRecordParser::parsePriority() {
    m_bytes.push_back(m_buffer->get());
    if (m_bytes.size() < 2) {
        return;
    }

    uint32_t priority{0};
    priority += (m_bytes[0] & 0xff) << 8;
    priority += (m_bytes[1] & 0xff);
    m_record->setPriority(priority);

    m_state = State::WEIGHT;
    m_bytes.clear();
}

void SrvRecordParser::parseWeight() {
    m_bytes.push_back(m_buffer->get());
    if (m_bytes.size() < 2) {
        return;
    }

    uint32_t weight{0};
    weight += (m_bytes[0] & 0xff) << 8;
    weight += (m_bytes[1] & 0xff);
    m_record->setWeight(weight);

    m_state = State::PORT;
    m_bytes.clear();
}

void SrvRecordParser::parsePort() {
    m_bytes.push_back(m_buffer->get());
    if (m_bytes.size() < 2) {
        return;
    }

    uint32_t port{0};
    port += (m_bytes[0] & 0xff) << 8;
    port += (m_bytes[1] & 0xff);
    m_record->setPort(port);

    m_state = State::TARGET;
    m_bytes.clear();
}

void SrvRecordParser::parseTarget() {
    auto queryName = m_queryNameParser.parse(m_buffer);
    if (queryName.empty()) {
        return;
    }

    m_state = State::END;
    m_record->setTarget(queryName);
}
