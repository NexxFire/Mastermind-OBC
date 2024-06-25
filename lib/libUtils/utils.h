#ifndef UTILS_H
#define UTILS_H

#include "socketSession.h"
#include "socketData.h"
#include <ncursesw/ncurses.h>


void getUserInput(char *buffer, size_t size);
void clearBuffer ();

void sendData(socket_t *socket, char *data, int expectedCode);
void receiveData(socket_t *socket, char *data, int validationCode);

#endif // UTILS_H