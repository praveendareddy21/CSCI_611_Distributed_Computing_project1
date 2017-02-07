#include<iostream>
#include "goldchase.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

#define SM_SEM_NAME "/PD_semaphore"
#define SM_NAME "/PD_SharedMemory"


/*
unsigned char players_playing;
if(players_playing & G_ANYP == false) //nobody is playing
if(players_playing == 0) //nobody is playing
if(players_playing & G_PLR2)//true if third player is playing
*/

/*
int shm_fd=shm_open("/TAG_mymap",...); //read in file to determine # rows & cols
 ftruncate(shm_fd, rows*cols);

 char* map_pointer;//pointer to shared memory
 map_pointer=(char*)mmap(NULL,rows*cols, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);


 //read in the map a second time
 //loop
    if(char=='*')
       map_pointer[i]=G_WALL;

 map_pointer[34]&=~PLR_0; */

void initSharedMemory(int rows, int columns){
  int fd, size;
  char * map_pointer;
  fd = shm_open(SM_NAME,O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
  size = (rows*columns);
  ftruncate(fd, size);
  map_pointer = (char*) mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  return;   //(GameBoard*) mmap (NULL, countOT_READ|PROT_WRITE, MAP_SHARED, my_file_descriptor, 0);

}

void initGameMap(){

  return;
}
void readSharedMemory(){

return;
}

void readMapToSharedMemory(){




}

int main()
{

   sem_t* sem=sem_open(SM_SEM_NAME, O_CREAT|O_EXCL,
       S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH,1);

   if(sem==SEM_FAILED && errno!=EEXIST)
   {
     perror("semaphore creation error!!");
     exit(1);
   }

   if(sem!=SEM_FAILED)
   {
     cout<<"first player"<<endl;

     initSharedMemory(10, 10)
     //read() //from section 2 of the man-pages
     //write() //from section 2 of the man-pages

   }
   else
   {
     cout<<"not first player"<<endl;
     //not the first player
   }

     //close();

   //some other place in our code. If we are the last player
     //shm_unlink();//delete shared memory

  cout<<"out before main return"<<endl;
  return 0;
}
