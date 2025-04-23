#include <iostream>   
#include <chrono>
#include <thread>
#include <cstdlib>
#include "DlaWszystkich.h"

using namespace std;
using namespace std::chrono;

const int SEED = 100;

void tablicamenu(DlaWszystkich* dlaWszyskich) {
    int choice, wartosc, indeks;
    do {
        cout << "\nTablica dynamiczna \n";
        cout << " 1. Utworz losowo \n 2. Wyswietl \n 3. Dodaj na poczatek \n 4. Dodaj na koniec \n 5. Dodaj z indeksem \n" << 
            " 6. Usun z poczatku \n 7. Usun z konca \n 8. Usun z indeksu \n 9. Wyszukiwanie \n" <<
            " 10. Wyczysc \n 0. Wyjdz \n";
        cout << "Wybor: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Rozmiar: "; cin >> wartosc;
            dlaWszyskich->fillRandom(wartosc, SEED);
            break;
        case 2:
            dlaWszyskich->wyswietl();
            break;
        case 3:
            cout << "Podaj wartosc: "; cin >> wartosc;
            dlaWszyskich->dodajNaPoczatek(wartosc);
            break;
        case 4:
            cout << "Podaj wartosc: "; cin >> wartosc;
            dlaWszyskich->dodajNaKoniec(wartosc);
            break;
        case 5:
            cout << "Podaj wartosc: "; cin >> wartosc;
            cout << "Podaj indeks: "; cin >> indeks;
            dlaWszyskich->dodaj(wartosc, indeks);
            break;
        case 6:
            dlaWszyskich->usunZPoczatku();
            break;
        case 7:
            dlaWszyskich->usunZKoncu();
            break;
        case 8:
            cout << "Podaj indeks: "; cin >> indeks;
            dlaWszyskich->usun(indeks);
            break;
        case 9:
            cout << "Podaj wartosc: ";
            cin >> wartosc;
            bool znaleziono = dlaWszyskich->wyszukiwanie(wartosc);
            if (!znaleziono) {
                cout << "Nie znaleziono.\n";
            }
            else {
                cout << "Znaleziono " << wartosc << " w liscie.\n";
            }
        case 10:
            dlaWszyskich->clear();
            break;
        }

    } while (choice != 0);
}

void jednokmenu(listaJednokierunkowa& list) {
    int choice, wartosc, indeks;
    do {
        cout << "\nTablica dynamiczna \n";
        cout << " 1. Utworz losowo \n 2. Wyswietl \n 3. Dodaj na poczatek \n 4. Dodaj na koniec \n 5. Dodaj z indeksem \n" << 
            " 6. Usun z poczatku \n 7. Usun z konca \n 8. Usun z indeksu \n 9. Wyszukiwanie \n" <<
            " 10. Wyczysc \n 0. Wyjdz \n";
        cout << "Wybor: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Rozmiar: "; cin >> wartosc;
            list.fillRandom(wartosc, SEED);
            break;
        case 2:
            list.wyswietl();
            break;
        case 3:
            cout << "Podaj wartosc: "; cin >> wartosc;
            list.dodajNaPoczatek(wartosc);
            break;
        case 4:
            cout << "Podaj wartosc: "; cin >> wartosc;
            list.dodajNaKoniec(wartosc);
            break;
        case 5:
            cout << "Podaj wartosc: "; cin >> wartosc;
            cout << "Podaj indeks: "; cin >> indeks;
            list.dodaj(wartosc, indeks);
            break;
        case 6:
            list.usunZPoczatku();
            break;
        case 7:
            list.usunZKoncu();
            break;
        case 8:
            cout << "Podaj indeks: "; cin >> indeks;
            list.usun(indeks);
            break;
        case 9:
            cout << "Podaj wartosc: ";
            cin >> wartosc;
            bool znaleziono = list.wyszukiwanie(wartosc);
            if (!znaleziono) {
                cout << "Nie znaleziono.\n";
            }
            else {
                cout << "Znaleziono " << wartosc << " w liscie.\n";
            }
        case 10:
            list.clear();
            break;
        }

    } while (choice != 0);
}

void dwukmenu(listaDwukierunkowa& list2) {
    int choice, wartosc, indeks;
    do {
        cout << "\nTablica dynamiczna \n";
        cout << " 1. Utworz losowo \n 2. Wyswietl \n 3. Dodaj na poczatek \n 4. Dodaj na koniec \n 5. Dodaj z indeksem \n" <<
            " 6. Usun z poczatku \n 7. Usun z konca \n 8. Usun z indeksu \n 9. Wyszukiwanie \n" <<
            " 10. Wyczysc \n 0. Wyjdz \n";
        cout << "Wybor: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Rozmiar: "; cin >> wartosc;
            list2.fillRandom(wartosc, SEED);
            break;
        case 2:
            list2.wyswietl();
            break;
        case 3:
            cout << "Podaj wartosc: "; cin >> wartosc;
            list2.dodajNaPoczatek(wartosc);
            break;
        case 4:
            cout << "Podaj wartosc: "; cin >> wartosc;
            list2.dodajNaKoniec(wartosc);
            break;
        case 5:
            cout << "Podaj wartosc: "; cin >> wartosc;
            cout << "Podaj indeks: "; cin >> indeks;
            list2.dodaj(indeks, wartosc);
            break;
        case 6:
            list2.usunZPoczatku();
            break;
        case 7:
            list2.usunZKoncu();
            break;
        case 8:
            cout << "Podaj indeks: "; cin >> indeks;
            list2.usun(indeks);
            break;
        case 9: {
            cout << "Podaj wartosc: ";
            cin >> wartosc;
            bool znaleziono = list2.wyszukiwanie(wartosc);
            if (!znaleziono) {
                cout << "Nie znaleziono.\n";
            }
            else {
                cout << "Znaleziono " << wartosc << " w liscie.\n";
            }
        }
        case 10:
            list2.clear();
            break;
        }

    } while (choice != 0);
}

int main() {
    tablicaDynamiczna* arr = nullptr;
    listaJednokierunkowa* list = nullptr;
    listaDwukierunkowa* list2 = nullptr;
    int choice;
    do {
        cout << "MENU\n";
        cout << "1. Tablica dynamiczna \n";
        cout << "2. Lista jednokierunkowa \n";
        cout << "3. Lista jednokierunkowa \n";
        cout << "0. Wyjdz \n";
        cout << "Wybor: ";
        cin >> choice;

        switch (choice) {
        case 1:
            arr = new tablicaDynamiczna;
            tablicamenu(arr);
            delete arr;
            arr = nullptr;
            break;
        case 2:
            list = new listaJednokierunkowa;
            jednokmenu(*list);
            delete list;
            list = nullptr;
            break;
        case 3:
            list2 = new listaDwukierunkowa;
            dwukmenu(*list2);
            delete list2;
            list2 = nullptr;
            break;
        }

    } while (choice != 0);

    return 0;
}
