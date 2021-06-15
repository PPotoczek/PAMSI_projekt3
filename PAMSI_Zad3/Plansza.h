#ifndef PAMSI_GRA_PLANSZA_H
#define PAMSI_GRA_PLANSZA_H
#include<iostream>
#include<vector>

class Plansza
{
private:
    int rozmiar; //rozmiar planszy
    int ile_wygrana; //ile znakow potrzebne do wygrania
    std::vector<std::vector<int>> plansza; //plansza
    int ostatnie_koordynaty[2]; //koordynaty ostatniego polozonego znaku na planszy
    int glebia_max; //wartosc glebi dla danej planszy
public:
    Plansza(int liczba); //konstruktor pustej planszy
    int Wez_rozmiar();  //getery i setery
    void Zmien_rozmiar(int liczba);
    int Wez_ile_wygrana();
    void Zmien_ile_wygrana(int liczba);
    void Wez_ostatnie_koordynaty(int tab[]);
    void Zmien_ostatnie_koordynaty(int x, int y);
    void Zmien_pole(int x, int y, int znak);
    int Wez_pole(int x, int y);
    int Wez_glebie_max();
    void Wyswietl();    //funkcja do wyswietalnia planszy
    int Czy_wygrywa();  //funkcja ktora sprawdza czy ktorys z graczy wygral gre lub czy jest remis
    void Ruch_gracza(); //funkcja rejestrujaca ruch gracza na planszy
};


#endif
