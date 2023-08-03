#include "LogPass.h"
#include "server.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>
 //-----------------------------------------------------------------
char buffer[MESSAGE_BUFFER]; 
char message[MESSAGE_BUFFER];
int socket_file_descriptor, message_size;
socklen_t length;
const char *end_string = "end";
struct sockaddr_in serveraddress, client;
std::string tempCin; 
std::string tempMessage;
std::string tempStateprogram;
std::string tempRequest;
Log_pass  objLogPass;
//auto it = _log_pass.find(user.get_PasswordUser()); 
//-------------------------------------------------------------------------------------
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
//------------------------------------------------------------------ 
//-------основная функция программы------Сервер--------------------
//---Все программы будут работать в констексте данной программы----- 
//------------------------------------------------------------------
void processRequest() 
 {
    // Создадим UDP сокет 
    socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим порт для соединения
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет 
    bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    while(1)  
    {
        // Длина сообщения от клиента
        length = sizeof(client);
        message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &length);
        buffer[message_size] = '\0';
        if(strcmp(buffer, end_string) == 0)  
        {
           std::cout << "Server is Quitting" << std::endl;
            close(socket_file_descriptor);
            exit(0);
        }

        objLogPass.parser(buffer);
        tempRequest=objLogPass.get_Request();
       
        if(tempRequest.compare("2")==0)// Создание нового лога и пароля
            objLogPass.addLogPass();
             // std::cout << "Сообщение полученно от клиента >> " << buffer << std::endl;

        else if(tempRequest.compare("6")==0) //Авторизация  на лог и пароль 
            objLogPass.enterLogPass();

        else if(tempRequest.compare("9")==0) //Запрос о количеси\тве зарегестрированых пользователях
            {
                  std::string tempStr;
                  std::vector<std::string> tempVector;
                  tempVector.reserve(3);
                  tempVector=objLogPass.countUser();
                  
                    for (int i = 0; i < tempVector.size(); i++) 
                     {
                         tempStr=tempVector[i];
                         strcpy(message ,tempStr.c_str());//преооразуем строку в массив char
                        // ответим клиенту
                         sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
                     }
                  
			}
//----------------------------------------------------------------------------------- 
        
          std::string logMessForClient=objLogPass.createMessLogToClient();
          std::cout << "ответное сообщение клиенту >> "<<logMessForClient << std::endl;
          strcpy(message ,logMessForClient.c_str());//преооразуем строку в массив char
          // ответим клиенту
          sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
    }
 
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
}
 
