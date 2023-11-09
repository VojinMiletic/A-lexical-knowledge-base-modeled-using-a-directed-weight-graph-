#ifndef _red_h_
#define _red_h_
#include <iostream>
using namespace std;

class Red {
	int duzina;
	int* niz;
	int zaglavlje;
	int front = 0;
	int rear = 0;
public:
	Red(int d, int z) : duzina(d), zaglavlje(z) {
		niz = new int[duzina];
		niz[front] = zaglavlje;
		front++;
		rear++;
	}
	void insert(int n) {
		niz[rear] = n;
		rear++;
	}
	int erase() {
		int n = niz[front];
		front++;
		return n;
	}
	bool empty() {
		if (front == rear) return true;
		return false;
	}
	~Red() {
		delete[] niz;
	}
	void brisiRed(){
		front = rear = 0;
		delete[] niz;
	} 
};
#endif // !_red_h_

