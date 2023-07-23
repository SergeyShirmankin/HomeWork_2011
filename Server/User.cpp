#include "User.h"
#include "server.h"
User::User()
{
	int a=1; //пустая операциЯ 
}
User::~User()
{
  int a=2;
}
void User::set_newLogin(const std::string& newLogin)
{
	NameUserSend = newLogin;
}
void User::set_newPassword(const std::string& newPassword)
{
	PasswordUser= newPassword;
}
std::string& User::getName()
{
	return NameUserSend;
}
std::string& User::getPass()
{
	return PasswordUser;
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
             User::set_newPassword(line.substr(posBegin+1, pos-1));//Устанавливаем в приватном поле пароль
             tempPassword=User::getPass();
             std::cout<< tempPassword<<std::endl;
             oldPos=pos;
             pos = line.find(delimiter,oldPos+1);
             User::set_newLogin(line.substr(oldPos+1, pos- oldPos-1));//Устанавливаем в приватном поле имя
             tempLogin=User::getName();
             std::cout<<tempLogin<<std::endl;
        }

}