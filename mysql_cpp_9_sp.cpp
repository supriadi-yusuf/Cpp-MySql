/****************************************************************************
this program demonstrate how to call Stored Procedure in mysql from c++.
we use statement for calling procedure.
the procedure takes inputs but it does not produce any output to the caller.
****************************************************************************/

#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/statement.h>

using namespace std;

int main(int argc, char* argv[]){

  try{

    sql::Driver* driver; 
    sql::Connection* conn; 
    sql::Statement* stmt;

    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    conn->setSchema("test");

    stmt = conn->createStatement();

    stmt->execute("CALL add_country('ATL', 'Atlantis', 'North America')");
    
    conn->close();

    delete stmt;
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


  cout << endl;
  cout << "finish end" << endl;

  return EXIT_SUCCESS;
} 
