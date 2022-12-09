cmake_minimum_required(VERSION 3.23)
project(dns_client)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

add_executable(dns_client main.cpp struct/header.cpp struct/header.h struct/OpCode.h headerbuilder.cpp headerbuilder.h
        struct/question.cpp struct/question.h struct/String.h struct/QType.h struct/QClass.h struct/response.cpp struct/response.h
        struct/packet.cpp struct/packet.h packetbuilder.cpp packetbuilder.h net/reactor.h net/IoHandler.h
        net/socket.h net/clientsocket.h net/clientsocket.cpp logger/logger.h logger/logger.cpp buffer/buffer.cpp buffer/buffer.h buffer/bufferexception.cpp buffer/bufferexception.h net/reactorpoll.cpp net/reactorpoll.h net/Client.h promise/promise.h promise/promiseimpl.cpp promise/promiseimpl.h buffer/bufferlistener.h net/closelistener.h net/clientimpl.cpp net/clientimpl.h packet/packetwritelistener.h)
target_link_libraries(dns_client PRIVATE spdlog)
target_include_directories(dns_client PRIVATE logger)