//Autorzy: Mateusz Czyż, Mateusz Serwan, Artur Kubok
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <athio.h>		//Biblioteka stworzona przez: Adam Małek
#include <string>
using namespace std;
class karta						//klasa karta posiadająca właśniwości
{
public:
	karta *next;				//wskaźnik następnej karty w talii
	karta *prev;				//wskaźnik poprzedniej karty w talii
	int wartosc;
	int kolor;
	bool widocznosc;			//1 gdy karta jest odwrócona wartością do góry, 0 gdy nie wiemy jaką ma wartość
};
class talia						//klasa talia która zawiera stos kart
{
public:
	karta *glowa = nullptr;		//początek każdej talii/stosu kart
	karta *ogon = nullptr;		//koniec każdej talii/stosu kart
	void dodaj(int wartosc, int kolor, bool widocznosc){		//funkcja dodająca karty do talii
		karta *tmp = new karta;
		tmp->kolor = kolor;
		tmp->wartosc = wartosc;
		tmp->widocznosc = widocznosc;
		tmp->next = nullptr;
		tmp->prev = nullptr;
		if (glowa == nullptr)
		{
			glowa = tmp;
			glowa->prev = nullptr;
			ogon = tmp;
			ogon->prev = nullptr;
		}
		else{
			ogon->next = tmp;
			karta *tmp2;
			tmp2 = ogon;
			ogon = tmp;
			ogon->prev = tmp2;
			ogon->next = nullptr;
		}
	}
	void usun(int ile, talia *tablica[12], int kolumna){		//fonkcja usuwająca daną ilość kart z końca talii
		if (ile != tablica[kolumna]->rozmiar())
		{
			karta *tmp = tablica[kolumna]->ogon;
			for (int i = 1; i < ile; i++)
			{
				tmp = tmp->prev;
			}
			tmp->next = nullptr;
			tmp->widocznosc = 1;
			tablica[kolumna]->ogon = tmp;
		}
		else {
			karta *tmp = nullptr;
			tablica[kolumna]->glowa = nullptr;
		}
	}
	void tasuj(){												//funkcja tasująca talię kart przed rozpoczęciem gry
		for (int i = 0; i < 100000; i++)
		{
			int pierwsza = (rand() % 104) + 1;
			int druga = (rand() % 104) + 1;
			zamien(pierwsza, druga);
		}
	}
	void zamien(int pierwsza, int druga){						//funkcja pomocnicza dla funkcji tasuj zamieniająca dwie karty miejscami
		karta *kartpierwsza = glowa, *kartdruga = glowa;
		karta tmp;
		for (int i = 1; i < pierwsza; i++)
		{
			kartpierwsza = kartpierwsza->next;
		}
		for (int i = 1; i < druga; i++)
		{
			kartdruga = kartdruga->next;
		}
		tmp.kolor = kartpierwsza->kolor;
		tmp.wartosc = kartpierwsza->wartosc;
		kartpierwsza->kolor = kartdruga->kolor;
		kartpierwsza->wartosc = kartdruga->wartosc;
		kartdruga->kolor = tmp.kolor;
		kartdruga->wartosc = tmp.wartosc;
	}
	int rozmiar(){									//funkcja obliczająca rozmiar talii
		karta *tmp;
		int ile = 0;
		tmp = glowa;
		while (tmp != nullptr)
		{
			ile++;
			tmp = tmp->next;
		}
		return ile;
	}
	bool sprawdzZaznaczenie(int nrKarty){			//funkcja sprawdzająca czy zaznaczony stos kart można przenieść
		karta *tmp;
		tmp = ogon;
		int liczba = 0;
		for (int i = 1; i <= nrKarty; i++)
		{
			if (tmp->wartosc == tmp->prev->wartosc - 1) liczba++;
			tmp = tmp->prev;
		}
		if (liczba == nrKarty) return 1;
		else return 0;
	}
	void sprawdzcalosc(talia *tablica[12], int kolumna, int nrkarta){		//funkcja sprawdzająca czy można usunąć dany ciąg od Króla do Asa
		karta *tmp = tablica[kolumna]->glowa;
		int x = 0;
		for (int i = 0; i < nrkarta; i++)
		{
			tmp = tmp->next;
		}
		while (tmp != nullptr)
		{
			x++;
		}
		if (x == 13)
		{
			//	tablica[kolumna]->usun(13, tablica, kolumna);	//wymaga dopracowania bo program sie wysypuje
		}
		gotoxy(0, 17);
		cout << "x: " << x;
	}
};
void wydrukujekran(talia *tablica[12], int x, int y, int nrzaznaczonejKolumny, int nrkarty, int zaznaczenie){		//funkcja wyświetlająca całą grę na ekranie
	for (int i = 0; i < 10; i++)
	{
		textcolor(15);
		int j = 0;
		string war;
		karta *karta = tablica[i]->glowa;
		if (karta == nullptr)
		{
			gotoxy(x, y);
			cout << "    ";
			x = x + 4;
			y = 0;
		}
		else {
			while (karta != nullptr)
			{
				j++;
				if (i == nrzaznaczonejKolumny && j == nrkarty && zaznaczenie == 0) textcolor(5);
				else if (i == nrzaznaczonejKolumny && j == nrkarty) textcolor(11);
				gotoxy(x, y);
				switch (karta->wartosc)
				{
				case 1: war = "As"; break;
				case 2: war = "2"; break;
				case 3: war = "3"; break;
				case 4: war = "4"; break;
				case 5: war = "5"; break;
				case 6: war = "6"; break;
				case 7: war = "7"; break;
				case 8: war = "8"; break;
				case 9: war = "9"; break;
				case 10: war = "10"; break;
				case 11: war = "J"; break;
				case 12: war = "Q"; break;
				case 13: war = "K"; break;
				}
				if (karta->widocznosc == true){
					switch (karta->kolor)
					{
					case 3: cout << (char)karta->kolor << war << '\t'; break;
					case 4: cout << (char)karta->kolor << war << '\t'; break;
					case 5: cout << (char)karta->kolor << war << '\t'; break;
					case 6: cout << (char)karta->kolor << war << '\t'; break;
					default:
						break;
					}
					if (karta->wartosc == 13)
					{
						//tablica[nrzaznaczonejKolumny]->sprawdzcalosc(tablica, nrzaznaczonejKolumny, nrkarty); 
					}
				}
				else cout << "###\t";
				karta = karta->next;
				y++;
			}
			for (int i = 0; i < 13; i++)
			{
				gotoxy(x, y);
				cout << "    ";
				y++;
			}
			x = x + 4;
			y = 0;
		}
	}
}
void rozdajPoKarcie(talia *tablica[12]){		//funkcja dodająca z pozostałych kart po jednej karcie na każdy stos
	for (int i = 0; i < 10; i++)
	{
		tablica[i]->dodaj(tablica[10]->glowa->wartosc, tablica[10]->glowa->kolor, true);
		tablica[10]->glowa = tablica[10]->glowa->next;
	}
}
void przenies(talia *tablica[12], int kolumna1, int nrkarta){		//funkcja przenosząca karty z jednej talii do drugiej
	int kolumna = kolumna1;
	kolumna1--;
	while (true)
	{
		if (GetAsyncKeyState(VK_RIGHT)) {
			kolumna++; if (kolumna > 9) kolumna = 0;
			nrkarta = tablica[kolumna]->rozmiar();
			wydrukujekran(tablica, 10, 0, kolumna, nrkarta, 1);
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			kolumna--; if (kolumna < 0) kolumna = 9;
			nrkarta = tablica[kolumna]->rozmiar();
			wydrukujekran(tablica, 10, 0, kolumna, nrkarta, 1);
		}
		if (GetAsyncKeyState(VK_LSHIFT)) {
			if (tablica[11]->glowa->wartosc + 1 == tablica[kolumna]->ogon->wartosc || kolumna == kolumna1)
			{
				karta *tmp = tablica[11]->glowa;
				for (int i = 0; i < tablica[11]->rozmiar(); i++)
				{
					tablica[kolumna]->dodaj(tmp->wartosc, tmp->kolor, 1);
					tmp = tmp->next;
				}
				tablica[kolumna1]->usun(tablica[kolumna]->rozmiar() - nrkarta + 1, tablica, kolumna1);
				kolumna++;
				wydrukujekran(tablica, 10, 0, kolumna, nrkarta, 1);
				break;
			}
			else {
				gotoxy(0, 15);
				cout << "Nie można ustwić kart w tym miejscu";
				kolumna++; wydrukujekran(tablica, 10, 0, kolumna, nrkarta, 1);
			}
		}
		nrkarta = tablica[kolumna]->rozmiar();
		if (nrkarta < 1) nrkarta = 1;
		if (nrkarta > tablica[kolumna]->rozmiar()) nrkarta = tablica[kolumna]->rozmiar();
		Sleep(200);
	}
	tablica[11]->usun(tablica[11]->rozmiar(), tablica, 11);
}
void steruj(talia *tablica[12], int x, int y){	//funkcja sterująca zaznaczeniem, wczytująca naciskane klawisze
	int kolumna = 0;
	int tmpkolumna = 0;
	int rozdanie = 0;
	int nrkarta = tablica[0]->rozmiar();
	bool zaznaczenie = 0;
	wydrukujekran(tablica, 10, 0, kolumna, nrkarta, zaznaczenie);
	while (true)
	{
		if (GetAsyncKeyState(VK_RIGHT)) {
			kolumna++;
			if (kolumna == 10) kolumna = 0;
			nrkarta = tablica[kolumna]->rozmiar();
			wydrukujekran(tablica, 10, 0, kolumna, nrkarta, zaznaczenie);
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			kolumna--;
			if (kolumna == -1) kolumna = 9;
			nrkarta = tablica[kolumna]->rozmiar();
			wydrukujekran(tablica, 10, 0, kolumna, nrkarta, zaznaczenie);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			nrkarta++; wydrukujekran(tablica, 10, 0, kolumna, nrkarta, zaznaczenie);
		}
		if (GetAsyncKeyState(VK_UP)) { nrkarta--; wydrukujekran(tablica, 10, 0, kolumna, nrkarta, zaznaczenie); }
		if (GetAsyncKeyState(VK_SPACE)) {
			rozdanie++;
			if (rozdanie < 6)
			{
				rozdajPoKarcie(tablica); wydrukujekran(tablica, 10, 0, kolumna, nrkarta, zaznaczenie);
			}
			else
			{
				gotoxy(50, 1);
				cout << "Wykorzystales wszystkie rozdania";
			}
			}
		if (GetAsyncKeyState(VK_LCONTROL)) {
			zaznaczenie = tablica[kolumna]->sprawdzZaznaczenie(tablica[kolumna]->rozmiar() - nrkarta);
			tmpkolumna = kolumna;
			wydrukujekran(tablica, 10, 0, kolumna, nrkarta, zaznaczenie);
		}
		if (nrkarta < 1) nrkarta = 1;
		Sleep(100);
		gotoxy(0, 10);
		if (zaznaczenie == 1)
		{
			karta *tmp = tablica[kolumna]->glowa;
			for (int i = 1; i < nrkarta; i++)
			{
				tmp = tmp->next;
			}
			for (int i = nrkarta; i <= tablica[kolumna]->rozmiar(); i++)
			{
				tablica[11]->dodaj(tmp->wartosc, tmp->kolor, 1); //dodaje po jednej karcie do talii przenoszonych
				tmp = tmp->next;
			}
			cout << "                  ";
			kolumna++;
			przenies(tablica, kolumna, nrkarta);
			wydrukujekran(tablica, 10, 0, kolumna, nrkarta, zaznaczenie);
			zaznaczenie = 0;
		}
		else {
			gotoxy(50, 0);
			cout << "BLEDNE ZAZNACZENIE";
		}
	}
}
void animacjastartowa(){		//funkcja wyświetlająca ekran startowy
	int x = 10;
	int y = 5;
	x = 10;
	y = 5;
	gotoxy(x, y);
	cout << " #############################################"; y++; gotoxy(x, y);
	cout << " #                                           #"; y++; gotoxy(x, y);
	cout << " #  #######     ##        #    ##    #     # #"; y++; gotoxy(x, y);
	cout << " #  #      #   #  #       #   #  #   #    #  #"; y++; gotoxy(x, y);
	cout << " #  #      #  #    #      #  #    #  #   #   #"; y++; gotoxy(x, y);
	cout << " #  #######  #      #     # #      # #  #    #"; y++; gotoxy(x, y);
	cout << " #  #        ########     # ######## # #     #"; y++; gotoxy(x, y);
	cout << " #  #        #      #     # #      # #  #    #"; y++; gotoxy(x, y);
	cout << " #  #        #      # #   # #    # # #   #   #"; y++; gotoxy(x, y);
	cout << " #  #        #      #  ###  #    ### #    #  #"; y++; gotoxy(x, y);
	cout << " #                                           #"; y++; gotoxy(x, y);
	cout << " #############################################"; y += 3; x += 8; gotoxy(x, y);
	cout << "Nacisnij spacje aby kontynuowac"; y++; gotoxy(x, y);
	cout << "Nacisnij strzalke aby sterowac"; y++; gotoxy(x, y);
	cout << "Nacisnij lewy ctrl aby zaznaczyc"; y++; gotoxy(x, y);
	cout << "Nacisnij lewy shift aby przeniesc karty"; y++;
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE)) break;
		Sleep(100);
	}
}
void przygotujkarty(talia *wszystko){
	for (int kolor = 3; kolor < 7; kolor++)
	{
		for (int wartosc = 1; wartosc < 14; wartosc++)
		{
			wszystko->dodaj(wartosc, kolor, true);
			wszystko->dodaj(wartosc, kolor, true);
		}
	}
}
void podzielkarty(talia *tablica[12], talia *wszystko){			//funkcja dzieląca całą talię na 10 stosów
	karta *tmp = wszystko->glowa;
	int i = 1, j = 0;
	while (tmp != nullptr)
	{
		if (j < 4){
			if (i == 6)
			{
				tablica[j]->dodaj(tmp->wartosc, tmp->kolor, true);
				i = 0;
				j++;
			}
			else{ tablica[j]->dodaj(tmp->wartosc, tmp->kolor, false); }
		}
		else
		{
			if (j == 10)
			{
				tablica[j]->dodaj(tmp->wartosc, tmp->kolor, true);
			}
			else {
				if (i == 5)
				{
					tablica[j]->dodaj(tmp->wartosc, tmp->kolor, true);
					i = 0;
					j++;
				}
				else tablica[j]->dodaj(tmp->wartosc, tmp->kolor, false);
			}
		}
		i++;
		tmp = tmp->next;
	}
}
int main(){
	animacjastartowa();		//wyświetlanie ekranu startowego
	system("cls");			//czyszczenie ekranu
	srand(time(NULL));
	talia *wszystko = new talia, *talia1 = new talia, *talia2 = new talia, *talia3 = new talia, *talia4 = new talia, *talia5 = new talia, *talia6 = new talia, *talia7 = new talia, *talia8 = new talia, *talia9 = new talia, *talia10 = new talia, *reszta = new talia, *przenoszone = new talia;		//tworzenie talii
	talia *tablica[12] = { talia1, talia2, talia3, talia4, talia5, talia6, talia7, talia8, talia9, talia10, reszta, przenoszone };		//dodanie talii do tablicy wskaźników aby łatwiej przekazywać talie pomiędzy funkcjami
	przygotujkarty(wszystko);	//przygotowywanie talii kart
	wszystko->tasuj();			//mieszanie kart
	podzielkarty(tablica, wszystko);		//dzielenie kart na stosy
	steruj(tablica, 0, 0);					//uruchomienie gry
	cin.get();
	cin.get();
	cin.get();
	return 0;
}