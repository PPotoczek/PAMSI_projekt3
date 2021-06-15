#include "si.h"

int si::MinMax(Plansza tablica, int glebia, bool min_czy_max, int alfa, int beta)
{
    int wynik ;
    int najlepszy_wynik;
    if(glebia == tablica.Wez_glebie_max()) // ograniczamy rekurencyjnosc algorytmu min max glebia, poniwaz przy wiekszych planszach mozna w nieskanczonosc czekac na ruch komputera
    {
        return 0; //zwracam 0, poniewaz nie mozna stwierdzic czy ten ruch jest dobry czy zly
    }
    if(tablica.Czy_wygrywa() == 100 || tablica.Czy_wygrywa() == 0 || tablica.Czy_wygrywa() == -100) //jezeli parametr glebi nas nie zatrzymal i doszlismy do "konca" rozgrywki
    {                                                                                            // zwracam teraz odpowiednio wartosc w zaleznosci kto wygral tudziez czy byl remis
        return tablica.Czy_wygrywa();                                                           // dla tego danego przypadku rozegrania gry
    }
    if(min_czy_max == true)
    {
        najlepszy_wynik = 10000; //gracz minimalizujacy szuka ruchow o jak najmniejszej wartosci dlatego najlepszy wynik na poczatku bedzie rowny +nieskonczonosc
        for(int i=0;i<tablica.Wez_rozmiar();i++)
        {
            for(int j=0;j<tablica.Wez_rozmiar();j++)
            {
                if(tablica.Wez_pole(i,j)==0) //sprawdzamy czy pole jest puste jak tak to robimy tam ruch
                {
                    tablica.Zmien_pole(i,j,1);  //robie ruch
                    tablica.Zmien_ostatnie_koordynaty(i,j); //zapusuje koordynaty tego ruchu
                    wynik = MinMax(tablica,glebia+1,false,alfa, beta);  //szukam ewaluacji tego ruchu
                    tablica.Zmien_pole(i,j,0); //cofamy ruch, dzieki algorytmowi minmax znamy ewaluacje tego ruchu i mozemy stwierdzic czy jest on dobry czy zly
                    if(wynik < najlepszy_wynik) //sprawdzamy czy wynik tego ruchu jest mniejszy niz najlepszy dotychczasowy wynik
                    {
                        najlepszy_wynik = wynik;
                    }
                    if(wynik < beta) //sprawdzam czy uzyskany wynik jest mniejszy niz beta jak tak to beta jest rowna uzyskanemu wynikowi
                    {
                        beta = wynik;
                    }
                    if(beta <=  alfa)   //przycinanie galezi za pomoca ciec alfa beta
                    {
                        break;          //szybsze wyjscie z petli nie ma potrzeby sprawdzac pozostalych ruchow
                    }
                }
            }
            if(beta <=  alfa)
            {
                break;
            }
        }
        return najlepszy_wynik+glebia; //jezeli przegrana jest 'nieunikniona' to lepiej przegrac w wiekszej ilosci ruchow byc moze gracz-czlowiek nie zagra perfekcyjnie (tak jak zakladamy) wiec lepiej przedluzac rozgrywke
    }                                  //dlatego dodajemy glebie
    if(min_czy_max == false)
    {   //tu analogicznie tylko gracz maksymujacy
        najlepszy_wynik = -10000; //gracz maksymalizujacy wiec najlepszy wynik ustawiam na - nieskonczonosc
        for(int i=0;i<tablica.Wez_rozmiar();i++)
        {
            for(int j=0;j<tablica.Wez_rozmiar();j++)
            {
                if(tablica.Wez_pole(i,j)==0)
                {
                    tablica.Zmien_pole(i,j,2); //robie ruch
                    tablica.Zmien_ostatnie_koordynaty(i,j); //zapisuje koordynaty tego ruchu
                    wynik = MinMax(tablica,glebia+1,true, alfa, beta); //szukam ewaluacji
                    tablica.Zmien_pole(i,j,0); //cofam ruch (robilem go po to zeby ewaluacje uzyskac)
                    if(wynik > najlepszy_wynik) //porownuje sprawdzam czy jest wiekszy wynik niz dotychczas uzyskany
                    {
                        najlepszy_wynik = wynik;
                    }
                    if(wynik > alfa) //sprawdzam czy uzyskany wynik jest wiekszy niz alfa jak tak to alfa jest rowna uzyskanemu wynikowi
                    {
                        alfa = wynik;
                    }
                    if(beta <=  alfa) //przycinanie alfa beta
                    {
                        break;
                    }
                }
            }
            if(beta <=  alfa)
            {
                break;
            }
        }
        return najlepszy_wynik-glebia; //glebia rosnie z czasem wiec im szybciej znajdziemy zwycieski ruch tym lepiej dlatego odejmujemy glebie
    }
}

void si::Ruch(Plansza &tablica)
{
    int aktualnie_najlepszy_ruch[2];
    int wynik;
    int najlepszy_wynik = -10000; //komputer to gracz maksymalizujacy wiec najlepszy wynik ustawiam na poczatku na - nieskanczonosc
    for(int i=0;i<tablica.Wez_rozmiar();i++)
    {
        for(int j=0;j<tablica.Wez_rozmiar();j++)
        {
            if(tablica.Wez_pole(i,j)==0)
            {
                tablica.Zmien_pole(i,j,2); //ruszam sie w miejsce X żeby zobaczyć za pomoca algorytmu Min Max jak dobry jest ten ruch
                tablica.Zmien_ostatnie_koordynaty(i,j); //aktualizuje ostatnie koordynaty, zeby moc wywolac funkcje czy wygrywa od tego ruchu
                wynik = MinMax(tablica,0,true,-10000,10000); // sprawdzam ocene tego ruchu (czy jest 'dobry') ,na starcie glebia = 0 alfa = -nieskonczonosc beta = nieskonczonosc
                tablica.Zmien_pole(i,j,0); //cofam ten ruch, algorytm MinMax zworcil mi ocene tego ruchu nastepnie porownuje ta ocene z ocena innych ruchow
                if(wynik > najlepszy_wynik) //jezeli ruch byl lepszy niz dotychczasowy najlepszy ruch to on ot teraz jest nalepszym ruchem
                {
                    najlepszy_wynik = wynik;
                    aktualnie_najlepszy_ruch[0] = i;
                    aktualnie_najlepszy_ruch[1] = j;
                }
            }
        }
    }
    tablica.Zmien_pole(aktualnie_najlepszy_ruch[0],aktualnie_najlepszy_ruch[1],2); //znajac najlepszy ruch teraz jest on wykonywany
    tablica.Zmien_ostatnie_koordynaty(aktualnie_najlepszy_ruch[0],aktualnie_najlepszy_ruch[1]);
}
