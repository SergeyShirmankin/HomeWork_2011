// !!!!!!!!!!!!!!!!!!!!!!!!!!   Nain для  серверной части программы
#include <iostream>
#include <vector>
#include "server.h"

//#include <map>
//#include <Windows.h>
//#include "RunLogPass.h"
//#include "MapMess.h"
//#include "LogPass.h"
/*	int sizeMap;
	int sizePassLog = 0;
	countObject = 0; // количество созданых обьектов или количество элементов в массиве
	countMessage = 0;//порядковый номер сообщения
	char* op;//запись символа операции
	std::string tempOP;
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
	sizeMap=createNullMap();//создание пустых сообщений в Map
	Log_pass* lgPass = new Log_pass; // Создаем обьект логина и пароля*/

 int main() 
{
    std::cout << "SERVER IS LISTENING THROUGH THE PORT: " << PORT << " WITHIN A LOCAL SYSTEM" << std::endl;
    // Запускаем функцию обработки сообщений от клиентов и ответа на эти сообщения
    processRequest();
	return 0;
}
