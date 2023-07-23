#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Messages.h"
class Log_pass {
public:
	Log_pass();//Конструктор по умолчанию
  // get и set  в блоке user
	int addLogPass();//добавить логин и пароль
	Log_pass* getPtrObject();
	bool enterLogPass();
	void showMessages();
	void printLogPass();
//----------------------------------------------------------------------
	int AddScore(int idNumber, Messages score);
	void findMess();
	int writeMess();
//-----------------------------------------------------------------------
private:
	Log_pass* ptrObject;// Указатель на обьект
   // поля логина и пароля забираем блока User 
	std::map<std::string,std::string> _log_pass;
	std::map<int, Messages> _messages;
};
