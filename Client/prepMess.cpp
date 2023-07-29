#include <iostream>
#include "prepMess.h"
#include <vector>
#include "client.h"


PrevMess::PrevMess()//конструктор по умолчанию
{
	 managerInterLogPass=true;	
}

/*
std::string Log_pass::getLog()
{
	return login;
}

std::string Log_pass::getPass()
{
	return password;
}
*/

std::string PrevMess::addLogPass()
{
	std::cout << " Введите логин нового пользователя: " << std::endl;
	std::cout << ">> ";
	std::cin >> login;//Вводим новый логин				  	
	std::cout << "Введите нового пароля: " << std::endl;
	std::cout << ">> ";
	std::cin >> password;
    std::string resultStr=password+":"+login ;
	return resultStr;
}

std::string PrevMess::InterfaceLogPass(bool StartFunction)//Создаесм стартовое окно для создания логина и пароля или авторизация на сервере
{
    std::string tempStr;
	std::string tempOP;
    char* op;//запись символа операции
//----------------------------------------------------------------------
	if( StartFunction)
	{
		std::cout << "Press key:''n'-create ";
		std::cout << ">> ";
		std::cin >> tempOP;
		if (tempOP.size() == 1)
		 {
			std::vector<char>chars(tempOP.begin(), tempOP.end());//преобразователь string ->char
			chars.push_back('\0');
			op = &chars[0];
			switch (*op) 
			{
			case'n':
				 tempStr=addLogPass();
				 tempStr="*"+tempStr+":--:2:1:--&";
				 return tempStr;
			defalt:
				std::cout << "Неправильно выбрали букву";
			}
		}
	}	
//----------------------------------------------------------------------

}