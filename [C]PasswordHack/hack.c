//#define _XOPEN_SOURCE 600
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <crypt.h>
//<Read>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//</Read>
//<sysconf>
#include <unistd.h>
#include <limits.h>
//</sysconf>
//<thread>
#include <pthread.h>
//</thread>

#define IloscHaselDoTestowania 1000
#define AmmountToRead 40000

#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define RESET "\033[0m"

char *Key;
char Salt[100] = "";
char Password[100] = "";
int PassFDS = 0;
int Found = 0;
int Test = 0;
int Working = 0;
long int LiczbaSprawdzonychHasel = 0;
long long int FileSize = 0;

pthread_mutex_t FastMutex=PTHREAD_MUTEX_INITIALIZER;

void *Hack();
void printfINT(char* str);

int main (int argc, char **argv){

  char TMP[2];
  int gui=0;
  int procesorAmmount = 0;
  int maxProcesorAmmount = 0;
  float postep;
  long int currentLocation = 0;
  int i,o,k;

    struct timespec CzasStart, CzasStop;

    //Maksymalna liczba wątków systemu
    maxProcesorAmmount = sysconf(_SC_NPROCESSORS_ONLN);
    printf("maxProcesorAmmount : %d\n", maxProcesorAmmount);
    pthread_t *threadID = malloc (sizeof(pthread_t)*maxProcesorAmmount);

    Key=argv[1];
    printf("Key %s\n", Key);

    char dotestow[100] = "";

    strcpy(dotestow,Key);

    strcat(Salt,"$");
    strcat(Salt,strtok(dotestow,"$"));
    strcat(Salt,"$");
    strcat(Salt,strtok(NULL,"$"));
    strcat(Salt,"$");
    printf("Salt %s\n", Salt);

    if (argv[3] == NULL){
      Test=1;
      procesorAmmount = 0;
    }
    else
      procesorAmmount = atoi(argv[3]);
    printf("procesorAmmount :%d\n", procesorAmmount);

      //TODO: zamienić na arcv[2];
    PassFDS = open ("medium.txt",O_RDONLY);
    if (PassFDS == -1)
    {
      printf("Brak pliku\n");
      return -1;
    }

    //sprawdzamy rozmiar pliku
    FileSize=lseek(PassFDS,0,SEEK_END);
    lseek(PassFDS,0,SEEK_SET);
    printf("FileSize :  %lld\n", FileSize);

  if(Test == 1)
    procesorAmmount = maxProcesorAmmount;

  printf("Testuje !\n");
  while(procesorAmmount >0)
  {

    if (Test == 1){
      clock_gettime(CLOCK_MONOTONIC,&CzasStart);
      // clock_gettime(CLOCK_REALTIME,&CzasStart);
    }


    for(i = 0;i < procesorAmmount && i < maxProcesorAmmount;i++) {
      pthread_create (&threadID[i],NULL,Hack,NULL);
    }

    ///////////////////////////////////////////////
    pthread_mutex_lock(&FastMutex);
      currentLocation = lseek(PassFDS,0,SEEK_CUR);
    pthread_mutex_unlock(&FastMutex);
    ///////////////////////////////////////////////

    sleep(1);

    while((currentLocation < FileSize && Test == 0) || (LiczbaSprawdzonychHasel <= IloscHaselDoTestowania && Test == 1))
    {
      //sprawdzenie aktualnej pozycji jeżeli == koniec czyli filesize to return
      //lub found == 1;
      if (Found)
      {
        // system("clear");
        //int i;
        //for (i=0;i< 21;i++)
        //printf("\n");
        printf("Znaleziono Hasło!\n");
        printf("%s\n", Password);
        break;
      }
      // jeżeli skończył się plik i wątki skączyły prace to można zakończyć
      if(currentLocation == FileSize && (!Working && Test == 0))
      {
          //system("clear");
          //for (i=0;i< 22;i++)
          //printf("\n");
          printf("Nie znaleziono hasła.\n");
          break;
      }
      if (Test == 1 && !Working)
      {
        break;
      }
      pthread_mutex_lock(&FastMutex);
        currentLocation = lseek(PassFDS,0,SEEK_CUR);
      pthread_mutex_unlock(&FastMutex);

      if(Test == 0)
     {

        // system("clear");

        postep = (float)currentLocation / (float)FileSize *10000;

        printf("\n");
          if(postep < (float)FileSize * 0.4)
          {
            printf("Zaawansowanie obliczen: "KRED"%.2f%%"RESET,(float)currentLocation/FileSize*100);
          }
          else
          {
            if (postep < (float)FileSize * 0.7)
            {
              printf("Zaawansowanie obliczen: "KYEL"%.2f%%"RESET,(float)currentLocation/FileSize*100);
            }
            else
            {
              printf("Zaawansowanie obliczen: "KGRN"%.2f%%"RESET,(float)currentLocation/FileSize*100);
            }
          }
          //wyświetlanie postępu obliczeń
          printf(" [%ld/%lld]",currentLocation,FileSize);

          switch(gui)
          {
            case 1:
              printf("[|]");
              break;
            case 2:
              printf("[\\]");
              break;
            case 3:
              printf("[/]");
              break;
            case 4:
              printf("[|]");
              break;
            case 5:
              printf("[\\]");
              break;
            case 6:
              printf("[/]");
              gui=0;
              break;
          }//end switch gui
          gui++;
     }

      sleep(1);
    }

    if(Test == 1){

      clock_gettime(CLOCK_MONOTONIC,&CzasStop);
      
      printf("Czas dla %d watkow: ",procesorAmmount);

      if ((CzasStop.tv_nsec - CzasStart.tv_nsec) < 0)
      {

          char temp[100]="";
          sprintf(temp, "%ld", CzasStop.tv_nsec - CzasStart.tv_nsec);

          long int wartosc=1;
          for (i =0;i<strlen(temp)-1;i++)
            wartosc*=10;

          //printf("%ld,%ld\n",CzasStop.tv_sec - CzasStart.tv_sec,CzasStop.tv_nsec - CzasStart.tv_nsec);
          float b = ((float)CzasStop.tv_nsec - (float)CzasStart.tv_nsec) / wartosc;
          printf(" %f<---\n", ((float)CzasStop.tv_sec - (float)CzasStart.tv_sec) +b);

      }
      else{
        printf(" %ld,%ld\n",
        CzasStop.tv_sec - CzasStart.tv_sec,
        CzasStop.tv_nsec - CzasStart.tv_nsec );
      }

      LiczbaSprawdzonychHasel = 0;
      lseek(PassFDS,0,SEEK_SET);

      procesorAmmount--;
    }
    else
    {
      procesorAmmount = 0;
    }
  }
  close(PassFDS);
  return 0;
}

void *Hack(){
  Working = 1;
  //printf("Hack Begin\n");

  int k=0,j=0;
  long int i=0,a=AmmountToRead;
  char *tmpStr;
  char *saveptr;
  char *buffer = malloc(sizeof(char)*AmmountToRead);
  struct crypt_data *data = malloc(sizeof(struct crypt_data));
  data->initialized =0;

  while(Found != 1 && a>=AmmountToRead){
    //sekjca krytyczna!.
    pthread_mutex_lock(&FastMutex);

    a = read(PassFDS, buffer, AmmountToRead);

    //if(a>0 && Found == 0)
    if(a==AmmountToRead && Found == 0)
    {
        //odcinamy końcówkę hasła o ile jest
        for(i = AmmountToRead,k=0;i > 0;i--,k++)
        {
          if (buffer[i]==10)
          {
            //problem przy czytaniu ponieważ read nie zwraca zero caly czas cofamy do tylu :/
            lseek(PassFDS,-k+1,SEEK_CUR);
            buffer[i]='\n';
            buffer[i+1]='\0';
            break;
          }
        }
    }
    else if(a == 0 || Found == 1)
    {
      //Jeżeli plik jest pusty bądź znaleziono hasło zakończ
      pthread_mutex_unlock(&FastMutex);
      break;
    }

    pthread_mutex_unlock(&FastMutex);

    tmpStr = strtok_r(buffer,"\n\r",&saveptr);
    while (tmpStr != NULL)
    {
      Working=1;

      if((LiczbaSprawdzonychHasel >= IloscHaselDoTestowania && Test == 1) || Found == 1)
      {
        break;
      }
      else if(Test == 1)
        LiczbaSprawdzonychHasel++;

      //printf("%s\n", tmpStr);
      if(strcmp(Key,crypt_r(tmpStr,Salt,data)) == 0 && Test == 0)
      {
        Found=1;
        strcat(Password,tmpStr);
        break;
      }//Porównujemy czy skrót pasuje do skrótu hasła które mamy
      tmpStr = strtok_r(NULL,"\n\r",&saveptr);
    }
  }
  //printf("Hack Stop!\n");
  free(buffer);
  Working=0;
}

//Funkcja wyświetlająca danego stringa w postaci ascii i charów
//przeznaczona do diagnostyki
void printfINT(char* str){
  int i;
  for (i = 0; i < strlen(str); i++)
  {
    if(str[i]==10)
      printf("[\\n:10]\n");
    else
      //printf("[%c:%d]",str[i],str[i]);
      printf("[%c]",str[i]);
  }
  printf("\n");
}
