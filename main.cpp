#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

//Clasa rotor
class Rotor
{
    public:
        //constructorul rotor care pleaca de la pozitia 0
        Rotor(char pos = 0);

        //declararea functiilor pentru stare,pozitie,revers
        void Setare_Rotor_Pozitie(int Pozitie_Noua);
        void Mutare_Pozitie_Rotor(int Pas);
        void Inapoi_Rotor(int Pas);
        int Ia_Pozitie() const;
        char Ia_Pozitia_Curenta()const;
        char Caracter_Index(int Index)const;
        char Caracter_Invers(int i) const;

    private:
        int Pozitie_Curenta;
        int Pas;
};

//Clasa Enigma
class Enigma
{
    public:
        //constructorul enigma pentru fiecare rotor
        Enigma(char r1, char r2, char r3, char r4, char r5)
        {
            R[0] = r1;
            R[1] = r2;
            R[2] = r3;
            R[3] = r4;
            R[4] = r5;
        }
        //deconstructor
        ~Enigma(){}

        string Criptare(const string& Text_Curat);
        static int Map_Caracter(char the_char);
        static const char *alfabet;
        static const char *reflector;
        static const char *Tablou1;
        static const int no_chars;

    private:
        char Tablou(char Char);
        Rotor R[5];
};

Rotor::Rotor(char pos) : Pozitie_Curenta(0), Pas(0)
{
	Setare_Rotor_Pozitie(Enigma::Map_Caracter(pos));
}
int Rotor::Ia_Pozitie() const
{
	return Pas;
}
void Rotor::Inapoi_Rotor(int Pas)
{
	Mutare_Pozitie_Rotor(-Pas);
}
char Rotor::Ia_Pozitia_Curenta() const
{
	return Enigma::alfabet[Pozitie_Curenta];
}
char Rotor::Caracter_Index(int Index) const
{
	return Enigma::alfabet[(Pozitie_Curenta + Index) % Enigma::no_chars];
}
char Rotor::Caracter_Invers(int i) const
{
	return (i >= Pozitie_Curenta) ? Enigma::alfabet[i - Pozitie_Curenta] : Enigma::alfabet[Enigma::no_chars + i - Pozitie_Curenta];
}
void Rotor::Setare_Rotor_Pozitie(int Pozitie_Noua)
{
	while (Pozitie_Noua < 0)
		Pozitie_Noua += Enigma::no_chars;

    Pozitie_Curenta = Pozitie_Noua % Enigma::no_chars;
    Pas = 0;
}
void Rotor::Mutare_Pozitie_Rotor(int Pas)
{
	Pozitie_Curenta += Pas;
	while (Pozitie_Curenta < 0)
		Pozitie_Curenta += Enigma::no_chars;

	Pozitie_Curenta %= Enigma::no_chars;
	Pas += Pas % Enigma::no_chars;
}

//Returneaza indexlul in afabet
int Enigma::Map_Caracter(char the_char)
{
    char *p = strchr(alfabet, the_char);
	return p ? (int)(p - alfabet) : no_chars;
}

//Returneaza litera corespunzatoare din tablou
char Enigma::Tablou(char Char)
{
	if (isalpha(Char))
		return (Tablou1[toupper(Char) - 'A']);

	if (isdigit(Char))
		return (Tablou1[Char - '0' + 26]);

	//caracter gresit
	return ' ';
}

//Criptarea textului
string Enigma::Criptare(const string& Text_Curat)
{
string ciphertext;

	ciphertext.resize(Text_Curat.size());

	for (size_t i = 0; i < Text_Curat.length(); i++) {
		 int vali = Map_Caracter(Tablou(Text_Curat[i]));
		 char valc;

		if (vali < no_chars) {
			for (int r = 0; r <= 4; r++) {
				valc = R[r].Caracter_Index(vali);
				vali = Map_Caracter(valc);
			}

			valc = reflector[vali];
			vali = Map_Caracter(valc);

			for (int r = 4; r >= 0; r--) {
				valc = R[r].Caracter_Invers(vali);
				vali = Map_Caracter(valc);
			}

			ciphertext[i] = Tablou(valc);

			for (int r = 0; r <= 4; r++) {
				R[r].Mutare_Pozitie_Rotor(1);
				if ((R[r].Ia_Pozitie() % no_chars) != 0)
					break;
			}

		} else {
			ciphertext[i] = Text_Curat[i];
		}
	}

	return ciphertext;
}

const char* Enigma::alfabet =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char* Enigma::reflector = "COAYIWV7E3809TBUZ26NPGF4DQL5RJX1SHKM";
const char *Enigma::Tablou1 = "0QWEDTYUIOPSNMJKBZLFHXCVGRA987654321";
const int Enigma::no_chars = (int)strlen(Enigma::alfabet);

int main()
{
char opt;

	do {
		char R1, R2, R3, R4, R5;
		string ciphertext;
        cout<<"--------------------------------------------------------"<<endl;
		cout<< "Introduceti cele 5 setari ale rotoarelor: "<<endl;
		cout<<"R1=";cin>>R1;
		cout<<"R2=";cin>>R2;
		cout<<"R3=";cin>>R3;
		cout<<"R4=";cin>>R4;
		cout<<"R5=";cin>>R5;
        cout<<"--------------------------------------------------------"<<endl;
		Enigma Criptareor(R1, R2, R3, R4, R5);
        cout<<endl;
		cin.ignore(100, '\n');
		cout<<"--------------------------------------------------------"<<endl;
		cout << "Introduceti textul care doriti sa il criptati/decriptari: ";
		getline(cin, ciphertext);
		cout<<"--------------------------------------------------------"<<endl;
		cout << "Texttul Criptat/Decriptat: " << Criptareor.Criptare(ciphertext) << endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<endl;

		do {
            cout<<"--------------------------------------------------------"<<endl;
			cout << "Daca mai doriti sa mai criptati introduceti la 'opt' "<<endl;
			cout<<"A-pentru a cripta inca o data"<<endl;
			cout<<"Q-pentru a inchide criptarea"<<endl;
			cout<<"opt=";cin >> opt;
            cout<<"--------------------------------------------------------"<<endl;
			if ((opt = (char)toupper(opt)) != 'Q' && opt != 'A')
				cout << "Optiune invalida\n";

		} while (opt != 'A' && opt != 'Q');
	} while (opt == 'A');

	return 0;
}
