#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <queue>
#include <vector>

#define DEBUG 1

#if DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x) 
#endif

struct cords {
	int x, y;
	bool found=false;
};

class Item {
public:
	Item() {;};
	Item(std::string str, int n) : name(str), value(n) {;};
	void setName() { name = nameTypes[rand() %5] + itemName[rand() %5];};
	void setValue(int n) { value = n;};
	std::string getItem() const
	{ 
		std::stringstream outputFileName;
		std::string str;
		outputFileName << name << " " << value;
		return outputFileName.str();
	};
	int getValue() const { return value; };
private:
	std::string name;
	std::string nameTypes[5] = { "Rare ","Old ", "Awesome ", "Excelent ", "Normal " };
	std::string itemName[5] = { "Ball","Spoon","Sweets","Apple","Shoe" };
	int value=0;
};

class Room {
public:
	Room() {};
	Room(int y, int x, std::string str) : y(y), x(x), description(str) {
		n = NULL;
		s = NULL;
		w = NULL;
		e = NULL;
	};
	void setRoomDescription(std::string str) { description = str; };
	std::string getRoomDescription() const
	{ return description; };
	std::string getItemData() const
	{ return item.getItem(); };
	bool isObject() const
	{ return item.getValue(); };
	Item &getItem() { return item; };
	void addItem() { item.setName(); item.setValue(rand() % 100); };
	void setN(Room *wsk) { n = wsk; };
	void setS(Room *wsk) { s = wsk; };
	void setW(Room *wsk) { w = wsk; };
	void setE(Room *wsk) { e = wsk; };
	int getX() const
	{ return x; };
	int getY() const
	{ return y; };
	void setBeen(int a) { been = a; };
	bool getBeen() const
	{ return been; };
	Room *getN() const
	{return n;};
	Room *getS() const
	{return s;};
	Room *getW() const
	{return w;};
	Room *getE() const
	{return e;};
private:
	std::string description;
	int y, x;
	bool been=false;
	Room *n, *s, *w, *e;
	Item item;
};

std::queue < cords > Q;

class Map {
public:
	Map(){
		LOG("Konstruktor")
			for (int i = 0; i < (sizeX*size); ++i)
				RoomArray[i] = new Room*[sizeX];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7;j++)
				if (!((i == 0 && j == 2) || (i == 0 && j == 4) ||
					  (i == 1 && j == 0) || (i == 1 && j == 6) ||
					  (i == 2 && j == 2) || (i == 2 && j == 4))) {
					std::stringstream outputFileName;
					outputFileName <<"Room " << i << j <<'\0';
					Room *room = new Room(i,j, outputFileName.str());
					RoomArray[i][j] = room;
				}
				else{
					RoomArray[i][j] = NULL;
				}
			}
		//dodanie 3 losowych przedmiotów do pokojów.
		for (int k = 0; k < 3;) {
			int i, j;
			i = rand() % 2; // iloœæ wierszy
			j = rand() % 6; // iloœæ kolumn
 			if (!((i == 0 && j == 2) || (i == 0 && j == 4) || (i == 1 && j == 0) || (i == 1 && j == 6) || (i == 2 && j == 2) || (i == 2 && j == 4))) {
				if (!RoomArray[i][j]->isObject()) {
					RoomArray[i][j]->addItem();
					item[k].x = i;
					item[k].y = j;
					k++;
				}
			}
		}
		bindRoomNS(RoomArray[0][1], RoomArray[1][1]); 
		bindRoomNS(RoomArray[1][1], RoomArray[2][1]);
		bindRoomNS(RoomArray[1][3], RoomArray[2][3]);
		bindRoomNS(RoomArray[0][3], RoomArray[1][3]);
		bindRoomNS(RoomArray[0][5], RoomArray[1][5]);
		bindRoomNS(RoomArray[1][5], RoomArray[2][5]);
		bindRoomWE(RoomArray[0][0], RoomArray[0][1]);
		bindRoomWE(RoomArray[2][0], RoomArray[2][1]);
		bindRoomWE(RoomArray[1][1], RoomArray[1][2]);
		bindRoomWE(RoomArray[1][2], RoomArray[1][3]);
		bindRoomWE(RoomArray[1][3], RoomArray[1][4]);
		bindRoomWE(RoomArray[1][4], RoomArray[1][5]);
		bindRoomWE(RoomArray[0][5], RoomArray[0][6]);
		bindRoomWE(RoomArray[2][5], RoomArray[2][6]);
	};
	Map(int number) : size(number){
		LOG("Konstruktor wiekszy")
			RoomArray = new Room**[sizeY*size];
			for (int i = 0; i < (sizeY*size); i++)
				RoomArray[i] = new Room*[sizeX*size];

		std::vector < bool > Y0; // góra i dó³ s¹ takie same
		std::vector < bool > Y1; // œrodek jest ró¿ny
		std::vector < bool > ConnectY; //wektor do NS kiedy ³¹czyæ.
		std::vector < bool > ConnectX; //wektor do WE kiedy ³¹czyæ.
		std::vector < int > axeX;
		std::vector < int > axeY;

		for (int i = 0; i < size; i++) {
			Y0.push_back(true);
			Y0.push_back(true);
			Y0.push_back(false);
			Y0.push_back(true);
			Y0.push_back(false);
			Y0.push_back(true);
			Y0.push_back(true);

			Y1.push_back(false);
			Y1.push_back(true);
			Y1.push_back(true);
			Y1.push_back(true);
			Y1.push_back(true);
			Y1.push_back(true);
			Y1.push_back(false);

			ConnectY.push_back(true);
			ConnectY.push_back(false);
			ConnectY.push_back(false);

			ConnectX.push_back(true);
			ConnectX.push_back(false);
			ConnectX.push_back(false);
			ConnectX.push_back(false);
			ConnectX.push_back(false);
			ConnectX.push_back(false);
			ConnectX.push_back(false);

			axeX.push_back(7*(i));
			axeY.push_back(3*(i));
		}


		int j, i;
		//pêtla dodaj¹ca roomy
		for (i = 0; i < 3*number; i++) {   // wiersze
			for (j = 0; j < 7 * number; j++) { // kolumny
				if (isValid(Y0, Y1, j, i)) {
					std::stringstream outputFileName;
					outputFileName << "Room " << i << " " << j << '\0';
					Room *room = new Room(i, j, outputFileName.str());
					RoomArray[i][j] = room;
				}
				else {
					RoomArray[i][j] = NULL;
				}
				if (j>0)
				if (ConnectX[j] && RoomArray[i][j] != NULL) {
					bindRoomWE(RoomArray[i][j-1], RoomArray[i][j]);
				}
				if (i>0)
				if (RoomArray[i-1][j] != NULL && i > 0 && ConnectY[i]){
					bindRoomNS(RoomArray[i-1][j], RoomArray[i][j]);
				}
			}
		}
		//dodanie 3 losowych przedmiotów do pokojów.
		for (int k = 0; k < 3;) {
			int i, j;
			i = rand() % ((sizeY*size)-1); // iloœæ wierszy
			j = rand() % ((sizeX*size)-1); // iloœæ kolumn
			if (isValid(Y0,Y1,j,i)) {
				if (!RoomArray[i][j]->isObject()) {
					RoomArray[i][j]->addItem();
					item[k].x = i;
					item[k].y = j;
					k++;
				}
			}
		}
		int l = 0;
		int k = 0;
		for (int j = 0; j < size; j++) {
			for (int i = 0; i < size; i++) {
				bindRoomNS(RoomArray[0 + axeY[i]][1 + axeX[j]], RoomArray[1 + axeY[i]][1 + axeX[j]]);
				bindRoomNS(RoomArray[1 + axeY[i]][1 + axeX[j]], RoomArray[2 + axeY[i]][1 + axeX[j]]);
				bindRoomNS(RoomArray[1 + axeY[i]][3 + axeX[j]], RoomArray[2 + axeY[i]][3 + axeX[j]]);
				bindRoomNS(RoomArray[0 + axeY[i]][3 + axeX[j]], RoomArray[1 + axeY[i]][3 + axeX[j]]);
				bindRoomNS(RoomArray[0 + axeY[i]][5 + axeX[j]], RoomArray[1 + axeY[i]][5 + axeX[j]]);
				bindRoomNS(RoomArray[1 + axeY[i]][5 + axeX[j]], RoomArray[2 + axeY[i]][5 + axeX[j]]);
				bindRoomWE(RoomArray[0 + axeY[i]][0 + axeX[j]], RoomArray[0 + axeY[i]][1 + axeX[j]]);
				bindRoomWE(RoomArray[2 + axeY[i]][0 + axeX[j]], RoomArray[2 + axeY[i]][1 + axeX[j]]);
				bindRoomWE(RoomArray[1 + axeY[i]][1 + axeX[j]], RoomArray[1 + axeY[i]][2 + axeX[j]]);
				bindRoomWE(RoomArray[1 + axeY[i]][2 + axeX[j]], RoomArray[1 + axeY[i]][3 + axeX[j]]);
				bindRoomWE(RoomArray[1 + axeY[i]][3 + axeX[j]], RoomArray[1 + axeY[i]][4 + axeX[j]]);
				bindRoomWE(RoomArray[1 + axeY[i]][4 + axeX[j]], RoomArray[1 + axeY[i]][5 + axeX[j]]);
				bindRoomWE(RoomArray[0 + axeY[i]][5 + axeX[j]], RoomArray[0 + axeY[i]][6 + axeX[j]]);
				bindRoomWE(RoomArray[2 + axeY[i]][5 + axeX[j]], RoomArray[2 + axeY[i]][6 + axeX[j]]);
			}
		}
		////////
	};
	void deleteMap() {
		LOG("destruktor");
		int i = 0;
		int j = 0;
		//usówanie zaalokowanych wartoœci w tablicy
		for ( i = 0; i < sizeY*size; i++) {
			for ( j = 0; j < sizeX*size; j++)
				delete RoomArray[i][j];
			delete []RoomArray[i];
		}
		delete RoomArray;

		for (int i = 0; i < sizeY*size; i++)
				delete roomTemplate[i];
		delete []roomTemplate;
	};
	void setRoom(Room *&room, int x, int y) { this->RoomArray[x][y] = room; };
	Room *&getRoom(int i, int j) { return RoomArray[i][j]; };
	void drawRoom(int showItem) {
			for (int i = 0; i < sizeY*size; i++) {
				for (int j = 0; j < sizeX*size; j++) {
					if (RoomArray[i][j]){
						if (showItem && RoomArray[i][j]->isObject()) {
							std::cout << RoomArray[i][j]->getItemData()[0];
						}else {
						std::cout << "#";
						}
					}
					else
					{
						std::cout << "X";
					}			
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
	};
	void findWay() {
		//przygotowanie tablicy pomocniczej do poruszania siê. oraz negowanie jakichkolwiek odwiedzin w aktualniej tablicy stanów.
		roomTemplate = new int*[sizeY*size];
		for (int i = 0; i < (sizeY*size); i++)
			roomTemplate[i] = new int[sizeX*size];

		for (int i = 0; i < sizeY; i++) {
			for (int j = 0; j < sizeX; j++) {
				if (RoomArray[i][j] != NULL) {
					RoomArray[i][j]->setBeen(false);
					roomTemplate[i][j] = 0;
				}
				else {
					roomTemplate[i][j] = -1;
				}
			}
		}
		//znajdowanie najkrótszej drogi ~~~~~~~~~~~~Algorytm Dijkstry~~~~~~~~~~~~~~~

		int o=0; // iloœæ elementów do wyszukania.
		cords s, v, w, tmp;
		s.x = 0;		//pocz¹tek od którego zaczynamy nasze poszukiwania.
		s.y = 0;		//
		Q.push(s);		//wstawiamy nasz pocz¹tek do kolejki Q
		while(o<3){
			while (!Q.empty()) { //puki kolejka nie jest pusta wykonujemy kroki
				v = Q.front();	 //pobieramy nasz element z kolejki i sprawdzamy gdzie mo¿emy dojœæ z niego.
				Q.pop();// warunek na pierwsze pole;
				if (((v.x == item[0].x && v.y == item[0].y) && !item[0].found) || ((v.x == item[1].x && v.y == item[1].y) && !item[1].found) || ((v.x == item[2].x && v.y == item[2].y) && !item[2].found)) {
						if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found)) {
							item[0].found = true;
							setRoomTemplateFalse();
							o++;
							Q.push(w);
							break;
						}
						if (((w.x == item[1].x && w.y == item[1].y) && !item[1].found)) {
							item[1].found = true;
							setRoomTemplateFalse();
							o++;
							Q.push(w);
							break;
						}
						if (((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
							item[2].found = true;
							setRoomTemplateFalse();
							o++;
							Q.push(w);
							break;
						}
				}
				if (RoomArray[v.x][v.y]->getN() != NULL) {
					w.y = RoomArray[v.x][v.y]->getN()->getX();
					w.x = RoomArray[v.x][v.y]->getN()->getY();
					if (!RoomArray[w.x][w.y]->getBeen()) {
						roomTemplate[w.x][w.y] = roomTemplate[v.x][v.y] + 1;
						if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found) || ((w.x == item[1].x && w.y == item[1].y) && !item[1].found) || ((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
							if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found)) {
								item[0].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
							if (((w.x == item[1].x && w.y == item[1].y) && !item[1].found)) {
								item[1].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
							if (((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
								item[2].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
						}
						else {
							Q.push(w);
							RoomArray[v.x][v.y]->setBeen(1);
						}
					}
				}
				if (RoomArray[v.x][v.y]->getS() != NULL)
				{
					w.y = RoomArray[v.x][v.y]->getS()->getX();
					w.x = RoomArray[v.x][v.y]->getS()->getY();
					if (!RoomArray[w.x][w.y]->getBeen()) {
						roomTemplate[w.x][w.y] = roomTemplate[v.x][v.y] + 1;
						if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found) || ((w.x == item[1].x && w.y == item[1].y) && !item[1].found) || ((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
							if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found)) {
								item[0].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
							if (((w.x == item[1].x && w.y == item[1].y) && !item[1].found)) {
								item[1].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
							if (((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
								item[2].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
						}
						else {
							Q.push(w);
							RoomArray[v.x][v.y]->setBeen(1);
						}
					}
				}
				if (RoomArray[v.x][v.y]->getW() != NULL) {
					w.y = RoomArray[v.x][v.y]->getW()->getX();
					w.x = RoomArray[v.x][v.y]->getW()->getY();
					if (!RoomArray[w.x][w.y]->getBeen()) {
						roomTemplate[w.x][w.y] = roomTemplate[v.x][v.y] + 1;
						if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found) || ((w.x == item[1].x && w.y == item[1].y) && !item[1].found) || ((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
							if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found)) {
								item[0].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
							if (((w.x == item[1].x && w.y == item[1].y) && !item[1].found)) {
								item[1].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
							if (((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
								item[2].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
						}
						else {
							Q.push(w);
							RoomArray[v.x][v.y]->setBeen(1);
						}
					}
				}
				if (RoomArray[v.x][v.y]->getE() != NULL) {
					w.y = RoomArray[v.x][v.y]->getE()->getX();
					w.x = RoomArray[v.x][v.y]->getE()->getY();
					if (!RoomArray[w.x][w.y]->getBeen()) {
						roomTemplate[w.x][w.y] = roomTemplate[v.x][v.y] + 1;
						if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found) || ((w.x == item[1].x && w.y == item[1].y) && !item[1].found) || ((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
							if (((w.x == item[0].x && w.y == item[0].y) && !item[0].found)) {
								item[0].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
							if (((w.x == item[1].x && w.y == item[1].y) && !item[1].found)) {
								item[1].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
							if (((w.x == item[2].x && w.y == item[2].y) && !item[2].found)) {
								item[2].found = true;
								setRoomTemplateFalse();
								o++;
								while (!Q.empty()) { Q.pop(); };
								Q.push(w);
								break;
							}
						}
						else {
							Q.push(w);
							RoomArray[v.x][v.y]->setBeen(1);
						}
					}
				}
			}
			if (o == 3) {tmp = Q.front();}
		}
			std::cout << "Minimalna liczba krokow to :" << roomTemplate[tmp.x][tmp.y] << std::endl;
	};
private:
	bool isValid(std::vector < bool > Y0, std::vector < bool > Y1, int x, int y) {
			for (int j = 1; j < (size*3); j+=3)
				if (y == j) {
					return Y1[x];
				}
			return Y0[x];
	};
	int sizeX = 7;
	int sizeY = 3;
	int size = 1;
	int **roomTemplate;
	Room ***RoomArray;
	cords item[3];
	void setRoomTemplateFalse() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				if (RoomArray[i][j] != NULL) {
					RoomArray[i][j]->setBeen(false);
				}
			}
		}
	};
	void bindRoomNS(Room *room1, Room *room2) { room2->setN(room1); room1->setS(room2); };
	void bindRoomWE(Room *room1, Room *room2) { room2->setW(room1);	room1->setE(room2); };
};

class player { //TODO: funkcja poruszania siê po pokojach.
public:
	void setItemCount() { ItemCount++; };
	void move(Map map1) {
		int k = 0;
		Room *room1 = map1.getRoom(0, 0);
		for (int i = 0; i < 19; i++) {
			if (ItemCount == 3)break;
			if (TestArray[i] == 'n') {
				if (room1->isObject() && !room1->getBeen()) {
					std::cout << "Znaleziono przedmiot : " << room1->getItemData() << " po " << i << " probach. " << std::endl;
					room1->setBeen(1);
					ItemCount++;
				}
				room1 = room1->getN();
				continue;
			}
			if (TestArray[i] == 's') {
				if (room1->isObject() && !room1->getBeen()) {
					std::cout << "Znaleziono przedmiot : " << room1->getItemData() << " po " << i << " probach. "<< std::endl;
					room1->setBeen(1);
					ItemCount++;
				}
				room1 = room1->getS();
				continue;
			}
			if (TestArray[i] == 'w') {
				if (room1->isObject() && !room1->getBeen()) {
					std::cout << "Znaleziono przedmiot : " << room1->getItemData() << " po " << i << " probach. "<< std::endl;
					room1->setBeen(1);
					ItemCount++;
				}
				room1 = room1->getW();
				continue;
			}
			if (TestArray[i] == 'e') {
				if (room1->isObject() && !room1->getBeen()){
					std::cout << "Znaleziono przedmiot : " << room1->getItemData() << " po " << i << " probach. "<< std::endl;
					room1->setBeen(1);
					ItemCount++;
				}
				room1 = room1->getE();
				continue;
			}

		}
		
	};
private: //znaleziono przedmiot?, które pokoje ju¿ odwiedziliœmy 
	std::string isObject(Room *room) {room->getItemData();};
	int ItemCount;
	char TestArray[20] = { 'e','s','s','w','e','n','e','e','s','n','n','s','e','e','n','e','w','s','s','e'}; // done.
};

int main()
{
	srand(time(NULL));
	try{
		Map map(1);
		player player1;

		map.drawRoom(0);
		player1.move(map);
		map.drawRoom(1);

		map.findWay();
		map.deleteMap();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	};

	system("PAUSE");

	return 0;
}