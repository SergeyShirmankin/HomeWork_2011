// 
#include "server.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

 //-----------------------------------------------------------------
char buffer[MESSAGE_BUFFER]; 
char message[MESSAGE_BUFFER];
int socket_file_descriptor, message_size;
socklen_t length;
const char *end_string = "end";
struct sockaddr_in serveraddress, client;
std::string tempCin; 
std::string tempMessage;
//------------------------------------------------------------------ 
void processRequest()  {
    // Создадим UDP сокет 
    socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим порт для соединения
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет 
    bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    while(1)  {
        // Длина сообщения от клиента
        length = sizeof(client);
        message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &length);
        buffer[message_size] = '\0';
        if(strcmp(buffer, end_string) == 0)  {
           std::cout << "Server is Quitting" << std::endl;
            close(socket_file_descriptor);
            exit(0);
        }
        std::cout << "Сообщение полученно от клиента >> " << buffer << std::endl;
        // ответим клиенту
       std::cout << "Введите ответное сообщение клиенту >> " << std::endl;
        std::getline(std::cin >> tempCin, tempMessage);//забираем всю строку
		tempMessage = tempCin + " " + tempMessage;
        strcpy(message ,tempMessage.c_str());//преооразуем строку в массив char
        sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
    }
 
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
}
 
