#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "socketSession.h"
#include "socketData.h"
#include "utils.h"
#include "clientData.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 58392


void connexionWithServer(game_t *game);
void getResult(game_t *game);
void fetchOtherClientsData(game_t *game);





#endif