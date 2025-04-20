#include "DlaWszystkich.h"
#include <iostream>
#include <cstring>

using namespace std;

listaJednokierunkowa::listaJednokierunkowa() : head(nullptr), tail(nullptr), rozmiar(0) {}

//Destruktor - usuwa wszystkie wezly listy i zwalnia pamiec
listaJednokierunkowa::~listaJednokierunkowa() {
	Node* teraz = head;
	while (teraz) {
		Node* temp = teraz;
		teraz = teraz->next;
		delete temp;
	}
}

void listaJednokierunkowa::dodajNaPoczatek(int wartosc) {
	Node* newNode = new Node(wartosc);
	if (tail == 0) {
		tail = newNode;
	}
	else {
		newNode->next = head;
	}
	head = newNode;
	rozmiar++;
}

void listaJednokierunkowa::dodajNaKoniec(int wartosc) {
	Node* newNode = new Node(wartosc);
	if (head == 0) {
		head = newNode;
	}
	else {
		tail->next = newNode;
	}
	tail = newNode;
	rozmiar++;
}

void listaJednokierunkowa::dodaj(int wartosc, int indeks) {
	if (indeks > rozmiar) {
		cout << " jest poza granicami\n";
	}
	if (indeks == 0) {
		dodajNaPoczatek(wartosc);
	}
	if (indeks == rozmiar) {
		dodajNaKoniec(wartosc);
	}
	Node* newNode = new Node(wartosc);
	Node* current = head;
	for (int i = 1; i < indeks; ++i) {
		current = current->next;
	}
	newNode->next = current->next;
	current->next = newNode;
	rozmiar++;
}
void listaJednokierunkowa::usunZPoczatku() {
	if (head == 0) {
		cout << "Nie ma elementów\n";
	}
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	rozmiar--;
}

void listaJednokierunkowa::usunZKoncu() {
	if (head == 0) {
		cout << "Nie ma elementów\n";
	}
	Node* temp = tail;
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* current = head;
		for (int i = 1; i < rozmiar - 1; i++) {
			current = current->next;
		}
		current->next = nullptr;
		tail = current;
	}
	delete temp;
	rozmiar--;
}

void listaJednokierunkowa::usun(int indeks) {
	if (indeks >= rozmiar) cout << "Jest poza granicami\n";
	if (indeks == 0) return this->usunZPoczatku();
	if (indeks == rozmiar - 1) return this->usunZKoncu();
	Node* previous = head;
	int i = 0;
	while (i < indeks - 1) {
		previous = previous->next;
		i++;
	}
	Node* usunac = previous->next;
	int wartosc = usunac->dane;
	previous->next = usunac->next;
	rozmiar--;
	delete usunac;
}

bool listaJednokierunkowa::wyszukiwanie(int wartosc) {
	Node* current = head;
	while (current) {
		if (current->dane == wartosc) {
			return true;
		}
		current = current->next;
	}
	return false;
}

int listaJednokierunkowa::pobierz(int indeks) const {
	if (indeks >= rozmiar) {
		cout << "Jest poza granicami\n";
		return 0;
	}
	if (indeks == rozmiar - 1) {
		return tail->dane;
	}
	Node* current = head;
	for (int i = 0; i < indeks; i++) {
		current = current->next;
	}
	return current->dane;
}

void listaJednokierunkowa::wyswietl() {
	Node* current = head;
	while (current) {
		cout << "Lista jednokierunkowa: " << current->dane;
		current = current->next;
	}
}

int listaJednokierunkowa::getRozmiar() const {
	return rozmiar;
}


void listaJednokierunkowa::fillRandom(int count, int seed) { 
	srand(seed);
	for (int i = rozmiar; i < count; i++) {
		int wartosc = rand() % 10000;
		dodajNaKoniec(wartosc);
	}
}

void listaJednokierunkowa::clear() { 
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
	rozmiar = 0;
}
