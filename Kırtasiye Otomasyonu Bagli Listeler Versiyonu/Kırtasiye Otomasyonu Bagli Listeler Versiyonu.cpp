#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct kirtasiyeUrunu {
    char urunAdi[80];
    int gelenAdet;
    int kalanAdet;
    int fiyat;
    kirtasiyeUrunu* link;
};

kirtasiyeUrunu* head = NULL;


void arama() {
    char aranan[80];
    cout << "Aranacak �r�n Ad�n� Giriniz: ";
    cin >> aranan;

    kirtasiyeUrunu* yedek = head;
    bool bulundu = false;
    while (yedek != NULL) {
        if (strcasecmp(yedek->urunAdi, aranan) == 0) {
            cout << "�r�n�n Ad�: " << yedek->urunAdi << endl;
            cout << "�r�n�n Fiyat�: " << yedek->fiyat << endl;
            cout << "�r�n�n �uanki Sto�u: " << yedek->gelenAdet << endl;
            cout << "--------------------------------------" << endl;
            bulundu = true;
            break;
        }
        yedek = yedek->link;
    }

    if (!bulundu) {
        cout << "Aranan �r�n bulunamad�." << endl;
    }
}

void dosyayaKaydet() {
    ofstream file("stok.dat", ios::binary | ios::trunc);
    kirtasiyeUrunu* yedek = head;
    while (yedek != NULL) {
        file.write((char*)yedek, sizeof(kirtasiyeUrunu));
        yedek = yedek->link;
    }
    file.close();
}
void stokEkle() {
    char secim;
    int cesit = 0;

    do {
        kirtasiyeUrunu* yeni = new kirtasiyeUrunu();
        cout << "Sto�a Girilecek �r�n�n Ad�n� Giriniz" << endl;
        cin >> yeni->urunAdi;
        kirtasiyeUrunu* yedek = head;
        bool bulundu = false;
        while (yedek != NULL) {
        if (strcasecmp(yedek->urunAdi, yeni->urunAdi) == 0) {
            bulundu = true;
            break;
        }
        yedek = yedek->link;
    }
    if(bulundu == false){
        cout << "Sto�a Girilecek �r�n�n Adetini Giriniz" << endl;
        cin >> yeni->gelenAdet;
        cout << "Sto�a Girilecek �r�n�n 1 Adedinin Fiyat�n� Giriniz" << endl;
        cin >> yeni->fiyat;
        yeni->kalanAdet = yeni->gelenAdet;
        yeni->link = head;
        head = yeni;
        cesit++;
        cout << "Sto�a Ba�ka Bir Kay�t Yapacak m�s�n�z? (e/h)" << endl;
        secim = getche();
        cout << endl;
        dosyayaKaydet();
    }else{cout << "Stokta Zaten Var!" << endl; break;}
	} while (secim == 'e' || secim == 'E');
	if(cesit!=0){
    cout << cesit << " �e�it �r�n Sto�a Girildi.." << endl;}
}

void stokListeleme() {
    kirtasiyeUrunu* yedek = head;
    int index = 1;

    if (yedek == NULL) {
        cout << "Stok Bulunamad�" << endl;
        return;
    }

    while (yedek != NULL) {
        cout << index++ << ". �r�n�n Bilgileri" << endl;
        cout << "�r�n�n Ad�: " << yedek->urunAdi << endl;
        cout << "�r�n�n Fiyat�: " << yedek->fiyat << endl;
        cout << "�r�n�n �uanki Sto�u: " << yedek->gelenAdet << endl;
        cout << "--------------------------------------" << endl;
		yedek = yedek->link;
    }
}

void urunSatis() {
    char urunAdi[80];
    cout << "Sat�lacak �r�n�n Ad�n� Giriniz" << endl;
    cin >> urunAdi;

    kirtasiyeUrunu* yedek = head;
    kirtasiyeUrunu* once = NULL;

    while (yedek != NULL && strcasecmp(yedek->urunAdi, urunAdi) != 0) {
        once = yedek;
        yedek = yedek->link;
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamad�" << endl;
        return;
    }

    cout << "Sat�lacak �r�n�n Bilgileri" << endl;
    cout << "�r�n�n Ad�: " << yedek->urunAdi << endl;
    cout << "�r�n�n Fiyat�: " << yedek->fiyat << endl;
    cout << "�r�n�n �uanki Sto�u: " << yedek->gelenAdet << endl;
    cout << endl;

    int satis;
    cout << "Ka� Adet Sat�laca��n� Giriniz: ";
    cin >> satis;
    cout << endl;

    int ucret = 0;

    if (satis > yedek->gelenAdet) {
        cout << "�stenilen adetten az stok var. T�m stok sat�ld�." << endl;
        ucret = yedek->gelenAdet * yedek->fiyat;
        cout << "Sat�� Tutar�: " << ucret << endl;
        yedek->gelenAdet = 0;
        dosyayaKaydet();
    } else {
        ucret = satis * yedek->fiyat;
        cout << "Sat�� Tutar�: " << ucret << endl;
        yedek->gelenAdet -= satis;
        dosyayaKaydet();
    }

    if (yedek->gelenAdet == 0) {
        cout << "Stok s�f�rland��� i�in �r�n silindi." << endl;
        if (once == NULL) {
            head = yedek->link;
        } else {
            once->link = yedek->link;
        }
        delete yedek;
    }
}

void stokSilme() {
    char urunAdi[80];
    cout << "Silinecek �r�n�n Ad�n� Giriniz" << endl;
    cin >> urunAdi;

    kirtasiyeUrunu* yedek = head;
    kirtasiyeUrunu* once = NULL;

    while (yedek != NULL && strcasecmp(yedek->urunAdi, urunAdi) != 0) {
        once = yedek;
        yedek = yedek->link;
        system("cls");
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamad�" << endl;
        return;
    }
    cout << "Silinecek �r�n�n Bilgileri" << endl;
    cout << "�r�n�n Ad�: " << yedek->urunAdi << endl;
    cout << "�r�n�n Fiyat�: " << yedek->fiyat << endl;
    cout << "�r�n�n �uanki Sto�u: " << yedek->gelenAdet << endl;
    cout << endl;

    char secim;
    cout << "Stoktan Silinecek �r�n bu mu? (e/h)" << endl;
    secim = getche();
    cout << endl;

    if (secim == 'e' || secim == 'E') {
        if (once == NULL) {
            head = yedek->link;
        } else {
            once->link = yedek->link;
        }
        delete yedek;
        cout << "Stok Silindi" << endl;
        dosyayaKaydet();
    } else {
        cout << "Stok Silme �ptal Edildi" << endl;
    }
}

void stokDuzenle() {
    char urunAdi[80];
    cout << "D�zeltilecek �r�n�n Ad�n� Giriniz" << endl;
    cin >> urunAdi;

    kirtasiyeUrunu* yedek = head;

    while (yedek != NULL && strcasecmp(yedek->urunAdi, urunAdi) != 0) {
        yedek = yedek->link;
        system("cls");
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamad�" << endl;
        return;
    }

    cout << "D�zeltilecek �r�n�n Bilgileri" << endl;
    cout << "�r�n�n Ad�: " << yedek->urunAdi << endl;
    cout << "�r�n�n Fiyat�: " << yedek->fiyat << endl;
    cout << "�r�n�n �uanki Sto�u: " << yedek->gelenAdet << endl;
    cout << endl;

    char secim;
    cout << "D�zeltilecek �r�n Bu mu? (e/h)" << endl;
    secim = getche();
    cout << endl;

    if (secim == 'e' || secim == 'E') {
        cout << "Yeni �r�n�n Ad�n� Giriniz" << endl;
        cin >> yedek->urunAdi;
        cout << "Yeni �r�n�n Adetini Giriniz" << endl;
        cin >> yedek->gelenAdet;
        cout << "Yeni �r�n�n 1 Adedinin Fiyat�n� Giriniz" << endl;
        cin >> yedek->fiyat;
        yedek->kalanAdet = yedek->gelenAdet;
        cout << "Stok D�zeltildi" << endl;
        dosyayaKaydet();
    } else {
        cout << "Stok D�zeltme �ptal Edildi" << endl;
    }
}

void cizgi() {
    cout <<" "<<" "<<" "<<"----------------------------------" << endl;
}
void bosluk(){
	cout<<"                                                                                                                                                           ";
}

void dosyadanYukle() {
    ifstream file("stok.dat", ios::binary);
    if (!file.is_open()) return;

    while (true) {
        kirtasiyeUrunu* yeni = new kirtasiyeUrunu();
        file.read((char*)yeni, sizeof(kirtasiyeUrunu));
        if (file.eof()) {
            delete yeni;
            break;
        }
        yeni->link = head;
        head = yeni;
    }
    file.close();
}


int main() {
    setlocale(LC_ALL, "Turkish");
    char menu;
    dosyadanYukle();
    do {
        system("cls");
    bosluk(); cout << "          KIRTAS�YE OTOMASYONU       "  << endl;
    bosluk(); cizgi();
	bosluk(); cout << " /*          Ana Men�               *\\ " << endl;
	bosluk(); cout << " \\*          1.�r�n Giri�i          */ " << endl;               
	bosluk(); cout << " /*          2.Stok Listesi          *\\ " << endl;
	bosluk(); cout << " \\*          3.�r�n Sat���          */ " << endl;
	bosluk(); cout << " /*          4.�r�n Silme         *\\" << endl;
	bosluk(); cout << " \\*          5.Stok D�zeltme         */ " << endl;
    bosluk(); cout << " \\*          6.�r�n Arama           */ " << endl;
	bosluk(); cout << " \\*          7.��k��                 *\\ " << endl;
	bosluk(); cizgi();
    cout << endl; 
        char islemSecme;
		islemSecme = getche();
        
        switch (islemSecme) {
            case '1': {
                system("cls");
                stokListeleme();
				stokEkle();
                break;
            }
            case '2': {
            	system("cls");
                stokListeleme();
                break;
            }
            case '3': {
            	system("cls");
            	stokListeleme();
                urunSatis();
                break;
            }
            case '4': {
            	system("cls");
            	stokListeleme();
                stokSilme();
                break;
            }
            case '5': {
            	system("cls");
            	stokListeleme();
                stokDuzenle();
                break;
            }
            case '6':{
            	system("cls");
            	arama();
				break;
			}
            case '7':{
            	system("cls");
            	menu = 'h';
                cout << "Programdan ��kt�n�z!" << endl;
				break;
			}
        }
        if(islemSecme!='7'){
        cout << "Ana men�ye d�nmek istiyorsan�z (e), ��kmak istiyorsan�z (h) bas�n�z." << endl;
        menu = getche();
		}
    } while (menu == 'e' || menu == 'E');
    
    dosyadanYukle();
    return 0;
}

