#include <iostream>
#include <ctime>


using namespace std;

class karta
{
public:
	karta *next;
	karta *prev;
	int wartosc;
	int kolor;

private:

};
class talia
{
public:
	karta *glowa=nullptr;
	karta *ogon=nullptr;
	void dodaj(int wartosc, int kolor){
		karta *tmp = new karta;
		tmp->kolor = kolor;
		tmp->wartosc = wartosc;
		if (glowa==nullptr)
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
	void wypisz(){
		int i = 0;
		karta *tmp = glowa;
		while (tmp!=nullptr)
		{
			i++;
			cout << i<<". "<<(char)tmp->kolor << ' ' << tmp->wartosc<<endl;
			tmp = tmp->next;
		}
	}
	void tasuj(){
		for (int i = 0; i < 100000; i++)
		{
			int pierwsza = (rand() % 104) + 1;;
			int druga = (rand() % 104) + 1;;
			zamien(pierwsza, druga);
		}
	}
	void zamien(int pierwsza, int druga){
		karta *kartpierwsza=glowa, *kartdruga=glowa;
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
private:

};


void wydrukujekran(talia *tablica[11]){
	
	for (int i = 0; i < 10; i++)
	{
		karta *karta = tablica[i]->glowa;
		while (karta!=nullptr)
		{
			switch (karta->kolor)
			{
			case 3: cout << (char)karta->kolor << karta->wartosc << '\t'; break;
			case 4: cout << (char)karta->kolor << karta->wartosc << '\t'; break;
			case 5: cout << (char)karta->kolor << karta->wartosc << '\t'; break;
			case 6: cout << (char)karta->kolor << karta->wartosc << '\t'; break;
			default:
				break;
			}
			
			karta = karta->next;
		}
		cout << endl;
	}
}
void rozdajPoKarcie(talia *tablica[11]){
	for (int i = 0; i < 10; i++)
	{
		tablica[i]->dodaj(tablica[10]->glowa->wartosc, tablica[10]->glowa->kolor);
		tablica[10]->glowa = tablica[10]->glowa->next;
	}
}


int main(){
	srand(time(NULL));
	talia wszystko, talia1, talia2, talia3, talia4, talia5, talia6, talia7, talia8, talia9, talia10, reszta;
	talia *tablica[11] = { &talia1, &talia2, &talia3, &talia4, &talia5, &talia6, &talia7, &talia8, &talia9, &talia10, &reszta };
	for (int kolor = 3; kolor < 7; kolor++)
	{
		for (int wartosc = 1; wartosc < 14; wartosc++)
		{
			wszystko.dodaj(wartosc, kolor);
			wszystko.dodaj(wartosc, kolor);
		}
	}
	wszystko.tasuj();
	wszystko.wypisz();

	karta *tmp = wszystko.glowa;
	int i = 0,j=0;
	while (tmp!= nullptr)
		
	{
		if (j < 4){
			if (i==6)
			{
				i = 0;
				j++;
			}
		}
		else
		{
			if (j==10)
			{
				//i = 0;
			}
			else {
				if (i == 5)
				{
					i = 0;
					j++;
				}
			}
		}
		i++;
		tablica[j]->dodaj(tmp->wartosc,tmp->kolor);
		tmp = tmp->next;
	}
	wydrukujekran(tablica);
	cin.get();
	rozdajPoKarcie(tablica);
	wydrukujekran(tablica);
	cin.get();
	cin.get();
	return 0;
}