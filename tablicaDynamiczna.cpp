#include "DlaWszystkich.h"
#include <iostream>
#include <cstring>

using namespace std;

//Konstruktor domyslny - ustawia poczatkowa pojemnosc i alokuje pamiec
tablicaDynamiczna::tablicaDynamiczna() : rozmiar(0), pojemnosc(4) {
	tablica = new int[pojemnosc];
}

tablicaDynamiczna::~tablicaDynamiczna() {
	delete[] tablica;
}

tablicaDynamiczna::tablicaDynamiczna(int poczatkowaPojemnosc) : rozmiar(0), pojemnosc(poczatkowaPojemnosc) {
	tablica = new int[pojemnosc];
	if (poczatkowaPojemnosc == 0) {
		pojemnosc = 1;
	}
}

void tablicaDynamiczna::zmienRozmiar(int nowaPojemnosc) {
	int* tablica2 = new int[nowaPojemnosc];
	memcpy(tablica2, tablica, rozmiar * sizeof(int));
	delete[] tablica;
	tablica = tablica2;
	pojemnosc = nowaPojemnosc;
}

void tablicaDynamiczna::dodajNaPoczatek(int wartosc) {
	if (rozmiar == pojemnosc) zmienRozmiar(pojemnosc * 2);
	for (int i = rozmiar; i > 0; i--) {
		tablica[i] = tablica[i - 1];
	}
	tablica[0] = wartosc;
	rozmiar++;
}

void tablicaDynamiczna::dodajNaKoniec(int wartosc) {
	if (rozmiar == pojemnosc) zmienRozmiar(pojemnosc * 2);
	tablica[rozmiar] = wartosc;
	rozmiar++;
}

void tablicaDynamiczna::dodaj(int wartosc, int indeks) {
	if (rozmiar == pojemnosc) zmienRozmiar(pojemnosc * 2);
	if (indeks > rozmiar || indeks == 0) {
		cout << " jest poza granicami\n";
		return;
	}
	for (int i = rozmiar; i > indeks; i--) {
		tablica[i] = tablica[i - 1];
	}
	tablica[indeks] = wartosc;
	rozmiar++;
}

void tablicaDynamiczna::usunZPoczatku() {
	if (rozmiar == 0) {
		cout << "Nie ma elementów\n";
		return;
	}
	int temp = tablica[0];
	for (int i = 0; i < rozmiar; i++) {
		tablica[i] = tablica[i + 1];
	}
	rozmiar--;
}

void tablicaDynamiczna::usunZKoncu() {
	if (rozmiar == 0) {
		cout << "Nie ma elementów\n";
		return;
	}
	rozmiar--;
	int temp = tablica[rozmiar];
}

void tablicaDynamiczna::usun(int indeks) {
	if (rozmiar == 0) {
		cout << "Nie ma elementów\n";
		return;
	}
	if (indeks >= rozmiar) {
		cout << " jest poza granicami\n";
		return;
	}
	int temp = tablica[indeks];
	for (int i = indeks; i < rozmiar; i++) {
		tablica[i] = tablica[i + 1];
	}
	rozmiar--;
}

bool tablicaDynamiczna::wyszukiwanie(int wartosc) {
	if (rozmiar == 0) {
		return false;
	}
	for (int i = 0; i < rozmiar / 2; i++) {
		if (tablica[i] == wartosc) {
			return true;
		}
	}
	for (int i = rozmiar - 1; i >= rozmiar / 2; i--) {
		if (tablica[i] == wartosc) {
			return true;
		}
	}
	return false;
}

int tablicaDynamiczna::pobierz(int indeks) const {
	if (indeks >= rozmiar) {
		cout << " jest poza granicami\n";
		return -1;
	}
	return tablica[indeks];
}

void tablicaDynamiczna::wyswietl() {
	cout << "Tablica dynamiczna: " << tablica[0];
	for (int i = 1; i < rozmiar; i++) {
		cout << ", " << tablica[i];
	}
}

int tablicaDynamiczna::getRozmiar() const {
	return rozmiar;
}

void tablicaDynamiczna::fillRandom(int count, int seed) { //wypełnia pseudolosowymi liczbami
	srand(seed);
	for (int i = rozmiar; i < count; i++) {
		int wartosc = rand() % 10000;
		dodajNaKoniec(wartosc);
	}
}

void tablicaDynamiczna::clear() {
	delete[] tablica;
	tablica = nullptr;
	rozmiar = 0;
	pojemnosc = 0;
}
