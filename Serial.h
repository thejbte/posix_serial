/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   Serial.h
 * @brief:  This program file contains prototypes and definitions for serial port communication 
 * @author: Esp.Ing.Julian Bustamante N
 * <mailto:thejbte@gmail.com>
 * @date: Created on 8 de mayo de 2020, 04:36 PM
 */

#ifndef SERIAL_H
#define SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>   /* Standard input/output definitions */
    
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/select.h> /*Monitorear multiples fd*/
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdint.h>
/**
 * 
 * @brief Check if a file exist using stat() function
 * @param filename
 * @return 1 if the file exist otherwise return 0
 * @see https://www.zentut.com/c-tutorial/c-file-exists/
 */
int File_Exist(char *filename);
    /**
 * @brief Open port serial
 * @param Serial_Name
 * @param baud
 * @return file descriptor
 */
int Serial_Open(char *Serial_Name, speed_t baud);

/**
 * @brief Send data by serial port
 * @param Serial_fd : file descriptor of serial port
 * @param Data : data to send
 * @param Size : amount data to send
 * @return bytes writed
 */
int Serial_Send(int Serial_fd, char *Data, int Size);


/**
 * @brief Read data received by serial port
 * @param Serial_fd
 * @param Data
 * @param Size
 * @param Timeout_usec
 * @return 
 */
int Serial_Read(int Serial_fd, char *Data, int Size);





/**
 * @brief Close serial port
 * @param fd : file descriptor
 */
void Serial_Close(int fd);
    
int serialBytesAvailable(int descriptor);
    



#ifdef __cplusplus
}
#endif

#endif /* SERIAL_H */

