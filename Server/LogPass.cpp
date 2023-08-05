#include <iostream>
#include "LogPass.h"
#include "server.h"
#define DEBUG1
Log_pass::Log_pass()//конструктор по умолчанию
{
	StateProgram=1;
  countObjectLogPass=0;
}

void Log_pass::set_StateProgram(int newStateProgram)
{
	StateProgram= newStateProgram;
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
   void Log_pass::set_NumMess(const std::string& newNumMess)
  {
        NumMess=newNumMess;
  }
  void Log_pass::set_NumCurrMess(const std::string& newNumCurrMess )
  {
        NumCurrMess=newNumCurrMess;
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
  int Log_pass::get_StateProgram()
  {
    return StateProgram;
  }
      std::string& Log_pass::get_NumMess()  //количество сообщени
    {
         return NumMess;
    }
    std::string& Log_pass::get_NumCurrMess() //номер сообщения 
    {
        return NumCurrMess;
    }

void Log_pass::parser(char arrChar[])
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
        //posBegin = 0;
        posEnd = line.find(markerEnd);
        if (posEnd!=std::string::npos||posBegin!=std::string::npos )
        {
             pos = line.find(delimiter,posBegin);
             set_PasswUser(line.substr(posBegin+1, pos-1));//Устанавливаем в приватном поле пароль
          
            #ifdef DEBUG 
             tempPassword=get_PasswordUser();
             std::cout<<"Password = "<< tempPassword<<std::endl;
            #endif
             
             oldPos=pos;
             
             pos = line.find(delimiter,oldPos+1);
             set_NameUserSend(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
            
            
             #ifdef DEBUG 
             tempLogin=get_NameUserSend();
             std::cout<<"NameUserSen = "<<tempLogin<<std::endl;
             #endif
             oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_NameUserRecive(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
             
             #ifdef DEBUG 
             tempLogin=get_NameUserRecive();
             std::cout<<"NameUserReciv = "<<tempLogin<<std::endl;
            #endif
             oldPos=pos;
            
             pos = line.find(delimiter,oldPos+1);
             set_Request(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
             
             #ifdef DEBUG 
             tempLogin=get_Request();
             std::cout<<"Request = "<<tempLogin<<std::endl;
             #endif

             oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_CurrentState(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
            
             #ifdef DEBUG 
             tempLogin=get_CurrentState();
             std::cout<<"CurrentState = "<<tempLogin<<std::endl;
             #endif
 //-------------------Вставка новых полей---------------------------------------------------
             oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_NumCurrMess(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
            
             #ifdef DEBUG 
             tempLogin=get_NumCurrMess();
             std::cout<<"NumCurrMess = "<<tempLogin<<std::endl;
             #endif

            oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_NumMess(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
            
             #ifdef DEBUG 
             tempLogin=get_NumMess();
             std::cout<<"NumMess = "<<tempLogin<<std::endl;
             #endif
//----------------------------------------------------------------------------------------

            oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_Messaqge(line.substr(oldPos+1, posEnd- oldPos-1));//Устанавливаем в приватном поле имя
            
             #ifdef DEBUG 
             tempLogin=get_Messaqge();
             std::cout<<tempLogin<<"Messaqge = "<<tempLogin<<std::endl;
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
//-----------------Обработка сообщения---------------------------------------
//------------------------------------------------------------------------------------------------------
void Log_pass::addLogPass()
{
	//Вводим новый логин	*/		

  if (!CurrentState.compare("1") && !Request.compare("2"))
  {
        login = NameUserSend; 
	      auto it = _log_pass.find(login);
  
	    if (it != _log_pass.end())
	    {
        //	Логин уже есть. Выберите другой" 
         StateProgram = 5;
         CurrentState="5";
	    }
	    else
	  {
		    // "Введите нового пароля: " 
		      password = PasswordUser;
		      _log_pass.emplace(login, password);//создание записи в памяти компьютера
          countObjectLogPass++;
          StateProgram = 3;
          CurrentState="3";
	  }
   }
   else
    {
          StateProgram = 4;//значения по умолчанию
          CurrentState="4";
    }
  }
//-------------------------------------------------------------------------------------------
//---------------------------Создание сообщения----------------------------------------------
//-------------------------------------------------------------------------------------------
std::string Log_pass::createMessLogToClient()
{
 std::string tempStr;
  //  *123123:Misha:--:2:1:1:1--&
   // tempStr = "*"+password+":"+login+":"+"--:"+Request+":"+CurrentState+":--&";
   tempStr = "*"+password+":"+login+":"+"--:"+Request+":"+CurrentState+":1:1:--&";
  return tempStr;
}
//-----------------------------------------------------------------------------------------------
// ----------------------------Функция авторизациии---------------------------------------------
//---------------------------------------------------------------------------------------------
std::string Log_pass::enterLogPass()
{
  std::string tempStr;
	std::string _password;	
  std::string _login;
  _password= PasswordUser;
  _login=NameUserSend;
  bool resultCompare = false;
	int i = -1;
	
	for (auto it = _log_pass.begin(); it != _log_pass.end(); ++it)
	{ 
	    i++;
		if (!(_login.compare(it->first))&& !(_password.compare(it->second)))
       	{
 		    	  curSession = i;
		    	  currUser = it->first;
      		  resultCompare = true;
            CurrentState = "7";
            //tempStr = "*"+password+":"+login+":"+"--:"+Request+":"+CurrentState+":1:1:--&";
            tempStr = "*"+it->second+":"+it->first+":"+"--:"+Request+":"+CurrentState+":1:1:--&";
            return tempStr;
      	}
	}
   CurrentState = "8";
   tempStr = "*:--:--:"+Request+":"+CurrentState+":1:1:--&";   
   return tempStr;
}
//--------------------------------------------------------------------------------------------------
//------------------------------------Запрос по пользователеи -------------------------------------
//--------------------------------------------------------------------------------------------------
std::vector<std::string> Log_pass:: countUser()
  {
        int countUsers = -1;
        std::vector<std::string> r;
        std::string str;
        std::string strCountUser;
         r.reserve(3);// принял ограничение по 3 useram

       //-----------------------------------------------------------------------------------
    for (auto it = _log_pass.begin(); it != _log_pass.end(); ++it)
			{
				countUsers++;
        strCountUser=std::to_string(countUsers);
          #ifdef DEBUG 
            std::cout << it->first << "[" << countUsers << "], ";
          #endif 
        
        str=it->first;
        str=str+" ["+ strCountUser + "], ";
        r.push_back(str);
			}
       return r;
  }
  //-----------------------------------------------------------------------------------------------
  //-----------------------------Запрос текущего пользователя--------------------------------------
  //-----------------------------------------------------------------------------------------------
  std::string&  Log_pass:: get_currUser ()
  {
     return currUser;
  }
  

