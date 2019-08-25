/*****************************************************************************
In order to access mysql database from c++, we have to install mysql connector.

Install mysql/c++ connector (https://centos.org/forums/viewtopic.php?t=65560) :
1. wget https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-1.1.9-linux-el7-x86-64bit.rpm
2. rpm -Uvh mysql-connector-c++-1.1.9-linux-el7-x86-64bit.rpm

For compiling source code :
g++ [file_cpp_name].cpp -o [output] -l mysqlcppconn
ex. : g++ mysql-cpp-example-1.cpp -o test -l mysqlcppconn
*****************************************************************************/

#include <iostream> 

#include <mysql_connection.h> 

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(int argc, char* argv[]){

  cout << endl;
  cout << "Running SELECT 'Hello World' AS _message' ..." << endl;

  try{
   // define variable
   sql::Driver* driver;
   sql::Connection* conn;
   sql::Statement* stmt; 
   sql::ResultSet* res;

   // create connection
   driver = get_driver_instance();
   conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");

   // connect to mysql test database
   conn->setSchema("test");

   // create statement
   stmt = conn->createStatement();

   // execute statement
   res = stmt->executeQuery("SELECT 'Hello World' AS _message");

   // fetch result
   while(res->next()){
      cout << "\t... MySQL replies: ";

      // access column data by alias or column name
      cout << res->getString("_message") << endl;

      cout << "\t... MySQL says it again: ";
      // access column data by numeric offset, 1 is the first column
      cout << res->getString(1) << endl;

   }

   delete res;
   delete stmt;
   delete conn;    

  }catch(sql::SQLException &e){
    cout << "# ERR: SQLException in " << __FILE__;
    cout << " ( " << __FUNCTION__ << " ) ";
    cout << "on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " ( MySQL error code: " << e.getErrorCode();
    cout << ", SQL state: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;
  cout << "finish at the end" << endl;

  return EXIT_SUCCESS;
} 
