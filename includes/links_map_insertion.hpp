#ifndef ABSTRUCT_LINKS_DATA_HPP
#define ABSTRUCT_LINKS_DATA_HPP

#include <unordered_map>
#include <vector>
#include <string>

namespace se{

class LinksMamInsertion
{
public:
    virtual ~LinksMamInsertion() = default;

    virtual void insert(const std::vector<std::string>& related_links,const std::string& link) = 0;
    virtual size_t size()const = 0;
};

} // namespace se
#endif
