/**
 * @mainpage Local Search Engine
 *
 * @author Mark
 *
 * @section intro_sec Введение
 *
 * Это простой поисковый движок, который использует инвертированный индекс для поиска ключевых слов в наборе документов.
 *
 * @section install_sec Установка
 *
 * @subsection step1 Шаг 1
 *
 * Клонируйте репозиторий.
 *
 * @subsection step2 Шаг 2
 *
 * Запустите `cmake .` в корневом каталоге.
 *
 * @subsection step3 Шаг 3
 *
 * Запустите `make`, чтобы построить проект.
 *
 * @subsection step4 Шаг 4
 *
 * Запустите `./localSearchEngine`, чтобы запустить программу.
 *
 */

#pragma once

#include <vector>

#include "../header/SearchEngine.h"

//// @EXCEPTIONS
class ConfigFileEmpty_Exception : public std::exception {
public:
    const char *what() const noexcept override {
        return "Config file is empty!";
    }
};

class ConfigFileMissing_Exception : std::exception {
public:
    const char *what() const noexcept override {
        return "Config file is missing!";
    }
};

class ConfigFileVersionEmpty_Exception : public std::exception {
public:
    const char *what() const noexcept override {
        return "Config file version is empty!";
    }
};

class ConfigFileVersionIncorrect_Exception : public std::exception {
public:
    const char *what() const noexcept override {
        return "Config file has incorrect file version!";
    }
};

class RequestsFileEmpty_Exception : public std::exception {
public:
    const char *what() const noexcept override {
        return "Requests file is empty!";
    }
};

class RequestsFileMissing_Exception : std::exception {
public:
    const char *what() const noexcept override {
        return "Requests file is missing!";
    }
};

class Text_ExceptionALotOf : public std::exception {
public:
    const char *what() const noexcept override {
        return "Text file contains more than 1.000 words!";
    }
};

class Word_Exception100Chars : std::exception {
public:
    const char *what() const noexcept override {
        return "Word from text file contains more than 100 chars!";
    }
};

class MoreThen1000Requests_Exception : public std::exception {
public:
    const char *what() const noexcept override {
        return "Requests file contains more than 1.000 requests!";
    }
};

class WordsRequests_Exception : std::exception {
public:
    const char *what() const noexcept override {
        return "Request from requests file contains more than 10 words!";
    }
};

/**
* Класс для работы с JSON-файлами */
class ConverterJSON {

public:

    ConverterJSON() = default;

    /**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных * в config.json
*/
    std::vector<std::string> GetTextDocuments(const std::string& fileName);

    /**
* Метод считывает поле max_responses для определения предельного * количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();

    /**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json */
    std::vector<std::string> GetRequests();

    /**
    * Положить в файл answers.json результаты поисковых запросов */
    void PutAnswers(std::vector<std::vector<RelativeIndex>> answers);
};
