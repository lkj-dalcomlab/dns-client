#include "headerbuilder.h"
#include "packet/packetbuilder.h"
#include "net/socket.h"

int main() {
    HeaderBuilder headerBuilder;
    auto header = headerBuilder.build("www.dalcomlab.com");

    PacketBuilder packetBuilder;
    auto buffer = packetBuilder.build(header.get());

    auto socket = std::make_unique<Socket>();
    if (!socket->connect("168.126.63.1", 53)) {
        return 0;
    }

    int write = 0;
    while (buffer->getReadableBytes() > 0) {
        write += socket->write(buffer->getReadableData(), buffer->getReadableBytes());
        buffer->setIndex(buffer->getIndex() + write);
    }
    char buf[1024] = {0,};

    int read = socket->read(buf, 1024);
    while (read <= -1) {
        read = socket->read(buf, 1024);
    }
    return 0;
}
