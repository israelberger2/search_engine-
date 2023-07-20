#ifndef CONNECTOR 
#define CONNECTOR 

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <memory>
   

namespace db{

class Connector
{
public:
    Connector();
    ~Connector() = default;
    Connector(const Connector&) = delete;
    Connector& operator= (const Connector&) = delete;

    std::unique_ptr<sql::Connection> get_conector()const;

private:
    sql::Driver* m_driver;
};

} //db
#endif

