/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   Serial.c
 * @brief:  Serial port communication 
 * @author: Esp.Ing.Julian Bustamante N
 * <mailto:thejbte@gmail.com>
 * @date: Created on 8 de mayo de 2020, 04:36 PM
 */

#include "Serial.h"
#include "stdio.h"
#include "stdlib.h"
#include <termios.h> /* POSIX terminal control definitions */

/**
 * 
 * @brief Check if a file exist using stat() function
 * @param filename
 * @return 1 if the file exist otherwise return 0
 * @see https://www.zentut.com/c-tutorial/c-file-exists/
 */
int File_Exist(char *filename){
  struct stat   buffer;   
  return (stat(filename, &buffer) == 0);
}


/**
 * @brief Open port serial
 * @param Serial_Name
 * @param baud
 * @return file descriptor
 */
int Serial_Open(char *Serial_Name, speed_t baud){
    struct termios PortSetting;
    int fd,error; /*File Descriptor*/
    
    fd = open(Serial_Name,O_RDWR | O_NOCTTY ); /*O_NONBLOCK *//*"/dev/serial0"*/
    if(fd < 0){
        perror("Failed opening port");
        return (-1);
    }
    
    if(tcgetattr(fd, &PortSetting) < 0){
      perror("Failed to obtain port attributes");
      return (-1);
      //exit(EXIT_FAILURE);
    }
    
    //Configure the serial port----------------------------------------------/
    //Disable input processing
    PortSetting.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | 
                        PARMRK | INPCK | ISTRIP | IXON);
    
    PortSetting.c_iflag &= ~(IXON | IXOFF | IXANY);
        //Disable output processing
    PortSetting.c_oflag = 0;
    PortSetting.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    PortSetting.c_oflag &= ~ONLCR;
    //Disable line processing
    PortSetting.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    
    //Disable character processing
    PortSetting.c_cflag &= ~(CSIZE | PARENB | CSTOPB);
    PortSetting.c_cflag |= CS8;
    
    //PortSetting.c_cflag &= ~(CREAD | CLOCAL);

    tcflush(fd, TCIOFLUSH);
    //One byte to return from read, no time between chars
    PortSetting.c_cc[VMIN] = 0;  //1
    PortSetting.c_cc[VTIME] = 50;  //0
    
        //Comm speed
    if(cfsetspeed(&PortSetting, baud)){
     perror("Failed setting port speed" );
     return (-1); 
     //  exit(EXIT_FAILURE);
    }
        //Set attributes to the serial port
    if(tcsetattr(fd, TCSADRAIN, (const struct termios*)&PortSetting)){
        perror("Failed setting port attributes");
       return (-1); 
    }

    return (fd); /*file descriptor*/
}


/**
 * @brief Send data by serial port
 * @param Serial_fd : file descriptor of serial port
 * @param Data : data to send
 * @param Size : amount data to send
 *  @return bytes writed
 */
int Serial_Send(int Serial_fd, char *Data, int Size){
  return write(Serial_fd, Data, Size);
}

/**
 * @brief Read data received by serial port
 * @param Serial_fd
 * @param Data
 * @param Size
 * @return 
 */
int Serial_Read(int Serial_fd, char *data, int size){
  int  status;
  status = read (Serial_fd, (void*)data, size); 
  if(status < 0){
      perror("Failed reading from port");
      return (-1);
   }
  return status;
}

/**
 * @brief Close serial port
 * @param fd : file descriptor
 */
void Serial_Close(int fd){
  close(fd);
}


 
 int serialBytesAvailable(int descriptor){
    int bytes_avail = 0;
    ioctl(descriptor, TIOCINQ, &bytes_avail); //FIONREAD
    return bytes_avail;
}


/**mia
 */