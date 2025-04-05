Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

Треба да се направи функција со потпис

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.


#include <iostream>
#include <cstring>
using namespace std;

struct Voz {
	char relacija[51];
	float kilometri;
	int patnici;
};

struct ZeleznickaStanica {
	char grad[21];
	Voz vozovi[30];
	int brojVozovi;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad) {
	float minKm = -1;
	Voz najkratokVoz;
	bool pronajden = false;

	for (int i = 0; i < n; ++i) {
		if (strcmp(zs[i].grad, grad) == 0) {
			for (int j = 0; j < zs[i].brojVozovi; ++j) {
				Voz v = zs[i].vozovi[j];
				if (!pronajden || v.kilometri <= minKm) {
					if (!pronajden || v.kilometri < minKm || v.kilometri == minKm) {
						minKm = v.kilometri;
						najkratokVoz = v;
						pronajden = true;
					}
				}
			}
		}
	}

	if (pronajden) {
		cout << "Najkratka relacija: " << najkratokVoz.relacija << " (" << (int)(najkratokVoz.kilometri) << " km)" << endl;
	} else {
		cout << "Nema vozovi od dadeniot grad." << endl;
	}
}

int main() {
	int n;
	cin >> n;

	ZeleznickaStanica zStanica[100];

	for (int i = 0; i < n; ++i) {
		cin >> zStanica[i].grad;
		cin >> zStanica[i].brojVozovi;

		for (int j = 0; j < zStanica[i].brojVozovi; ++j) {
			cin >> zStanica[i].vozovi[j].relacija
				>> zStanica[i].vozovi[j].kilometri
				>> zStanica[i].vozovi[j].patnici;
		}
	}

	char grad[25];
	cin >> grad;

	najkratkaRelacija(zStanica, n, grad);

	return 0;
}
