#include <iostream>
#include <string>
#include <vector>

#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h> 

using namespace std;


int main(int argc, char* argv[]){
  
  vector<string> vCode, vName, vContinent;

  vCode.push_back("SLD");
  vCode.push_back("DSN");
  vCode.push_back("ATL");

  vName.push_back("Sealand");  
  vName.push_back("Disneyland");  
  vName.push_back("Atlantis");  

  vContinent.push_back("Europe");  
  vContinent.push_back("North America");  
  vContinent.push_back("Oceania");  

  try{
    sql::Driver * driver;
    sql::Connection* conn;
    sql::PreparedStatement* pstmt; 

    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    conn->setSchema("test");

    pstmt = conn->prepareStatement("CALL add_country(?,?,?)");
    for( int i=0; i < vCode.size() ; i++){
       pstmt->setString( 1, vCode[i]);
       pstmt->setString( 2, vName[i]);
       pstmt->setString( 3, vContinent[i]);

       pstmt->execute();
    }

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
