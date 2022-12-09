//
// Created by lkj on 2022/12/05.
//

#include "bufferexception.h"

BufferException::BufferException(const String &msg) : runtime_error(msg) {
}
