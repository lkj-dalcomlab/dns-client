//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_RESPONSE_H
#define DNS_CLIENT_RESPONSE_H


#include "question.h"

class Response {
private:
    QuestionPtr m_question;
    uint8_t m_ttl{0};
    uint8_t m_resDataLen{0};
    char* m_data;
public:
    Response();

    const QuestionPtr &getQuestion() const;

    uint8_t getTtl() const;

    void setTtl(uint8_t ttl);

    uint8_t getResDataLen() const;

    void setResDataLen(uint8_t resDataLen);

    char *getData() const;

    void setData(char *data);
};

using ResponsePtr = std::unique_ptr<Response>;

#endif //DNS_CLIENT_RESPONSE_H
