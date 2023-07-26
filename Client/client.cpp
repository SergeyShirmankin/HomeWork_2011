#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h> // Библиотека для работы с сокетами
#include <arpa/inet.h>
#include "client.h"
#include "prepMess.h"
#include "User.h" 
/* У клиента с сервером есть поля сообения и они будут кодироваться так:
  -- программа имеет немколько состояний:
     1. состояние: программа не активна т.е нет подключения нет сообщений 
     2. Создание лога и пароля 
     3. Авторизация  на лог и пароль 
     4. Успешная авторизация  лог и пароль  
     5. Не успешный лог или пароль
     6. Передача сообщения от сервера
     7. Передача сообщения от клиента
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
         --  NameUserRecive:-- (нет получателя ) 
         --  Request:2; 
         --  CarrentState:1
         --  Messaqge:--(нет сообщения)
    
            *123123:Misha:--:2:1:--&
 //----------------------------------------------------------------------           
     Обьект из класса  User создается в момент прихода сообщения либо от 
     сервера либо от клиента меняет состояние программы и уничтодается!!!!!       
*/
char buffer[MESSAGE_BUFFER] ="Нет ответа от сервера !!!!";
char message[MESSAGE_BUFFER]="not message";
int socket_descriptor;
struct sockaddr_in serveraddress;
std::string tempCin; 
std::string tempMessage;
User user;


void sendMess(std::string clientMessage) // формирование строки для  отправки сообщения серверу
{
     char tempChar='t';//инициализация пустой ячейки  значением "temp"
     // отправляем сообщение серверу 
     strcpy(message ,clientMessage.c_str());
}

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
 
void sendRequest(){
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
    if(connect(socket_descriptor, (struct sockaddr*) &serveraddress, sizeof(serveraddress)) < 0) 
    {
        std::cout << std::endl << " Something went wrong Connection Failed" <<std:: endl;
        exit(1);
    }
    
    while(1)
    {
         std::cout<<"Для завершения работы наберите  end   или  log  для создание логина и пароля  или авторизации на сервере "<<std::endl;
         std::cout<< ">>"<< std::endl;
         std::getline(std::cin >> tempCin, tempMessage);//забираем всю строку
	    tempMessage = tempCin + " " + tempMessage;
         strcpy(message ,tempMessage.c_str());//преооразуем строку в массив char
 //       if (strcmp(message, "end") == 0)  
        if (tempMessage.compare("end ")==0) 
        { //Закрываем соединение при отпрвке сообщения "end"
             sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
             std::cout << "Клиент работу  сделал.!" << std::endl;
             close(socket_descriptor);
             exit(0);
        }   
           else if (tempMessage.compare("log ")==0)
           {
               tempMessage=objPrevMess.InterfaceLogPass( objPrevMess.managerInterLogPass);
               strcpy(message ,tempMessage.c_str());//преооразуем строку в массив char
           }
            sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));//отправка сообщения серверу
            std::cout << "Сообщение успешно было отправленно на сервер:  " <<  message << std::endl;
            std::cout << "Дождитесь ответа от сервера ..." << std::endl;
        
             std::cout << "Сообщение полученно от сервера " << std::endl;
             recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr); //получение сообщения от сервера 
             std::cout <<  buffer << std::endl;
    }        
    // закрываем сокет, завершаем соединение
    close(socket_descriptor);
 }

 
