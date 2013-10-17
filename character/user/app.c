#include <stdio.h>
#include <fcntl.h>
#include <string.h>
//#include <asm-generic/uaccess.h>

int main(int argc, char *argv[])
{

  //  assert(argc > 1);
    char buffer[100];
    int  counter = 0;
    int i = 0;
    memset(buffer, 0, 100);
    printf("Input string is %s\n", argv[1]);

    int fp = open("/dev/myDec", O_RDWR);

    write(fp, argv[1],strlen(argv[1]));

      while(read(fp, &buffer[counter++],1));
 //  bzero(buffer,100);

   //  read(fp, buffer,strlen(argv[1]));

    printf("Reserved by driver:");
     
   // while(i<100)
   
  
    printf("%s\n", buffer);
     
     
    

   return 0;
}
