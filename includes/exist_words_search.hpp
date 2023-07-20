#ifndef EXISTING_WORDS_SEARCHER_HPP
#define EXISTING_WORDS_SEARCHER_HPP

#include <vector>
#include <string>
#include  <utility>

#include "database.hpp"
#include "searcher.hpp"


namespace se{

using pairVector = std::vector<std::pair<std::string, size_t>>;
using StringsVector = std::vector<std::string>;

class ExistWordsSearch : public Searcher
{
public:
    explicit ExistWordsSearch(const Database& database);
    ~ExistWordsSearch() = default;
    ExistWordsSearch(const ExistWordsSearch&) = default;
    ExistWordsSearch& operator=  (const ExistWordsSearch&) = default;

    pairVector get_links(const StringsVector& query)const override;

private:
    void update_list(pairVector& related_links,const std::string& word)const;
    bool noFind(const pairVector& updated_links,pairVector& current_links)const;
    
private:
   const Database& m_database;
};

} // namespace se
#endif
