#ifndef __WORD_REPOSITORY_H__
#define __WORD_REPOSITORY_H__

#include <string>
#include <vector>
#include <memory>

struct WordInfo {              // 대명사   // 전치사      // 형용사    //부사   // 접속사
    enum Type { kNoun, kVerb, kPronoun, kPreposition, kAdjective, kAdverb, kConjunction };

    Type type;
    std::string word;
    std::vector<std::string> ko_meanings;
    std::string sound_url;
    std::vector<std::string> synonyms;
    std::vector<std::string> examples;
};


class WordRepository {
public:
    WordRepository() = default;
    ~WordRepository() = default;

    WordRepository(const WordRepository& copy) = delete;
    WordRepository& operator=(const WordRepository& copy) = delete;

    static WordRepository& instance();

    std::vector<std::shared_ptr<WordInfo>>& word_infos();

    void LoadWordInfos();

    

private:
    std::vector<std::shared_ptr<WordInfo>> word_infos_;
};

#endif
