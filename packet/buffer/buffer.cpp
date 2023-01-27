//
// Created by lkj on 2022/12/05.
//

#include "buffer.h"
#include "logger.h"
#include "bufferexception.h"

Buffer::~Buffer() {
    LOG_INFO("delete buffer");
}

bool Buffer::hasNext() {
    return m_bufSize > m_index;
}

char Buffer::current() {
    return m_buf[m_index];
}

char Buffer::get() {
    if (!hasNext()) {
        throw new BufferException("buffer size overflow : " +
                                  std::to_string(m_bufSize) + "<=" + std::to_string(m_index));
    }
    return m_buf[m_index++];
}

uint16_t Buffer::getIndex() {
    return m_index;
}

void Buffer::setIndex(uint16_t idx) {
    m_index = idx;
}

const char* Buffer::getReadableData() {
    return m_buf + m_index;
}

uint16_t Buffer::getReadableBytes() {
    return m_bufSize - m_index;
}

void Buffer::appendBuffer(const char *buf, uint16_t bufSize) {
    auto extBufSize = m_bufSize + bufSize;
    char *extBuf = new char[extBufSize];

    if (m_bufSize > 0) {
        memcpy(extBuf, m_buf, m_bufSize);
        delete []m_buf;
    }
    memcpy(&extBuf[m_bufSize], buf, bufSize);
    m_buf = extBuf;
    m_bufSize = extBufSize;
}

void Buffer::clear() {
    if (m_bufSize > 0) {
        delete []m_buf;
        m_bufSize = 0;
        m_index = 0;
    }
}
