#include <iostream>
#include "prepMess.h"
#include <vector>
#include "client.h"


Log_pass::Log_pass()//конструктор по умолчанию
{
	int a = 1; // пустая операция, чтобы не было ошибок
}
std::string Log_pass::getLog()
{
	return login;
}

std::string Log_pass::getPass()
{
	return password;
}
std::string Log_pass::addLogPass()
{
	std::cout << " Введите логин нового пользователя: " << std::endl;
	std::cout << ">> ";
	std::cin >> login;//Вводим новый логин				  	
	std::cout << "Введите нового пароля: " << std::endl;
	std::cout << ">> ";
	std::cin >> password;
    std::string resultStr=getLog()+":"+getPass();
	return resultStr;
}

void StartMessage()//Создаесм стартовое окно ссобщениями
{
    std::string tempOP;
    char* op;//запись символа операции
    Log_pass* lgPass = new Log_pass; // Создаем обьект логина и пароля*
    std::string messServer;
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
			    sendMess(lgPass->addLogPass());
				 return;
			case'e':
				//if (lgPass->enterLogPass())
				//	lgPass->showMessages();
				return;
			defalt:
				std::cout << "Неправильно выбрали букву";
			}
		}
	}
//----------------------------------------------------------------------

}