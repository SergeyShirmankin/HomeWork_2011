#pragma once
#include <iostream>
#include <string>
class Log_pass {
public:
	Log_pass();//Конструктор по умолчанию
	std::string getLog();//геттеры
	std::string getPass();
	std::string addLogPass();//добавить логин и пароль
	//Log_pass* getPtrObject();
	//std::string enterLogPass();
	//void showMessages();
	//void printLogPass();
//----------------------------------------------------------------------
	int writeMess();
//-----------------------------------------------------------------------
private:
	Log_pass* ptrObject;// Указатель на обьект
	std::string login;//поле логина
	std::string password;// поле пароля
};
void StartMessage();//Создаесм стартовое окно ссобщениями