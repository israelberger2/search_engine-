#ifndef CONNECTOR 
#define CONNECTOR 

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>

#include <memory>
#include <string>


namespace db{

class Connector
{
public:
    Connector();
    ~Connector() = default;
    Connector(const Connector&) = delete;
    Connector& operator= (const Connector&) = delete;

    std::unique_ptr<sql::Connection> get_conector()const;
    std::unique_ptr<sql::PreparedStatement> get_conector(const std::string& query)const;

private:
    sql::Driver* m_driver;
};

class Connector1
{
public:
    Connector1();
    ~Connector1() = default;
    Connector1(const Connector1&) = delete;
    Connector1& operator= (const Connector1&) = delete;

    std::unique_ptr<sql::Connection> get_conector()const;
    std::unique_ptr<sql::PreparedStatement> get_conector(const std::string& query)const;

private:
    sql::Driver* m_driver;
    std::unique_ptr<sql::Connection> m_con;
};

} //db
#endif

