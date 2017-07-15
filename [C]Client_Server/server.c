#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // OPTGET
#include <sys/types.h>	//
#include <sys/socket.h>	//recv
#include <netinet/in.h> // sockaddr_in
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <poll.h>


#define buffersize 100
#define MaxUsers 10
#define CERROR "\x1B[31m"
#define RESET "\033[0m"


extern char *optarg;
extern int optind, opterr, optopt;

struct user {
	char *name;
	int socket;
	int connected;
};

struct user **Clients=NULL;
struct pollfd fds[MaxUsers];
int ConnectedClients=0;
pthread_t thread_id;

void funkcjaCzyszczaca(){
	//pthread_kill(thread_id, SIGINT);//???
	int i;
	for (i = 0; i < ConnectedClients; ++i)
	{
		write(Clients[i]->socket,"t0",3);
		close(Clients[i]->socket);
		free(Clients[i]->name);
		free(Clients[i]);
	}
	exit(0);
}

int sendMgsTo(char *mgs,char *target,char *from);
int isRunning(char *name);
void *connection();

//TODO:
/*
-logika demona
-przechwytywanie sigint (czyszczenie informacji)
*/


int main(int argc, char **argv){

	int ret=0,PortInt=0;
	char *PortChar=NULL;
	int flagP = 0 ,flagQ = 0;

	while((ret = getopt(argc, argv, "qp:"))!=-1){
		switch(ret){
			case 'p':
			flagP = 1;
			PortChar = optarg;
			PortInt = atoi(PortChar);
			break;
			case 'q':
			flagQ = 1;
			break;
			default:
			break;
		}//Switch => flagi
	}//while => getopt

	int pid = isRunning(argv[0]); 	// sprawdzamy czy proces o takiej nazwie już istnieje
								// jak tak to wysyłamy sygnał do wyłączenia
if (flagQ == 1 && pid > 0 ){ // flagQ = 1 chcemy wyłączyć pid>0 proces jest uruchomiony

	printf("Wyłączono server %s z pid %d.\n\n",argv[0],pid);
	//sprawdzenie czy zakończono. wszystko oprócz tego procesu getpid();
	while ((pid = isRunning(argv[0])) != -1){
		kill(pid,SIGINT);
	}
	return 0;
	
}else if (flagQ == 1 && pid == -1 ){
	printf("%d\n",getpid());
	printf("Nie można wyłączyć servera ponieważ server nie jest uruchomiony.\n\n");
	printf("Aby uruchomić server napisz: \"%s -p port\" gdzie port - port servera\n",argv[0]);
	
}

if ( flagP == 1 && pid > 0 ){ // flagP chcemy uruchomić server pid > 0 server jest uruchomiony

	printf("Server jest już uruchomiony jego parametry to:\n");
	printf("Port:\t%d\n",PortInt);
	//printf("Adres hosta: %s\n",hostname);
	
}else if(flagP == 1 && pid == -1){ // flagP chcemy uruchomić i pid = -1 brak uruchomionego servera

		
	
	if (pid=fork() >0)
		exit(0);
	else
	{
		/////////////////////////////////////
		//  							   //
		//  TODO: dodać tworzenie demona.  //
		//  							   //
		/////////////////////////////////////
	
		//odłączenie od procesu macierzystego
		setsid();
		//ustawienie katalogu na katalog w którym jesteśmy.
		chdir(".");
		//zamykamy deskryptory stdin, stdout, stderr
		close(0);
		close(1);
		close(2);
		//ustawiamy deskryptory na dev/null
		int fd = open("dev/null",O_RDWR);
		dup2(fd,0);
		dup2(fd,1);
		dup2(fd,2);

	
	
			struct sigaction sa;
	
			sa.sa_handler = &funkcjaCzyszczaca; // ustawiamy funkcję która ma się wykonać C
			sigaction(SIGINT, &sa,NULL);

			Clients = (struct user **)malloc(sizeof(struct user *)*MaxUsers);
	
			int serverSocket, newsockfd;
			socklen_t clilen;

			struct sockaddr_in serv_addr, cli_addr;	// sockaddr_in AF_INEt IPv4
			char buffer[256];
			
			
			serverSocket = socket(AF_INET, SOCK_STREAM, 0); // ipv4 sosck_stream przesyłanie wiadomości
			
			if (serverSocket == -1){
				system ("clear");
				printf(CERROR"Nie można utworzyć gniazda\n"RESET);
				return 1;
			}
			
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = INADDR_ANY;
			serv_addr.sin_port = htons(PortInt);
			
			if (bind(serverSocket, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
				system ("clear");
				printf(CERROR"ERROR on binding"RESET"\n");
				return 1;
			}
			printf("%d\n",getpid());
			printf("Server został uruchomiony poprawnie:\n");
			printf("Port\t\t:%d\n",PortInt);
			//printf("Host Name\t:%s\n",hostname);
			printf("Host Adres\t:%s\n",inet_ntoa(serv_addr.sin_addr));
			
			listen(serverSocket,10); // uruchamiamy tryb nasłchiwawnia na połączenie klienta
			
			clilen = sizeof(cli_addr);
			
			int timeout, inQueue;
			char tempid[10];
			timeout = 1000;


			pthread_create( &thread_id, NULL, connection, NULL);
			
			while(1){
				//printf("Czekam na nowego usera\n");
				newsockfd = accept(serverSocket, (struct sockaddr *) &cli_addr, &clilen); 
				
				if (newsockfd < 0){
					system ("clear");
					printf(CERROR"ERROR on accept"RESET);
				}
				else
				{ 
					int exitFlag=1;
					int k=0,i=0,j=0;
					char tempchar[20]="";
					char TMP[2];
					

					if (ConnectedClients > 0){
						do{
							bzero(buffer,256);// czyszczenie buforu wiadomości 
							tempchar[0]='\0';
							
							read(newsockfd,buffer,255);
							
							for (i=2; buffer[i] != '0'; i++) {
								TMP[0] = buffer[i];
								TMP[1] = '\0';
								if(TMP[0]!=10)
									strcat(tempchar, TMP);
							}
							
							for (i=0;i<ConnectedClients;i++){

								if(strcmp(Clients[i]->name,tempchar) == 0){
									//printf("[SERVER]Już jest takie imię! \n");
									write(newsockfd,"u0",3);
									continue;
								}
								else
								{
									buffer[0]='\0';
									strcat(buffer,"s0");
									strcat(buffer,tempchar);
									//printf("Nowy Nick %s\n",buffer);
									exitFlag =0;
								}
							}
						}while(exitFlag);//read(newsockfd,buffer,255)
					}	
					else
					{

						bzero(buffer,256);// czyszczenie buforu wiadomości 
						read(newsockfd,buffer,255);
						
						//Nowy user
						printf("buffer :%s\n",buffer);
						for (i=2; buffer[i] != '0'; i++) {
							TMP[0] = buffer[i];
							TMP[1] = '\0';
							if(TMP[0]!=10)
								strcat(tempchar, TMP);
						}
						tempchar[i+1]='\0';
					}

					write(newsockfd,"d0",3);
					
					struct user *temp;
					temp = (struct user*)malloc(sizeof(struct user));
					
					temp->name = malloc(sizeof(char)*strlen(tempchar)+1);
					temp->name[0]='\0';
					
						//nowy string
					if (tempchar[strlen(tempchar)-1]=='\n')	
						tempchar[strlen(tempchar)-1]='\0';	
					
					strcat(temp->name, tempchar);
					
					temp->connected = 1;
					temp->socket = newsockfd;
					fds[ConnectedClients].fd = newsockfd;
					fds[ConnectedClients].events = POLLIN;
					
					Clients[ConnectedClients] = temp;
					
					ConnectedClients++;	
				}//end else (no errors);
			}//end inf while	
			close(serverSocket);
		}//end else fork!
		}
		return 0;
	}

void *connection(){

		int i;
		int flag=0;
		int SprawdzanyKlient=0;

		char buffer[256];
		char ClientName[25]="";

		while(1){

			flag = poll(fds,ConnectedClients,0);
			if (flag != 0)
			{
				for (SprawdzanyKlient = 0; SprawdzanyKlient < ConnectedClients; SprawdzanyKlient++)
				{
					if (fds[SprawdzanyKlient].revents & POLLIN)
					{
						bzero(buffer,256);// czyszczenie buforu wiadomości 
						if (read(fds[SprawdzanyKlient].fd,buffer,255) < 0)  //odczytanie wiadomości
							printf(CERROR"ERROR reading from socket"RESET);
						
						printf("[BUFFOR odczytany]: %s\n",buffer);
						switch(buffer[0]){
							case 'q':{ // klient się odłączył

								close(Clients[SprawdzanyKlient]->socket);
								free(Clients[SprawdzanyKlient]);

								int j;
								for (j=SprawdzanyKlient;j<ConnectedClients-1;j++)
								{
									Clients[j]=Clients[j+1];
									fds[j]=fds[j+1];
								}
								//fds[ConnectedClients];
								ConnectedClients--;
							break;}
							case 'l':{//wysyłamy listę do klienta//char buffer[50] = "l0name1,name2,name3,name4,name5,0";
								int i;
								char tempBufer[buffersize]="l0";
								char jakisstring[20];
								sprintf(jakisstring, "%d", ConnectedClients);
								//dodajemy liczbę userów do stringa
								strcat(tempBufer,jakisstring);

								for (i=0;i<ConnectedClients;i++){
									strcat(tempBufer,Clients[i]->name);
									strcat(tempBufer,",");
								}
								strcat(tempBufer,"0");
								//printf("%s\n",tempBufer);
								write(fds[SprawdzanyKlient].fd,tempBufer,sizeof(tempBufer)+1);
							break;}
							case 'n':{ // wysyłanie wiadomośći (przekazanie)
								int i=0,j=0;
								char tmpName[20];
								tmpName[0]='\0';

								char tmpMgs[100];
								tmpMgs[0]='\0';

								char TMP[2];
								TMP[0]='\0';

								for (i=2;buffer[i]!='0';i++){		
									TMP[0]= buffer[i];
									TMP[1] = '\0';
									strcat(tmpName, TMP);
								}

								j=i+1;

								for (j; buffer[j] != '\0'; j++)
								{
									TMP[0] = buffer[j];
									TMP[1] = '\0';
									strcat(tmpMgs, TMP);
								}

								ClientName[0]='\0';

								for (i=0;i<ConnectedClients;i++){
									if(Clients[i]->socket==fds[SprawdzanyKlient].fd)
										strcat(ClientName,Clients[i]->name);
								}

								printf("Od %s do %s:\n",ClientName,tmpName);
								printf("\t%s\n",tmpMgs);
								int status=0;

								status = sendMgsTo(tmpMgs,tmpName,ClientName);
								if (status == 0)
								{
									write(fds[SprawdzanyKlient].fd,"d",2); //(d) że dostarczono
								}
								else
								{
									write(fds[SprawdzanyKlient].fd,"e",2); //(e) !(że dostarczono)
								}
							break;}
							case 's':{

							break;}
							case 'h':{
								write(fds[SprawdzanyKlient].fd,"---Help---\n -enter wiadomość do ostatniej osoby\n -l wyswietlenie listy dostępnych klientow\n -h pomoc\n -r odczytanie wiadomości\n -q wyjście\n",148);
							break;}
							default:
							break;
						}//end switch po read
					}//end revents if
				}// end for
			}
	} //end while
}

int sendMgsTo(char *mgs,char *target,char *from){
	int status=-1;
	char Buffer[buffersize]="";
	strcat(Buffer,"n0");
	strcat(Buffer,from);
	strcat(Buffer,"0");
	strcat(Buffer,mgs);
	strcat(Buffer,"\0");

	if (target[strlen(target)-1]=='\n')	
		target[strlen(target)-1]='\0';	

	int i;
	for (i=0;i<ConnectedClients;i++){
		if(strcmp(Clients[i]->name,target)==0){
			status = write(Clients[i]->socket,Buffer,strlen(Buffer)+1);
		}
	}
	if (status < 0) 
		return -1;
	
	return 0;
}

int isRunning(char *name){
	name=name+2;//pominięcie ./
	char wsk[buffersize]="/proc";
	char temp[buffersize]="";
	char tempname[buffersize]="";

	DIR *folder;
	folder = opendir(wsk); // otiweramy /proc
	
	int i;
	for (i=2;i<strlen(name);i++)
		tempname[i-2] = name[i];
	
	if (folder != NULL){
		struct dirent *infoFolder;
		while (infoFolder = readdir(folder)){
		//czyli lecimy po folderach zliczbami potem patrzymy na execa jak jest dowiązany
		// do naszego procesu który chcemy zamknąć to zamykamy.
		//exe zawiera wskaźnik na plik rozruchowy który uruchomiliśmy;
			if (strspn(infoFolder->d_name,"0123456789")==strlen(infoFolder->d_name)){

				strcat(wsk,"/");
				strcat(wsk,infoFolder->d_name);
				char bufer[buffersize]="";
				
				DIR *subFolder;
				
				subFolder = opendir(wsk); // otiweramy /name
				
				
				if (subFolder != NULL){
					
					struct dirent *subInfoFolder;
					
					while (subInfoFolder = readdir(subFolder)){
						if (strcmp(subInfoFolder->d_name,"exe")==0){
							strcat(wsk,"/");
							strcat(wsk,subInfoFolder->d_name);
							readlink(wsk,bufer,buffersize-1);
							if (strstr(bufer,name) != NULL){
								if(atoi(infoFolder->d_name)!= getpid())
									return atoi(infoFolder->d_name);
							}
						}
					}
				}
				wsk[0]='\0';
				strcat(wsk,"/proc");
			}
		};
		
	}
	return -1;
}
