#include<iostream>
#include "goldchase.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


/*
unsigned char players_playing;
if(players_playing & G_ANYP == false) //nobody is playing
if(players_playing == 0) //nobody is playing
if(players_playing & G_PLR2)//true if third player is playing

*/
int main()
{
       sem_t *sem_open(const char *name, int oflag,
                       mode_t mode, unsigned int value);


       sem_t* sem=sem_open("/mySem",
           O_CREAT|O_EXCL,
           S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH,
           1);

       if(sem==SEM_FAILED && errno!=EEXIST)
       {
         perror("sem failed");
         exit(1);
       }


       if(sem!=SEM_FAILED)
       {
         //I am the first player
         //shm_open();

         //read() //from section 2 of the man-pages
         //write() //from section 2 of the man-pages

       }
       else
       {
         //not the first player
       }

         //close();

       //some other place in our code. If we are the last player
         //shm_unlink();//delete shared memory

  cout<<"out before main return"<<endl;
  return 0;
}
