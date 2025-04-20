#include "DlaWszystkich.h"
#include <iostream>
#include <cstring>

using namespace std;

listaDwukierunkowa::listaDwukierunkowa() : head(nullptr), tail(nullptr), rozmiar(0) {}

listaDwukierunkowa::~listaDwukierunkowa() {
	Node* teraz = head;
	while (teraz) {
		Node* temp = teraz;
		teraz = teraz->next;
		delete temp;
	}
}

//Tworzy nowy wezel i umieszcza go na poczatku listy.
//Jesli lista byla pusta, ustawia tez tail na ten element.
void listaDwukierunkowa::dodajNaPoczatek(int wartosc) {
	Node* newNode = new Node(wartosc);
	if (head == 0) {
		tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
	}
	head = newNode;
	rozmiar++;
}

void listaDwukierunkowa::dodajNaKoniec(int wartosc) {
	Node* newNode = new Node(wartosc);
	if (head == 0) {
		head = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
	}
	tail = newNode;
	rozmiar++;
}


//Dodaje nowy wezel na wskazanej pozycji w liscie.
//Uzywa optymalnej trasy (od head lub od tail) w zaleznosci od indeksu.
void listaDwukierunkowa::dodaj(int wartosc, int indeks) {
	if (indeks > rozmiar) {
		cout << " jest poza granicami\n";
	}
	if (indeks == 0) {
		this->dodajNaPoczatek(wartosc);
	}
	if (indeks == rozmiar) {
		this->dodajNaKoniec(wartosc);
	}
	Node* newNode = new Node(wartosc);
	Node* current;
	if (indeks <= rozmiar / 2) {
		current = head;
		for (int i = 1; i < indeks; ++i) {
			current = current->next;
		}
	}
	else {
		current = tail;
		for (int i = rozmiar - 1; i > indeks; --i) {
			current = current->prev;
		}
	}
	newNode->next = current->next;
	newNode->prev = current;
	if (current->next) {
		current->next->prev = newNode;
	}
	current->next = newNode;
	rozmiar++;
}

void listaDwukierunkowa::usunZPoczatku() {
	if (head == 0) {
		cout << "Nie ma elementów\n";
	}
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* temp = head;
		head->next->prev = nullptr;
		head = head->next;
		delete temp;
	}
	rozmiar--;
}

void listaDwukierunkowa::usunZKoncu() {
	if (head == 0) {
		cout << "Nie ma elementów\n";
	}
	Node* temp = tail;
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		tail->prev->next = nullptr;
		tail = tail->prev;
		delete temp;
	}
	rozmiar--;
}

void listaDwukierunkowa::usun(int indeks) {
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
	if (indeks <= rozmiar / 2) {
		usunac = head;
		for (int i = 0; i < indeks; i++) {
			usunac = usunac->next;
		}
	}
	else {
		usunac = tail;
		for (int i = rozmiar - 1; i > indeks; i--) {
			usunac = usunac->prev;
		}
	}
	usunac->prev->next = usunac->next;
	usunac->next->prev = usunac->prev;
	rozmiar--;
	delete usunac;
}

//Szuka wartosci w liscie.
//Porownuje jednoczesnie z przodu i z tylu, by przyspieszyc wyszukiwanie.
bool listaDwukierunkowa::wyszukiwanie(int wartosc) {
	if (rozmiar == 0) return false;
	if (rozmiar == 1) return head->dane == wartosc;
	Node* front = head;
	Node* back = tail;
	while (front != back && front->prev != back) {
		if (front->dane == wartosc || back->dane == wartosc) {
			return true;
		}
		front = front->next;
		back = back->prev;
	}
	if (front == back && front->dane == wartosc) {
		return true;
	}

	return false;
}

int listaDwukierunkowa::pobierz(int indeks) const {
	if (indeks >= rozmiar) {
		cout << "Jest poza granicami\n";
		return 0;
	}
	Node* current = nullptr;
	size_t dystansOdHead = indeks;
	size_t dystansOdTail = rozmiar - 1 - indeks;
	if (dystansOdHead <= dystansOdTail) {
		current = head;
		while (dystansOdHead--) {
			current = current->next;
		}
	}
	else {
		current = tail;
		while (dystansOdTail--) {
			current = current->prev;
		}
	}
	return current->dane;
}

void listaDwukierunkowa::wyswietl() {
	Node* current = head;
	while (current) {
		cout << "Lista dwukierunkowa: " << current->dane;
		current = current->next;
	}
}

int listaDwukierunkowa::getRozmiar() const {
	return rozmiar;
}


void listaDwukierunkowa::fillRandom(int count, int seed) { 
	srand(seed);
	for (int i = rozmiar; i < count; i++) {
		int wartosc = rand() % 10000;
		dodajNaKoniec(wartosc);
	}
}

void listaDwukierunkowa::clear() {
	Node* current = head;
	while (current) {
		Node* next = current->next; 
		delete current;            
		current = next;            
	}
	head = nullptr; 
	tail = nullptr; 
}
