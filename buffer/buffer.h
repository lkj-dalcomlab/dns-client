//
// Created by lkj on 2022/12/05.
//

#ifndef DNS_CLIENT_BUFFER_H
#define DNS_CLIENT_BUFFER_H

#include <cstdint>
#include <memory>

class Buffer {
private:
    const char* m_buf;
    uint64_t m_bufSize{0};
    uint64_t m_index{0};
public:
    Buffer(const char *buf, uint64_t bufSize);
    ~Buffer();
    bool hasNext();
    char get();
    uint64_t getIndex();
    void setIndex(uint64_t idx);
    const char* getReadableData();
    uint64_t getReadableBytes();
    void consumeReadableBytes(uint64_t bytes);
};

using BufferPtr = std::unique_ptr<Buffer>;


#endif //DNS_CLIENT_BUFFER_H
