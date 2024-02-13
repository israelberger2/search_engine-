#ifndef MYSQLWORD_HPP 
#define MYSQLWORD_HPP 


namespace db{
 
class MysqlWords 
{
public:
    MysqlWords();
    ~MysqlWords() = default;
    MysqlWords(const MysqlWords&) = delete;
    MysqlWords& operator= (const MysqlWords&) = delete;

    int insertAndGetID(const std::string& word)const;
    std::vector<int> getWordsID(const std::vector<std::string>& queries)const;
};
 
} //db
#endif
