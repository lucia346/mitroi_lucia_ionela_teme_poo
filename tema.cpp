#include<iostream>
#include<string>

using namespace std;

enum Categorie { STELE_3 = 3, STELE_4 = 4, STELE_5 = 5 };

class Hotel {
private:
	const int id;
	string denumire;
	Categorie categorie;
	int nrCamere;
	float* preturiCamere; 
public:
	static int nrHoteluri;

	Hotel() : id(++nrHoteluri) {
		this->denumire = "Hotel Anonim";
		this->categorie = STELE_3;
		this->nrCamere = 0;
		this->preturiCamere = nullptr;
	}

	Hotel(int id, string denumire, Categorie categorie, int nrCamere, float* preturiCamere) : id(id) {
		this->denumire = denumire;
		this->categorie = categorie;
		this->nrCamere = nrCamere;
		if (nrCamere > 0 && preturiCamere != nullptr) {
			this->preturiCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->preturiCamere[i] = preturiCamere[i];
			}
		}
		else {
			this->preturiCamere = nullptr;
			this->nrCamere = 0;
		}
		nrHoteluri++;
	}

	Hotel(const Hotel& h) : id(++nrHoteluri) {
		this->denumire = h.denumire;
		this->categorie = h.categorie;
		this->nrCamere = h.nrCamere;

		if (h.preturiCamere != nullptr) {
			this->preturiCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->preturiCamere[i] = h.preturiCamere[i];
			}
		}
		else {
			this->preturiCamere = nullptr;
		}
	}

	Hotel& operator=(const Hotel& h) {
		if (this == &h) {
			return *this; // auto-atribuire
		}

		this->denumire = h.denumire;
		this->categorie = h.categorie;
		this->nrCamere = h.nrCamere;

		if (this->preturiCamere != nullptr) {
			delete[] this->preturiCamere;
			this->preturiCamere = nullptr;
		}

		if (h.preturiCamere != nullptr) {
			this->preturiCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->preturiCamere[i] = h.preturiCamere[i];
			}
		}
		else {
			this->preturiCamere = nullptr;
		}

		return *this;
	}

	~Hotel() {
		if (this->preturiCamere != nullptr) {
			delete[] this->preturiCamere;
		}
	}

	void afisareHotel() {
		cout << endl << "------------------------";
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Categorie: " << this->categorie << " stele";
		cout << endl << "Nr camere: " << this->nrCamere;

		if (this->nrCamere > 0 && this->preturiCamere != nullptr) {
			cout << endl << "Preturi camere: ";
			for (int i = 0; i < this->nrCamere; i++) {
				cout << this->preturiCamere[i] << " lei";
				if (i < this->nrCamere - 1) cout << ", ";
			}
		}
		cout << endl;
	}

	int getNrCamere() {
		return this->nrCamere;
	}

	void setNrCamere(int nrCamereNou) {
		if (nrCamereNou >= 0) {
			this->nrCamere = nrCamereNou;
		}
		else {
			throw "Numarul de camere nu poate fi negativ!";
		}
	}

	bool operator<(const Hotel& h) {
		return this->nrCamere < h.nrCamere;
	}
};

int Hotel::nrHoteluri = 0;

void main() {
	Hotel hDefault;
	hDefault.afisareHotel();

	float* preturi = new float[4] {250.5f, 300.0f, 450.0f, 600.0f};
	Hotel* pHotelLux = new Hotel(10, "Grand Hotel", STELE_5, 4, preturi);
	pHotelLux->afisareHotel();

	Hotel hCopie = *pHotelLux;
	hCopie.afisareHotel();

	hDefault = *pHotelLux;
	hDefault.afisareHotel();

	cout << endl << "Total hoteluri create: " << Hotel::nrHoteluri;
 <
	if (hDefault < hCopie) {
		cout << endl << "Hotelul default are mai putine camere.";
	}
	else {
		cout << endl << "Hotelurile au acelasi numar de camere sau cel de-al doilea are mai putine.";
	}

	delete pHotelLux;
}
