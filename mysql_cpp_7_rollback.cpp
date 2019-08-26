#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main(int argc, char* argv[]){

  if( argc < 3){
     cout << "Should be " << argv[0] << " " << argv[1] << " " << argv[2] << endl;
     return 0;
  }

  try{
    sql::Driver* driver;
    sql::Connection* conn;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;

    driver = get_driver_instance();//not thread safe
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");

    conn->setSchema("test");

    pstmt = conn->prepareStatement("INSERT INTO test( id, label) VALUES( ?, ?)");

    stmt = conn->createStatement();

    // Disable autocommit via SQL command
    stmt->execute("SET autocommit = 0");// we can use 0 or OFF
    stmt->execute("START TRANSACTION"); // we can also use BEGIN or BEGIN WORK

    pstmt->setInt( 1, 1000);
    pstmt->setString( 2, "test");
    pstmt->execute();

    stmt->execute("ROLLBACK");

    // Before coming to an end we need to restore previous value
    stmt->execute("SET autocommit = 1"); // we can use 1 or ON

    delete stmt;

    // Disable Auto Commit Mode via c++ command
    conn->setAutoCommit(0);

    pstmt->setInt( 1, atoi(argv[1]));
    pstmt->setString( 2, argv[2]);
    pstmt->execute();

    // Rollback
    conn->rollback();
    
    conn->close();

    delete pstmt;
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
  cout << "finish at the end" << endl;


  return EXIT_SUCCESS;
}

