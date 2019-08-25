#include <iostream>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

using namespace std;

int main(int argc, char* argv[]){

  // declare variables
  sql::Driver* driver;
  sql::Connection* conn;
  sql::Statement* stmt;
  sql::PreparedStatement* pstmt;
  sql::ResultSet* res;

  try{

    // create connection
    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");

    // set database
    conn->setSchema("test");

    // create statement
    stmt = conn->createStatement();

    // execute statement 
    stmt->execute("DROP TABLE IF EXISTS test");
    stmt->execute("CREATE TABLE test(id INT)");

    delete stmt;

    // create prepared statement
    pstmt = conn->prepareStatement("INSERT INTO test(id) VALUES(?)");
    for(int i=1; i<=10; i++){
      pstmt->setInt( 1, i);
      pstmt->executeUpdate();
    }

    delete pstmt;

    // select in ascending order
    pstmt = conn->prepareStatement("SELECT id FROM test ORDER BY id ASC");
    res = pstmt->executeQuery();

    // fetch in descending order
    res->afterLast(); // go to last record
    while( res->previous()){
      cout << "\t... MySQL counts: " << res->getInt("id") << endl;
    }

    delete res;
    delete pstmt;
    delete conn;

  }catch(sql::SQLException& e){
    cout << "# ERR: SQL exception in " << __FILE__;
    cout << " (" << __FUNCTION__ << ") online ";
    cout << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQL state: " << e.getSQLState();
    cout << ")" << endl;
  }
  
  cout << endl;

  return EXIT_SUCCESS;
}
