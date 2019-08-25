#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main(int argc, char* argv[]){

  try{
    sql::Driver* driver;
    sql::Connection* conn;
    sql::PreparedStatement* pstmt;

    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    conn->setSchema("test");

    pstmt = conn->prepareStatement("INSERT INTO test(id,label) VALUES( ?, ?)");

    pstmt->setInt(1, 1);
    pstmt->setString(2, "a");
    pstmt->execute();

    pstmt->setInt(1, 2);
    pstmt->setString(2, "b");
    pstmt->execute();

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

  return EXIT_SUCCESS;
}
