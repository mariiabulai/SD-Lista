#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <string>

#include "DlaWszystkich.h"

using namespace std;
using namespace std::chrono;

//Szablon funkcji mierzacy czas wykonania dowolnej funkcji
template<typename Function>
long long measure_time(Function func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    nanoseconds elapsed = duration_cast<nanoseconds>(end - start);
    return elapsed.count(); // Zwraca czas w nanosekundach
}

int main() {
    //Tablice rozmiarów danych testowych i nasion losowych
    const int rozmiarS[] = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };
    const int TESTS = 100;
    const int SEEDS[] = { 250, 300, 350, 400, 450, 500, 550, 600, 650, 700 };

    //Pliki wyjściowe do zapisu wyników
    ofstream tablicaDynamicznaPlik("D:\\SD\\miniprojekt1\\tablicaDynamiczna.txt");
    ofstream listaJednokierunkowaPlik("D:\\SD\\miniprojekt1\\listaJednokierunkowa.txt");
    ofstream listaDwukierunkowaPlik("D:\\SD\\miniprojekt1\\listaDwukierunkowa.txt");

    //Sprawdzenie poprawności otwarcia plików
    if (!tablicaDynamicznaPlik.is_open() || !listaJednokierunkowaPlik.is_open() || !listaDwukierunkowaPlik.is_open()) {
        cout << "Blad" << endl;
    }

    //Tablica dynamiczna
    for (int rozmiar : rozmiarS) {
        //Wypisanie aktualnego rozmiaru
        cout << "\nTablica dynamiczna: Rozmiar: " << rozmiar << endl;
        tablicaDynamicznaPlik << "\nTablica dynamiczna: Rozmiar: " << rozmiar << endl;
        int seedCount = 0;
        //Sumy czasów operacji (do obliczenia średniej)
        double tablica_dodajNaPoczatku = 0.0;
        double tablica_dodajNaKoncu = 0.0;
        double tablica_dodaj = 0.0;
        double tablica_usunZPoczatku = 0.0;
        double tablica_usunZKoncu = 0.0;
        double tablica_usun = 0.0;
        double tablica_wyszukiwanie = 0.0;

        for (int seed : SEEDS) {
            //Ustawienie seed'u
            srand(seed);
            tablicaDynamiczna tablica;
            //Lokalne sumy dla danego seed'u
            double tablica_dodajNaPoczatku_suma = 0.0;
            double tablica_dodajNaKoniec_suma = 0.0;
            double tablica_dodaj_suma = 0.0;
            double tablica_usunZPoczatku_suma = 0.0;
            double tablica_usunZKoncu_suma = 0.0;
            double tablica_usun_suma = 0.0;
            double tablica_wyszukiwanie_suma = 0.0;

            for (int i = 0; i < TESTS; i++) {
                tablica.fillRandom(rozmiar, seed);
                //Pomiar czasu dla różnych operacji
                int wartosc = rand() % 10000;
                tablica_dodajNaPoczatku_suma += measure_time([&]() {
                    tablica.dodajNaPoczatek(wartosc);
                    });
                wartosc = rand() % 10000;
                tablica_dodajNaKoniec_suma += measure_time([&]() {
                    tablica.dodajNaKoniec(wartosc);
                    });
                wartosc = rand() % 10000;
                int indeks = (tablica.getRozmiar() > 0) ? (rand() % tablica.getRozmiar()) : 0;
                tablica_dodaj_suma += measure_time([&]() {
                    tablica.dodaj(wartosc, indeks);
                    });
                tablica.fillRandom(rozmiar, seed);
                if (tablica.getRozmiar() > 0) {
                    int remove_indeks = rand() % tablica.getRozmiar();
                    tablica_usun_suma += measure_time([&]() {
                        tablica.usun(remove_indeks);
                        });
                }
                tablica.fillRandom(rozmiar, seed);
                if (tablica.getRozmiar() > 0) {
                    tablica_usunZPoczatku_suma += measure_time([&]() {
                        tablica.usunZPoczatku();
                        });
                }
                tablica.fillRandom(rozmiar, seed);
                if (tablica.getRozmiar() > 0) {
                    tablica_usunZKoncu_suma += measure_time([&]() {
                        tablica.usunZKoncu();
                        });
                }
                int search_wartosc = rand() % 10000;
                tablica_wyszukiwanie_suma += measure_time([&]() {
                    tablica.wyszukiwanie(search_wartosc);
                    });
            }

            //Dodanie średnich z danego seed'a
            tablica_dodajNaPoczatku += tablica_dodajNaPoczatku_suma / TESTS;
            tablica_dodajNaKoncu += tablica_dodajNaKoniec_suma / TESTS;
            tablica_dodaj += tablica_dodaj_suma / TESTS;
            tablica_usun += tablica_usun_suma / TESTS;
            tablica_usunZPoczatku += tablica_usunZPoczatku_suma / TESTS;
            tablica_usunZKoncu += tablica_usunZKoncu_suma / TESTS;
            tablica_wyszukiwanie += tablica_wyszukiwanie_suma / TESTS;
            seedCount++;
        }

        //Wypisanie średnich wyników
        cout << "\nWyniki tablica dynamiczna: Rozmiar: " << rozmiar << " ( " << seedCount << " seedow):\n";
        tablicaDynamicznaPlik << "\nWyniki tablica dynamiczna: Rozmiar: " << rozmiar << " ( " << seedCount << " seedow):\n";
        cout << "Dodanie na poczatek: " << (tablica_dodajNaPoczatku / seedCount) << " ns\n" <<
            "Dodanie na koniec: " << (tablica_dodajNaKoncu / seedCount) << " ns\n" <<
            "Dodanie z indeksem: " << (tablica_dodaj / seedCount) << " ns\n" <<
            "Usuniecie z poczatku: " << (tablica_usunZPoczatku / seedCount) << " ns\n" <<
            "Usuniecie z konca: " << (tablica_usunZKoncu / seedCount) << " ns\n" <<
            "Usuniecie z indeksem: " << (tablica_usun / seedCount) << " ns\n" <<
            "Wyszukiwanie: " << (tablica_wyszukiwanie / seedCount) << " ns\n";

        tablicaDynamicznaPlik << "Dodanie na poczatek: " << (tablica_dodajNaPoczatku / seedCount) << " ns\n" <<
            "Dodanie na koniec: " << (tablica_dodajNaKoncu / seedCount) << " ns\n" <<
            "Dodanie z indeksem: " << (tablica_dodaj / seedCount) << " ns\n" <<
            "Usuniecie z poczatku: " << (tablica_usunZPoczatku / seedCount) << " ns\n" <<
            "Usuniecie z konca: " << (tablica_usunZKoncu / seedCount) << " ns\n" <<
            "Usuniecie z indeksem: " << (tablica_usun / seedCount) << " ns\n" <<
            "Wyszukiwanie: " << (tablica_wyszukiwanie / seedCount) << " ns\n";
    }


    //Lista jednokierunkowa
    for (int rozmiar : rozmiarS) {
        //Wypisanie aktualnego rozmiaru
        cout << "\nLista jednokierunkowa: Rozmiar: " << rozmiar << endl;
        listaJednokierunkowaPlik << "\nLista jednokierunkowa: Rozmiar: " << rozmiar << endl;

        //Sumy czasów operacji (do obliczenia średniej)
        double jednokier_dodajNaPoczatku = 0.0;
        double jednokier_dodajNaKoniec = 0.0;
        double jednokier_dodaj = 0.0;
        double jednokier_usunZPoczatku = 0.0;
        double jednokier_usunZKoncu = 0.0;
        double jednokier_usun = 0.0;
        double jednokier_wyszukiwanie = 0.0;
        int seedCount = 0;

        for (int seed : SEEDS) {
            //Ustawienie seed'u
            srand(seed);
            //Lokalne sumy dla danego seed'u
            double jednokier_dodajNaPoczatku_suma = 0.0;
            double jednokier_dodajNaKoniec_suma = 0.0;
            double jednokier_dodaj_suma = 0.0;
            double jednokier_usunZPoczatku_suma = 0.0;
            double jednokier_usunZKoncu_suma = 0.0;
            double jednokier_usun_suma = 0.0;
            double jednokier_wyszukiwanie_suma = 0.0;

            listaJednokierunkowa jednokierunkowa;

            //Pomiar czasu dla różnych operacji
            for (int i = 0; i < TESTS; i++) {
                jednokierunkowa.fillRandom(rozmiar, seed);
                int wartosc = rand() % 10000;
                jednokier_dodajNaPoczatku_suma += measure_time([&]() {
                    jednokierunkowa.dodajNaPoczatek(wartosc);
                    });
                wartosc = rand() % 10000;
                jednokier_dodajNaKoniec_suma += measure_time([&]() {
                    jednokierunkowa.dodajNaKoniec(wartosc);
                    });
                wartosc = rand() % 10000;
                jednokier_dodaj_suma += measure_time([&]() {
                    jednokierunkowa.dodaj(wartosc, rand() % jednokierunkowa.getRozmiar());
                    });
                jednokierunkowa.fillRandom(rozmiar, seed);
                jednokier_usun_suma += measure_time([&]() {
                    jednokierunkowa.usun(rand() % jednokierunkowa.getRozmiar());
                    });
                jednokierunkowa.fillRandom(rozmiar, seed);
                jednokier_usunZPoczatku_suma += measure_time([&]() {
                    jednokierunkowa.usunZPoczatku();
                    });
                jednokierunkowa.fillRandom(rozmiar, seed);
                jednokier_usunZKoncu_suma += measure_time([&]() {
                    jednokierunkowa.usunZKoncu();
                    });
                jednokier_wyszukiwanie_suma += measure_time([&]() {
                    jednokierunkowa.wyszukiwanie(rand() % 10000);
                    });
            }

            //Dodanie średnich z danego seed'a
            jednokier_dodajNaPoczatku += jednokier_dodajNaPoczatku_suma / TESTS;
            jednokier_dodajNaKoniec += jednokier_dodajNaKoniec_suma / TESTS;
            jednokier_dodaj += jednokier_dodaj_suma / TESTS;
            jednokier_usun += jednokier_usun_suma / TESTS;
            jednokier_usunZPoczatku += jednokier_usunZPoczatku_suma / TESTS;
            jednokier_usunZKoncu += jednokier_usunZKoncu_suma / TESTS;
            jednokier_wyszukiwanie += jednokier_wyszukiwanie_suma / TESTS;
            seedCount++;
        }


        //Wypisanie średnich wyników
        cout << "\nWyniki lista jednokierunkowa: Rozmiar: " << rozmiar << " ( " << seedCount << " seedow):\n";
        listaJednokierunkowaPlik << "\nWyniki lista jednokierunkowa: Rozmiar: " << rozmiar << " ( " << seedCount << " seedow):\n";
        cout << "Dodanie na poczatek: " << (jednokier_dodajNaPoczatku / seedCount) << " ns\n" <<
            "Dodanie na koniec: " << (jednokier_dodajNaKoniec / seedCount) << " ns\n" <<
            "Dodanie z indeksem: " << (jednokier_dodaj / seedCount) << " ns\n" <<
            "Usuniecie z poczatku: " << (jednokier_usunZPoczatku / seedCount) << " ns\n" <<
            "Usuniecie z konca: " << (jednokier_usunZKoncu / seedCount) << " ns\n" <<
            "Usuniecie z indeksem: " << (jednokier_usun / seedCount) << " ns\n" <<
            "Wyszukiwanie: " << (jednokier_wyszukiwanie / seedCount) << " ns\n";

        listaJednokierunkowaPlik << "Dodanie na poczatek: " << (jednokier_dodajNaPoczatku / seedCount) << " ns\n" <<
            "Dodanie na koniec: " << (jednokier_dodajNaKoniec / seedCount) << " ns\n" <<
            "Dodanie z indeksem: " << (jednokier_dodaj / seedCount) << " ns\n" <<
            "Usuniecie z poczatku: " << (jednokier_usunZPoczatku / seedCount) << " ns\n" <<
            "Usuniecie z konca: " << (jednokier_usunZKoncu / seedCount) << " ns\n" <<
            "Usuniecie z indeksem: " << (jednokier_usun / seedCount) << " ns\n" <<
            "Wyszukiwanie: " << (jednokier_wyszukiwanie / seedCount) << " ns\n";
    }

    //Lista dwukierunkowa
    for (int rozmiar : rozmiarS) {
        //Wypisanie aktualnego rozmiaru
        cout << "\nLista dwukierunkowa: Rozmiar: " << rozmiar << endl;
        listaDwukierunkowaPlik << "\nLista dwukierunkowa: Rozmiar: " << rozmiar << endl;

        //Sumy czasów operacji (do obliczenia średniej)
        double dwukier_dodajNaPoczatku = 0.0;
        double dwukier_dodajNaKoniec = 0.0;
        double dwukier_dodaj = 0.0;
        double dwukier_usunZPoczatku = 0.0;
        double dwukier_usunZKoncu = 0.0;
        double dwukier_usun = 0.0;
        double dwukier_wyszukiwanie = 0.0;
        int seedCount = 0;

        for (int seed : SEEDS) {
            //Ustawienie seed'u
            srand(seed);
            //Lokalne sumy dla danego seed'u
            double dwukier_dodajNaPoczatku_suma = 0.0;
            double dwukier_dodajNaKoniec_suma = 0.0;
            double dwukier_dodaj_suma = 0.0;
            double dwukier_usunZPoczatku_suma = 0.0;
            double dwukier_usunZKoncu_suma = 0.0;
            double dwukier_usun_suma = 0.0;
            double dwukier_wyszukiwanie_suma = 0.0;

            listaDwukierunkowa dwukierunkowa;

            //Pomiar czasu dla różnych operacji
            for (int i = 0; i < TESTS; i++) {
                dwukierunkowa.fillRandom(rozmiar, seed);
                int wartosc = rand() % 10000;
                dwukier_dodajNaPoczatku_suma += measure_time([&]() {
                    dwukierunkowa.dodajNaPoczatek(wartosc);
                    });
                wartosc = rand() % 10000;
                dwukier_dodajNaKoniec_suma += measure_time([&]() {
                    dwukierunkowa.dodajNaKoniec(wartosc);
                    });
                wartosc = rand() % 10000;
                dwukier_dodaj_suma += measure_time([&]() {
                    dwukierunkowa.dodaj(wartosc, rand() % dwukierunkowa.getRozmiar());
                    });
                dwukierunkowa.clear();
                dwukierunkowa.fillRandom(rozmiar, seed);
                dwukier_usun_suma += measure_time([&]() {
                    dwukierunkowa.usun(rand() % dwukierunkowa.getRozmiar());
                    });
                dwukierunkowa.clear();
                dwukierunkowa.fillRandom(rozmiar, seed);
                dwukier_usunZPoczatku_suma += measure_time([&]() {
                    dwukierunkowa.usunZPoczatku();
                    });
                dwukierunkowa.clear();
                dwukierunkowa.fillRandom(rozmiar, seed);
                if (dwukierunkowa.getRozmiar() > 0) {
                    dwukier_usunZKoncu_suma += measure_time([&]() {
                        dwukierunkowa.usunZKoncu();
                        });
                }
                int search_wartosc = rand() % 10000;
                dwukier_wyszukiwanie_suma += measure_time([&]() {
                    dwukierunkowa.wyszukiwanie(search_wartosc);
                    });
            }

            //Dodanie średnich z danego seed'a
            dwukier_dodajNaPoczatku += dwukier_dodajNaPoczatku_suma / TESTS;
            dwukier_dodajNaKoniec += dwukier_dodajNaKoniec_suma / TESTS;
            dwukier_dodaj += dwukier_dodaj_suma / TESTS;
            dwukier_usun += dwukier_usun_suma / TESTS;
            dwukier_usunZPoczatku += dwukier_usunZPoczatku_suma / TESTS;
            dwukier_usunZKoncu += dwukier_usunZKoncu_suma / TESTS;
            dwukier_wyszukiwanie += dwukier_wyszukiwanie_suma / TESTS;
            seedCount++;
        }

        //Wypisanie średnich wyników
        cout << "\nWyniki lista dwukierunkowa: Rozmiar: " << rozmiar << " ( " << seedCount << " seedow):\n";
        listaDwukierunkowaPlik << "\nWyniki lista dwukierunkowa: Rozmiar: " << rozmiar << " ( " << seedCount << " seedow):\n";
        cout << "Dodanie na poczatek: " << (dwukier_dodajNaPoczatku / seedCount) << " ns\n" <<
            "Dodanie na koniec: " << (dwukier_dodajNaKoniec / seedCount) << " ns\n" <<
            "Dodanie z indeksem: " << (dwukier_dodaj / seedCount) << " ns\n" << \
            "Usuniecie z poczatku: " << (dwukier_usunZPoczatku / seedCount) << " ns\n" <<
            "Usuniecie z konca: " << (dwukier_usunZKoncu / seedCount) << " ns\n" <<
            "Usuniecie z indeksem: " << (dwukier_usun / seedCount) << " ns\n" <<
            "Wyszukiwanie: " << (dwukier_wyszukiwanie / seedCount) << " ns\n";

        listaDwukierunkowaPlik << "Dodanie na poczatek: " << (dwukier_dodajNaPoczatku / seedCount) << " ns\n" <<
            "Dodanie na koniec: " << (dwukier_dodajNaKoniec / seedCount) << " ns\n" <<
            "Dodanie z indeksem: " << (dwukier_dodaj / seedCount) << " ns\n" <<
            "Usuniecie z poczatku: " << (dwukier_usunZPoczatku / seedCount) << " ns\n" <<
            "Usuniecie z konca: " << (dwukier_usunZKoncu / seedCount) << " ns\n" <<
            "Usuniecie z indeksem: " << (dwukier_usun / seedCount) << " ns\n" <<
            "Wyszukiwanie: " << (dwukier_wyszukiwanie / seedCount) << " ns\n";
    }

    tablicaDynamicznaPlik.close();
    listaDwukierunkowaPlik.close();
    listaJednokierunkowaPlik.close();

    return 0;
}
