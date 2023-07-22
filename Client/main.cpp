// !!!!!!!!!!!!!!!!!!!!!!!!!!   Nain для клиенской части
#include <iostream>
#include <vector>

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
//----------------------------------------------------------------------
std::string tempOP;
char* op;//запись символа операции
//----------------------------------------------------------------------
	while (true) {
		std::cout << "Press key:'q'-quit, 'n'-create , 'd'-delete , 'e'-enter , 's'- show\n";
		//std::cout << "Выберите опцию:'в'-Выход, 'н'-Создать нового пользователя , 'л'-Войти под лог. и паролем\n";
		std::cout << ">> ";
		std::cin >> tempOP;
		if (tempOP.size() == 1) {
			std::vector<char>chars(tempOP.begin(), tempOP.end());//преобразователь string ->char
			chars.push_back('\0');
			op = &chars[0];

			if (*op == 'q') {
				exit(0);
			}
			switch (*op) {
			case'n':
				sizePassLog = lgPass->addLogPass();
				lgPass->printLogPass();
				break;
			case'e':
				if (lgPass->enterLogPass())
					lgPass->showMessages();
				break;
			defalt:
				std::cout << "Неправильно выбрали букву";
			}
		}
	}
//----------------------------------------------------------------------

	return 0;
}
