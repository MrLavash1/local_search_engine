

#pragma once

#include <map>

struct Entry {
    size_t docId, count;

    bool operator==(const Entry &other) const {
        return (docId == other.docId &&
                count == other.count);
    }
};

class [[maybe_unused]] InvertedIndex {
public:
    InvertedIndex() = default;

    /**
* Обновить или заполнить базу документов, по которой будем совершать
поиск
* @param texts_input содержимое документов */
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    /** Метод определяет количество вхождений слова word в загруженной базе документов
    * @param word слово, частоту вхождений которого необходимо определить * @return возвращает подготовленный список с частотой слов
    */
    std::vector<Entry> GetWordCount(const std::string &word);

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};