#include "WordRepository.h"

WordRepository& WordRepository::instance() {
    static WordRepository instance;
    return instance;
}

std::vector<std::shared_ptr<WordInfo>>& WordRepository::word_infos() {
    return word_infos_;
}

void WordRepository::LoadWordInfos() {
    auto word_info = std::make_shared<WordInfo>();
    word_info->type = WordInfo::kNoun;
    word_info->word = "sediment";
    word_info->ko_meanings = { "침전물" };
    word_info->examples = { "침전물" };
    word_infos_.emplace_back(word_info);

}
