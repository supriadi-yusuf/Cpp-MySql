#include <iostream> 

#include <cppconn/driver.h> 
#include <cppconn/prepared_statement.h> 
//#include <cppconn/resultset.h> 

using namespace std;

int main(int argc, char* argv[]){

  try{
    sql::Driver * driver;
    sql::Connection* conn; 
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    conn->setSchema("test"); 

    pstmt = conn->prepareStatement("CALL get_data()"); 

    pstmt->execute();
    
    do{ 
      res = pstmt->getResultSet(); 

      while( res->next()){
        cout << "Name : " << res->getString("Name") << ", Population : " << res->getInt("Population") << endl;
      }

      delete res;

    }
    while(pstmt->getMoreResults()); 

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

  return EXIT_SUCCESS;
}
