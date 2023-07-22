#pragma  ones;
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

#define MESSAGE_BUFFER 4096 // Максимальный размер буфера для приема и передачи
#define PORT 7777 // Номер порта, который будем использовать для приема и передачи 

void processRequest();
 