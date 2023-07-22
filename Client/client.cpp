#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h> // Библиотека для работы с сокетами
#include <arpa/inet.h>
#include "client.h"
#include "prepMess.h"
 
 
char buffer[MESSAGE_BUFFER] ="Нет ответа от сервера !!!!";
char message[MESSAGE_BUFFER]="not message";
int socket_descriptor;
struct sockaddr_in serveraddress;
std::string tempCin; 
std::string tempMessage;

void sendMess(std::string clientMessage) // формирование строки для  отправки сообщения серверу
{
     char tempChar='t';//инициализация пустой ячейки  значением "temp"
     // отправляем сообщение серверу 
     strcpy(message ,clientMessage.c_str());
}

std::string  recivMess() //формирование сообщения для полученная с сервера  
{
     char tempChar='t';//инициализация пустой ячейки  значением "temp"
     int i=0;
     std::string tempStr="";
     while(tempChar!='\0')
     {
        tempChar=message[i];
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
    if(connect(socket_descriptor, (struct sockaddr*) &serveraddress, sizeof(serveraddress)) < 0) {
        std::cout << std::endl << " Something went wrong Connection Failed" <<std:: endl;
        exit(1);
    }
    
    while(1){
        std::cout<<"Для завершения работы наберите  end   или  наберите сообщение серверу "<<std::endl;
        std::cout<< ">>"<< std::endl;
        std::getline(std::cin >> tempCin, tempMessage);//забираем всю строку
		tempMessage = tempCin + " " + tempMessage;
        strcpy(message ,tempMessage.c_str());//преооразуем строку в массив char
      //  std::cin>> message;
        if (strcmp(message, "end") == 0)  { //Закрываем соединение при отпрвке сообщения "end"
        sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
        std::cout << "Клиент работу  сделал.!" << std::endl;
        close(socket_descriptor);
        exit(0);
        }   
        else {
            sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));//отправка сообщения серверу
            std::cout << "Сообщение успешно было отправленно на сервер:  " <<  message << std::endl;
            std::cout << "Дождитесь ответа от сервера ..." << std::endl;
        }
    std::cout << "Сообщение полученно от сервера " << std::endl;
    recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr); //получение сообщения от сервера 
    std::cout <<  buffer << std::endl;
    }
    // закрываем сокет, завершаем соединение
    close(socket_descriptor);
}
 
