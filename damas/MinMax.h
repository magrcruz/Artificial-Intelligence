// MinMax.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <string>
using namespace std;
// TODO: Reference additional headers your program requires here.
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
struct Nodo {
	int table[64];
	int player[12], computer[12];
	int available_chips_jugador= 12;
	int available_chips_computadora = 12;

	int size = 0;
	Nodo* children = 0, * next = 0;
	Nodo() {
		int base[64] = {
			-9,  0,-10,  0,-11,  0,-12,  0,
			0, -5,  0, -6,  0, -7,  0, -8,
			-1,  0, -2,  0, -3,  0, -4,  0,
			 0,  0,  0,  0,  0,  0,  0,  0,
			 0,  0,  0,  0,  0,  0,  0,  0,
			 0,  1,  0,  2,  0,  3,  0,  4,
			 5,  0,  6,  0,  7,  0,  8,  0,
			 0,  9, 0,  10, 0,  11, 0,  12
		};
		int starterPlayer[12]   = { 41,43,45,47, 48,50,52,54, 57,59,61,63 };
		int starterComputer[12] = { 16,18,20,22, 9,11,13,15, 0,2,4,6 };
		for (int* p = table, *q = base; p < table + 64; p++, q++) *p = *q;
		for (int* p = player, *q = starterPlayer; p < player + 12; p++, q++) *p = *q;
		for (int* p = computer, *q = starterComputer; p < computer + 12; p++, q++) *p = *q;
	}
	Nodo(Nodo& n) {
		available_chips_jugador = n.available_chips_jugador;
		available_chips_computadora = n.available_chips_computadora;
		for (int* p = table, *q = n.table; p < table + 64; p++, q++) *p = *q;
		for (int* p = player, *q = n.player; p < player + 12; p++, q++) *p = *q;
		for (int* p = computer, *q = n.computer; p < computer + 12; p++, q++) *p = *q;
	}
	Nodo(int* tab,int *play, int *comp) {
		for (int* p = table, *q = tab; p < table + 64; p++, q++) *p = *q;
		for (int* p = player, *q = play; p < player + 12; p++, q++) *p = *q;
		for (int* p = computer, *q = comp; p < computer + 12; p++, q++) *p = *q;
	}
};

class Tree {
public:
	Nodo* root;
	int deep;
	bool persona;// Ir actualizando
	/*
	 Valores que puede tener la variable order player
	 0 -> Computadora
	 1 -> Persona
	*/
	///Persona
	bool JcomprobarJugada1(Nodo* nodito, int pos) {
		////Jugada 1 mover la ficha a la derecha
		if (pos - 7 < 0 || pos % 8 == 7) return false;// modulo para no salirse de col y comparacion para no salir de la parte de abajo
		if (nodito->table[pos - 7] == 0) return true;
		else return false;
	}
	bool JcomprobarJugada2(Nodo* nodito, int pos) {
		////Jugada 2 mover a la derecha y comer
		if (pos - 14 < 0||pos - 7 < 0 || pos % 8 == 7) return false;// modulo para no salirse de col y comparacion para no salir de la parte de abajo
		if (nodito->table[pos - 7] < 0 && nodito->table[pos - 14] == 0) return true;
		else return false;
	}
	bool JcomprobarJugada3(Nodo* nodito, int pos) {
		////Jugada 3 mover a la izquierda
		if (pos - 9 < 0 || pos % 8 == 0) return false;// modulo para no salirse de col y comparacion para no salir de la parte de abajo
		if (nodito->table[pos - 9] == 0) return true;
		else return false;
	}
	bool JcomprobarJugada4(Nodo* nodito, int pos) {
		////Jugada 3 mover a la izquierda y comer 
		if (pos - 18 < 0 || pos - 9 < 0 || pos % 8 == 0 || pos % 8 == 1) return false;// modulo para no salirse de col y comparacion para no salir de la parte de abajo
		if (nodito->table[pos - 9]<0 && nodito->table[pos - 18] == 0) return true;
		else return false;
	}

	///Computer
	bool CcomprobarJugada1(Nodo* nodito, int pos) {
		////Jugada 1 mover la ficha a la derecha
		if (pos % 8 == 7 || pos + 9 > 64) return false;// modulo para no salirse de col y comparacion para no salir de la parte de abajo
		if (nodito->table[pos + 9] == 0) return true;
		else return false;
	}
	bool CcomprobarJugada2(Nodo* nodito, int pos) {
		////Jugada 2 mover a la derecha y comer
		if (pos % 8 == 7 || pos + 9 > 64 || pos + 18 > 64) return false;// modulo para no salirse de col y comparacion para no salir de la parte de abajo
		if (nodito->table[pos + 9]>0 && nodito->table[pos + 18] == 0) return true;
		else return false;
	}
	bool CcomprobarJugada3(Nodo* nodito, int pos) {
		////Jugada 3 mover a la izquierda
		if (pos == 0 || pos % 8 == 0 || pos + 9 > 64) return false;// modulo para no salirse de col y comparacion para no salir de la parte de abajo
		if (nodito->table[pos + 7] == 0) return true;
		else return false;
	}
	bool CcomprobarJugada4(Nodo* nodito, int pos) {
		////Jugada 4 mover a la izquierda y comer 
		if (pos == 0 || pos % 8 == 0 || pos + 7 > 64 || pos + 14 > 64) return false;// modulo para no salirse de col y comparacion para no salir de la parte de abajo
		if (nodito->table[pos + 7]>0 && nodito->table[pos + 14] == 0) return true;
		else return false;
	}

	///Jugador make_movement
	void makeMovementJ1(Nodo* ptr, int i) {
		///Jugada 1 mover la ficha a la derecha
		/// Debido a que no come la cantidad de fichas se mantiene
		int pos_ficha = ptr->player[i];// Saca del array de las fichas en posicion del tablero se encuentra
		ptr->table[pos_ficha] = 0;//Posicion actual de la ficha se coloca como vacia
		ptr->table[pos_ficha - 7] = i + 1;//Se actualiza la nueva posicion de la ficha, i+1 ya que las fichas van de 1-12
		ptr->player[i] = pos_ficha - 7;/// En el array de fichas se guarda la nueva pos en el tablero
	}

	void makeMovementJ2(Nodo* ptr, int i) {
		///Jugada 2 mover la ficha a la derecha y comer 
		int pos_ficha = ptr->player[i];// Saca del array de las fichas en posicion del tablero se encuentra
		ptr->table[pos_ficha] = 0;//Posicion actual de la ficha se coloca como vacia
		int ficha_oponente = -1 * (ptr->table[pos_ficha - 7]);
		ptr->table[pos_ficha - 7] = 0;//Se coloca cero ya que es la ficha eliminada del otro jugador
		ptr->table[pos_ficha - 14] = i + 1;//Se actualiza la nueva posicion de la ficha, i+1 ya que las fichas van de 1-12
		ptr->player[i] = pos_ficha - 14;/// En el array de fichas se guarda la nueva pos en el tablero
		ptr->computer[ficha_oponente - 1] = -1;/// La ficha eliminada se le coloca -1
		ptr->available_chips_computadora--;
		///How to change available chips of a specific player?

	}

	void makeMovementJ3(Nodo* ptr, int i) {
		///Jugada 3 mover la ficha a la izquierda
		/// Debido a que no come la cantidad de fichas se mantiene
		int pos_ficha = ptr->player[i];// Saca del array de las fichas en posicion del tablero se encuentra
		ptr->table[pos_ficha] = 0;//Posicion actual de la ficha se coloca como vacia
		ptr->table[pos_ficha - 9] = i + 1;//Se actualiza la nueva posicion de la ficha, i+1 ya que las fichas van de 1-12
		ptr->player[i] = pos_ficha - 9;/// En el array de fichas se guarda la nueva pos en el tablero
	}

	void makeMovementJ4(Nodo* ptr, int i) {
		///Jugada 2 mover la ficha a la derecha y comer 
		int pos_ficha = ptr->player[i];// Saca del array de las fichas en posicion del tablero se encuentra
		ptr->table[pos_ficha] = 0;//Posicion actual de la ficha se coloca como vacia
		int ficha_oponente = -1 * (ptr->table[pos_ficha - 9]);
		ptr->table[pos_ficha - 9] = 0;//Se coloca cero ya que es la ficha eliminada del otro jugador
		ptr->table[pos_ficha - 18] = i + 1;//Se actualiza la nueva posicion de la ficha, i+1 ya que las fichas van de 1-12
		ptr->player[i] = pos_ficha - 18;/// En el array de fichas se guarda la nueva pos en el tablero
		ptr->computer[ficha_oponente - 1] = -1;/// La ficha eliminada se le coloca -1
		ptr->available_chips_computadora--;
		///How to change available chips of a specific player?
	}

	///Computer make_movement

	void makeMovementC1(Nodo* ptr, int i) {
		///Jugada 1 mover la ficha a la derecha
		/// Debido a que no come la cantidad de fichas se mantiene
		int pos_ficha = ptr->computer[i];// Saca del array de las fichas en posicion del tablero se encuentra
		ptr->table[pos_ficha] = 0;//Posicion actual de la ficha se coloca como vacia
		ptr->table[pos_ficha + 9] = (i + 1)*-1;//Se actualiza la nueva posicion de la ficha, i+1 ya que las fichas van de 1-12
		ptr->computer[i] = pos_ficha + 9;/// En el array de fichas se guarda la nueva pos en el tablero
	}

	void makeMovementC2(Nodo* ptr, int i) {
		///Jugada 2 mover la ficha a la derecha y comer 
		int pos_ficha = ptr->computer[i];// Saca del array de las fichas en posicion del tablero se encuentra
		ptr->table[pos_ficha] = 0;//Posicion actual de la ficha se coloca como vacia
		int ficha_oponente = (ptr->table[pos_ficha + 9]);
		ptr->table[pos_ficha + 9] = 0;//Se coloca cero ya que es la ficha eliminada del otro jugador
		ptr->table[pos_ficha + 18] = (i + 1) * -1;//Se actualiza la nueva posicion de la ficha, i+1 ya que las fichas van de 1-12
		ptr->computer[i] = pos_ficha + 18;/// En el array de fichas se guarda la nueva pos en el tablero
		ptr->player[ficha_oponente - 1] = -1;/// La ficha eliminada se le coloca -1
		ptr->available_chips_jugador--;
		///How to change available chips of a specific player?

	}

	void makeMovementC3(Nodo* ptr, int i) {
		///Jugada 3 mover la ficha a la izquierda
		/// Debido a que no come la cantidad de fichas se mantiene
		int pos_ficha = ptr->computer[i];// Saca del array de las fichas en posicion del tablero se encuentra
		ptr->table[pos_ficha] = 0;//Posicion actual de la ficha se coloca como vacia
		ptr->table[pos_ficha + 7] = (i + 1) * -1;//Se actualiza la nueva posicion de la ficha, i+1 ya que las fichas van de 1-12
		ptr->computer[i] = pos_ficha + 7;/// En el array de fichas se guarda la nueva pos en el tablero

	}

	void makeMovementC4(Nodo* ptr, int i) {
		///Jugada 4 mover la ficha a la izquierda y comer 
		int pos_ficha = ptr->computer[i];// Saca del array de las fichas en posicion del tablero se encuentra
		ptr->table[pos_ficha] = 0;//Posicion actual de la ficha se coloca como vacia
		int ficha_oponente = (ptr->table[pos_ficha + 7]);
		ptr->table[pos_ficha + 7] = 0;//Se coloca cero ya que es la ficha eliminada del otro jugador
		ptr->table[pos_ficha + 14] = (i + 1) * -1;//Se actualiza la nueva posicion de la ficha, i+1 ya que las fichas van de 1-12
		ptr->computer[i] = pos_ficha + 14;/// En el array de fichas se guarda la nueva pos en el tablero
		ptr->player[ficha_oponente - 1] = -1;/// La ficha eliminada se le coloca -1
		ptr->available_chips_jugador--;
		///How to change available chips of a specific player?
	}


	void generate_movements(Nodo* nodito, bool persona) {
		Nodo** ptr = &(nodito->children);
		if (persona) {///Jugador
			for (int i = 0; i < 12; i++) {//La ficha que mueve es i
				if (nodito->player[i] != -1) {//Existe
					if (JcomprobarJugada1(nodito, nodito->player[i])) {
						*ptr = new Nodo(*nodito);// Duplica al padre
						makeMovementJ1(*ptr, i);// hace jugada uno
						ptr = &((*ptr)->next);// conecta a la magia xd
						nodito->size++;
					}
					if (JcomprobarJugada2(nodito, nodito->player[i])) {
						*ptr = new Nodo(*nodito);// Duplica al padre
						makeMovementJ2(*ptr, i);// hace jugada 
						ptr = &((*ptr)->next);// conecta
						nodito->size++;
					}
					if (JcomprobarJugada3(nodito, nodito->player[i])) {
						*ptr = new Nodo(*nodito);// Duplica al padre
						makeMovementJ3(*ptr, i);// hace jugada 
						ptr = &((*ptr)->next);// conecta
						nodito->size++;
					}
					if (JcomprobarJugada4(nodito, nodito->player[i])) {
						*ptr = new Nodo(*nodito);// Duplica al padre
						makeMovementJ4(*ptr, i);// hace jugada
ptr = &((*ptr)->next);// conecta
nodito->size++;
					}
				}
			}
		}
		else {///Computadora
		for (int i = 0; i < 12; i++) {//La ficha que mueve es i
			if (nodito->computer[i] != -1) {//Existe
				if (CcomprobarJugada1(nodito, nodito->computer[i])) {
					*ptr = new Nodo(*nodito);// Duplica al padre
					makeMovementC1(*ptr, i);// hace jugada uno
					ptr = &((*ptr)->next);// conecta a la magia xd
					nodito->size++;
				}
				if (CcomprobarJugada2(nodito, nodito->computer[i])) {
					*ptr = new Nodo(*nodito);// Duplica al padre
					makeMovementC2(*ptr, i);// hace jugada 
					ptr = &((*ptr)->next);// conecta
					nodito->size++;
				}
				if (CcomprobarJugada3(nodito, nodito->computer[i])) {
					*ptr = new Nodo(*nodito);// Duplica al padre
					makeMovementC3(*ptr, i);// hace jugada 
					ptr = &((*ptr)->next);// conecta
					nodito->size++;
				}
				if (CcomprobarJugada4(nodito, nodito->computer[i])) {
					*ptr = new Nodo(*nodito);// Duplica al padre
					makeMovementC4(*ptr, i);// hace jugada
					ptr = &((*ptr)->next);// conecta
					nodito->size++;
				}
			}
		}
		}
	}

	void construct() {
		//Para llamar a la funcion iniciar en la raiz, los niveles que se quieren aniadir, los niveles que tiene actualmente y el turno como computadora
		addLevels(root, deep, 0, !persona);//La negacion de persona porque agrega un nivel nuevo que tiene el otro turno
	}

	//Para llamar a la funcion iniciar en la raiz, los niveles que se quieren aniadir, los niveles que tiene actualmente (no cuenta raiz) y el turno como computadora
	void addLevels(Nodo* node, int newLevels, int leftLevels, bool persona) {
		//Bajar en recursion al ultimo nivel
		if (!node) return;
		if (leftLevels) {//Si aun falta para llegar al ultimo nivel, recorre los hijos para bajar un nivel
			for (Nodo** p = &(node->children); *p; p = &((*p)->next))
				addLevels(*p, newLevels, leftLevels - 1, !persona);
		}
		else if (newLevels) {//Si ya llego al limite crea el nuevo nivel y manda los hijos recursivamente
			//CARE, &(node->children) por node
			for (Nodo** p = &(node); *p; p = &((*p)->next)) {
				generate_movements(*p, persona);
				if (newLevels - 1 > 0)
					for (Nodo** q = &((*p)->children); *q; q = &((*q)->next))//Recorre los hijos que creo
						addLevels(*q, newLevels - 1, 0, !persona);
			}
		}
	}

	/*Nodo* minMaxRecursion(Nodo* actual, int nivelesRestantes, bool maxLevel, int& value) {
		if (!actual) {
			value = maxLevel ? INT_MIN : INT_MAX;
			return nullptr;
		}
		if (nivelesRestantes) {
			int bestValue = maxLevel ? INT_MIN : INT_MAX, actualValue = 0;
			//Nodo* bestNode = actual->children, * actualNode = actual->children;
			Nodo* bestNode = nullptr, * actualNode = nullptr;
			for (Nodo* p = actual->children; p&&p < actual->children + actual->size; p = p->next) {
				actualNode = minMaxRecursion(p, nivelesRestantes - 1, !maxLevel, actualValue);
				if (!bestNode) bestNode = p;
				if (maxLevel && actualValue > bestValue) {//Comparacion del MaxMin
					bestValue = actualValue;
					if (nivelesRestantes == deep)
						bestNode = p;
					//bestNode = actual;
				}
				else if (!maxLevel && actualValue < bestValue) {
					bestValue = actualValue;
					if (nivelesRestantes == deep)
						bestNode = p;
				}
			}
			return bestNode;
		}
		else {
			value = actual->available_chips;//Funcion de utilidad
			return actual;
		}
	}*/
	Nodo* minMaxRecursion(Nodo* actual, int nivelesRestantes, bool maxLevel, int& value) {
		Nodo* bestNode = nullptr;
		minMaxRecursive(actual, nivelesRestantes, maxLevel, bestNode);
		return bestNode;
	}
	int minMaxRecursive(Nodo* actual, int nivelesRestantes, bool maxLevel, Nodo* &bestNode) {
		/*if (!actual) {
			bestNode = actual;
			return maxLevel ? INT_MIN : INT_MAX;
		}*/
		if (nivelesRestantes) {
			Nodo** p = &(actual->children);
			int bestValue = maxLevel ? INT_MIN : INT_MAX;
			for (; *p; p = &((*p)->next)){
				int actualValue = minMaxRecursive(*p, nivelesRestantes - 1, !maxLevel, bestNode);
				if (maxLevel && actualValue > bestValue) {
					bestValue = actualValue;
					if (nivelesRestantes == deep) bestNode = *p;
				}
				else if (!maxLevel && actualValue < bestValue) {
					bestValue = actualValue;
					if (nivelesRestantes == deep) bestNode = *p;
				}

			}
			return bestValue;
		}
		else {
			return actual->available_chips_computadora - actual->available_chips_jugador;//Funcion de utilidad
		}
	}


	void delTree(Nodo* node) {
		if (!node) return;
		for (Nodo* p = node->children; p < node->children + node->size; p = p->next) {
			delTree(p);
			delete p;
		}
	}

	///Comprobar por Magr
	void actualizarRaiz(Nodo* nuevaRaiz) {//Tiene que ser un hijo de la raiz
		Nodo** p= &(root->children);
		for (p = &(root->children); *p != nuevaRaiz; p = &((*p)->next));//Avanza al puntero
		*p = nuevaRaiz->next;//Desconecta del arbol
		delTree(root);//Elimina el arbol
		root = nuevaRaiz;//Actualiza la nueva raiz
	}

	void computerPlayed() {//Asume que el arbol esta completo
	//Encuentra la mejor jugada con min max
		int valAux = 0;
		/*Nodo** p = &(root->children);
		cout << "Desde aqui se imprimen las opciones" << endl;
		for (; *p; p = &((*p)->next)) {
			printHijos(*p);
		}
		cout << "Fin de opciones" << endl;*/
		Nodo* bestPlayed = minMaxRecursion(root, deep, 1, valAux);
		if (!bestPlayed) {
			cout << "No hay mas jugadas, fin del juego" << endl;
			partida = false;
			//Finalizar juego
			return;
		}
		actualizarRaiz(bestPlayed);
	}
	void playerPlayedTree(int ficha, int newPos) {//Ya sabemos la jugada y en base a eso actualizamos
		//Busca en los hijos de la raiz cual es la jugada que hizo el jugador
		Nodo** p = &(root->children), * played = nullptr;
		for (; *p && (*p)->player[ficha] != newPos; p=&((*p)->next));
		played = *p;//Guarda la jugada
		*p = (*p)->next;//Desconecta
		delTree(root);//Elimina el arbol
		root = played;//Asigna la nueva raiz
		//addLevels(root, 2, deep - 2, !persona);//Ya que se quitaron dos turnos por la jugada de la computadora
	}
	/// Funciones que Magr paso

//public:
	bool partida = true;
	Tree(int _deep, bool order_player) {
		root = new Nodo;
		deep = _deep;
		persona = order_player;
		addLevels(root, deep, 0, persona);//TODO Revisar si la persona esta en negacion
	}
	void printTablero() {
		//system("CLS");
		int* ptr = getTablero();
		cout << endl << "                    " << "DAMAS" << endl;
		if (persona)
			cout << "         " << " Ultimo turno de: PERSONA" << endl << "  ";
		else
			cout << "         " << " Ultimo turno de: COMPUTADORA" << endl << "  ";

		SetConsoleTextAttribute(hConsole, 14);//amarillo
		for (int i = 0; i < 8; i++) cout << setw(5) << i;
		cout << endl << "  ";
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (*ptr > 0) SetConsoleTextAttribute(hConsole, 12);//verde
				else if (*ptr < 0) SetConsoleTextAttribute(hConsole, 15);//celeste
				else SetConsoleTextAttribute(hConsole, 8);
				cout << setw(5) << *ptr++;
			}
			cout << endl << "  ";
			cout << endl << "  ";
		}
		SetConsoleTextAttribute(hConsole, 8);//gris
	}

	void printHijos(Nodo *p) {
		system("CLS");
		int* ptr = p->table;
		cout << endl << "                    " << "DAMAS" << endl;
		if (persona)
			cout << "         " << " Ultimo turno de: PERSONA" << endl << "  ";
		else
			cout << "         " << " Ultimo turno de: COMPUTADORA" << endl << "  ";
		//cout << "Available chips" << p->available_chips<<endl;
		SetConsoleTextAttribute(hConsole, 14);//gris
		for (int i = 0; i < 8; i++) cout << setw(5) << i;
		cout << endl << "  ";
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (*ptr > 0) SetConsoleTextAttribute(hConsole, 12);//rojo
				else if (*ptr < 0) SetConsoleTextAttribute(hConsole, 15);//blanco
				else SetConsoleTextAttribute(hConsole, 8);
				cout << setw(5) << *ptr++;
			}
			cout << endl << "  ";
			cout << endl << "  ";
		}
		SetConsoleTextAttribute(hConsole, 8);//gris
	}
	~Tree() {
		delTree(root);
	}
	int* getTablero() { return root->table; }

	void startGameTree() {
		//Si mueve primero la computadora genera todo el arbol y juega, usa funcion existente
		if (!persona) {
			//construct();
			computerPlayed();

		}
	}
	void inputPlayerMove(int &ficha, int &jugada, int& newPos, bool &valid) {
		cout << "Es el turno del JUGADOR" << endl;
		printTablero();
		cout << "Ingrese la ficha que desea mover: " << endl;
		cin >> ficha;
		cout << "Que jugada desea hacer?" << endl;
		cout << "IZQUIERDA   |   DERECHA\nAvanzar(3)      Avanzar (1)\nComer(4)        Comer (2)" << endl;
		cin >> jugada;
		switch (jugada) {
		case 1:
			valid = JcomprobarJugada1(root, root->player[ficha - 1]);
			newPos = root->player[ficha - 1] - 7;
			break;
		case 2: {
			valid = JcomprobarJugada2(root, root->player[ficha - 1]);
			newPos = root->player[ficha - 1] - 14;
			break;
		}
		case 3: {
			valid = JcomprobarJugada3(root, root->player[ficha - 1]);
			newPos = root->player[ficha - 1] - 9;
			break;
		}
		case 4: {
			valid = JcomprobarJugada4(root, root->player[ficha - 1]);
			newPos = root->player[ficha - 1] - 18;
			break;
		}
		default:
			break;
		}
	}
	void gameLoop() {
		//Inicia con el jugador
		while (partida) {
			int ficha, jugada, newPos = 0;
			bool valid = 0;

			//system("CLS");

			inputPlayerMove(ficha, jugada, newPos,valid);
			
			if (!valid) {
				cout << "La jugada no es valida, intente otra jugada" << endl << endl;
				Sleep(5000);
				continue;
			}
			playerPlayedTree(ficha-1, newPos);
			addLevels(root, 1, deep - 1, !persona);//Revisar si se pone persona o !persona
			persona = !persona;
			
			//system("CLS");

			cout << "Es el turno de la computadora" << endl;
			printTablero();
			computerPlayed();
			addLevels(root, 1, deep - 1, !persona);
			persona = !persona;
		}
	}

	

};
//No esta considerado el caso en que nos quedemos sin jugadas
//Estaba en public
	/*void computerPlayed() {//Asume que el arbol esta completo
		int valAux = 0;
		Nodo* bestPlayed = minMaxRecursion(root, deep, 1, valAux);
		//Rompler los lazos con sus hermanos
		Nodo** p;
		//Avanza al puntero de best played
		for (p= &(root->children); *p != bestPlayed; p = &((*p)->next));
		*p = bestPlayed->next;//Desconecta a best played del arbol
		desconectTree(bestPlayed);

		delTree(root);//Elimina el arbol
		root = bestPlayed;//Actualiza la nueva raiz


	}*/