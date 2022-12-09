//
// Created by lkj on 2022/12/05.
//

#ifndef DNS_CLIENT_BUFFEREXCEPTION_H
#define DNS_CLIENT_BUFFEREXCEPTION_H


#include <stdexcept>
#include "../struct/String.h"

class BufferException : std::runtime_error {
public:
    BufferException(const String &msg);
};


#endif //DNS_CLIENT_BUFFEREXCEPTION_H
