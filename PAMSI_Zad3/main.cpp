#include<iostream>
#include<vector>
#include "Plansza.h"
#include "si.h"

int main()
{
    int dana;   //Wczytywanie danych
    int c;
    si b;
    std::cout << "Podaj rozmiar planszy:" << std::endl;
    std::cin >> dana;
    Plansza plansza1(dana);
    plansza1.Zmien_rozmiar(dana);
    std::cout << "Podaj ile znakow w jednej linii wygrywa:" << std::endl;
    std::cin >> dana;
    if(dana > plansza1.Wez_rozmiar())
    {
        std::cerr << "Zle podane parametry gra nie mozliwa";
        return 0;
    }
    else
    {
        plansza1.Zmien_ile_wygrana(dana);
    }

    //b.Ruch(plansza1); //komputer rusza sie jako pierwszy
    //plansza1.Wyswietl();

    while(1) //petla w ktorej odbywa sie rozrywka, na przemian ruchy gracza-komputera i gracza-czlowieka gra sie konczy kiedy jeden z nich wygra lub bedzie remis
    {
        plansza1.Ruch_gracza();
        c = plansza1.Czy_wygrywa();
        if (c==-100)
        {
            plansza1.Wyswietl();
            std:: cout <<"==========WYGRANA================";
            break;
        }
        if (c==0)
        {
            plansza1.Wyswietl();
            std:: cout <<"=========REMIS============";
            break;
        }
        b.Ruch(plansza1);
        c = plansza1.Czy_wygrywa();
        if (c==100)
        {
            plansza1.Wyswietl();
            std:: cout <<"=========PRZEGRANA===============";
            break;
        }
        if (c==0)
        {
            plansza1.Wyswietl();
            std:: cout <<"==========REMIS=========";
            break;
        }
        plansza1.Wyswietl();
    }
}
