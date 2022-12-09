/*
 * Copyright DALCOMLAB Corporation - Flexus Web Server. 2021-2022
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */
#pragma once

#include <spdlog/spdlog.h>


#define LOG_DEBUG(fmt, ...)          \
  do {                                      \
        auto logger = Logger::getLogger();                                \
        logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::debug, fmt, ##__VA_ARGS__);  \
  } while (0)                               \


#define LOG_ERROR(fmt, ...)          \
  do {                                      \
        auto logger = Logger::getLogger();                                \
        logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::err, fmt, ##__VA_ARGS__);  \
  } while (0)                               \


#define LOG_INFO(fmt, ...)           \
  do {                                      \
        auto logger = Logger::getLogger();                                \
        logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::info, fmt, ##__VA_ARGS__);   \
  } while (0)                        \

#define LOG_TRACE(fmt, ...)           \
  do {                                      \
        auto logger = Logger::getLogger();                                \
        logger->log(spdlog::source_loc{__FILE__, __LINE__, __func__}, spdlog::level::trace, fmt, ##__VA_ARGS__);   \
  } while (0)                               \

class Logger {
public:
    static spdlog::logger *getLogger();
};
