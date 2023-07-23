#include <iostream>
#include "LogPass.h"
Log_pass::Log_pass()//конструктор по умолчанию
{
	int a = 1; // пустая операция, чтобы не было ошибок
}
// Создание логина и паррля
int Log_pass::addLogPass()
{
	/*std::cout << " Введите логин нового пользователя: " << std::endl;
	std::cout << ">> ";
	std::cin >> login;//Вводим новый логин				  
	auto it = _log_pass.find(login);
	if (it != _log_pass.end())
	{
		std::cout << std::endl;
		std::cout << ">> Логин уже есть. Выберите другой" << std::endl;
	}
	else
	{
		std::cout << "Введите нового пароля: " << std::endl;
		std::cout << ">> ";
		std::cin >> password;
		_log_pass.emplace(login, password);
	}
	       	countObject++;
	return _log_pass.size();*/
}