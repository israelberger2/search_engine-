#ifndef INDEXER_GET_HPP
#define INDEXER_GET_HPP

#include <vector>
#include <string>


namespace se{

class IndexerGet
{
public:
    virtual ~IndexerGet() = default;

    virtual std::vector<std::pair<std::string, size_t>> get_links(const std::string& key)const = 0;
    virtual bool is_here(const std::string& data)const = 0;
    virtual size_t size()const = 0;
};

} // namespace se
#endif
