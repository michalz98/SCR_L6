#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char *argv[]){

  char buff[255];
  char fname[15];
  struct stat file_stat;
  int nbytes;
  
  const char *mapfile = argv[1];
  int fd = open(mapfile, O_RDWR);
  if(fstat(fd, &file_stat) < 0){
    printf("\n ERROR \n");
  }

  char *ptr = (char*)mmap(NULL,file_stat.st_size,
            PROT_READ|PROT_WRITE,MAP_SHARED,
            fd,0);
  if(ptr == MAP_FAILED){
        printf("Mapping Failed\n");
        return 1;
  }
  close(fd);
  while(1){
   printf( "\nNazwa pliku :");
   scanf("%s", fname);
   int filedes = open(fname, O_RDONLY);
   
   if(fstat(filedes, &file_stat) < 0){
     printf("\n ERROR \n");
   }
   ftruncate(fd,file_stat.st_size);
   ptr = (char*)mmap(NULL,file_stat.st_size,
          PROT_READ|PROT_WRITE,MAP_SHARED,
          fd,file_stat.st_size);
   
   while ((nbytes = read(filedes, buff, sizeof(buff))) > 0){
      printf("%s", buff);
    }
  }
  if(munmap(ptr, file_stat.st_size)<0){
    printf("Unmapping Failed\n");
    return 1;
  }
  return 0;
}
