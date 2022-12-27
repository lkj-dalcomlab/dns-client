//
// Created by lkj on 2022/12/26.
//

#include "responseparser.h"

ResponsePtr ResponseParser::parse(Buffer *buffer) {
    while (buffer->hasNext()) {
        switch (m_state) {
            case State::QUERY:
                parseQuery();
                break;
            case State::TTL:
                parseTTL();
                break;
            case State::RD_LENGTH:
                parseRdLength();
                break;
            case State::RDATA:
                parseRdata();
                break;
            case State::END:
                return std::move(m_response);
        }
    }

    return nullptr;
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
    if (m_bytes.size() < 4) {
        m_bytes.push_back(m_buffer->get());
        return;
    }

    uint32_t ttl{0};
    for (auto i = 0; i < m_bytes.size(); ++i) {
        auto shift = i * 8;
        ttl += (m_bytes[0] << shift) & 0xff ;
    }
    m_response->setTtl(ttl);
    m_state = State::RD_LENGTH;
}

void ResponseParser::parseRdLength() {
    if (m_bytes.size() < 2) {
        m_bytes.push_back(m_buffer->get());
        return;
    }

    uint32_t rdLength{0};
    for (auto i = 0; i < m_bytes.size(); ++i) {
        auto shift = i * 8;
        rdLength += (m_bytes[0] << shift) & 0xff ;
    }
    m_response->setResDataLen(rdLength);
    m_state = State::RDATA;
}

void ResponseParser::parseRdata() {
    if (m_bytes.size() < m_response->getResDataLen()) {
        m_bytes.push_back(m_buffer->get());
        return;
    }

    String rdata(m_bytes.begin(), m_bytes.end());
    m_response->setData(rdata);
    m_state = State::END;
}
