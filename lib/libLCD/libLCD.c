#include "libLCD.h"

int lcdHandle;

int initLcd(){
	int i;
  	int fd = wiringPiI2CSetup(ADRESSELCD);
  	
	for(i=0;i<9;i++){
		wiringPiI2CWriteReg8(fd,i,0xFF);
	}
	wiringPiSetupSys();
	mcp23008Setup(AF_BASE,ADRESSELCD);
	pinMode(AF_BLUE,OUTPUT);
	lcdHandle = lcdInit(2, 17, 4, AF_RS, AF_STRB, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0);
	if(lcdHandle < 0){
	    	printf("lcdInit failed\n");
		return -1;
	}
	lcdDisplay(lcdHandle,1);
	return lcdHandle;
}

void displayLcd(char* msg){
	char * buffer = NULL;
	if (strlen(msg) > 16){
		buffer = msg+16;
	}
    lcdPosition(lcdHandle, 0, 0);
    lcdPuts(lcdHandle, msg);
	if (buffer != NULL){
		lcdPosition(lcdHandle, 0, 1);
		lcdPuts(lcdHandle, buffer);
	}
}
