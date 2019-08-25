In order to access mysql database from c++, we have to install mysql connector.

Steps to install mysql/c++ connector (https://centos.org/forums/viewtopic.php?t=65560) :
1. wget https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-1.1.9-linux-el7-x86-64bit.rpm
2. rpm -Uvh mysql-connector-c++-1.1.9-linux-el7-x86-64bit.rpm


Source Code compilation :

 g++ [file_cpp_name].cpp -o [output] -l mysqlcppconn

 ex. : g++ mysql-cpp-example-1.cpp -o test -l mysqlcppconn
