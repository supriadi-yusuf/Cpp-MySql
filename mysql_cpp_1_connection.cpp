#include <iostream>
//#include <cstdlib>
//#include <mysql_connection.h>
#include <cppconn/driver.h>

using namespace std;


int main(int argc, char* argv[]){

  try{
    sql::Driver *driver;
    sql::Connection* conn;

    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root1");

    if( !conn->isValid() )
       conn->reconnect();

    conn->close();

    delete conn;

  }catch(sql::SQLException& e){
    cout << "# ERR: SQLException in " << __FILE__;
    cout << " ( " << __FUNCTION__ << " ) ";
    cout << "on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " ( MySQL error code: " << e.getErrorCode();
    cout << ", SQL state: " << e.getSQLState() << " )" << endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
