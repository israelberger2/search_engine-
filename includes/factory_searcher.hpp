#ifndef FACTORY_SEARCHER_HPP
#define FACTORY_SEARCHER_HPP

#include <string>
#include <memory>
#include <vector>

#include "searcher.hpp"
#include "database.hpp"


namespace se{

class FactorySearcher
{
public:
    FactorySearcher() = default;
    ~FactorySearcher() = default;
    FactorySearcher(const FactorySearcher&) = default;
    FactorySearcher& operator= (const FactorySearcher&) = default;

    static std::unique_ptr<Searcher> creator(const std::vector<std::string>& input,const Database& database);

private:
    static bool exist_words(const std::vector<std::string>& input);
};

}
#endif
 