//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_QUERY_H
#define DNS_CLIENT_QUERY_H

#include "String.h"
#include "QType.h"
#include "QClass.h"

class Query {
private:
    String m_name;
    QType m_qType{QType::A};
    QClass m_qClass{QClass::IN};

public:
    explicit Query(const String &name);

    const String &getName() const;

    void setName(const String &name);

    QType getQType() const;

    void setQType(QType qType);

    QClass getQClass() const;

    void setQClass(QClass qClass);
};

using QueryPtr = std::unique_ptr<Query>;

#endif //DNS_CLIENT_QUERY_H
