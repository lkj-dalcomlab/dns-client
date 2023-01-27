//
// Created by lkj on 2022/12/22.
//

#include "packetparser.h"

PacketPtr PacketParser::parse(BufferPtr buffer) {
    m_buffer = std::move(buffer);
    while (m_buffer->hasNext()) {
        switch (m_state) {
            case State::INIT:
                init();
                break;
            case State::HEADER_BYTES :
                saveHeaderBytes();
                break;
            case State::TRANSACTION_ID :
                parseTransactionId();
                break;
            case State::FLAGS :
                parseFlags();
                break;
            case State::COUNT :
                parseCount();
                break;
            case State::QUERY :
                parseQuery();
                break;
            case State::ANSWER :
                parseAnswer();
                break;
            case State::AUTHORITY :
                parseAuthority();
                break;
            case State::ADDITIONAL :
                parseAdditional();
                break;
            case State::END:
                return std::move(m_packet);
        }
    }

    if (m_state == State::END) {
        return std::move(m_packet);
    }
    return nullptr;
}

void PacketParser::init() {
    m_packet = std::make_unique<Packet>();
    m_headerBytes.clear();
    m_state = State::HEADER_BYTES;
}

void PacketParser::saveHeaderBytes() {
    if (m_headerBytes.size() < 12) {
        m_headerBytes.push_back(m_buffer->get());
        return;
    }
    m_state = State::TRANSACTION_ID;
}

void PacketParser::parseTransactionId() {
    m_packet->setId((m_headerBytes[1] & 0xff) + ((m_headerBytes[0] << 8) & 0xff00));
    m_state = State::FLAGS;
}

void PacketParser::parseFlags() {
    m_packet->setResponse(m_headerBytes[2] & 0x80);
    uint8_t opcode = (m_headerBytes[2] << 1) & 0xf0;
    m_packet->setOpCode((OpCode)opcode);
    m_packet->setAa((m_headerBytes[2]) & 0x04);
    m_packet->setTc((m_headerBytes[2]) & 0x02);
    m_packet->setRd((m_headerBytes[2]) & 0x01);

    m_packet->setRa(m_headerBytes[3] & 0x80);
    m_packet->setZ((m_headerBytes[3] >> 4) & 0x07);
    m_packet->setRCode((m_headerBytes[3]) & 0x0f);
    m_state = State::COUNT;
}

void PacketParser::parseCount() {
    m_qCount = (m_headerBytes[4] << 8) + m_headerBytes[5];
    m_anCount = (m_headerBytes[6] << 8) + m_headerBytes[7];
    m_nsCount = (m_headerBytes[8] << 8) + m_headerBytes[9];
    m_arCount = (m_headerBytes[10] << 8) + m_headerBytes[11];
    m_state = !m_qCount && !m_anCount && !m_arCount && !m_nsCount ? State::END : State::QUERY;
}

void PacketParser::parseQuery() {
    if (m_qCount == 0) {
        m_state = State::ANSWER;
        return;
    }

    m_packet->addQuery(m_queryParser.parse(m_buffer.get()));
    if (m_qCount > m_packet->getQDCount()) {
        return;
    }
    m_state = !m_anCount && !m_arCount && !m_nsCount ? State::END : State::ANSWER;
}

void PacketParser::parseAnswer() {
    if (m_anCount == 0) {
        m_state = State::AUTHORITY;
        return;
    }

    m_packet->addResponse(m_responseParser.parse(m_buffer.get()));
    if (m_anCount > m_packet->getANCount()) {
        return;
    }
    m_state = !m_arCount && !m_nsCount ? State::END : State::AUTHORITY;
}

void PacketParser::parseAuthority() {
    if (m_nsCount == 0) {
        m_state = State::ADDITIONAL;
        return;
    }

    m_packet->addAuthority(m_responseParser.parse(m_buffer.get()));
    if (m_nsCount > m_packet->getNSCount()) {
        return;
    }
    m_state = !m_arCount ? State::END : State::ADDITIONAL;
}

void PacketParser::parseAdditional() {
    if (m_arCount == 0) {
        m_state = State::END;
        return;
    }

    m_packet->addAdditional(m_responseParser.parse(m_buffer.get()));
    if (m_arCount > m_packet->getARCount()) {
        return;
    }
    m_state = State::END;
}
