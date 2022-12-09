//
// Created by lkj on 2022/12/01.
//

#include "headerbuilder.h"
uint8_t HeaderBuilder::m_id;
HeaderPtr HeaderBuilder::build(const std::string &domain) {
    auto header = std::make_unique<Header>();
    header->setId(m_id);

    auto question = std::make_unique<Question>(domain);
    header->addQuestion(std::move(question));

    m_id++;
    return header;
}
