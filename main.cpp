#include <iostream>
#include <string>

using namespace std;

int main()
{
    string zdanie;

    int *tablica;

    int licz = 0;
    char znak=5;

    /*
     * sposoby na konwersję (rzutowanie) typów zmiennych na inne typy zmienne:
     * - static_cast - rzutowanie następuje pomiędyz zmiennymi  w ramach tego samego fragmentu kodu. Rzutowanie pozwala na rzutowanie
     *                 elementów wskaźnikowe na elementy niewskaźnikowe.
     * - dynamic_cast - rzutowanie następępuje pomiędzy wskaźnikiem a referncją do tejże klasy. W przeciwieństwie do static jest tzw. bezpieczne
     * - const_cast - pozwala na konwersję wskaźnika na formę bezwskaźnikową
     * reinterpret_cast - rzutowanie jednego typu na inny, z pełnym zachowaniem bitów 1:1 (czyli nie jest sprawdzana ani zgodność ani
     * wartość konwertowanych bajtów, tylko sam efekt). Rozwiązanie to może prowadzić do nietabilności tworzonego programu, nawet doprowadzając
     * do destabilizacji całego systemu operacyjnego.
     * */
    for (znak=' ',licz=0; znak<='z'; znak++,licz++); //FOR NUMER 1

    tablica = new int[licz];
    for(int i=0;i<licz;i++) tablica[i]=0;

    cout << "Podaj dowolnej długści zdanie: ";
    getline(cin, zdanie);
    cout << "W treści występują następujące znaki. Podana zostaje także ilość wystąpień:" << endl;


    for (int i=0; i < zdanie.length();i++) {
        //cout << zdanie.at(i) << endl;
        //tablica zawiera taką ilość "zmiennych" (indeksów, pod którymi zachowane są potencjalne wartości/ilości zliczeń
        //kolejnych znaków), ile wcześniej zostało to sprawdzone pętla for numer 1. Znaki są ułożone jeden po drugim,
        //zaś to ułożenie opisane zostało w dokumencie ANSII (instytucja standaryzacyjna w USA)
        //Ogólnie, obecny kod, na dzień 13.05.2022 pozwalał na znalezienie 91 znaków (od białej przestrzeni - SPCJI, do małej
        //litery z; duże litery są umiejscowione przez małymi literami)

        //żeby odwołać się do miejsca w tablicy, żeby jednoznacznie wskazać na relację litera-zliczona wartości jej występowania,
        //użyto poniżej prostego algorytmu przesuwającego indeks naszej tablicy o numer pierwszego znaku z tablic ASCII.
        //Dlaczego tak? Dlatego, że tablice w C++ ZAWSZE rozpoczynają się od wartości 0 i nie ma możliwości fizycznej przesunąć
        //jakiejkolwiek wartości indeksu powyżej zera (lub poniżej zera).

        //PRZYKŁAD program znajdzie literę - małe z. Litera ta jest ostatnią literą zapisaną w alfabecie ASCII. Z materiałów, które
        //można znaleść na internecie da się wywnioskować, że litera małe z opisane jest liczbą 122. Nasza tablica, mająca wartości
        //określane od wartości 0 do wartości 90 (łącznie 91 stanów), nie mogłaby zapisać informacji o występowaniu z, bo próbowalibyśmy
        //realnie nadpisać nieistniejący indeks (ostatnio to 90, a tutaj byśmy mieli wartość indeksu 122).
        //W związku z tym, by określić indeks litery, którą chcemy zliczyć zastosujemy pewien trick - wyciągniemy każdą literę ze zdania,
        //po czym pomniejszymy jej wartość kodowania o wartość spacji/liczbę 32 (liczba ta stanowi kod wspominanej spacji). Dzięki temu
        //spacja zostałaby zapisana na wartości indeksu 0 (32-32=0), zaś znak z zostałaby wywołany/zapisany pod wartością 90 (122-32=90) -
        //ostatni indeks w tablicy!
        tablica[zdanie.at(i)-' ']++;
    }

    string zero,jeden,wiele;
    zero=jeden=wiele="";
    for (int i=0; i < licz; i++) {
        if(tablica[i] == 0) {
            zero += string(static_cast<char>(i+' ') + ", ");
            //cout << "Znak " << static_cast<char>(i+' ') << " zostal uzyty " << tablica[i] << " razy." << endl;
        }
        else if (tablica[i] == 1) {
            jeden.append(" ");
            jeden.at(jeden.length()-1) = static_cast<char>(i+' ');
            jeden += ", ";
        }
        else {
            wiele += static_cast<char>(i+' ') + ", ";
            //cout << "znak " << static_cast<char>(i+' ') << " nie jest obecny w zdaniu!" << endl;
        }
    }

    //cout << "Znaki nie użyte w zdaniu: " << zero << endl;
    cout << "Znaki użyte dokładnie raz w zdaniu: " << jeden << endl;
    //cout << "Znaki użyte wielokrotnie w zdaniu: " << wiele << endl;

    delete [] tablica;

    return 0;
}
