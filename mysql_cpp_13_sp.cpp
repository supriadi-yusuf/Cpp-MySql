#include <iostream>
#include <string>
#include <vector>

#include <cppconn/driver.h>
//#include <cppconn/statement.h> 
#include <cppconn/prepared_statement.h> 
//#include <cppconn/resultset.h> 

using namespace std;

int main(int argc, char* argv[]){
  
  vector<string> vName, vContinent; 

  vName.push_back("Washington");  
  vName.push_back("Irak");  
  vName.push_back("Atlantis");  

  vContinent.push_back("Europe");  
  vContinent.push_back("North America");  
  vContinent.push_back("Oceania");  

  try{
    sql::Driver * driver;
    sql::Connection* conn;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    driver = get_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    conn->setSchema("test");

    stmt = conn->createStatement();

    pstmt = conn->prepareStatement("CALL get_pop(?,@pop)"); 

    for(int i=0; i < vName.size(); i++){
      pstmt->setString( 1, vName[i]); 
      pstmt->execute();       

      res = stmt->executeQuery("SELECT @pop as population"); 
      while( res->next()){
        cout << "Population of " << vName[i] << " : " << res->getInt("population") << endl;
      }

      delete res;
    }


    delete pstmt;

    pstmt = conn->prepareStatement("CALL get_pop_continent(?,@pop)"); 

    for(int i=0; i < vContinent.size(); i++){
      pstmt->setString( 1, vContinent[i]); 
      pstmt->execute();       

      res = stmt->executeQuery("SELECT @pop as population"); 
      while( res->next()){
        cout << "Population of " << vContinent[i] << " : " << res->getInt("population") << endl;
      }

      delete res;
    }

    conn->close();

    delete pstmt;
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

  return EXIT_SUCCESS;
}
