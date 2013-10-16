/********************************************************************
*Programmer: George Wang(Haoran Wang)                               *
*Date: 04/25/2011                                                   *
*Name: Herky                                                        *
*Description:For this assignment, you will be manipulating an       *
*ASCII image. An ASCII image is an image that is created by the     *
*clever placement of characters defined by the ASCII standard.Figure*
********************************************************************/


//image file https://dl.dropbox.com/u/98138259/image.txt


#include <stdio.h>

void read_function(int *jPtr,int *xPtr,int *yPtr,char letters[200][200]);/*function prototype of read_function*/
void inversion(int junk,int row,int col,char letters[200][200]);/*function prototype of inversion_function*/
void tanslation_function(int row,int col,char letters[200][200]);/*function prototype of translation_function*/
void rotate_function(int row,int col,char letters[200][200]);/*function prototype of rotate function*/
void shrink_function(int row,int col,char letters[200][200]);/*function prototype of shrink function*/

int main()/*main function starts*/
{
   FILE *readPtr;/*intialize read pointer of file*/
   FILE *writePtr;/*intialize write pointer of file*/

   int row;/*initialize row*/
   int col;/*initialize col*/
   int junk;/*initialize junk*/
   int i=0;/*initialize i counter as zero*/
   int j=0;/*initialize j counter as zero*/
   int input=0;/*initialize input as zero*/
   char letters[200][200];/*initialize letters as 200 by 200;*/
   char namestring[80];/*initialize namestring and size by 80*/

   printf("What is the name of your input image file?\n");
   scanf("%s",namestring);

   readPtr=fopen(namestring,"r");/*open files*/

   while (readPtr == NULL)/*while loop to check if file exists*/
   {/*while starts*/
    printf("Could not open %s\n",namestring);
    printf("Please take valid name\n");
    scanf("%s",namestring);
    readPtr=fopen(namestring,"r");
   }/*end while*/


     printf("What input do you want?\n");/*as use to prompt type of change*/
     printf("1.inversion\n2.translation\n3.rotation\n4.shrink\n");/*4 types of change*/
     scanf("%d",&input);/*input as scanf*/

   while(input<1 || input>4)/*to check while or not input is valid*/
   {
    printf("Error!!Please take the valid input!!\n");
    scanf("%d",&input);
   }/* end while*/


         if(input==1)
         {
            inversion(junk,row,col,letters);/*call function of inversion*/
            printf("Modified image successfully printed to 'finalimage.txt'");
         }/*end if*/
         else if(input==2)
         {
            tanslation_function(row,col,letters);/*call function of translation*/
            printf("Modified image successfully printed to 'finalimage.txt'");
         }/*end if*/
         else if(input==3)
         {
            rotate_function(row,col,letters);/*call function of rotation*/
            printf("Modified image successfully printed to 'finalimage.txt'");
         }/*end if*/
         else if(input==4)
         {
            shrink_function(row,col,letters);/*/*call function of shrink*/
            printf("Modified image successfully printed to 'finalimage.txt'");
         }/*end if*/

      return 0;/*end main*/
}


void read_function(int *jPtr,int *xPtr,int *yPtr,char letters[200][200])/*function of read, initialize three pointers and letters*/
{
  FILE *readPtr;/*read pointer of file*/
  FILE *writePtr;/*write pointer of file*/
  writePtr = fopen("finalimage.txt","w");/*out put as finalimage.txt*/
  int row;/*initialize row*/
  int col;/*initialize col*/
  int i=0;/*initialize i as a counter*/
  int j=0;/*initialize j as a counter*/
  readPtr = fopen("image.txt","r");/* read in original function*/
  fscanf(readPtr, "%d %d", &*xPtr, &*yPtr);/*store numbers in xPtr and yPtr*/
  fscanf(readPtr, "%c", &*jPtr);/* store junk*/

   for(i=0;i<*xPtr;i++)
   {
     for(j=0;j<*yPtr;j++)
     {
        fscanf(readPtr, "%c", &letters[i][j]);/*read characters from original image*/
     }/*end for*/
   fscanf(readPtr, "%c", &jPtr);/*read junk and skip it*/
   }/*end for*/

 fclose(writePtr);/*clode write pointer*/

}

void inversion(int junk,int row,int col,char letters[200][200])/*function of inversion,intialzie junk,row,col and letters*/
{
  FILE *writePtr;/*initialize write pointer*/
  writePtr = fopen("finalimage.txt","w");/*output stored as finalimage.txt*/

  read_function(&junk,&row,&col,letters);/*call function of read from original image file*/

  int i=0;
  int j=0;

  fprintf(writePtr, "%d %d", row, col);/*printf row and col*/
  fprintf(writePtr, "%c",junk);/*printf junk*/

/*two for loops to change charcter and change the color*/
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
       if(letters[i][j]=='M')
       {
           letters[i][j]='.';
       }
       else if(letters[i][j]=='W')
       {
           letters[i][j]=',';
       }
       else if(letters[i][j]=='B')
       {
           letters[i][j]=';';
       }
       else if(letters[i][j]=='H')
       {
           letters[i][j]='+';
       }
       else if(letters[i][j]=='A')
       {
          letters[i][j]='I';
       }
       else if(letters[i][j]=='S')
       {
           letters[i][j]='S';
       }
       else if(letters[i][j]=='I')
       {
           letters[i][j]='A';
       }
       else if(letters[i][j]=='+')
       {
           letters[i][j]='H';
       }
       else if(letters[i][j]==';')
       {
           letters[i][j]='B';
       }
       else if(letters[i][j]==',')
       {
           letters[i][j]='W';
       }
       else if(letters[i][j]=='.')
       {
           letters[i][j]='M';
       }

    }

}/*end for*/


   for(i=0;i<row;i++)
   {
     for(j=0;j<col;j++)
     {
         fprintf(writePtr, "%c", letters[i][j]);

     }

     fprintf(writePtr, "%c",junk);
   }


   fclose(writePtr);/*clode write pointer*/

}/*end inersion function*/


void tanslation_function(int row,int col,char letters[200][200])/*function of translation and initialize row, col, letters in this function*/
{
  int junk;/*intialize junk*/
  FILE *writePtr;/*initialize write pointer*/
  writePtr = fopen("finalimage.txt","w");/*output file*/
  read_function(&junk,&row,&col,letters);/*call function of read and pass address of junk,row,col,letters*/

  int i=0;/*initialize i as a counter*/
  int j=0;/*initialize j as a counter*/
  int k;/*initiliaze k as a value of units of right direction*/
  int l;/*initilize l store to col*/
  int n;/*initilize n store to row*/
  int m;/*initiliaze k as a value of units of down direction*/
  int right=0;/*intialize right as zero*/
  int down=0;/*initialize down as zero*/
  char letters1[200][200];/*initialize a new array of right direction*/
  char letters2[200][200];/*initialize a new array of down direction*/

   printf("How many units right do you want to move?\n");
   scanf("%d",&right);
   printf("How many units down do you want to move?\n");
   scanf("%d",&down);

   for(i=0;i<row;i++)
   {
     l=col;/*store l as value of col which is read from original function*/
     k=right;/*store k as value of right units*/
      for(j=0;j<col;j++)
      {
         if(j-right<0)/*give value of rear numbers to front numbers*/
         {
           letters1[i][j]=letters[i][l-k];/*store new array*/
           k--;/*k minus each time*/
         }/*end if*/
           else
           {
           letters1[i][j]=letters[i][j-right];/*store letters1 from letters*/
           }/*end else*/
      }

   }/*end for*/

    n=row;/*store n as value of row which is read from original image*/
    m=down;/*stroe m as value of down units*/

   for(i=0;i<row;i++)
   {

    for(j=0;j<col;j++)
    {
       if(i-down<0)/*give value of down numbers to up numbers*/
       {
         letters2[i][j]=letters1[n-m][j];/*store x direction to a new array*/
         fprintf(writePtr, "%c", letters2[i][j]);/*printf out letters2 which has already store right units and down unites*/
       }
          else
          {
           letters2[i][j]=letters1[i-down][j];/*store letters2 from letters1*/
           fprintf(writePtr, "%c", letters2[i][j]);/*printf out letters2 which has already store right units and down unites*/
          }

    }
         m--;
             fprintf(writePtr, "%c",junk);
}


fclose(writePtr);/*clode wite pointer*/

}/* end translation funtion*/

void rotate_function(int row,int col,char letters[200][200])/* function of rotation and initialize row,col and letters*/
{
    int junk;/*initialize junk*/
    int l;
    int k;
    char letters1[200][200];
    int i;/*initialize i as a counter*/
    int j;/*initialize j as a counter*/
    int n;
    int m;
    int rotate_input=0;/*initialize rotate input stored as zero*/

    FILE *writePtr;
    writePtr = fopen("finalimage.txt","w");

    read_function(&junk,&row,&col,letters);/*call function of read and pass adress of junk, row, col, and letters*/

    fprintf(writePtr, "%d %d", row, col);/*printf out row and col*/
    fprintf(writePtr, "%c",junk);/*printf out junk*/

    /*ask the useer to input whether clockwise or counterclockwise*/
    printf("What kind of rotate do you want to do?\n");
    printf("1,clockwise\n");
    printf("2,counterclockwise\n");
    scanf("%d",&rotate_input);
    while(rotate_input<1||rotate_input>2)
    {
      printf("Invalid input!!!!please get the correct input!\n");
      scanf("%d",&rotate_input);
    }/*end while*/
     if(rotate_input==1)/*clockwise*/
     {
      l=0;/*store l as zero*/
        for(j=0;j<col;j++)
        {
         k=row-1;/*store k as a counter*/
           for(i=0;i<row;i++)
           {
             letters1[j][i]=letters[k][l];/*store a new array letters*/
             fprintf(writePtr, "%c", letters1[j][i]);
             k--;/*counter k*/
           }/*end for*/
            l++;/*counter ;*/
            fprintf(writePtr, "%c",junk);/*print out white space*/
        }

         fclose(writePtr);/*close write pointer*/
     }

     else if(rotate_input==2)/*counter clock wise*/
     {
       fprintf(writePtr, "%d %d", row, col);/*print out row and col*/
       fprintf(writePtr, "%c",junk);/*print out junk*/
       m=col-1;/*store m as a counter*/
        for(j=0;j<col;j++)
        {
         n=0;
          for(i=0;i<row;i++)
          {
           letters1[j][i]=letters[n][m];
           fprintf(writePtr, "%c", letters1[j][i]);

           n++;/*n plus plus*/
          }/*end for*/
              m--;
              fprintf(writePtr, "%c",junk);
        }/*end for*/

       fclose(writePtr);/*close write pointer*/

      }/*end else if*/

}/* end rotation function*/

void shrink_function(int row,int col,char letters[200][200])/* functino of shrink and initialize row,col and letters*/
{
    int junk;/*initialize junk*/
    int i;/* initialize i as a counter*/
    int j;/* initialize j as a counter*/
    int rotate_input=0;/*initialize roate input as zero*/

    FILE *writePtr;/*initialize write pointer*/
    writePtr = fopen("finalimage.txt","w");/*output file*/

    read_function(&junk,&row,&col,letters);/*call fucntion of read and pass address of junk,row,col and letters to read*/

    fprintf(writePtr, "%d %d", row, col);
    fprintf(writePtr, "%c",junk);

    for(i=0;i<row;i=i+2)/*skip each two character of x direction*/
    {
      for(j=0;j<col;j=j+2)/*skip each two character of y direction*/
      {
        fprintf(writePtr, "%c", letters[i][j]);/*print ot letters*/
      }

            fprintf(writePtr, "%c",junk);
    }

       fclose(writePtr);/*close write pointer*/
}/*end shrink function*/



