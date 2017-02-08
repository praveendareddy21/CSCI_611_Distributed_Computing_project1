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
#include "Map.h"

using namespace std;

#define SM_SEM_NAME "/PD_semaphore_2"
#define SM_NAME "/PD_SharedMemory_2"

struct mapboard{
  int rows;
  int cols;
  unsigned char players;
  unsigned char map[0];
};

// mapboard * mbp;
// mpb = (mapboard * ) mmap(...);
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

mapboard * initSharedMemory(int rows, int columns){
  int fd, size;
  mapboard * mbp;
  fd = shm_open(SM_NAME,O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
  size = (rows*columns + sizeof(mapboard));
  ftruncate(fd, size);
  mbp = (mapboard*) mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  return mbp;
}



mapboard * readSharedMemory(){
  int fd, size, rows, columns;
  mapboard * mbp;
  fd = shm_open(SM_NAME,O_RDWR, S_IRUSR|S_IWUSR);
  read(fd,&rows,sizeof(int));
  read(fd,&columns,sizeof(int));
  size = (rows*columns + sizeof(mapboard));
  ftruncate(fd, size);
  mbp = (mapboard*) mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

return mbp;
}

vector<vector< char > > readMapFromFile(char * mapFile, int &golds){
  vector<vector< char > > mapVector;
  vector< char > temp;
  string line;
  char c;
  ifstream mapStream(mapFile);
  mapStream >>golds;
  cout<<"golds "<<golds;
  mapStream.get(c);

  while(getline(mapStream,line))
  {
     for(int i=0; i < line.length(); i++){
       temp.push_back(line[i]);
     }
     mapVector.push_back(temp);
     temp.clear();
  }
  cout<<"ve size "<<mapVector.size()<<" col "<<mapVector[0].size()<<endl;;
  return mapVector;
}

void readMapToSharedMemory(){




}
void initGameMap(unsigned char * mp, vector<vector< char > > mapVector ){

  for(unsigned i=0;i<mapVector.size();i++){
    for(unsigned j=0;j<mapVector[i].size();j++){
      if(mapVector[i][j]==' ')
        *mp=0;
      else if(mapVector[i][j]== '*')
        *mp=G_WALL;
      mp++;
    }
  }
  return;
}

int main()
{
    mapboard * mbp = NULL;
    int rows, cols, goldCount;
    char * mapFile = "mymap.txt";

    unsigned char * mp; //map pointer
    vector<vector< char > > mapVector;



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

     mapVector = readMapFromFile(mapFile, goldCount);
     rows = mapVector.size();
     cols = mapVector[0].size();
     cout<<"rows "<<rows<<"cols "<<cols<<endl;

     mbp = initSharedMemory(rows, cols);
     mbp->rows = rows;
     mbp->cols = cols;
     mbp->players = 0;
     mp = mbp->map;
     initGameMap(mp, mapVector);
     cout<<"shm init done"<<endl;

    // mbp->map = 10;

     //read() //from section 2 of the man-pages
     //write() //from section 2 of the man-pages

   }
   else
   {
     cout<<"not first player"<<endl;
     mbp = readSharedMemory();
     //mbp = gb->board;
     rows = mbp->rows;
     cols = mbp->cols;
     mp = mbp->map;
     cout<<"rows "<<rows<<"cols "<<cols<<endl;
     //not the first player
   }


   Map goldMine(reinterpret_cast<const unsigned char*>(mp),rows,cols);


     //close();

   //some other place in our code. If we are the last player
     //shm_unlink();//delete shared memory

  return 0;
}
