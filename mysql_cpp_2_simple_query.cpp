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
    stmt = conn->createStatement();

    stmt->execute("USE test");
    stmt->execute("DROP TABLE IF EXISTS test");
    stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");
    stmt->execute("INSERT INTO test( id, label) VALUES( 1, 'a')");

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

  return EXIT_SUCCESS;
}
