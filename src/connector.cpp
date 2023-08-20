#include "connector.hpp"
#include "configuration.hpp"


db::Connector::Connector()
: m_driver(sql::mysql::get_mysql_driver_instance())
, m_con(m_driver->connect(se::Config::getSqlConnectionString(), se::Config::getSqlUsername(), se::Config::getSqlPassword()))
{
    m_con->setSchema(se::Config::getSqlSchema());
}

std::unique_ptr<sql::PreparedStatement> db::Connector::get_conector(const std::string& query) const
{
    return std::unique_ptr<sql::PreparedStatement>(m_con->prepareStatement(query));
}