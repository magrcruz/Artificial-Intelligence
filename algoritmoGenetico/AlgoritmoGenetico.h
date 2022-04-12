// AlgoritmoGenetico.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include <random>
#include <math.h>

using namespace std;
// TODO: Reference additional headers your program requires here.

double dEuclediana(pair<int, int>& p1, pair<int, int>& p2) {
	return sqrt(pow((p1.first - p2.first), 2) + pow((p1.second - p2.second), 2));
}

struct TSP {
	//  PARAMETROS
	int ciudades = 10;//Ingresa al inicio
	int tamPoblacion = 3000;
	float pCruzamiento = 50;//% Revisar luego
	float pMutacion = 50;//%
	int numeroGeneraciones = 1000;
	// Buscar si se puede calcular los parametros optimos
//  VARIABLES
	int generacion = 0;
	double ranking = 0.5;
	int ciudadInicial = 0;
	ofstream archivoPromedio, archivoBest;
	vector < vector<double>> distances;// Matriz de distancia
	vector < pair<int, int>> coordenadas;
	//vector < pair<double,string&>> fitnesses;

	vector <string>individuos;// Los individuos son strings
	double promedio = 0.0;
	double funcionAptitud(const string& str) {
		double fitness = 0;
		for (int i = 0; i < ciudades; i++)
			fitness += distances[str[i] - 'A'][str[i + 1] - 'A'];
		return fitness;
	}
	TSP(int _ciudades) {
		ciudades = _ciudades;
		distances = vector<vector<double>>(ciudades, vector<double>(ciudades));
		coordenadas = vector<pair<int, int>>(ciudades);
		generarCoordenadas();
		armarMatrizDistancias();
		individuos = vector<string>(tamPoblacion);
		//fitnesses = vector<pair<double, string&>>(tamPoblacion);
		archivoPromedio.open("datos.txt");
		archivoBest.open("datos2.txt");
	}
	~TSP() {
		archivoPromedio.close();
		archivoBest.close();
	}

	void getCoordsOpenGL(float *coord) {
		for (int i = 0, j = 0; i < ciudades; i++, j += 3) {
			coord[j] = float(coordenadas[i].first)/50.0-1.0;
			coord[j+1] = (float(coordenadas[i].second) / 50.0 - 1.0);
			coord[j+2] = 0.0f;
		}
	}
	void getCoordsOpenGLBest(float* coord) {
		//Sacar el mejor individuo y copiar las coordenadas
		string individuo = individuos[0];
		for (int i = 0, j = 0; i < ciudades; i++, j += 3) {
			coord[j] = float(coordenadas[(individuo[i]-'A')].first) / 50.0 - 1.0;
			coord[j + 1] = (float(coordenadas[(individuo[i] - 'A')].second) / 50.0 - 1.0) ;
			coord[j + 2] = 0.0f;
		}
	}

	//  START
		// Elegir Ciudad Inicial
	void elegirCiudadInicial() {// Por ahora por consola
		//Console Version
		char seleccion = '\0';
		cout << "Las ciudades son: " << endl;
		for (int i = 0; i < ciudades; i++) {
			cout << char(i + 'A') << " -> (" << coordenadas[i].first << ", " << coordenadas[i].second << ")" << endl;
		}
		cout << "Ingrese ciudad" << endl;
		cin >> seleccion;
		ciudadInicial = seleccion - 'A';
		generarIndividuos();
	}
	void generarCoordenadas() {
		random_device rd;  //obtain a seed
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> distrib(0, 100);
		for (int i = 0; i < ciudades; i++) {
			int a = distrib(gen), b = distrib(gen);
			if (a > 0 && a < 100 && b > 0 && b < 100) {
				coordenadas[i] = make_pair(a, b);
			}
		}
	}
	void armarMatrizDistancias() {
		for (int i = 0; i < ciudades; i++)
			for (int j = 0; j < ciudades; j++)
				distances[i][j] = dEuclediana(coordenadas[i], coordenadas[j]);
	}

	void _swap(char& c1, char& c2) {
		char aux = c1;
		c1 = c2;
		c2 = aux;
	}

	//  PROBLACION INICIAL
	void generarIndividuos() {
		random_device rd;  //obtain a seed
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> distrib(0, ciudades - 2);
		// Plantilla
		string plantilla;
		char cInicial = char(ciudadInicial + 'A');
		for (int i = 0; i < ciudades; i++)
			plantilla += char(i + 'A'); //Genera una plantilla
		plantilla.erase(plantilla.find(cInicial), 1); // Borra la ciudad inicial
		//Generar los individuos
		for (int i = 0; i < tamPoblacion; i++) {
			string individuo(plantilla); // Copia la plantilla en el nuevo individuo
			for (int j = 0; j < ciudades - 1; j++)
				_swap(individuo[j], individuo[distrib(gen)]);// Desordena de forma aleatoria para no tener duplicados
			individuos[i] = cInicial + individuo + cInicial;
		}
	}
	//void generarPoblacionInicial();

//  SELECCION
	//Seleccion proporcional
	void evaluacion(vector< pair<double, string*>>& fitnesses, double& media, double& suma) {// Evalua los mas aptos, saca promedio y saca el mejor
		suma = 0;// best = 1;
		double fitness;
		//int iBest=0;
		for (int i = 0; i < individuos.size(); i++) {
			fitness = 1 / funcionAptitud(individuos[i]);
			//cout << fitness << endl;
			suma += fitness;
			/*if (fitness < best) {
				best = fitness;
				iBest = i;
			}*/
			fitnesses[i] = pair<double, string*>(fitness, &individuos[i]);
		}
		media = suma / double(individuos.size());
		//cout << "Promedio de la poblacion: " << media << endl;
		sort(fitnesses.begin(), fitnesses.end(), greater<pair<double, string*>>());
		cout << "Mejor elemento: " << *fitnesses[0].second << " con fitness " << fitnesses[0].first << endl;
		archivoPromedio << media << " " << generacion << endl;
		archivoBest << fitnesses[0].first << " " << generacion << endl;
		/*suma = 0;
		// Sacar promedio de los mejores
		for (int i = 0; i < tamPoblacion * mejores; i++)
			suma += fitnesses[i].first;
		media = suma / (tamPoblacion * mejores);*/

	}

	int busqueda(vector<double>& frecuenciaAcumulada, double val) {
		int half = 0;
		for (int i = 0; i < frecuenciaAcumulada.size() && frecuenciaAcumulada[i] < val; half = i, i++);
		return half;
	}
	void generarNuevaPoblacion() {
		generacion++;
		//Para el crossover mezcla randoms
		//1. Elitismo, el mejor elemento ya esta al inicio, no tocar
		//2. Para hacer el crossover
		random_device rd;  //obtain a seed
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> distrib(0, tamPoblacion - 2);
		uniform_int_distribution<> cross(0, 99);

		//Sacar la frecuencia acumulada para simular la ruleta
		vector< pair<double, string*>> fitnesses(individuos.size());
		double media, suma;
		evaluacion(fitnesses, media, suma);
		//
		double sumaBest = 0;
		fitnesses.resize(ranking * fitnesses.size());
		//Sacar suma de los mejores
		for (int i = 0; i < fitnesses.size(); i++) sumaBest += fitnesses[i].first;

		vector<double> frecuenciaAcumulada(fitnesses.size());
		frecuenciaAcumulada[0] = fitnesses[0].first / sumaBest * 100;
		for (int i = 1; i < fitnesses.size(); i++)
			frecuenciaAcumulada[i] = frecuenciaAcumulada[i - 1] + fitnesses[i].first / sumaBest * 100;
		uniform_real_distribution<> dis(0.0, 100.0);

		//Genera nueva poblacion
		vector<string> newPopulation;
		newPopulation.reserve(tamPoblacion);
		newPopulation.push_back(*fitnesses[0].second);//Aqui hacemos el elitismo

		while (newPopulation.size() < tamPoblacion) {
			//Generamos dos padres
			double percentage = dis(gen);//Padre 1
			int P1 = busqueda(frecuenciaAcumulada, percentage);// Ubicar en la ruleta
			percentage = dis(gen);//Padre 2
			int P2 = busqueda(frecuenciaAcumulada, percentage);// Ubicar en la ruleta
			//Genera dos hijos
			newPopulation.push_back(*fitnesses[P1].second);
			newPopulation.push_back(*fitnesses[P2].second);
			if(cross(gen)<=pCruzamiento)
			  crossover(newPopulation[newPopulation.size() - 1], newPopulation[newPopulation.size() - 2]);
		}
		newPopulation.resize(tamPoblacion);
		individuos = newPopulation;

		//3. Para hacer la mutacion
		mutacion();
	}
	string patron(int tam) {//Original
		string pat(tam, ' ');
		random_device rd;  //obtain a seed
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> distrib(1, tam);

		for (int i = 0; i < tam; i++) {
			int j = distrib(gen);
			if (j % 2) {//odd
				pat[i] = '1';
			}
			else
				pat[i] = '0';
		}
		return pat;
	}

	void crossover(string& individuo1, string& individuo2) {
		char cInicial = char(ciudadInicial + 'A');
		random_device rd;  //obtain a seed
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> distrib(0, 100);
		//Quitar los extremos, solo necesitamos el cruzamiento con el resto
		individuo1.erase(0, 1);
		individuo1.erase(individuo1.size() - 1, 1);
		individuo2.erase(0, 1);
		individuo2.erase(individuo2.size() - 1, 1);

		string pat = patron(ciudades - 1);

		// A B C D E F G H I J
		vector<bool> maskA(ciudades, false);//individuo1
		vector<bool> maskB(ciudades, false);//individuo2
		string newIndividuoA(ciudades - 1, ' ');
		string newIndividuoB(ciudades - 1, ' ');
		//cout << "Before Crossover" << endl;
		for (int a = 0; a < pat.size(); a++) {
			if (pat[a] == '1') {
				newIndividuoA[a] = individuo2[a];
				maskA[individuo2[a] - 'A'] = true;
				newIndividuoB[a] = individuo1[a];
				maskB[individuo1[a] - 'A'] = true;
			}
		}

		//Letras que faltan
		int missingLetter = 0;
		for (int i = 0; i < newIndividuoA.size(); i++) {
			if (newIndividuoA[i] == ' ') {
				while (maskA[missingLetter] || missingLetter == ciudadInicial)  // Busca en la mascara el primer 0
					missingLetter++;
				newIndividuoA[i] = char(missingLetter + 'A');
				maskA[missingLetter] = true;
			}
		}
		missingLetter = 0;
		for (int i = 0; i < newIndividuoB.size(); i++) {
			if (newIndividuoB[i] == ' ') {
				while (maskB[missingLetter] || missingLetter == ciudadInicial)  // Busca en la mascara el primer 0
					missingLetter++;
				newIndividuoB[i] = char(missingLetter + 'A');
				maskB[missingLetter] = true;
			}
		}
		individuo1 = cInicial + newIndividuoA + cInicial;
		individuo2 = cInicial + newIndividuoB + cInicial;
		
		//cout << "After Crossover" << endl;
		//cout << "newIndividuoA->" << individuo1 << endl;
		//cout << "newIndividuoB->" << individuo2 << endl;
	}
	void mutacion() {
		///Parece que esta completo
		random_device rd;  //obtain a seed
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> distrib(1, ciudades - 1);
		uniform_int_distribution<> p(0, 100);
		for (int i = 1; i < individuos.size(); i++) {
			if (p(gen) < pMutacion)
				_swap(individuos[i][distrib(gen)], individuos[i][distrib(gen)]);
		}
	}

	/// Esta funcion solo se utilizo para hacer las pruebas en consola 
	void generaciones() {
		for (int i = 0; i < numeroGeneraciones; i++) {
			generarNuevaPoblacion();
			//cout << endl;
		}
	}

};

struct Graphic {};//TO-DO

/*
// BACKLOG
// 3.0 Programa completo pero
la poblacion no mejora porque al sacar los procentajes sigue habiendo un individuo de cada uno y no cambia esa poblacion
Aun sigue bajandose el primer elemento

// 4.0
Pasar el mejor elemento al final para eliminarlo y guardarlo en lugar vip, asi no se modificara
Sacar el promedio de x% mejores y no de todos
guardar en un pair para hacer el sort

*/