#ifndef ABSTRUCT_TEXT_DATA_HPP
#define ABSTRUCT_TEXT_DATA_HPP

#include <vector>
#include <string>
#include <unordered_map>


namespace se{

using TextMap = std::unordered_map<std::string, size_t>;

class IndexerInsertion
{
public:
    virtual ~IndexerInsertion() = default;
    virtual void insert(const TextMap& textMap, const std::string& url) = 0;
};

} // namespace se
#endif
