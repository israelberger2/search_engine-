#ifndef MYSQLWORD_HPP 
#define MYSQLWORD_HPP 

#include "word_data.hpp"
#include "connector.hpp"


namespace db{
 
class MysqlWordData : public WordData
{
public:
    MysqlWordData();
    ~MysqlWordData() = default;
    MysqlWordData(const MysqlWordData&) = delete;
    MysqlWordData& operator= (const MysqlWordData&) = delete;

    int insertAndGetID(const std::string& word)override;
    std::vector<int> getWordsID(const std::vector<std::string>& queries)const override;
};
 
} //db
#endif
