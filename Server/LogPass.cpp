#include <iostream>
#include "LogPass.h"
#include "server.h"
#define DEBUG
Log_pass::Log_pass()//конструктор по умолчанию
{
	int a = 1; // пустая операция, чтобы не было ошибок
}

void Log_pass::set_NameUserSend(const std::string& newNameUserSend)
{
	NameUserSend = newNameUserSend;
}
void Log_pass::set_PasswUser(const std::string& newPasswUser)
{
	PasswordUser= newPasswUser;
}
	void Log_pass::set_NameUserRecive(const std::string& newNameUserRecive)
  {
      NameUserRecive= newNameUserRecive;
  }
	void Log_pass::set_Request(const std::string& newRequest)
  {
        Request=newRequest;
  }
	void Log_pass::set_CurrentState(const std::string& newCurrentStat)
  {
        CurrentState=newCurrentStat;
  }
	void Log_pass::set_Messaqge(const std::string& newMessaqge)
  {
      Messaqge = newMessaqge;
  }


std::string& Log_pass::get_NameUserSend()
{
	return NameUserSend;
}
std::string& Log_pass::get_PasswordUser()
{
	return PasswordUser;
}
	std::string& Log_pass::get_NameUserRecive()
  {
    return NameUserRecive;
  }
	std::string& Log_pass::get_Request()
  {
      return Request;
  }
	std::string& Log_pass::get_CurrentState()
  {
     return CurrentState;
  }
	std::string& Log_pass::get_Messaqge()
  {
     return Messaqge;
  }

void Log_pass::readUser(char arrChar[])
{
        std::string delimiter=":";
        std::string line;
        std::string markerBegin="*";
        std::string markerEnd="&";     
        size_t posBegin;
        size_t posEnd;
        size_t pos;
        size_t oldPos;
        std::string tempPassword;
        std::string tempLogin;
        
        line=recivMess(arrChar);
		    posBegin = line.find(markerBegin);
        posEnd = line.find(markerEnd);
        if (posEnd!=std::string::npos||posBegin!=std::string::npos )
        {
             pos = line.find(delimiter,posBegin);
             set_PasswUser(line.substr(posBegin+1, pos-1));//Устанавливаем в приватном поле пароль
          
            #ifdef DEBUG 
             tempPassword=get_PasswordUser();
             std::cout<< tempPassword<<std::endl;
            #endif
             
             oldPos=pos;
             
             pos = line.find(delimiter,oldPos+1);
             set_NameUserSend(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
            
            
             #ifdef DEBUG 
             tempLogin=get_NameUserSend();
             std::cout<<tempLogin<<std::endl;
             #endif
             oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_NameUserRecive(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
             
             #ifdef DEBUG 
             tempLogin=get_NameUserRecive();
             std::cout<<tempLogin<<std::endl;
            #endif
             oldPos=pos;
            
             pos = line.find(delimiter,oldPos+1);
             set_Request(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
             
             #ifdef DEBUG 
             tempLogin=get_Request();
             std::cout<<tempLogin<<std::endl;
             #endif

             oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_CurrentState(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
            
             #ifdef DEBUG 
             tempLogin=get_CurrentState();
             std::cout<<tempLogin<<std::endl;
             #endif
            
            oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_Messaqge(line.substr(oldPos+1, posEnd- oldPos-1));//Устанавливаем в приватном поле имя
            
             #ifdef DEBUG 
             tempLogin=get_Messaqge();
             std::cout<<tempLogin<<std::endl;
             #endif
          
        }
}

//=======================================================================================================
int Log_pass::AddScore(int idNumber, Messages score)
{
	auto it = _messages.find(idNumber);
	if (it != _messages.end())
	{
		score = it->second;
	}
	else
		_messages.emplace(idNumber, score);
	return _messages.size();
}

//------------------------------------------------------------------------------------------------------
// Создание логина и паррля
int Log_pass::addLogPass()
{
	/*std::cout << " Введите логин нового пользователя: " << std::endl;
	std::cout << ">> ";
	std::cin >> login;//Вводим новый логин	*/			  
	//auto it = _log_pass.find(login);
     //auto it = _log_pass.find(user.get_PasswordUser()); 
	/*if (it != _log_pass.end())
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
	       	countObject++;*/
	return _log_pass.size();
}