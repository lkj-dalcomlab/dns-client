//
// Created by lkj on 2022/11/30.
//

#ifndef DNS_CLIENT_HEADER_H
#define DNS_CLIENT_HEADER_H

#include <vector>
#include "query.h"
#include "response.h"
#include "OpCode.h"

//                                    1  1  1  1  1  1
//      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                      ID                       |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                    QDCOUNT                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                    ANCOUNT                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                    NSCOUNT                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                    ARCOUNT                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

class Header {
private:
    uint16_t m_id;

    bool m_isResponse{false}; // QR
    OpCode m_opCode{OpCode::QUERY};
    bool m_aa{false};
    bool m_tc{false};
    bool m_rd{true};
    bool m_ra{false};
    char m_z = {0x00};
    char m_rCode{0x00};
    std::vector<QueryPtr> m_questions;
    std::vector<ResponsePtr> m_answers;
    std::vector<ResponsePtr> m_authority;
    std::vector<ResponsePtr> m_additional;

public:
    Header();

    uint16_t getId() const;

    void setId(uint16_t mId);

    bool isResponse() const;

    void setResponse(bool mIsResponse);

    OpCode getOpCode() const;

    void setOpCode(OpCode mOpCode);

    bool isAa() const;

    void setAa(bool mAa);

    bool isTc() const;

    void setTc(bool mTc);

    bool isRd() const;

    void setRd(bool rd);

    bool isRa() const;

    void setRa(bool ra);

    char getZ() const;

    void setZ(char z);

    char getRcode() const;

    void setRCode(char rCode);

    void addQuery(QueryPtr query);

    Query *getQuery(int idx);
//    void addAnswer();
//    void addAuthority();
//    void addAdditional();

    uint8_t getQDCount();
    uint8_t getANCount();
    uint8_t getNSCount();
    uint8_t getARCount();
};

using HeaderPtr = std::unique_ptr<Header>;

#endif //DNS_CLIENT_HEADER_H
