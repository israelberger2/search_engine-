#include "connector.hpp"


db::Connector::Connector()
: m_driver(sql::mysql::get_mysql_driver_instance())
{}

std::unique_ptr<sql::Connection> db::Connector::get_conector()const
{
    return std::unique_ptr<sql::Connection>(m_driver->connect("tcp://127.0.0.1:3306", "sammy", "#Bb12345678"));
}

std::unique_ptr<sql::PreparedStatement> db::Connector::get_conector(const std::string& query) const
{
    auto con = std::shared_ptr<sql::Connection>(m_driver->connect("tcp://127.0.0.1:3306", "sammy", "#Bb12345678"));
    con->setSchema("DBsearchEngine");
 
    auto stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(query));
    return stmt;
}


db::Connector1::Connector1()
: m_driver(sql::mysql::get_mysql_driver_instance())
, m_con(m_driver->connect("tcp://127.0.0.1:3306", "sammy", "#Bb12345678"))
{
    m_con->setSchema("DBsearchEngine");
}

std::unique_ptr<sql::PreparedStatement> db::Connector1::get_conector(const std::string& query) const
{
    return std::unique_ptr<sql::PreparedStatement>(m_con->prepareStatement(query));
}