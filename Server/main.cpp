#include <iostream>
#include <vector>
#include "server.h"
#include "RunLogPass.h" 
//#include "LogPass.h"
 int main() 
{
    
    int sizeMap;
  	sizeMap=createNullMap();//создание пустых сообщений в Maptouch
   	std::cout << "SERVER IS LISTENING THROUGH THE PORT: " << PORT << " WITHIN A LOCAL SYSTEM" << std::endl;
    // Запускаем функцию обработки сообщений от клиентов и ответа на эти сообщения
     processRequest();
	return 0;
}
