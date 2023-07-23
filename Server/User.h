#pragma once
#include <string>
class User
{
public:
	User();
	~User();

	//void set_PasswUser(const std::string& newName);
	void set_PasswUser(const std::string& );
	void set_NameUserSend(const std::string& );
	void set_NameUserRecive(const std::string& );
	void set_Request(const std::string& );
	void set_CurrentState(const std::string&) ;
	void set_Messaqge(const std::string& );

	std::string& get_PasswordUser();
	std::string& get_NameUserSend();
	std::string& get_NameUserRecive();
	std::string& get_Request();
	std::string& get_CurrentState();
	std::string& get_Messaqge();

	void readUser(char str[]);

private:
 std::string PasswordUser;//Пароль пользователя  отправителя сообщения
 std::string NameUserSend;// Имя пользователя  отправителя сообщения 
 std::string NameUserRecive;//  Имя пользователя принимающего сообщения 
 std::string Request;// Запрос на измененимя состояния (команда)
 std::string CurrentState;//Текущее состояние программы 
 std::string Messaqge;
void writeUser();
};
