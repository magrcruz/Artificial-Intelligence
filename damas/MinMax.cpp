// MinMax.cpp : Defines the entry point for the application.
//

#include "MinMax.h"

using namespace std;

//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;
void changeWindow() {
    int Ancho = 50, Alto = 23;

    _COORD Coordenada;
    Coordenada.X = Ancho;
    Coordenada.Y = Alto;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Right = Ancho;
    Rect.Bottom = Alto;

    // Cambiar tama�o de consola a lo especificado en el buffer
    SetConsoleWindowInfo(hConsole, TRUE, &Rect);
    SetConsoleTitle(TEXT("Damas"));
}
int main(){
    int _deep = 5;
    bool order_player = 0;
    cout << " Weenas soy damIA y vengo a vencerte en damas" << endl;
    cout << "Ingrese dificultad (profundidad)" << endl;
    cin >> _deep;
    cout << "Si desea empezar ingrese 1, de lo contrario ingrese 0" << endl;
    cin >> order_player;
    changeWindow();
   	Tree tablero(_deep,order_player);
    tablero.startGameTree();
    tablero.gameLoop();
	return 0;
}
/*int tableroPrueba[64] = {
        -9,  0,-10,  0,-11,  0,-12,  0,
        0, -5,  0, -6,  0, -7,  0, -8,
        -1,  0, -2,  0, 0,  0, -4,  0,
         0,  0,  0,  -3,  0,  0,  0,  0,
         0,  0,  1,  0,  0,  0,  0,  0,
         0,  0,  0,  2,  0,  3,  0,  4,
         5,  0,  6,  0,  7,  0,  8,  0,
         0,  9, 0,  10, 0,  11, 0,  12
};
int starterPlayer[12] = { 34,43,45,47, 48,50,52,54, 57,59,61,63 };
int starterComputer[12] = { 16,18,27,22, 9,11,13,15, 0,2,4,6 };


Nodo prueba(tableroPrueba, starterPlayer, starterComputer);
Tree pruebas(_deep, order_player);
pruebas.root = new Nodo(tableroPrueba, starterPlayer, starterComputer);
cout<<pruebas.CcomprobarJugada4(pruebas.root, pruebas.root->computer[2]);
*/