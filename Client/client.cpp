#include "LogPass.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h> // Библиотека для работы с сокетами
#include <arpa/inet.h>
#include "client.h"
#include "prepMess.h"
#include "logic.h"
//#include "User.h" 
#define ESC "\033"

/* У клиента с сервером есть поля сообения и они будут кодироваться так:
  -- программа имеет немколько состояний:
     1. состояние: программа не активна т.е нет подключения нет сообщений 
     2. Создание нового лога и пароля 
     3. Успешное создание лога и павроля 
     4. Не удалось создать лог и пароль.
     5. Такой лог или пароль уже есть
     6. Авторизация  на лог и пароль 
     7. Успешная авторизация  лог и пароль  при авторизации
     8. Не успешный лог или пароль при авторизации
     9. Сколько текущих пользователе в online
     10. Ответ о количестве пользователей
     11 Получить сообщения от пользователей
     12 Ответ о получения сообщения 

  ---Структура сообщения
     -- Пароль пользователя  отправителя сообщения >> PasswordUser:value
     -- Имя пользователя  отправителя сообщения   >> NameUserSend:value
     -- Имя пользователя принимающего сообщения   >> NameUserRecive:value 
     -- Запрос на измененимя состояния (команда) >>  Request:value; 
     -- Текущее состояние программы  >> CarrentState:value;
     -- Сообщение пользователей >> Messaqge:value;
     -- Начало сообщение маркируется знаком *
     -- Конец сообщения маркируется  знаком &
     -- Поле сообщения отделяется друг от друга :
     -- Пробелы не допускаются    
     Нгапример:
     ---Запрос на создания лога и пароля выглядеть будет так:
         -- PasswordUser:123123
         -- NameUserSend:Misha
         --  NameUserRecive:-- (нет получателя ) для сообщения
         --  Request:2; 
         --  CarrentState:1
         --  NumCurrMess:1 //номер сообщения 
         --  NumMess:1  //количество сообщение
         --  Messaqge:--(нет сообщения)
    

            *123123:Misha:--:2:1:1:1--&
 //----------------------------------------------------------------------                  
*/

char buffer[MESSAGE_BUFFER] ="Нет ответа от сервера !!!!";
char message[MESSAGE_BUFFER]="not message";
int socket_descriptor;
struct sockaddr_in serveraddress;
std::string tempCin; 
std::string tempMessage;
//User user;
Log_pass  objLogPass;
std::string tempStateProgram;

//---------------------------------------------------------------------
void treeger(Logic& inLogogic)
{
	if (inLogogic.temp1 && inLogogic.signal1)
	{
		inLogogic.temp1 = false;
		inLogogic.temp2 = true;
		std::cout << "State1" << std::endl;
	}
	else if (inLogogic.temp2 && inLogogic.signal2)
	{
		inLogogic.temp1 = true;
		inLogogic.temp2 = false;
		std::cout << "State2" << std::endl;
	}
}
//----------------------------------------------------------------------
void sendMess(std::string clientMessage) // формирование строки для  отправки сообщения серверу
{
     char tempChar='t';//инициализация пустой ячейки  значением "temp"
     // отправляем сообщение серверу 
     strcpy(message ,clientMessage.c_str());
}
//-----------------------------------------------------------------------
std::string  recivMess(char arryChar[]) //формирование сообщения для полученная с сервера  
{
     char tempChar='t';//инициализация пустой ячейки  значением "temp"
     int i=0;
     std::string tempStr="";
     while(tempChar!='\0')
     {
        tempChar=arryChar[i];
        tempStr = tempStr + tempChar;
        i++;
     }
     return  tempStr;
}
 //---------------------------------------------------------------------------
void sendRequest(){
   bool autorization =false;//переменная для авторизацииж 
    // Укажем адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта для соединения с сервером
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Создадим сокет 
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    // Установим соединение с сервером
    PrevMess objPrevMess;
    bool breakCicle=false;
    Logic shema1;

    if(connect(socket_descriptor, (struct sockaddr*) &serveraddress, sizeof(serveraddress)) < 0) 
    {
        std::cout << std::endl << " Something went wrong Connection Failed" <<std:: endl;
        exit(1);
    }
    
    while(1)
    {
      if (autorization==false)
      {
            std::cout<<"Для завершения работы наберите  --end--   или  --log--  для создание логина и пароля  --enter-- авторизации на сервере "<<std::endl;
            std::cout<< ">>"<< std::endl;
            std::getline(std::cin >> tempCin, tempMessage);//забираем всю строку
	        tempMessage = tempCin + " " + tempMessage;
            strcpy(message ,tempMessage.c_str());//преооразуем строку в массив char
            if (tempMessage.compare("end ")==0) 
                { //Закрываем соединение при отпрвке сообщения "end"
                   sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
                   std::cout << "Клиент работу  сделал.!" << std::endl;
                   close(socket_descriptor);
                   exit(0);
                }   
            else if (tempMessage.compare("log ")==0)
            {  
               tempMessage=objPrevMess.InterfaceLogPass( objPrevMess.managerInterLogPass);//Создаесм стартовое окно для создания логина и пароля или авторизация на сервере
               strcpy(message ,tempMessage.c_str());//преооразуем строку в массив char
            }
            else if (tempMessage.compare("enter ")==0)
             {
                 tempMessage=objPrevMess.enterLogPass(objLogPass.get_StateProgram());//Авторизация под логинои и паролем
                 strcpy(message ,tempMessage.c_str());
             }
      }
      else
 //-------------------------------------------------------------------------------------------------------------------------
 //-----------------------------Программа работы ссобщениямми---------------------------------------------------------------
 //-------------------------------------------------------------------------------------------------------------------------
            {
                 char key;
	              int countUsers = -1;
	              while (shema1.temp1 == true)
	               {
		              // breakCicle=false;
                       std::cout << "\nДля выхода нажмите клавишу '1' для продолжения нажмите любую кл и ent";
		               std::cout << "\n>> ";
		               std::getline(std::cin >> tempCin, tempMessage);//забираем всю строку
	                   tempMessage = tempCin + " " + tempMessage;
                       if (tempMessage.compare("1 ")==0) 
                       {
                        	shema1.signal1 = true;
                            treeger(shema1);
                            shema1.signal1 = false;
                       }
                       	   if (shema1.temp1 == false)
		                    	break;
                       else 
                     {
                        shema1.signal2 = true;
			            treeger(shema1);
			            shema1.signal2 = false;
                       
                        if (shema1.temp1 == false)
		                    break;

			            std::string	resultStr =  "*--:--:--:9:--:1:1:--&" ;
                        strcpy(message ,resultStr .c_str());//преооразуем строку в массив char
                        sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));//отправка сообщения серверу
                       // std::cout << "Сообщение успешно было отправленно на сервер:  " <<  message << std::endl;
                        std::cout << "Сообщение успешно было отправленно на сервер:  "<< std::endl;
                        std::cout << "Дождитесь ответа от сервера ..." << std::endl;
                        recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr); //получение сообщения от сервера
                        objLogPass.parserMessage(buffer);                                 
                        tempStateProgram=objLogPass.get_CurrentState();
                         int res =std::stoi(objLogPass.get_NumMess());
                     if(tempStateProgram.compare("10")==0)// успешное создание лога и пароля 
                         {
                            for (int localTemp=0;localTemp< res;localTemp++)
                                {
                                 std::cout << "\n>> Сообщение полученно от сервера\n " ;
                                 std::cout <<">> Online users "<<objLogPass.get_Messaqge() <<std::endl;
                                 std::string	resultStr =  "*--:--:--:--:--:--:--:--&" ;
                                 strcpy(message ,resultStr .c_str());//преооразуем строку в массив char
                                 sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
                                 recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr);  //синхрогизация сообщений
                                 objLogPass.parserMessage(buffer);//парсинг сообщения
                                }
                        std::cout << "\nStart Session[" << objLogPass.get_NameUserSend() << "]:\n";
			            std::cout << "Hello " << objLogPass.get_NameUserSend() << "\n";
                         }
                     } 
                  }  

            }    
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
 

      sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));//отправка сообщения серверу
      std::cout << "Сообщение успешно было отправленно на сервер:  " <<  message << std::endl;
      std::cout << "Дождитесь ответа от сервера ..." << std::endl;
        
             //std::cout << "Сообщение полученно от сервера " << std::endl;
       recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr); //получение сообщения от сервера
       objLogPass.parserMessage(buffer);
             //std::cout << "Сообщение полученно от сервера " << std::endl; 
            
       tempStateProgram=objLogPass.get_CurrentState();
       std::string  tempRequestProgram= objLogPass.get_Request();
         if(tempStateProgram.compare("3")==0)// успешное создание лога и пароля 
          {
               std::cout << "\n>> Сообщение полученно от сервера\n " ;
               std::cout <<">> Успешное создание лога и павроля!!!\n";
          }
         else if(tempStateProgram.compare("4")==0)//Не удалось создать  лог ипароль 
          {
              std::cout << "\n>> Сообщение полученно от сервера\n " ;
              std::cout<<">> Не удалось создать логин ипароль!!!\n ";
          }
         else if(tempStateProgram.compare("5")==0)//Такой логин и пароль уже есть 
          {
              std::cout << "\n>> Сообщение полученно от сервера \n" ;
              std::cout<<">> Такой пароль уже есть!!!\n" ;
          }
         else if(tempStateProgram.compare("7")==0 && tempRequestProgram.compare("6")==0)//успешная авторизация
          {
              std::cout << "\n>> Сообщение полученно от сервера \n" ;
              std::cout<<">> Успешное авторизация!!!!\n" ;
              autorization=true; 
          }
         else if(tempStateProgram.compare("8")==0)//Нету доступа
          {
              std::cout << "\n>> Сообщение полученно от сервера \n" ;
              std::cout<<">> Нету доступа!!!\n" ;
          }
         else 
          {
              std::cout << "Сервер не отвечает " << std::endl;;
          }
             // objLogPass.addLogPass();
             // std::cout << "Сообщение полученно от клиента >> " << buffer << std::endl;
             // std::cout <<  buffer << std::endl;
        }
           
    // закрываем сокет, завершаем соединение
    close(socket_descriptor);
 }

 
