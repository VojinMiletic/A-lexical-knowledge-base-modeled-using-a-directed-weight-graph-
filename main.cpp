#include <iostream>
#include <vector>
using namespace std;
#include "graph.h"
#include <fstream>

int main() {
	Graph g1;
	ifstream iFile;
	iFile.open("graf2.txt");
	if (!iFile.is_open()) cout << "FAJL NIJE OTVOREN" << endl;
	else {
		int brCvorova, brGrana;
		iFile >> brCvorova >> brGrana;
		for (int i = 0; i < brCvorova; i++) {
			string ime;
			iFile >> ime;
			g1.dodajCvor(ime);
		}
		for (int i = 0; i < brGrana; i++) {
			string prvi, drugi;
			double tezina;
			iFile >> prvi;
			iFile >> drugi;
			iFile >> tezina;
			g1.dodajGranu(prvi,drugi,tezina);
		}
		g1.pisiGraf();
		iFile.close();
	}
	cout << endl;
	cout << endl;
	g1.jakoPovezane("preduzece");
	cout << endl;
	g1.nadji_k_najslicnijih("ETF", 20);
	cout << endl;
	g1.najkraciPut("preduzece", "berza");
	cout << endl;
	cout << endl;
	cout << endl;
	g1.dodajCvor("Matematika");
	g1.dodajGranu("Matematika", "skola", 0.99);
	g1.dodajGranu("Matematika", "ETF", 0.8);
	g1.pisiGraf();
	cout << endl<<endl;
	g1.brisiGranu("Matematika", "skola");
	g1.pisiGraf();
	cout << endl<<endl;
	g1.brisiGranu("Matematika", "ETF");
	g1.pisiGraf();
	cout << endl << endl;
	g1.brisiCvor("racunar");
	g1.pisiGraf();
	cout << endl << endl;
	g1.brisiCvor("Matematika");
	g1.pisiGraf();
	cout << endl << endl;
	return 0;
}