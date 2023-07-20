#ifndef unexist_words_search_hpp
#define unexist_words_search_hpp

#include <vector>
#include <string>
#include  <utility>

#include "database.hpp"
#include "searcher.hpp"


namespace se{

using StringsVector = std::vector<std::string>;
using pairVector = std::vector<std::pair<std::string, size_t>>;

class UnexistWordsSearch : public Searcher
{
public:
    explicit UnexistWordsSearch(const Database& database);
    ~UnexistWordsSearch() = default;
    UnexistWordsSearch(const UnexistWordsSearch&) = default;
    UnexistWordsSearch& operator= (const UnexistWordsSearch&) = default;

    pairVector get_links(const StringsVector& query)const override;

private:
    std::string clear_word(const std::string& query)const;
    void update_list(pairVector& current_links,const std::string& word)const;
 
private:
    const Database& m_database;
};

} // namespace se
#endif