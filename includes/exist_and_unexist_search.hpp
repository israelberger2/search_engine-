#ifndef EXIST_AND_UNEXIST_HPP
#define EXIST_AND_UNEXIST_HPP

#include <vector>
#include <string>
#include <utility>

#include "database.hpp"
#include "searcher.hpp"


namespace se {

using StringsVector = std::vector<std::string>;
using pairVector = std::vector<std::pair<std::string, size_t>>;

class ExistAndUnexistSearch : public Searcher
{
public:
    explicit ExistAndUnexistSearch(const Database& database); 
    ~ExistAndUnexistSearch() = default;
    ExistAndUnexistSearch(const ExistAndUnexistSearch&) = default;
    ExistAndUnexistSearch& operator=  (const ExistAndUnexistSearch&) = default;

    pairVector get_links(const StringsVector& query)const override;

private:
    std::pair<StringsVector ,StringsVector> query_for_searchers(const StringsVector& query)const;
    pairVector links_list(const pairVector& exist_answer , const pairVector& unexist_answer)const;

private:
    const Database& m_database;
};

}
#endif
