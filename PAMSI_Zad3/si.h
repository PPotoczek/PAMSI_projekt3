#ifndef PAMSI_GRA_SI_H
#define PAMSI_GRA_SI_H
#include <iostream>
#include <vector>
#include "Plansza.h"

class si {
public:
    int MinMax(Plansza tablica, int glebia, bool min_czy_max, int alfa, int beta); //algorytm MinMax
    void Ruch (Plansza &tablica); //funkcja generujaca ruch dla gracza-komputera (si)
};


#endif
