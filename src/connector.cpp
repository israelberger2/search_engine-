#include "connector.hpp"


db::Connector::Connector()
: m_driver(sql::mysql::get_mysql_driver_instance())
{}

std::unique_ptr<sql::Connection> db::Connector::get_conector()const
{
    return std::unique_ptr<sql::Connection>(m_driver->connect("tcp://127.0.0.1:3306", "sammy", "#Bb12345678"));
}
