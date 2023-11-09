#ifndef _graph_h_
#define _graph_h_
#include <iostream>
#include "vector.h"
using namespace std;
#include <iomanip>
bool check(int* niz, int f) {
	for (int m = 0; m < f; m++) {
		if (niz[m] == 0)
			return true;
	}
	return false;
}

class Graph {
	struct Cvor {
		string identifikator;
		int indeksEdges;
		bool flag;
		Cvor(string s , int i = -1, bool f = false) : identifikator(s), indeksEdges(i), flag(f) {};
	};
	struct Grana {
		int indeksCvora;
		double tezina;
		Grana(int i , double t ) : indeksCvora(i), tezina(t) {};
	};
	vector<Cvor> indices = {Cvor("END",edges.size(),true)};
	vector<Grana> edges;
public:
	~Graph() {
		indices.clear();
		edges.clear();
	}
	void dodajCvor(string ime) {
		indices.insert(indices.end()-1,Cvor(ime));
	}
	
	void dodajGranu(string pocetni, string krajnji, double w) {
		int i;//Pozicija pocetnog u nizu indices
		for (i = 0; i < indices.size() && indices[i].identifikator != pocetni; i++);
		int j;//Pozicija krajnjeg u nizu indices
		for (j = 0; j < indices.size() && indices[j].identifikator != krajnji; j++);
		if (j == indices.size() || i == indices.size()) return;
		if (!indices[i].flag) {
			edges.insert(edges.end(), Grana(j, w));
			indices[i].flag = true;
			indices[i].indeksEdges = edges.size()-1;
			indices[indices.size() - 1].indeksEdges = edges.size();//Azuriranje granicnog cvora
			return;
		}
		edges.insert(edges.begin() + ((indices[i + 1].indeksEdges < 0) ? indices[indices.size()-1].indeksEdges : indices[i + 1].indeksEdges), Grana(j, w));
		if (!(indices[i + 1].indeksEdges < 0)) {
			for (int m = i + 1; m < indices.size(); m++) {
				indices[m].indeksEdges++;
			}
		}
		else {
			indices[indices.size() - 1].indeksEdges++;
		}
	}
	void pisiGraf() {
		for (int j = 0; j < edges.size(); j++) {
			cout << "(" << edges[j].indeksCvora << ", " << edges[j].tezina << ")" << " ";
		}
		cout << endl;
		for (int i = 0; i < indices.size(); i++) {
				cout<< "(" << indices[i].identifikator << ", " << indices[i].indeksEdges << ")" << " ";
		}
	}
	void brisiGranu(string pocetni, string krajnji) {
		int i;//Pozicija pocetnog u nizu indices
		for (i = 0; i < indices.size() && indices[i].identifikator != pocetni; i++);
		int j;//Pozicija krajnjeg u nizu indices
		for (j = 0; j < indices.size() && indices[j].identifikator != krajnji; j++);
		if (!indices[i].flag) return;
		if (j >= indices.size()-1 || i >= indices.size()-1) return;
		int alfa;
		int k = i + 1;
		while (k < indices.size()) {
			if (indices[k].indeksEdges > 0) {
				alfa = indices[k].indeksEdges;
				break;
			}
			k++;
		}
		int len = alfa - indices[i].indeksEdges;
		if (len == 1) {
			if (edges[indices[i].indeksEdges].indeksCvora != j) return;
			edges.erase(edges.begin() + indices[i].indeksEdges);
			indices[i].flag = false;
			indices[i].indeksEdges = -1;
			for (int m = i + 1; m < indices.size(); m++) {
				if (indices[m].indeksEdges > 0)
					indices[m].indeksEdges--;
			}
			return;
		}
		int l = len;
		for ( l; l && edges[indices[i].indeksEdges + l - 1].indeksCvora != j; l--);
		if (!l) return;

		edges.erase(edges.begin()+indices[i].indeksEdges + l - 1);

		for (int m = i + 1; m < indices.size(); m++) {
			if(indices[m].indeksEdges>0)
				indices[m].indeksEdges--;
		}
	}
	void brisiCvor(string ime) {
		for (int m = 0; m < indices.size(); m++) {
			brisiGranu(indices[m].identifikator, ime);
		}

		int i;//Pozicija cvora u nizu indices
		for (i = 0; i < indices.size() && indices[i].identifikator != ime; i++);
		if (i >= indices.size() - 1) return;
		if (!indices[i].flag) {
			indices.erase(indices.begin() + i);
			return;
		}	
		int alfa;
		int k = i + 1;
		while (k < indices.size()) {
			if (indices[k].indeksEdges > 0) {
				alfa = indices[k].indeksEdges;
				break;
			}
			k++;
		}
		int len = alfa - indices[i].indeksEdges;
		int l = len;
		while (l) {
			edges.erase(edges.begin() + indices[i].indeksEdges);
			l--;
		}
		for (int m = i + 1; m < indices.size(); m++) {
			if (indices[m].indeksEdges > 0)
				indices[m].indeksEdges-=len;
		}
		indices.erase(indices.begin() + i);
		for (int m = 0; m < edges.size(); m++) {
			if (edges[m].indeksCvora > i)
				edges[m].indeksCvora--;
		}
		
	}
	void obrisiGraf() {
		indices.clear();
		edges.clear();
	}
	struct Nizovi {
		double* nizTezina;
		int* nizPrethodnika;
	};
	
	Nizovi Dijkstra(string ime) {
		Nizovi nz;
		int n = indices.size()-1;
		double *tezine = new double[n];
		int* posecenost = new int[n];
		int* prethodnici = new int[n];
		int pocetni;
		for (pocetni = 0; pocetni < n && indices[pocetni].identifikator != ime; pocetni++);
		for (int m = 0; m < n; m++) {
			if (m == pocetni) {
				tezine[m] = 1;
				posecenost[m] = 0;
				prethodnici[m] = pocetni;
			}
			else {
				tezine[m] = 0;
				posecenost[m] = -1;
				prethodnici[m] = -1;
			}
		}
		int i = 0;
		while (i < n && check(posecenost, n)) {
			if (!indices[pocetni].flag) {
				posecenost[pocetni] = 1;
				for (int m = 0; m < n; m++) {
					if (posecenost[m] == 0) {
						pocetni = m;
						m = n;
					}
				}
				continue;
			}
			int alfa = 0;
			int f = pocetni + 1;
			while (f < indices.size()) {
				if (indices[f].indeksEdges > 0) {
					alfa = indices[f].indeksEdges;
					break;
				}
				f++;
			}
			int len = alfa - indices[pocetni].indeksEdges;
			int l = 0;
			while (l < len) {
				int j = edges[indices[pocetni].indeksEdges + l].indeksCvora;
				if (edges[indices[pocetni].indeksEdges + l].tezina * tezine[pocetni] > tezine[j]) {
					tezine[j] = edges[indices[pocetni].indeksEdges + l].tezina * tezine[pocetni];
					prethodnici[j] = pocetni;
				}
				if(posecenost[j] != 1)
					posecenost[j] = 0;
				l++;
			}
			posecenost[pocetni] = 1;
			for (int m = 0; m < n; m++) {
				if (posecenost[m] == 0) {
					pocetni = m;
					m = n;
				}
			}
			i++;
		}
		nz.nizPrethodnika = prethodnici;
		nz.nizTezina = tezine;
		return nz;
	}
	
	void nadji_k_najslicnijih(string ime, int k) {
		int n = indices.size() - 1;
		double* niz = Dijkstra(ime).nizTezina;
		int broj = 0;
		for (int i = 0; i < n; i++) {
			if (niz[i] != 0 && niz[i] != 1)
				broj++;
		}
		double max = 0;
		int pos;
		for (int i = 0; i < n && k && broj; i++) {
			for (int j = 0; j < n; j++) {
				if (niz[j] > max && niz[j] != 1) {
					max = niz[j];
					pos = j;
				}
			}
			niz[pos] = 0.0;
			cout <<i+1<<".Najclicniji: " << indices[pos].identifikator<< "-" << max << endl;
			max = 0.0;
			broj--;
			k--;
		}
	}
	void najkraciPut(string rec1, string rec2) {
		
		int n = indices.size() - 1;
		int* niz = new int[n];
		int pokazivac = 0;

		Nizovi nz = Dijkstra(rec1);
		int pocetni;
		int kraj;
		for (kraj = 0; kraj < n && indices[kraj].identifikator != rec2; kraj++);
		for (pocetni = 0; pocetni < n && indices[pocetni].identifikator != rec1; pocetni++);
		if (nz.nizPrethodnika[kraj] == -1) return;
		
		niz[pokazivac++] = kraj;
		while (nz.nizPrethodnika[kraj] != pocetni) {
			kraj = nz.nizPrethodnika[kraj];
			niz[pokazivac++] = kraj;
		}
		niz[pokazivac] = pocetni; // pokazivac ukazuje na poslednju zauzetu lokaciju u niz-u
		while (pokazivac) {
			int indexPocetnog = niz[pokazivac];
			int indexKrajnjeg = niz[pokazivac - 1];
			cout << indices[indexPocetnog].identifikator << "-(";
			int m;
			for (m = indices[indexPocetnog].indeksEdges; edges[m].indeksCvora != indexKrajnjeg; m++);
			cout << edges[m].tezina << ")->";
			pokazivac--;
		}
		cout << indices[niz[0]].identifikator;
	}

	void pisiDijkstru(Nizovi nz) {
		int len = indices.size() - 1;
		for (int m = 0; m < len; m++) {
			cout<<setw(4)<< nz.nizTezina[m]<<" ";
		}
		cout << endl;
		for (int m = 0; m < len; m++) {
			cout<<setw(4) << nz.nizPrethodnika[m] << " ";
		}
		cout << endl;
	}
	void jakoPovezane(string ime) {
		int n = indices.size() - 1;
		int pocetni;
		for (pocetni = 0; pocetni < n && indices[pocetni].identifikator != ime; pocetni++);
		if (pocetni == n) return;
		cout << "Jako povezane reci: ";
		cout << indices[pocetni].identifikator << " ";
		if (!indices[pocetni].flag) return;
		double* niz = Dijkstra(ime).nizTezina;
		for (int i = 0; i < n; i++) {
			if (niz[i] == 0 || niz[i] == 1) continue;
			double* niz2 = Dijkstra(indices[i].identifikator).nizTezina;
			if (niz2[pocetni] != 0) cout << indices[i].identifikator << " ";
		}
		cout << endl;
	}
};


#endif // _graph_h_

