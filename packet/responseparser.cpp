//
// Created by lkj on 2022/12/26.
//

#include <sstream>
#include "responseparser.h"
#include "struct/arecord.h"
#include "struct/emptyrecord.h"

ResponsePtr ResponseParser::parse(Buffer *buffer) {
    m_buffer = buffer;
    while (buffer->hasNext()) {
        switch (m_state) {
            case State::INIT:
                init();
                break;
            case State::QUERY:
                parseQuery();
                break;
            case State::TTL:
                parseTTL();
                break;
            case State::RECORD:
                parseRecord();
                break;
            case State::END:
                m_state = State::INIT;
                return std::move(m_response);
        }
    }

    if (m_state == State::END) {
        m_state = State::INIT;
        return std::move(m_response);
    }
    return nullptr;
}

void ResponseParser::init() {
    m_response = std::make_unique<Response>();
    m_state = State::QUERY;
}

void ResponseParser::parseQuery() {
    auto query = m_queryParser.parse(m_buffer);
    if (!query) {
        return;
    }

    m_response->setQuery(std::move(query));
    m_state = State::TTL;
}

void ResponseParser::parseTTL() {
    m_bytes.push_back(m_buffer->get());
    if (m_bytes.size() < 4) {
        return;
    }

    uint32_t ttl{0};
    uint8_t byteIdx = 0;
    for (int i = m_bytes.size()-1; i >= 0; --i) {
        auto shift = byteIdx++ * 8;
        ttl += (m_bytes[i] & 0xff) << shift;
    }

    m_response->setTtl(ttl);
    m_state = State::RECORD;
    m_bytes.clear();
}

void ResponseParser::parseRecord() {
    RecordPtr record = nullptr;
    auto qType = m_response->getQuery()->getQType();
    if (qType == RecordType::A) {
        record = m_aParser.parse(m_buffer);
    } else if (qType == RecordType::SRV) {
        record = m_srvParser.parse(m_buffer);
    } else {
        record = std::make_unique<EmptyRecord>();
    }

    if (record) {
        m_response->setRecord(std::move(record));
        m_state = State::END;
    }
}
