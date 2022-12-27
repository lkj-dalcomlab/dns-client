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
        struct/query.cpp struct/query.h struct/String.h struct/QType.h struct/QClass.h struct/response.cpp struct/response.h
        struct/packet.cpp struct/packet.h packet/packetbuilder.cpp packet/packetbuilder.h logger/logger.h logger/logger.cpp
        buffer/buffer.cpp buffer/buffer.h buffer/bufferexception.cpp packet/packetwritelistener.h net/socket.cpp net/socket.h packet/packetparser.cpp packet/packetparser.h packet/queryparser.cpp packet/queryparser.h packet/qnameparser.cpp packet/qnameparser.h packet/responseparser.cpp packet/responseparser.h)
target_link_libraries(dns_client PRIVATE spdlog)
target_include_directories(dns_client PRIVATE logger)