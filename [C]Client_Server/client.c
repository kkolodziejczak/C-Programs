#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // OPTGET
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <poll.h>
#include <sys/ioctl.h>


#define buffersize 100
#define CERROR "\x1B[31m"
#define RESET "\033[0m"

extern char *optarg;
extern int optind, opterr, optopt;

struct user {
	char *name;
	int socket;
	int connected;
};

void czytaj(char type);
int sendMgs(char *mgs, char type);
int sendMgsTo(char *mgs,char *who);

int PortInt=0;
char *PortChar=NULL;
char *AdressChar=NULL;

char *ClientName;
int ServerSocket=0;

struct user **Clients=NULL;
int ammount = 0;


int main(int argc, char **argv){

	int ret=0;
	int flagP = 0 ,flagA = 0,flagN=0;

	while((ret = getopt(argc, argv, "p:n:a:"))!=-1){
		switch(ret){
			case 'p':
				flagP = 1;
				PortChar = optarg;
				PortInt = atoi(PortChar);
			break;
			case 'a':
				flagA = 1;
				AdressChar = optarg;
				//inet_pton - convert IPv4 and IPv6 addresses from text to binary form
			break;
			case 'n':
				ClientName = optarg;
				flagN = 1;
			break;
			default:
			break;
		}//Switch => flagi
	}//while => getopt

	if(flagP==1 && flagA ==1 && flagN==1)
	{
		int n,count,flagaa =1;
		char buffer[256];
		char LastUserName[30]="",TargetUserName[40]="";
	    struct sockaddr_in serv_addr;
	    struct hostent *server=NULL;
		

	    ServerSocket = socket(AF_INET, SOCK_STREAM, 0);	
			if (ServerSocket < 0) {
				printf(CERROR"ERROR opening socket"RESET);
				exit(1);
			}
			
	    server = gethostbyname(AdressChar);
			if (server == NULL) {
				printf(CERROR"ERROR, no such host\n"RESET);
				exit(1);
			}
		
	    bzero((char *) &serv_addr, sizeof(serv_addr));
		bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
			 
	    serv_addr.sin_family = AF_INET;		 // ustawiamy protokół ipv4
	    serv_addr.sin_port = htons(PortInt); // ustawiamy port 
		
	    if (connect(ServerSocket,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){ //łączymy się 
			printf(CERROR"ERROR connecting\n"RESET);
			return 1;
		} 
		
		system ("clear");
		printf("Klient uruchomiony!\n");
		printf("Port:\t%s\n",PortChar);
		printf("Adres:\t%s\n",AdressChar);
		printf("Nick:\t%s\n",ClientName);
		printf("\n\n---Help---\n -m wysłanie wiadomści \n -enter wiadomość do ostatniej osoby\n -l wyswietlenie listy dostępnych klientow\n -h pomoc\n -r odczytanie wiadomości\n -q wyjście\n\n\n");
			
		sendMgs(ClientName,'s'); //setup wysłanie do servera wiadomości o nazwie klienta
		
		czytaj('d');
		
		
		while(flagaa){	

			printf("->");
			bzero(buffer,256);
			fgets(buffer,255,stdin);		
				
			switch(buffer[0]){
				case 10:{ // ascii[10] == [\n] ostatnia osoba do której pisalimy
					do{
						ioctl(ServerSocket, FIONREAD, &count);
						//printf("cout: %d\n",count);
						if (count > 0)
							czytaj('n');
					}while(count < 0);
					
					if (strlen(LastUserName)>1){
					
						printf("Piszesz do %s:\n",LastUserName);
						//fgets(LastUserName,255,stdin);
						printf("wiadomość:");
						fgets(buffer,255,stdin);
						
						sendMgsTo(buffer,LastUserName);
						czytaj('d');
						}
					else
						printf("Nie wysłano jeszcze wadomości do nikogo.\n");
				break;}
				case 'm':{// wysłanie wiadomości do wybranego klienta
				
					write(ServerSocket,"l0",3);
					czytaj('l');
					
					printf("Podaj nr osoby:");
					fgets(TargetUserName,255,stdin);
					printf("wiadomość:");
					fgets(buffer,255,stdin);
					
					
					if(strlen(TargetUserName)==2){
						int numer = atoi(TargetUserName);
						TargetUserName[0]='\0';
						strcat(TargetUserName,Clients[numer-1]->name);
					}
					
					LastUserName[0]='\0';
					strcat(LastUserName,TargetUserName);
					
					if (TargetUserName != NULL){
						sendMgsTo(buffer,TargetUserName);
						czytaj('d');
					}
					else
						printf("Nie podano użytkownika.\n");	
				break;}
				case 'l':{ // oczekiwanie na listę użytkowników
					write(ServerSocket,"l0",3);
					czytaj('l');
				break;}
				case 'h':{ // oczekiwanie na helpa
					printf("\n\n---Help---\n -m wysłanie wiadomści \n -enter wiadomość do ostatniej osoby\n -l wyswietlenie listy dostępnych klientow\n -h pomoc\n -r odczytanie wiadomości\n -q wyjście\n\n\n");
				break;}
				case 'q':{ // wysłanie sygnału o zakończeniu pracy klienta
					write(ServerSocket,"q0",3);
					flagaa=0;
					continue;
				break;}	
				case 'r':{ // odczytywanie wiadomości
					do{
						ioctl(ServerSocket, FIONREAD, &count);
						//printf("cout: %d\n",count);
						if (count > 0)
							czytaj('n');
					}while(count < 0);
				break;}	
				default:
				break;
			} //end write switch
			
		}//end while
	}//end main if
return 0;
}

void czytaj(char type){

	char buffer[256];
	
	do{
	
		bzero(buffer,256);
		read(ServerSocket,buffer,255);//czekamy na odpowiedź od servera.
		switch(buffer[0]){
			case 't':{
				printf("Server został wyłączony!\n");
				exit(0);
				break;}
			case 'l':{ //Klient odpowiada na l(wyświetlając liste)
				int k=0,i=0,j=0;
				if(ammount >0){
					if (Clients != NULL){
						for (k = 0; k < ammount; k++){
							//printf("%d\n",k);
							free(Clients[k]);
						}
					}
				}

				ammount= buffer[2] - 48;
			
				char TMP[2];

					Clients = (struct user **)malloc(sizeof(struct user *)*ammount);
					
						i = 3; // i = 2 ponieważ pomijamy oznaczenie wiadomości [l0treść]

						//					 0|1|2|3|
						//char buffer[50] = "l|0|n|a|me1,name2,name3,name4,name5,0";
						for (j = 0; buffer[i] != '0'; j++) 
						{
							struct user *temp;
							temp = (struct user*)malloc(sizeof(struct user)); // tworzymy nowego usera

							char tempchar[20]="";

							for (i; buffer[i] != ','; i++) { //odczytujemy jego imię
								TMP[0] = buffer[i];
								TMP[1] = '\0';
								strcat(tempchar, TMP);
							}
							
							temp->name = malloc(sizeof(char)*strlen(tempchar)+1); //alokujemy pamięć na jego imię
							temp->name[0]='\0';
							strcat(temp->name, tempchar); // przypisujemy jego imię
							
							temp->connected = 1;
							temp->socket = 0;
							i++; //pominięcie ,
							
							Clients[j] = temp; //odłożenie na grupę.
						}
						
						printf("Lista dostępnych klientów:\n");
						
						for(k=0;k<ammount;k++)
							printf("\t%d. %s\n",k+1,Clients[k]->name);
						
				
			break;}
			case 'n':{ //Otrzymana wiadomość od nadawcy

				int i=0,j=0;
				
				char tmpName[20];//Imię nadawcy
				tmpName[0]='\0';
				
				char tmpMgs[256];//wiadomość
				tmpMgs[0]='\0';

				char TMP[2];
				TMP[0]='\0';
				
				//wyciągamy imię z wiadomości
				for (i=2;buffer[i]!='0';i++){		
					TMP[0]= buffer[i];
					TMP[1] = '\0';
					strcat(tmpName, TMP);
				}
				
				j=i+1; // pomijamy znak 0 oddzielający adresata z tekstem
				
				//wyciągamy treść z wiadomości
				for (j; buffer[j] != '\0'; j++)
				{
					TMP[0] = buffer[j];
					TMP[1] = '\0';
					strcat(tmpMgs, TMP);
				}
				//problemy z wczytaniem znaku [\n] ustawianie ostniego znaku na znak końca słowa [\0]
					tmpName[strlen(tmpName)]='\0';	
					tmpMgs[strlen(tmpMgs)-1]='\0';	
					
				//wyświetlnie otrzymanej wiadomośi
				printf("Wiadomość od %s:\n",tmpName);
				printf("\t\"%s\"\n",tmpMgs);
				
			break;}
			case 'd':{ //obsługa dostarczenia wiadomości
				//printf("Wiadomość dostarczono!\n");
			break;}
			case 'e':{ //obsługa dostarczenia wiadomości
				printf("Wiadomość"CERROR" nie"RESET" została dostarczona!\n Sprawdź listę dostępnych użytkowników.\n");
				buffer[0]='d';
			break;}
			case 'u':{
				printf(CERROR"Dany login został już zajęty.\n"RESET);
				
				printf("Podaj nowy Login:\n");
				fgets(ClientName,255,stdin);
				printf("New Username %s\n",ClientName);
				sendMgs(ClientName,'s'); //setup wysłanie do servera wiadomości o nazwie klienta
				czytaj('d'); 
				
				buffer[0]='d';
			break;}
			default:
			break;
		}//end read switch
	}while(buffer[0] != type);
}

int sendMgs(char *mgs, char type){

	int status;
	char Buffer[buffersize]="";
	
	Buffer[0] = type;
	Buffer[1] = '0';
	
	strcat(Buffer,mgs);
	strcat(Buffer,"0");
	
	status = write(ServerSocket,Buffer,strlen(Buffer));
		if (status < 0) 
			return -1;
		
	return 0;
}

int sendMgsTo(char *mgs,char *who){

	int status;
	char Buffer[buffersize]="";
	
	strcat(Buffer,"n0");
	strcat(Buffer,who);
	
	strcat(Buffer,"0");
	strcat(Buffer,mgs);
	//strcat(Buffer,"0");
		
	//printf("mgs:%s\n",Buffer);
	
	status = write(ServerSocket,Buffer,strlen(Buffer));
		if (status < 0) 
			return -1;
		
	return 0;
}
