//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_QUERY_H
#define DNS_CLIENT_QUERY_H

#include "String.h"
#include "RecordType.h"
#include "QClass.h"
#include <memory>

class Query {
private:
    String m_name{""};
    uint16_t m_offset{0};
    RecordType m_qType{RecordType::A};
    QClass m_qClass{QClass::IN};

public:
    Query();

    explicit Query(const String &name);

    const String &getName() const;

    void setName(const String &name);

//    uint16_t getNameOffset() const;
//
//    void setNameOffset(uint16_t offset);

    RecordType getQType() const;

    void setQType(RecordType qType);

    QClass getQClass() const;

    void setQClass(QClass qClass);
};

using QueryPtr = std::unique_ptr<Query>;

#endif //DNS_CLIENT_QUERY_H
