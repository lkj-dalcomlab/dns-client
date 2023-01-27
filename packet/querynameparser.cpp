//
// Created by lkj on 2023/01/18.
//

#include "querynameparser.h"
#include "struct/String.h"

void QueryNameParser::clear() {

}

String QueryNameParser::parse(Buffer *buffer) {
    m_buffer = buffer;
    while (buffer->hasNext()) {
        switch (m_state) {
            case State::DOMAIN_LENGTH:
                parseDomainLength();
                break;
            case State::DOMAIN_NAME:
                parseDomainName();
                break;
            case State::QUERY_NAME_OFFSET:
                parseQueryNameOffset();
                break;
            case State::END:
                String queryName = m_queryName;
                m_queryName = "";
                m_state = State::DOMAIN_LENGTH;
                return queryName;
        }
    }

    return "";
}

void QueryNameParser::parseDomainLength() {
    unsigned char c = m_buffer->get();

    if (m_bytes.empty() && (c & 0xc0) == 0xc0) {
        m_bytes.push_back(c & 0x3f);
        m_state = State::QUERY_NAME_OFFSET;
        return;
    }

    if (c == 0x00) {
        m_state = State::DOMAIN_NAME;
        return;
    }
    m_bytes.push_back(c);
}

void QueryNameParser::parseDomainName() {
    String qname;
    uint8_t size = m_bytes[0];
    for (auto idx = 1; idx < m_bytes.size(); ++idx) {
        qname += m_bytes[idx];
        --size;

        if (m_bytes.size() == idx + 1) {
            break;
        }

        if (size == 0) {
            ++idx;
            size = m_bytes[idx];
            qname += '.';
        }
    }
    m_bytes.clear();
    m_queryName = qname;

    if (m_tempOffset != 0) {
        m_buffer->setIndex(m_tempOffset);
        m_tempOffset = 0;
    }

    m_state = State::END;
}

void QueryNameParser::parseQueryNameOffset() {
    uint16_t offset = (m_bytes[0] << 8) + (m_buffer->get());
    m_tempOffset = m_buffer->getIndex();
    m_buffer->setIndex(offset);
    m_bytes.clear();
    m_state = State::DOMAIN_LENGTH;
}
