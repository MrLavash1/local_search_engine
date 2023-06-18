/**
* @file Doxyfile
* @brief This is the configuration file for Doxygen.
*
* @details This file contains the configuration options for Doxygen.
* It is used to generate documentation for the localSearchEngine project.
*
* @author LordJollu
*
*/
#pragma once

#include "InvertedIndex.h"

struct RelativeIndex {
    std::size_t docId;
    float rank;

    bool operator==(const RelativeIndex &other) const {
        return (docId == other.docId && rank == other.rank);
    }
};

class SearchServer { //// by SearchServer
public:
    /**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе */
    SearchServer(InvertedIndex &idx) : _index(idx) {};

/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла requests.json
* @return возвращает отсортированный список релевантных ответов для заданных запросов
*/
    std::vector<std::vector<RelativeIndex>> Search(const std::vector<std::string> &queries_input, int responses_limit);

private:
    InvertedIndex _index;
};