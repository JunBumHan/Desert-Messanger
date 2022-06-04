#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "show.h"
#include "set.h"


int main(int argc, char* argv[])
{
    
    if(argc != 3)
    {
        printf("Error\n");
        printf("Usage : %s <Port> <Name> \n",argv[0]);
        exit(1);
    }

   

    

}