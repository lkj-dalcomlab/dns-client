//
// Created by lkj on 2022/12/05.
//

#ifndef DNS_CLIENT_BUFFER_H
#define DNS_CLIENT_BUFFER_H

#include <cstdint>
#include <memory>

class Buffer {
private:
    const char* m_buf{nullptr};
    uint16_t m_bufSize{0};
    uint16_t m_index{0};
public:
    ~Buffer();
    bool hasNext();
    char current();
    char get();
    uint16_t getIndex();
    void setIndex(uint16_t idx);
    const char* getReadableData();
    uint16_t getReadableBytes();

    void appendBuffer(const char *buf, uint16_t bufSize);
    void clear();
};

using BufferPtr = std::unique_ptr<Buffer>;


#endif //DNS_CLIENT_BUFFER_H
