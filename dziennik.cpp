#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class uczen 
{
public:
	int id; //identyfikator ucznia
	int zachowanie; //ocena z zachowania 1-6
	int nagrody; //liczba zdobytych nagrod
	int *oceny; // tablica ocen 1-6	
	int ilosc; //ilosc ocen
private:
	void pobierz_oceny(int *napis) //np. napis "6123456" ilosc-6 i dalej oceny
	{
		ilosc=napis[0];
		oceny=new int[ilosc];
		for(int i=1;i<=ilosc;++i)
		{
			oceny[i-1]=napis[i];
		}
	}
public:
	void pobierz_zachowanie(int ocena)
	{
		zachowanie=ocena;
	}
	float srednia()
	{
		float suma=0;
		for(int i=0;i<ilosc;++i)
		{
			suma+=oceny[i];
		}
		return suma/(float)ilosc;
	}
	void wypisz()
	{
		cout<<"identyfikator "<<id<<endl;
		cout<<"ocena z zachowania "<<zachowanie<<endl;
		cout<<"ilosc nagrod "<<nagrody<<endl;
		cout<<"oceny:"<<endl;
		for(int i=0;i<ilosc;++i)
		{
			cout<<oceny[i]<<" ";
		}
		cout<<endl;
	}
	bool czy_pierwsza() //funkja spradzajaca czy jest to pierwsza nagroda ucznia
	{
		return nagrody==-1;
	}
	uczen()
	{
		id=-1;
		zachowanie=-1;
		nagrody=-1;
		oceny=nullptr;
		ilosc=-1;
	}
	uczen(int id, int *napis)
	{
		//cout<<"konstruktor"<<id<<endl;
		this->id=id;
		zachowanie=-1;
		nagrody=-1;
		oceny=nullptr;
		pobierz_oceny(napis);
	}
	uczen(uczen &orginal)
	{
		//cout<<"kopiujacy"<<id<<endl;
		this->id=orginal.id;
		this->zachowanie=orginal.zachowanie;
		this->nagrody=orginal.nagrody;
		this->ilosc=orginal.ilosc;
		this->oceny=new int [ilosc];
		for(int i=0;i<ilosc;++i)
		{
			this->oceny[i]=orginal.oceny[i];
		}
	}
	~uczen()
	{
		//cout<<"destruktor "<<id<<endl;
		delete []oceny;
	}
};
class grupa
{
private:
	static int ostatni_wolny; //	reprezentuj¹ce nastêpny wolny identyfikator ucznia
	static int nowe_id()
	{
		return ostatni_wolny+=5;
	}
public:
	uczen *uczniowie[30];//uczniowie w danej grupie
	int ilosc; //ilosc uczniow w grupie
	int nr; //numer grupy
	void dodaj(int *napis, int ocena) //dodoaje nowego ucznia do grupy
	{
		if(ilosc<30)
		{
			uczniowie[ilosc]= new uczen(nowe_id(),napis);// ilosc-1 wiec indeks ilosc jest pierwsy wolne
			uczniowie[ilosc]->zachowanie=ocena;
			ilosc++;			
		}
		else
		{
			uczen *u=new uczen(nowe_id(),napis);
			int ktory=0; //zmienna na indeks w tablicy uczniow ucznia o najnizszej sredniej
			for(int i=1;i<ilosc;++i)
			{
				if((uczniowie[i]->srednia())<(uczniowie[ktory]->srednia()))
				{
					ktory=i;
				}
			}
			if(u->srednia()>uczniowie[ktory]->srednia())
			{
				uczniowie[ktory]=u;	
				uczniowie[ktory]->zachowanie=ocena;
			}					
		}
	}
	void wypisz()
	{
		cout<<"NR GRUPY------------------------------------------------"<<nr<<endl;
		cout<<"ILOSC UCZNIOW:"<<ilosc<<endl;
		for(int i=0;i<ilosc;++i)
		{
			cout<<"uczen "<<i+1<<endl;
			uczniowie[i]->wypisz();
		}
	}
	float naj_srednia()
	{
		float naj=uczniowie[0]->srednia();
		for(int i=1;i<ilosc;++i)
		{
			if(naj<uczniowie[i]->srednia())
			{
				naj=uczniowie[i]->srednia();
			}
		}
		return naj;
	}
	grupa()
	{
		for(int i=0;i<30;++i)
		{
			uczniowie[i]=nullptr;			
		}
		ilosc=0;
		nr=-1;
	}
	grupa(int nr)
	{
		for(int i=0;i<30;++i)
		{
			uczniowie[i]=nullptr;			
		}
		ilosc=0;
		this->nr=nr;
	}

	~grupa()
	{
		for(int i=0;i<ilosc;++i)
		{
			delete uczniowie[i];			
		}

	}
};
bool czy_piatkowy(uczen *x) //funkcja sprawdza czy uczen ma przynajmniej 5 piatek
{
	int ile=0; //zmienna na liczbe ocen >=5
	for(int i=0;i<x->ilosc;++i)
	{
		if(x->oceny[i]>=5)
		{
			++ile;
		}
	}
	return ile>=5;
}
int grupa::ostatni_wolny=5;
int main()
{
	grupa dziennik[8];
	for(int i=0;i<8;++i)
	{
		dziennik[i]=grupa(i+1);//inicjalizacja grup
	}
	int *napis; //tablica int na napis
	string c;  //zmienna do pobierania z pliku
	int nr_grupy;
	int zachowanie;
	int ilosc_ocen;
	fstream file;
	file.open("uczniowie.txt", ios::in);
	if(!file.good())
	{
		cout<<"blad otwarcia pliku";
	}

	//pobieranie z pliku/////////////////////////////////////////////////
	
	int i=0;
	while(file>>c)
	{
		if(i==0)
		{
			nr_grupy=stoi(c);
			//cout<<nr_grupy<<" ";
			i++;
		}
		else if(i==1)
		{
			zachowanie=stoi(c);
			//cout<<zachowanie<<" ";
			i++;
		}
		else if(i==2)
		{
			ilosc_ocen=stoi(c);
			i++;
			napis=new int[ilosc_ocen+1];
			napis[0]=ilosc_ocen;
		}
		else if(i>2)
		{
			if(ilosc_ocen+3>i)
			{
				napis[i-2]=stoi(c); //od napis[1]
				i++;
			}
			if(ilosc_ocen+3==i)
			{
				for(int j=0;j<ilosc_ocen+1;++j)
				{
					//cout<<napis[j]<<" ";
				}
				dziennik[nr_grupy-1].dodaj(napis,zachowanie);
				i=0;
				delete []napis;
			}
		}
	}
	
	//nagrody///////////////////////////////////////

	float naj; //najwieksza srednia w szkole
		
	for(int i=0;i<8;++i) //szukanie najwiekszej sredniej w szkole
	{
		if(naj<dziennik[i].naj_srednia())
		{
			naj=dziennik[i].naj_srednia();
		}
	}
	
	//przyznanie nagrod 
	
	int zadna=0;
	int jedna=0; 
	int dwie=0;
	int trzy=0;
	int cztery=0; //zmienne na ilosc osob, ktore maja x nagrod
	for(int i=0;i<8;++i)
	{
		for(int j=0;j<dziennik[i].ilosc;++j)
		{
			if(dziennik[i].uczniowie[j]->srednia()==dziennik[i].naj_srednia()) //nagrody za najwiekaz srednia w grupie
			{
				if(dziennik[i].uczniowie[j]->czy_pierwsza())
				{
					dziennik[i].uczniowie[j]->nagrody+=2;//jesli to pierwsza nagroda ucznia trzeba dodac 2 bo taki uczen ma -1 nagrod
				}
				else
				{
					dziennik[i].uczniowie[j]->nagrody+=1;
				}
			}
			
			if(dziennik[i].uczniowie[j]->srednia()==naj) //nagroda za najwieksza srednia w szkole
			{
				if(dziennik[i].uczniowie[j]->czy_pierwsza())
				{
					dziennik[i].uczniowie[j]->nagrody+=2;//jesli to pierwsza nagroda ucznia trzeba dodac 2 bo taki uczen ma -1 nagrod
				}
				else
				{
					dziennik[i].uczniowie[j]->nagrody+=1;
				}
			}
			
			if(czy_piatkowy(dziennik[i].uczniowie[j])) //nagroda za przynajmniej 5 piatek
			{
				if(dziennik[i].uczniowie[j]->czy_pierwsza())
				{
					dziennik[i].uczniowie[j]->nagrody+=2;//jesli to pierwsza nagroda ucznia trzeba dodac 2 bo taki uczen ma -1 nagrod
				}
				else
				{
					dziennik[i].uczniowie[j]->nagrody+=1;
				}
			}
			
			if(dziennik[i].uczniowie[j]->zachowanie==6) //nagroda za 6 z zachowania
			{
				if(dziennik[i].uczniowie[j]->czy_pierwsza())
				{
					dziennik[i].uczniowie[j]->nagrody+=2;//jesli to pierwsza nagroda ucznia trzeba dodac 2 bo taki uczen ma -1 nagrod
				}
				else
				{
					dziennik[i].uczniowie[j]->nagrody+=1;
				}
			}
			
			if(dziennik[i].uczniowie[j]->nagrody==-1)
			{
				zadna++;
			}
			else if(dziennik[i].uczniowie[j]->nagrody==1)
			{
				jedna++;
			}
			else if(dziennik[i].uczniowie[j]->nagrody==2)
			{
				dwie++;
			}
			else if(dziennik[i].uczniowie[j]->nagrody==3)
			{
				trzy++;
			}
			else if(dziennik[i].uczniowie[j]->nagrody==4)
			{
				cztery++;
			}
		}

	}
	
	cout<<"Zadnej nagrody nie dostalo "<<zadna<< " uczniow"<<endl;
	cout<<"Jedna nagrode dostalo "<<jedna<< " uczniow"<<endl;
	cout<<"Dwie nagrody dostalo "<<dwie<< " uczniow"<<endl;
	cout<<"Trzy nagrody dostalo "<<trzy<< " uczniow"<<endl;
	cout<<"Cztery nagrody dostalo "<<cztery<< " uczniow"<<endl;
	
	//kopiowanie  
	
	uczen tab[8]={*dziennik[0].uczniowie[0], *dziennik[1].uczniowie[0], *dziennik[2].uczniowie[0], *dziennik[3].uczniowie[0], *dziennik[4].uczniowie[0], *dziennik[5].uczniowie[0], *dziennik[6].uczniowie[0], *dziennik[7].uczniowie[0]};

	//wypisanie tab
	
	/*for(int i=0;i<8;++i)
	{
		cout<<"uczen z grupy "<<i+1<<endl;
		tab[i].wypisz();
	}*/
	
	//wypisanie info wszystko//////////////////////////////
	
	/*for(int i=0;i<8;++i)
	{
		dziennik[i].wypisz();
	}*/
	
	file.close();
	return 0;

}
