# Mastermind-Contest
A multiplayer Mastermind game with client-server architecture.


## Installation
### Cross compile the project
Run the config script to initialize all needed variable in your shell for crossed compile
```
source config.source
```

Run make in the root directory

```bash
make
```
The server and client executables will be created in the build directory

### Joy-Pi configuration
Use any file transfert of your choice to move client and server executable to the JoyPi, You shold also include the rootRPI directory because you will need it to install all needed lib and include for the project

Once you have all the file on the JoyPi, move all file from rootRPI in designated directory. On the official JoyPi image you should copy rootRPI/bin to /bin, rootRPI/lib to /lib, rootRPI/include to /usr/include, rootRPI/share to /usr/share

## How to play

### Server
When everything is setted up, you can lanch the client and the server on one JoyPi, every other JoyPi should only launch a client
 
Run the server on a machine within your accessible networks
```bash
./build/server
```
The server will start listening on port 58392 on every available network interface

### Client
Run the client on a machine within the same network as the server
```bash
./build/client
```
The client will ask for the server's IP address and the port number, enter the server's IP address and 58392 as the port number

You can now play the game with your friends

## Game Rules

### Connection
The game can be played with a max of 4 players. The server will wait for minimumm 1 player to connect, when all player currently connected say they are ready, the game will start.

### Game
The game is played in rounds, each player will be codebreakers. In each round, the player will have to guess the secret code given by the server. The player will have 12 attempts to guess the code. 

The player will be given feedback after each guess in the form of hint. He will be given the number of correct colors in the correct position, and the number of correct colors in the wrong position. The player will have to use this feedback to guess the code in the next attempt.

The player who guesses the code first win the game.

### Code
The code is a 4 character string, each character can be one of the following colors: R, G, B, C, Y, M. It is possible that the code contains the same color multiple times.

The code is generated randomly by the server at the start of the game.

### End of the game
The game will end when a player guesses the code correctly. The server will announce the winner and the game will end. Client will then close automatically. The server will start a new game automatically and wait for new players to connect.

## Authors
- [Martin Ducoulombier]
- [Delphine Chichery]