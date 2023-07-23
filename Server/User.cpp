#include "User.h"
#include "server.h"
#define DEBUG
User::User()
{
	int a=1; //пустая операциЯ 
}
User::~User()
{
  int a=2;
}


void User::set_NameUserSend(const std::string& newNameUserSend)
{
	NameUserSend = newNameUserSend;
}
void User::set_PasswUser(const std::string& newPasswUser)
{
	PasswordUser= newPasswUser;
}
	void User::set_NameUserRecive(const std::string& newNameUserRecive)
  {
      NameUserRecive= newNameUserRecive;
  }
	void User::set_Request(const std::string& newRequest)
  {
        Request=newRequest;
  }
	void User::set_CurrentState(const std::string& newCurrentStat)
  {
        CurrentState=newCurrentStat;
  }
	void User::set_Messaqge(const std::string& newMessaqge)
  {
      Messaqge = newMessaqge;
  }


std::string& User::get_NameUserSend()
{
	return NameUserSend;
}
std::string& User::get_PasswordUser()
{
	return PasswordUser;
}


	std::string& User::get_NameUserRecive()
  {
    return NameUserRecive;
  }
	std::string& User::get_Request()
  {
      return Request;
  }
	std::string& User::get_CurrentState()
  {
     return CurrentState;
  }
	std::string& User::get_Messaqge()
  {
     return Messaqge;
  }





void User::readUser(char arrChar[])
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
             tempLogin=User::get_NameUserSend();
             std::cout<<tempLogin<<std::endl;
             #endif
             oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_NameUserRecive(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
             
             #ifdef DEBUG 
             tempLogin=User::get_NameUserRecive();
             std::cout<<tempLogin<<std::endl;
            #endif
             oldPos=pos;
            
             pos = line.find(delimiter,oldPos+1);
             set_Request(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
             
             #ifdef DEBUG 
             tempLogin=User::get_Request();
             std::cout<<tempLogin<<std::endl;
             #endif

             oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_CurrentState(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
            
             #ifdef DEBUG 
             tempLogin=User::get_CurrentState();
             std::cout<<tempLogin<<std::endl;
             #endif
            
            oldPos=pos;

             pos = line.find(delimiter,oldPos+1);
             set_Messaqge(line.substr(oldPos+1, posEnd- oldPos-1));//Устанавливаем в приватном поле имя
            
             #ifdef DEBUG 
             tempLogin=User::get_Messaqge();
             std::cout<<tempLogin<<std::endl;
             #endif
          
        }

}