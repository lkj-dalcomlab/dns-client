//
// Created by lkj on 2022/12/22.
//

#include "packetparser.h"

PacketParser::PacketParser() {
    m_header = std::make_unique<Header>();
    m_headerBytes.resize(12);
}

HeaderPtr PacketParser::parse(BufferPtr buffer) {
    m_buffer = std::move(buffer);
    while (buffer->hasNext()) {
        switch (m_state) {
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
                break;
            case State::AUTHORITY :
                break;
            case State::ADDITIONAL :
                break;
        }
    }
    return nullptr;
}

void PacketParser::saveHeaderBytes() {
    if (m_headerBytes.size() > 12) {
        m_headerBytes.push_back(m_buffer->get());
        return;
    }
    m_state = State::TRANSACTION_ID;
}

void PacketParser::parseTransactionId() {
    m_header->setId((m_headerBytes[1] & 0xff) + ((m_headerBytes[0] << 8) & 0xff00));
    m_state = State::FLAGS;
}

//OpCode getOpCodeType(const uint8_t &opcode) {
//    switch (opcode) {
//        case 0:
//            break;
//        case 1:
//            break;
//        case 2:
//            break;
//        case 3:
//            break;
//        case 4:
//            break;
//    }
//    return OpCode::UNASSIGNED_;
//}

void PacketParser::parseFlags() {
    m_header->setResponse(m_headerBytes[2] & 0x01);
    uint8_t opcode = (m_headerBytes[2] << 1) & 0xf0;
    m_header->setOpCode((OpCode)opcode);
    m_header->setAa((m_headerBytes[2] << 4) & 0x01);
    m_header->setTc((m_headerBytes[2] << 5) & 0x01);
    m_header->setRd((m_headerBytes[2] << 6) & 0x01);
    m_header->setRa(m_headerBytes[3] & 0x01);
    m_header->setZ((m_headerBytes[3] << 1) & 0x07);
    m_header->setRCode((m_headerBytes[3] << 4) & 0x0f);
    m_state = State::COUNT;
}

void PacketParser::parseCount() {
    m_qCount = m_headerBytes[4] & (m_headerBytes[5] << 8);
    m_anCount = m_headerBytes[6] & (m_headerBytes[7] << 8);
    m_nsCount = m_headerBytes[8] & (m_headerBytes[9] << 8);
    m_arCount = m_headerBytes[10] & (m_headerBytes[11] << 8);
}

void PacketParser::parseQuery() {
    if (m_qCount > 0) {
        m_header->addQuery(m_queryParser.parse(m_buffer.get()));
        return;
    }
    m_state = State::ANSWER;
}

void PacketParser::parseAnswer() {
    if (m_anCount > 0) {

    }
    m_state = State::AUTHORITY;
}

void PacketParser::parseAuthority() {
    if (m_arCount > 0) {

    }
    m_state = State::ADDITIONAL;
}

void PacketParser::parseAdditional() {
    if (m_nsCount > 0) {

    }
}
