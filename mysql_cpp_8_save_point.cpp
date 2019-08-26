#include <iostream>

//#include <mysql_connection.h> 

#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

// test
//#include <conio.h> // error there is no header file with this name

using namespace std;

int main(int argc, char* argv[]){

  if( argc < 3){
    cout << "# Error - it should be " << argv[0] << " " << argv[1] << " " << argv[2] << endl;
    return 0;
  }

  try{
    sql::Driver* driver;
    sql::Connection* conn; 
    sql::PreparedStatement* pstmt;
    sql::Savepoint* savept;

    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");

    conn->setSchema("test");

    pstmt = conn->prepareStatement("INSERT INTO test(id, label) VALUES( ?, ?)");

    conn->setAutoCommit(0);

    pstmt->setInt( 1, atoi(argv[1]));
    pstmt->setString( 2, argv[2]);
    pstmt->execute();

    /////////////// Use save point ///////////////////

    // create save point
    savept = conn->setSavepoint("sp1");

    pstmt->setInt( 1, 1000);
    pstmt->setString( 2, "test 1000");
    pstmt->execute();    

    // rollback on save point area
    conn->rollback(savept);

    // delete save point
    conn->releaseSavepoint(savept);

    // commit changes
    conn->commit();

    // restore auto commit
    conn->setAutoCommit(1); 

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
  cout << "finish end" << endl;

  return EXIT_SUCCESS;
}
