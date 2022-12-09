//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_QUESTION_H
#define DNS_CLIENT_QUESTION_H

#include "String.h"
#include "QType.h"
#include "QClass.h"

class Question {
private:
    String m_name;
    QType m_qType{QType::A};
    QClass m_qClass{QClass::IN};

public:
    explicit Question(const String &name);

    const String &getName() const;

    void setName(const String &name);

    QType getQType() const;

    void setQType(QType qType);

    QClass getQClass() const;

    void setQClass(QClass qClass);
};

using QuestionPtr = std::unique_ptr<Question>;

#endif //DNS_CLIENT_QUESTION_H
