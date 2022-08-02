#include <iostream>

using namespace std;

class Vertinimas
{
public:
	int vertinimas;
	string data;

	Vertinimas* vKitas;
public:

	Vertinimas(int iVertinimas, string iData) :
		vertinimas(iVertinimas), data(iData), vKitas(NULL)
	{ }

	void RodytiElementa()
	{
		if (vertinimas == -1) {
			cout << data << " [neivertinta]; ";
		}
		else {
			cout << data << " [" << vertinimas << "]; ";
		}
	}

};

class Dalykas
{
public:
	string dalykas;
	string tipas;
	string paskirtis;

	Dalykas* dKitas;
	Vertinimas* vKitas;
public:

	Dalykas(string iDalykas, string iTipas, string iPaskirtis) :
		dalykas(iDalykas), tipas(iTipas), paskirtis(iPaskirtis), dKitas(NULL), vKitas(NULL)
	{ }

	void RodytiElementa()
	{
		cout << "dalykas: " << dalykas << " " << tipas << " " << paskirtis;
	}

};

class Studentas
{
public:
	string vardas;

	Studentas* sKitas;
	Dalykas* dKitas;
public:

	Studentas(string iVardas) :
		vardas(iVardas), sKitas(NULL), dKitas(NULL)
	{ }

	void RodytiElementa()
	{
		cout << vardas << " ";
	}

};

class tiesiniu_sar_rinkinys
{
private:
	Studentas* pStud;
public:

	tiesiniu_sar_rinkinys() :
		pStud(NULL)
	{ }

	bool isEmpty()
	{
		return (pStud == NULL);
	}

	void iterpti_studenta(string iVardas)
	{
		Studentas* pNewLink = new Studentas(iVardas);

		pNewLink->sKitas = pStud;
		pStud = pNewLink;

	}

	Vertinimas* iterpti_vertinima(Vertinimas* verEile, int iVertinimas, string iData)
	{
		Vertinimas* pNewLink = new Vertinimas(iVertinimas, iData);
		pNewLink->vKitas = verEile;
		verEile = pNewLink;
		return verEile;
	}


	Dalykas* iterpti_dalyka(Dalykas* dalEile, string iDalykas, string iTipas, string iPaskirtis)
	{
		Dalykas* pNaujasSar = new Dalykas(iDalykas, iTipas, iPaskirtis);
		Dalykas* pPirmesnis = NULL;
		Dalykas* pPagalbinis = dalEile;


		while (pPagalbinis != NULL && iDalykas > pPagalbinis->dalykas)
		{
			pPirmesnis = pPagalbinis;
			pPagalbinis = pPagalbinis->dKitas;
		}
		if (pPirmesnis == NULL)
			dalEile = pNaujasSar;
		else
			pPirmesnis->dKitas = pNaujasSar;

		pNaujasSar->dKitas = pPagalbinis;

		return dalEile;
	}


	Studentas* rasti_studenta(Studentas* pRastas, string iRasti) {
		if (pStud == NULL) {
			cout << "Sarasas tuscias paieska yra neimanoma...";
		}
		else {
			Studentas* P = pStud;
			while (P != NULL) {
				if (P->vardas == iRasti) {
					pRastas = P;
					break;
				}
				else P = P->sKitas;
			}
		}
		return pRastas;
	}

	Dalykas* rasti_dalyka(Dalykas* pDalykas, Dalykas* pRastas, string iRasti) {
		if (pDalykas == NULL) {
			cout << "Sarasas tuscias paieska yra neimanoma...";
		}
		else {
			Dalykas* P = pDalykas;
			while (P != NULL) {
				if (P->dalykas == iRasti) {
					pRastas = P;
					break;
				}
				else P = P->dKitas;
			}
		}
		return pRastas;
	}

	Vertinimas* rasti_vertinima(Vertinimas* pVertinimas, Vertinimas* pRastas, string iRasti) {
		if (pVertinimas == NULL) {
			cout << "Sarasas tuscias paieska yra neimanoma...";
		}
		else {
			Vertinimas* P = pVertinimas;
			while (P != NULL) {
				if (P->data == iRasti) {
					pRastas = P;
					break;
				}
				else P = P->vKitas;
			}
		}
		return pRastas;
	}

	void naujas_dalykas_i_nurodyta_studenta(string sRasti, string iDalykas, string iTipas, string iPaskirtis) {
		Studentas* pR = NULL;
		pR = rasti_studenta(pR, sRasti);
		pR->dKitas = iterpti_dalyka(pR->dKitas, iDalykas, iTipas, iPaskirtis);
	}

	void naujas_vertinimas_i_nurodyta_dalyka(string sRasti, string dRasti, int iVertinimas, string iData) {
		Studentas* pS = NULL;
		Dalykas* pD = NULL;
		pS = rasti_studenta(pS, sRasti);
		pD = rasti_dalyka(pS->dKitas, pD, dRasti);
		pD->vKitas = iterpti_vertinima(pD->vKitas, iVertinimas, iData);
	}

	void atnaujinti_vertinima(string sRasti, string dRasti, int iVertinimas, string iData) {
		Studentas* pS = NULL;
		Dalykas* pD = NULL;
		Vertinimas* pV = NULL;
		pS = rasti_studenta(pS, sRasti);
		pD = rasti_dalyka(pS->dKitas, pD, dRasti);
		pV = rasti_vertinima(pD->vKitas, pV, iData);
		pV->vertinimas = iVertinimas;
	}

	void rodyti_vertinimus(Vertinimas* verEile)
	{
		if (verEile != NULL) {
			Vertinimas* pCurrent = verEile;
			cout << "Tarpiniu atsiskaitymu sarasas:" << endl;
			while (pCurrent != NULL)
			{
				pCurrent->RodytiElementa();
				pCurrent = pCurrent->vKitas;
			}
			cout << endl;
		}
	}


	void rodyti_dalykus(Dalykas* dalEile)
	{
		if (dalEile != NULL) {
			Dalykas* pCurrent = dalEile;
			cout << "Dalyku sarasas:" << endl;

			while (pCurrent != NULL)
			{
				pCurrent->RodytiElementa();
				cout << endl;
				rodyti_vertinimus(pCurrent->vKitas);

				pCurrent = pCurrent->dKitas;
			}
		}
	}

	void rodyti_studentus()
	{
		Studentas* pCurrent = pStud;
		cout << "Studentu sarasas" << endl;
		while (pCurrent != NULL)
		{
			pCurrent->RodytiElementa();
			cout << endl;
			rodyti_dalykus(pCurrent->dKitas);

			pCurrent = pCurrent->sKitas;
		}
	}

	void rodyti_studento_dalykus(string iVardas)
	{
		Studentas* pS = NULL;
		pS = rasti_studenta(pS, iVardas);
		cout << "Studento " << pS->vardas << " tarpiniai atsiskaitymai:" << endl;
		Dalykas* pCurrent = pS->dKitas;
		while (pCurrent != NULL)
		{
			pCurrent->RodytiElementa();
			cout << endl;
			rodyti_vertinimus(pCurrent->vKitas);

			pCurrent = pCurrent->dKitas;
		}
	}

	void rodyti_studento_tarpinius(string iVardas)
	{
		Studentas* pS = NULL;
		pS = rasti_studenta(pS, iVardas);
		cout << "Studento " << pS->vardas << " tarpiniai atsiskaitymai:" << endl;
		Dalykas* pCurrent = pS->dKitas;
		while (pCurrent != NULL)
		{
			rodyti_vertinimus(pCurrent->vKitas);

			pCurrent = pCurrent->dKitas;
		}
	}

	void rodyti_studento_dalykus_pagal_paskirti(string iVardas, string iPaskirtis)
	{
		Studentas* pS = NULL;
		pS = rasti_studenta(pS, iVardas);
		cout << "Studento " << pS->vardas << " dalykai pagal dalyko paskirti - " << iPaskirtis << " :" << endl;
		Dalykas* pCurrent = pS->dKitas;
		while (pCurrent != NULL)
		{
			if (pCurrent->paskirtis == iPaskirtis) {
				pCurrent->RodytiElementa();
				cout << endl;
			}
			pCurrent = pCurrent->dKitas;
		}
	}

	void rodyti_studento_dalykus_pagal_tipas(string iVardas, string iTipas)
	{
		Studentas* pS = NULL;
		pS = rasti_studenta(pS, iVardas);
		cout << "Studento " << pS->vardas << " dalykai pagal galutinio atsiskaitymo tipa - " << iTipas << " :" << endl;
		Dalykas* pCurrent = pS->dKitas;
		while (pCurrent != NULL)
		{
			if (pCurrent->tipas == iTipas) {
				pCurrent->RodytiElementa();
				cout << endl;
			}
			pCurrent = pCurrent->dKitas;
		}
	}

};

//meniu 
void Meniu_turinys() {
	cout << "Pasirinkite norima atlikti operacija:" << endl;
	cout << "-------------------------------------" << endl;
	cout << "[1] Registruoti studenta" << endl;
	cout << "[2] Registruoti dalyka" << endl;
	cout << "[3] Registruoti tarpini atsiskaityma" << endl;
	cout << "[4] Isvesti duomenis" << endl;
	cout << "[5] Ivesti vertinima" << endl;
	cout << "[6] Baigti darba su sistema" << endl;
}

//meniu valdymas
void Meniu(int* pas) {
	char lpas;
	Meniu_turinys();
	do {
		lpas = getchar();
		if ((isdigit(lpas) == false) && (lpas != '\n')) {
			system("CLS");
			cout << "Privalote nurodyti skaiciu... [!]" << endl;
			cout << "Bandykite dar karta:" << endl;
			Meniu_turinys();
		}
	} while (isdigit((unsigned char)lpas) == false);
	*pas = (int)lpas - '0';
}

string ivardas;
string idalykas;
string itipas;
string ipozymis;
string idata;
string itf;
int ivertinimas;

int main()
{
	int pas;
	tiesiniu_sar_rinkinys TSR;

	do {
		Meniu(&pas);
		switch (pas) {
		case 1:
			system("CLS");
			cout << "Pasirinkimas [1]" << endl;
			cout << "Iveskite studento varda: " << endl;
			cin >> ivardas;
			TSR.iterpti_studenta(ivardas);
			cout << "Studentas uzregistruotas, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			system("CLS");
			break;
		case 2:
			system("CLS");
			cout << "Pasirinkimas [2]" << endl;
			cout << "Iveskite kuriam studentui norite registruoti dalyka: " << endl;
			cin >> ivardas;
			cout << "Iveskite dalyko pavadinima: " << endl;
			cin >> idalykas;
			cout << "Iveskite dalyko galutinio atsiskaitymo tipa: " << endl;
			cin >> itipas;
			cout << "Iveskite dalyko paskirties pozymi: " << endl;
			cin >> ipozymis;
			TSR.naujas_dalykas_i_nurodyta_studenta(ivardas, idalykas, itipas, ipozymis);
			cout << "Dalykas uzregistruotas, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			system("CLS");
			break;

		case 3:
			system("CLS");
			cout << "Pasirinkimas [3]" << endl;
			cout << "Iveskite kuriam studentui norite registruoti tarpini atsiskaityma: " << endl;
			cin >> ivardas;
			cout << "Iveskite dalyko pavadinima: " << endl;
			cin >> idalykas;
			cout << "Iveskite tarpinio atsiskaitymo data (MMMM-mm-dd): " << endl;
			cin >> idata;
			cout << "Ar norite registruoti pazymi (taip/ne): " << endl;
			cin >> itf;
			if (itf == "taip" || itf == "Taip") {
				cout << "Iveskite vertinima: " << endl;
				cin >> ivertinimas;
				TSR.naujas_vertinimas_i_nurodyta_dalyka(ivardas, idalykas, ivertinimas, idata);
			}
			else {
				TSR.naujas_vertinimas_i_nurodyta_dalyka(ivardas, idalykas, -1, idata);
			}
			cout << "Tarpinis atsiskaitymas uzregistruotas, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			system("CLS");
			break;
		case 4:
			system("CLS");
			cout << "Pasirinkimas [4]" << endl;
			cout << "Pasirinkite kurios duomenis spausdinti: " << endl;
			cout << " [1] Isvesti visus duomenis \n [2] Isvesti dalyku ir tarpiniu atsiskaitymu sarasa \n [3] Isvesti dalyku sarasa pagal galutini atsiskaityma \n [4] Isvesti dalyku sarasa pagal nurodyta paskirti \n [5] Isvesti tarpiniu atsiskaitymu sarasa\n";
			cin >> pas;
			if (pas == 1) {
				system("CLS");
				TSR.rodyti_studentus();
			}
			else if (pas == 2) {
				system("CLS");
				cout << "Pasirinkite studenta: " << endl;
				cin >> ivardas;
				system("CLS");
				TSR.rodyti_studento_dalykus(ivardas);
			}
			else if (pas == 3) {
				system("CLS");
				cout << "Pasirinkite studenta: " << endl;
				cin >> ivardas;
				cout << "Pasirinkite galutinio atsiskaitymo tipa: " << endl;
				cin >> itipas;
				system("CLS");
				TSR.rodyti_studento_dalykus_pagal_tipas(ivardas, itipas);
			}
			else if (pas == 4) {
				system("CLS");
				cout << "Pasirinkite studenta: " << endl;
				cin >> ivardas;
				cout << "Pasirinkite paskirties pozymi: " << endl;
				cin >> ipozymis;
				system("CLS");
				TSR.rodyti_studento_dalykus_pagal_paskirti(ivardas, ipozymis);
			}
			else {
				system("CLS");
				cout << "Pasirinkite studenta: " << endl;
				cin >> ivardas;
				system("CLS");
				TSR.rodyti_studento_tarpinius(ivardas);
			}
			cout << "Spausdinimas atliktas sekmingai, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			system("CLS");
			break;
		case 5:
			system("CLS");
			cout << "Pasirinkimas [5]" << endl;
			cout << "Pasirinkite studenta: " << endl;
			cin >> ivardas;
			cout << "Pasirinkite dalyka: " << endl;
			cin >> idalykas;
			cout << "Pasirinkite atsiskaitymo data: " << endl;
			cin >> idata;
			cout << "Pasirinkite vertinima: " << endl;
			cin >> ivertinimas;
			TSR.atnaujinti_vertinima(ivardas, idalykas, ivertinimas, idata);
			cout << "Vertinimas irasytas sekmingai, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			system("CLS");
			break;
		default:
			system("CLS");
			cout << "Viso gero..." << endl;
			break;
		}
	} while (pas != 6);

	return 0;
}
