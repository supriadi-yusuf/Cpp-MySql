/***********************************************************************************
calling stored procedure in mysql from c++.
These procedures take input and return output.
in mysql :
CALL get_pop('Uganda', @population);
SELECT @population AS total_population;
************************************************************************************/
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>


using namespace std;

int main(int argc, char* argv[]){

  try{

    sql::Driver* driver;
    sql::Connection* conn;
    sql::Statement* stmt;
    sql::ResultSet* res;

    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");

    conn->setSchema("test");
    
    stmt = conn->createStatement();

    stmt->execute("CALL get_pop('Uganda', @pop)");
    res = stmt->executeQuery("SELECT @pop AS _reply");
    while( res->next())
      cout << "Population of Uganda : " << res->getInt("_reply") << endl;

    delete res;
    
    stmt->execute("CALL get_pop_continent('Asia', @pop)");
    res = stmt->executeQuery("SELECT @pop AS _reply");
    while( res->next())
      cout << "Population of Asia : " << res->getInt("_reply") << endl;    

    delete res;

    stmt->execute("CALL get_pop_world(@pop)");
    res = stmt->executeQuery("SELECT @pop AS _reply");
    while( res->next())
      cout << "Population of World : " << res->getInt("_reply") << endl;

    conn->close();

    delete res;
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
