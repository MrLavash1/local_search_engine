#include <vector>
#include <sstream>
#include <string>

#include "../header/SearchEngine.h"


std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string>& queries_input, int responses_limit)
{
    std::vector<std::vector<RelativeIndex>> Search_Result;
    Search_Result.resize(queries_input.size());
    int query_id = 0;

    for (auto query : queries_input) {

        std::stringstream DATA(query);
        std::string word;

        // loading map, key - words
        std::map<std::string, std::vector<Entry>> map_sort_by_word;
        while (DATA >> word)
            map_sort_by_word[word];

        // additional loading map, value - docs_info [docId, word's ABS_rank]
        for (auto& [word, docs_info] : map_sort_by_word)
            docs_info = _index.GetWordCount(word);

        // load new map, key - docId, value - doc's ABS_rank (sum of word's ABS_rank for all words)
        std::map<int, int> map_resort_by_doc_id;
        for (auto& [word, docs_info] : map_sort_by_word)
            for (auto doc_info : docs_info)
                map_resort_by_doc_id[doc_info.docId] += doc_info.count;

        if (!map_resort_by_doc_id.empty()) {

            // load nem multimap, key - doc's ABS_rank, value - docId
            std::multimap<int, int> map_resost_by_count;
            auto it_2 = rbegin(map_resort_by_doc_id);
            for ( ; it_2 != rend(map_resort_by_doc_id); ++it_2)
                map_resost_by_count.emplace(it_2->second, it_2->first);

            // relevance calculation for each docId according responses_limit
            auto it_3 = rbegin(map_resost_by_count);
            int max_count = it_3->first;
            RelativeIndex index;
            for ( ; it_3 != rend(map_resost_by_count); ++it_3) {
                index.docId = it_3->second;
                index.rank = (it_3->first == max_count) ? 1.f : (float)(it_3->first) / max_count;
                Search_Result[query_id].push_back(index);
                if (--responses_limit == 0) break;
            }
        }

        ++query_id;
    }

    return Search_Result;
}
