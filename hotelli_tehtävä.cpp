/* 
opiskelija: Ayham Ajam 
ryhmä: 24TietoA
tavoite: 5/5
tehtävän toteutukset: olen tehnyt kaikki vaatimukset 5 arvosanaan. 
-varauksien hakeminen toimi sekä nimellä että numerolla.
-olen tättänyt kaikki vaatimukset
-ohejelmaa tulostaa käyttäjän antamat tiedot varmistamiseski..... 
*/




#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>

using namespace std;

const int YKSIO = 100;
const int KAKSIO = 150;
const string TIEDOSTONIMI = "varaukset.txt";
const int MIN_VARAUSNUMERO = 10000;
const int MAX_VARAUSNUMERO = 99999;

struct Huone {
    int numero;
    string tyyppi;
    bool varattu;
    string varaaja;
    int varausnumero; 
};

int satunnainenVarausnumero() {
    return rand() % (MAX_VARAUSNUMERO - MIN_VARAUSNUMERO + 1) + MIN_VARAUSNUMERO;
}

bool onkoVarattu(const Huone& huone) {
    return huone.varattu;
}

void naytaHuoneet(const vector<Huone>& huoneet) {
    cout << "Saatavilla olevat huoneet:" << endl;
    for (const auto& huone : huoneet) {
        if (!huone.varattu) {
            cout << "Huone " << setw(3) << huone.numero << " (" << huone.tyyppi << ") - Vapaa" << endl;
        }
    }
}

void teeVaraus(vector<Huone>& huoneet, const string& tyyppi, int huoneMaara, const string& varaajanNimi) {
    for (auto& huone : huoneet) {
        if (!onkoVarattu(huone) && huone.tyyppi == tyyppi) {
            huone.varattu = true;
            huone.varaaja = varaajanNimi;
            huone.varausnumero = satunnainenVarausnumero();

            int huoneHinta = (tyyppi == "1hh") ? YKSIO : KAKSIO;
            double summa = huoneMaara * huoneHinta;

            cout << "Varaus tehty huoneeseen " << huone.numero << " (" << tyyppi << ") varaajalle " << varaajanNimi << "." << endl;
            cout << "Varausnumero: " << huone.varausnumero << endl;
            cout << "Laskun loppusumma: " << summa << "€" << endl;

            return;
        }
    }
    cout << "Valitsemasi huonetyyppi (" << tyyppi << ") ei ole saatavilla." << endl;
}

void haeVarauksia(const vector<Huone>& huoneet) {
    cout << "Haku varaukselle\n1. Varausnumerolla\n2. Varaajan nimellä\n";
    int valinta;
    cin >> valinta;

    if (valinta == 1) {
        int haettuVarausnumero;
        cout << "Anna varausnumero: ";
        cin >> haettuVarausnumero;

        for (const auto& huone : huoneet) {
            if (huone.varausnumero == haettuVarausnumero) {
               cout << "Huone " << huone.numero << " (" << huone.tyyppi << ") varattu nimellä " << huone.varaaja << "." << endl;
                return;
            }
        }
        cout << "Ei varauksia varausnumerolla: " << haettuVarausnumero << endl;

    }
    else if (valinta == 2) {
        cin.ignore();
        string hakijanNimi;
        cout << "Anna varaajan nimi: ";
        getline(cin, hakijanNimi);

        for (const auto& huone : huoneet) {
            if (huone.varattu && huone.varaaja == hakijanNimi) {
                cout << "Huone " << huone.numero << " (" << huone.tyyppi << ") varattu nimellä " << hakijanNimi << ". Varausnumero: " << huone.varausnumero << endl;
                return;
            }
        }
        cout << "Ei varauksia nimellä: " << hakijanNimi << endl;
    }
    else {
        cout << "Virheellinen valinta." << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<Huone> huoneet(300);
    for (int i = 0; i < 300; ++i) {
        huoneet[i].numero = i + 1;
        huoneet[i].tyyppi = (i < 150) ? "1hh" : "2hh";
        huoneet[i].varattu = false;
        huoneet[i].varaaja = "";
        huoneet[i].varausnumero = 0;
    }

    while (true) {
        cout << "\n--- Hotelli varausjarjestelma ---\n";
        cout << "1. Nayta vapaat huoneet\n";
        cout << "2. Tee varaus\n";
        cout << "3. Hae varauksia\n";
        cout << "4. Lopeta ohjelma\n";

        int valinta;
        cin >> valinta;

        switch (valinta) {
        case 1:
            naytaHuoneet(huoneet);
            break;
        case 2: {
            cout << "Valitse huonetyyppi: 1 (yhden hengen) tai 2 (kahden hengen)\n";
            int huonetyyppi;
            cin >> huonetyyppi;
            string tyyppi = (huonetyyppi == 1) ? "1hh" : "2hh";

            cout << "Kuinka monta yota haluat? ";
            int huoneMaara;
            cin >> huoneMaara;

            cin.ignore();
            string varaajanNimi;
            cout << "Anna nimesi: ";
            getline(cin, varaajanNimi);

            teeVaraus(huoneet, tyyppi, huoneMaara, varaajanNimi);
            break;
        }
        case 3:
            haeVarauksia(huoneet);
            break;
        case 4:
            cout << "Ohjelma lopetetaan." << endl;
            return 0;
        default:
            cout << "Virheellinen valinta." << endl;
            break;
        }
    }
}
