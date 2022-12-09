//
// Created by lkj on 2022/12/01.
//

#include "response.h"

Response::Response() {
    m_question = std::make_unique<Question>("");
}

const QuestionPtr &Response::getQuestion() const {
    return m_question;
}

uint8_t Response::getTtl() const {
    return m_ttl;
}

void Response::setTtl(uint8_t ttl) {
    m_ttl = ttl;
}

uint8_t Response::getResDataLen() const {
    return m_resDataLen;
}

void Response::setResDataLen(uint8_t resDataLen) {
    m_resDataLen = resDataLen;
}

char *Response::getData() const {
    return m_data;
}

void Response::setData(char *data) {
    m_data = data;
}
