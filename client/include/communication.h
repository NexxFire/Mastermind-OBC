#ifndef COMMUNICATION_H
#define COMMUNICATION_H

//send a message to the server

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH_NAME_SERVER "/tmp/maSocketUNIXServer"

// Définition du port et de l'adresse IP du client (TEST)
#define PORT_CLIENT 5001
#define INADDR_CLIENT "172.20.10.80"// Adresse IP du client
#define PATH_NAME_CLIENT "/tmp/maSocketUNIXClient"

//fgets
//parcourir le tableau de caractères 
//vérifier que le caractère est une lettre






#endif