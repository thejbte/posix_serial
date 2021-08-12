/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Julian
 *
 * Created on 8 de mayo de 2020, 04:35 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "Serial.h"
#include <signal.h>

#define MAX_PORT_SIZE   30


int main(int argc, char** argv) {
    
    int portFD;
    uint8_t byte = 0;
    int status = 0;
    uint32_t baudrate;
    char port[MAX_PORT_SIZE + 1] = "/dev/";
    uint32_t CountFrameIncomming = 0;
    
   
    if(argc < 3){
        printf("Usage: ./serial PORT BAUD e.g. ./serial ttyUSB0 9600");
        exit(EXIT_FAILURE);
    }
    
    //Get the input arguments
    strncpy(port + 5, argv[1], strlen(argv[1])+6);
    
    baudrate = (uint32_t)atoi(argv[2]);

     
   portFD = Serial_Open(port,baudrate);
    unsigned long Counter_reset=0;
    if(portFD < 0){
      exit(EXIT_FAILURE);
    }
    volatile int localReadyRx=0;
    while(1){
       
       if(File_Exist(port)){

        if( localReadyRx == 1 ){
                Serial_Send(portFD,"OUTPUT\r\n",strlen("OUTPUT\r\n"));
                localReadyRx = 0;
            }

            status = Serial_Read(portFD, (void*)&byte,1);
    
            if(status < 0){
                return (EXIT_SUCCESS);
            }else if(status > 0){
                    /*pasar byte a byte a parser frame ( decodificar trama)*/
            }else  if(status == 0){
                        localReadyRx = 1;
                    }
       }else {
           perror("File or directory does not exist");
           Serial_Close(portFD);
           exit(EXIT_FAILURE);
       }
 
    } 
    Serial_Close(portFD);   
    return (EXIT_SUCCESS);
}

/*--*/