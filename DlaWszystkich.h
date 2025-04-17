#pragma once

#include <iostream>
#include <string>

//Interfejs bazowy dla wszystkich struktur 

class DlaWszystkich {
public:
	virtual ~DlaWszystkich() = default;
	virtual int getRozmiar() const = 0;

	virtual void dodajNaPoczatek(int wartosc) = 0;
	virtual void dodajNaKoniec(int wartosc) = 0;
	virtual void dodaj(int wartosc, int indeks) = 0;

	virtual void usunZPoczatku() = 0;
	virtual void usunZKoncu() = 0;
	virtual void usun(int indeks) = 0;

	virtual bool wyszukiwanie(int wartosc) = 0;
	virtual int pobierz(int indeks) const = 0;

	virtual void wyswietl() = 0;
	virtual void clear() = 0;
	virtual void fillRandom(int count, int seed) = 0;
};

//Implementacja dynamicznej tablicy

class tablicaDynamiczna : public DlaWszystkich {
private:
	int rozmiar;
	int pojemnosc;
	int* tablica;

public:
	tablicaDynamiczna();
	~tablicaDynamiczna();
	int getRozmiar() const override;
	tablicaDynamiczna(int poczatkowaPojemnosc);
	void zmienRozmiar(int nowaPojemnosc);

	void dodajNaPoczatek(int wartosc) override;
	void dodajNaKoniec(int wartosc) override;
	void dodaj(int wartosc, int indeks) override;

	void usunZPoczatku() override;
	void usunZKoncu() override;
	void usun(int indeks) override;

	bool wyszukiwanie(int wartosc) override;
	int pobierz(int indeks) const override;

	void wyswietl() override;

	void fillRandom(int count, int seed);
	void clear() override;
};

//Implementacja listy jednokierunkowej

class listaJednokierunkowa : public DlaWszystkich {
private:
	int rozmiar;
	//Struktura wezla listy
	struct Node {
		int dane;
		Node* next;
		Node(int wartosc) : dane(wartosc), next(nullptr) {}
	};
	Node* head;
	Node* tail;
public:
	listaJednokierunkowa();
	~listaJednokierunkowa();
	int getRozmiar() const override;

	void dodajNaPoczatek(int wartosc) override;
	void dodajNaKoniec(int wartosc) override;
	void dodaj(int wartosc, int indeks) override;

	void usunZPoczatku() override;
	void usunZKoncu() override;
	void usun(int indeks) override;

	bool wyszukiwanie(int wartosc) override;
	int pobierz(int indeks) const override;

	void wyswietl() override;

	void fillRandom(int count, int seed);
	void clear();
};

//Implementacja listy dwukierunkowej

class listaDwukierunkowa : public DlaWszystkich {
private:
	int rozmiar;
	//Struktura wezla dwukierunkowego
	struct Node {
		int dane;
		Node* next;
		Node* prev;
		Node(int wartosc) : prev(nullptr), dane(wartosc), next(nullptr) {}
	};
	Node* head;
	Node* tail;
public:
	listaDwukierunkowa();
	~listaDwukierunkowa();
	int getRozmiar() const override;

	void dodajNaPoczatek(int wartosc) override;
	void dodajNaKoniec(int wartosc) override;
	void dodaj(int wartosc, int indeks) override;

	void usunZPoczatku() override;
	void usunZKoncu() override;
	void usun(int indeks) override;

	bool wyszukiwanie(int wartosc) override;
	int pobierz(int indeks) const override;

	void wyswietl() override;

	void fillRandom(int count, int seed);
	void clear();
};
