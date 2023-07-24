#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Messages.h"
class Log_pass 
{
public:	
    //void set_PasswUser(const std::string& newName);
	void set_PasswUser(const std::string& );
	void set_NameUserSend(const std::string& );
	void set_NameUserRecive(const std::string& );
	void set_Request(const std::string& );
	void set_CurrentState(const std::string&) ;
	void set_Messaqge(const std::string& );
    void set_StateProgram(int );

	
	std::string& get_PasswordUser();
	std::string& get_NameUserSend();
	std::string& get_NameUserRecive();
	std::string& get_Request();
	std::string& get_CurrentState();
	std::string& get_Messaqge();
    int get_StateProgram();


	void readUser(char str[]);
	Log_pass();//Конструктор по умолчанию
    std::string addLogPass(std::string reqest);
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
	int StateProgram;
	
	Log_pass* ptrObject;// Указатель на обьект
    std::string login;//поле логина в обьекте
    std::string password;// поле пароля в обьектн

    std::string PasswordUser;//Пароль пользователя  отправителя сообщения
    std::string NameUserSend;// Имя пользователя  отправителя сообщения 
    std::string NameUserRecive;//  Имя пользователя принимающего сообщения 
    std::string Request;// Запрос на измененимя состояния (команда)
    std::string CurrentState;//Текущее состояние программы 
    std::string Messaqge;
	std::map<std::string,std::string> _log_pass;
	std::map<int, Messages> _messages;
	void writeUser();
};
