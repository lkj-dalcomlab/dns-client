//
// Created by lkj on 2022/12/05.
//

#include "buffer.h"
#include "logger.h"
#include "bufferexception.h"


Buffer::Buffer(const char *buf, uint64_t bufSize) : m_bufSize(bufSize) {
    this->m_buf = buf;
}

Buffer::~Buffer() {
    LOG_INFO("delete buffer");
}

bool Buffer::hasNext() {
    return m_bufSize > m_index;
}

char Buffer::get() {
    if (!hasNext()) {
        throw new BufferException("buffer size overflow : " +
                                  std::to_string(m_bufSize) + "<=" + std::to_string(m_index));
    }
    return m_buf[m_index++];
}

uint64_t Buffer::getIndex() {
    return m_index;
}

void Buffer::setIndex(uint64_t idx) {
    m_index = idx;
}

const char* Buffer::getReadableData() {
    return m_buf + m_index;
}

uint64_t Buffer::getReadableBytes() {
    return m_bufSize - m_index;
}

void Buffer::consumeReadableBytes(uint64_t bytes) {
    m_index += bytes;
}