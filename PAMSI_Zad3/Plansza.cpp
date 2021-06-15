#include "Plansza.h"

Plansza::Plansza(int liczba)
{
    rozmiar = liczba;
    plansza.resize(rozmiar); //generuje plansze NxN
    for(int i=0;i<rozmiar;i++)
    {
        plansza[i].resize(rozmiar);
    }
    for(int i=0;i<rozmiar;i++)
    {
        for(int j=0;j<rozmiar;j++)
        {
            plansza[i][j] = 0; //zapelniam ja zerami
        }
    }
    // ustawiam parametr glebi. Bedzie on potrzebny do ograniczenia algorytmu MinMax, szczegolnie dla duzych plansz, poniewaz inaczej czas oczekiwania na ruch sztucznej inteligencji
    // jest bardzo duzy
    if(rozmiar <=3)
    {
        glebia_max = 15; //ustawiam 15 ale i tak do niej nie dojdzie, algorytm dla plansz do 3x3 nie potrzebuje ograniczenia glebi, dla takich plansz dziala wystarczajaco szybko
    }
    if(rozmiar == 4)
    {
        glebia_max = 8;
    }
    if(rozmiar == 5)
    {
        glebia_max = 6;
    }
    if(rozmiar == 6)
    {
        glebia_max = 4;
    }
    if(rozmiar == 7)
    {
        glebia_max = 3;
    }
    if(rozmiar > 7)
    {
        glebia_max = 2;
    }
}

/*Getery i Setery*/


int Plansza::Wez_rozmiar()
{
    return rozmiar;
}

void Plansza::Zmien_rozmiar(int liczba)
{
    rozmiar = liczba;
}

int Plansza::Wez_ile_wygrana()
{
    return ile_wygrana;
}

void Plansza::Zmien_ile_wygrana(int liczba)
{
    ile_wygrana = liczba;
}

void Plansza::Wez_ostatnie_koordynaty(int tab[])
{
    tab[0] = ostatnie_koordynaty[0];
    tab[1] = ostatnie_koordynaty[1];
}

void Plansza::Zmien_ostatnie_koordynaty(int x, int y)
{
    ostatnie_koordynaty[0] = x;
    ostatnie_koordynaty[1] = y;
}

void Plansza::Zmien_pole(int x, int y, int znak)
{
    plansza[x][y] = znak;
}

int Plansza::Wez_pole(int x, int y)
{
    return plansza[x][y];
}

int Plansza::Wez_glebie_max()
{
    return glebia_max;
}

void Plansza::Wyswietl()
{
    for(int i=0;i<rozmiar;i++)
    {
        for(int j=0;j<rozmiar;j++)
        {
            std::cout << "--";
        }
        std::cout << '-';
        std::cout << std::endl;
        std::cout << '|';
        for(int j=0;j<rozmiar;j++)
        {
            if(plansza[i][j]==0)
            {
                std::cout << ' ';
            }
            if(plansza[i][j]==1)
            {
                std::cout << 'O';
            }
            if(plansza[i][j]==2)
            {
                std::cout << 'X';
            }
            std::cout << '|';
        }
        std::cout << std::endl;
    }
}

int Plansza::Czy_wygrywa()
{
    bool pusta_plansza = false;
    int ostatni_x = ostatnie_koordynaty[0];
    int ostatni_y = ostatnie_koordynaty[1];
    int znak = plansza[ostatni_x][ostatni_y];
    int zm_pom = ostatni_y;
    int ile_jest_w_rzedzie=0;
    //najpierw sprawdzam czy ostatni ruch zapewnil graczowi wygrana, nastepnie jesli nie to sprawdzane jest czy jest remis (zapelniona plansza i nikt nie wygral)
    // Patrzymy czy jest wygrana poziomo
    while(zm_pom>=0) //dopoki nie dojdziemy do gornej granicy planszy
    {
        if(plansza[ostatni_x][zm_pom] == znak)  //sprawdzam czy pole obok ma taki sam znak jak pole przez nas sprawdzane (ostatni ruch)
        {
            ile_jest_w_rzedzie++; //jak tak to zwiekszam zmienna lizaca ilosc tych samych znakow w rzedzie
        }
        else
        {
            break; //jak nie to wychodze z petli
        }
        zm_pom--;
    }
    zm_pom= ostatni_y; //resetuje wartosc zmienej pomocniczej
    while(zm_pom<plansza.size()) //dopoki nie dojdziemy do dolnej granicy planszy
    {
        if(plansza[ostatni_x][zm_pom] == znak)  //tu analogicznie
        {
            ile_jest_w_rzedzie++;
        }
        else
        {
            break;
        }
        zm_pom++;
    }
    if(ile_jest_w_rzedzie-1 >= ile_wygrana) //-1 bo dwa razy zaczynam sprawdzanie od ostatniego zrobionego ruchu przez co licze go podwojnie
    {                                       // aby wygrac trzeba miec X znakow w rzedzie, gdzie X jest ustalane na poczatku gry
        if(znak == 1)                       // teraz jak wygra kolko (gracz, my) to zwracana jest wartosc -100. Jest to potrzebne dla algorytmu MinMax
        {
            return -100;
        }
        else if(znak == 2)                  // jak wygra krzyżyk (si) to zwracana jest wartosc 100. Jest to potrzebne dla algorytmu MinMax
        {
            return 100;
        }
    }
    //Tutaj analogicznie sprawdzamy tylko czy wygrana jest pionowo (wczesniej poziomo)
    // Patrzymy czy jest wygrana pionowo
    ile_jest_w_rzedzie = 0;
    zm_pom = ostatni_x;
    while(zm_pom>=0)
    {
        if(plansza[zm_pom][ostatni_y] == znak)
        {
            ile_jest_w_rzedzie++;
        }
        else
        {
            break;
        }
        zm_pom--;
    }
    zm_pom= ostatni_x;
    while(zm_pom<plansza.size())
    {
        if(plansza[zm_pom][ostatni_y] == znak)
        {
            ile_jest_w_rzedzie++;
        }
        else
        {
            break;
        }
        zm_pom++;
    }
    if(ile_jest_w_rzedzie-1 >= ile_wygrana) //analogicznie sprawdzam czy ktos wygral
    {
        if(znak == 1)
        {
            return -100;
        }
        else if(znak == 2)
        {
            return 100;
        }
    }
    // Sprawdzenia czy ktos wygral po przekatnej (diagonalu) sa analogiczne do poprzednich sprawdzan.
    //pierwszy diagonal
    ile_jest_w_rzedzie = 0;
    zm_pom =0;
    while(ostatni_x+zm_pom<plansza.size() && ostatni_y-zm_pom >= 0)
    {
        if(plansza[ostatni_x+zm_pom][ostatni_y-zm_pom] == znak)
        {
            ile_jest_w_rzedzie++;
        }
        else
        {
            break;
        }
        zm_pom++;
    }
    zm_pom =0;
    while(ostatni_x-zm_pom >= 0 && ostatni_y+zm_pom<plansza.size() )
    {
        if(plansza[ostatni_x-zm_pom][ostatni_y+zm_pom] == znak)
        {
            ile_jest_w_rzedzie++;
        }
        else
        {
            break;
        }
        zm_pom++;
    }
    if(ile_jest_w_rzedzie-1 >= ile_wygrana)
    {
        if(znak == 1)
        {
            return -100;
        }
        else if(znak == 2)
        {
            return 100;
        }
    }
    //drugi diagonal
    ile_jest_w_rzedzie = 0;
    zm_pom =0;
    while(ostatni_x+zm_pom < plansza.size() && ostatni_y+zm_pom < plansza.size())
    {
        if(plansza[ostatni_x+zm_pom][ostatni_y+zm_pom] == znak)
        {
            ile_jest_w_rzedzie++;
        }
        else
        {
            break;
        }
        zm_pom++;
    }
    zm_pom =0;
    while(ostatni_x-zm_pom >= 0 && ostatni_y-zm_pom >= 0 )
    {
        if(plansza[ostatni_x-zm_pom][ostatni_y-zm_pom] == znak)
        {
            ile_jest_w_rzedzie++;
        }
        else
        {
            break;
        }
        zm_pom++;
    }
    if(ile_jest_w_rzedzie-1 >= ile_wygrana)
    {
        if(znak == 1)
        {
            return -100;
        }
        else if(znak == 2)
        {
            return 100;
        }
    }

    // jezeli ostatnio zrobiony ruch nie byl wygywajacy to sprawdzam czy jest remis
    // remis jest wtedy jak plansza jest zapelniona znakami, a nikt jeszcze nie wygral
    for(int i=0;i<plansza.size();i++)
    {
        for(int j=0;j<plansza.size();j++)
        {
            if(plansza[i][j]==0) //jesli pole jest rowne zeru to znaczy ze jest puste
            {
                pusta_plansza = true;  // jezeli jest puste pole to bool ma wartosc 1 jezeli nie to ma wartosc 0 (wartosc boola jest ustawiana na 0 przy wywolywaniu fukncji)
            }
        }
    }
    if(pusta_plansza == false)  // jezeli plansza nie jest pusta a nikt nie wygral to jest remis i zwracana jest wartosc 0
    {
        return 0;
    }
}

void Plansza::Ruch_gracza()  //funkcja rejestrujaca ruch gracza na planszy
{
    int x;
    int y;
    std::cout << "Podaj ruch" << std::endl;
    std::cin >> x;
    if(x>plansza.size()-1)  //sprawdzam czy podany koordynat jest poprawny
    {
        std::cerr<<"Blad, zle koordynaty" << std::endl;
        exit (0);
    }
    std::cin >> y;
    if(y>plansza.size()-1) //sprawdzam czy podany koordynat jest poprawny
    {
        std::cerr<<"Blad, zle koordynaty" << std::endl;
        exit (0);
    }
    if(plansza[x][y]!=0)    //sprawdzam czy pole ktore chce zajac gracz nie jest juz przypadkiem zajete
    {
        std::cerr<<"Blad, to pole jest juz zajete" << std::endl;
        exit (0);
    }
    else //jezeli koordynaty zostaly dobrze podane i pole jest wolne wtedy jest ono zajmowane
    {
        plansza[x][y] = 1;
        ostatnie_koordynaty[0] = x;
        ostatnie_koordynaty[1] = y;
    }
}


