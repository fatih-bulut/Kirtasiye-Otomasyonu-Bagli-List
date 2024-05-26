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
    cout << "Aranacak Ürün Adýný Giriniz: ";
    cin >> aranan;

    kirtasiyeUrunu* yedek = head;
    bool bulundu = false;
    while (yedek != NULL) {
        if (strcasecmp(yedek->urunAdi, aranan) == 0) {
            cout << "Ürünün Adý: " << yedek->urunAdi << endl;
            cout << "Ürünün Fiyatý: " << yedek->fiyat << endl;
            cout << "Ürünün Þuanki Stoðu: " << yedek->gelenAdet << endl;
            cout << "--------------------------------------" << endl;
            bulundu = true;
            break;
        }
        yedek = yedek->link;
    }

    if (!bulundu) {
        cout << "Aranan ürün bulunamadý." << endl;
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
        cout << "Stoða Girilecek Ürünün Adýný Giriniz" << endl;
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
        cout << "Stoða Girilecek Ürünün Adetini Giriniz" << endl;
        cin >> yeni->gelenAdet;
        cout << "Stoða Girilecek Ürünün 1 Adedinin Fiyatýný Giriniz" << endl;
        cin >> yeni->fiyat;
        yeni->kalanAdet = yeni->gelenAdet;
        yeni->link = head;
        head = yeni;
        cesit++;
        cout << "Stoða Baþka Bir Kayýt Yapacak mýsýnýz? (e/h)" << endl;
        secim = getche();
        cout << endl;
        dosyayaKaydet();
    }else{cout << "Stokta Zaten Var!" << endl; break;}
	} while (secim == 'e' || secim == 'E');
	if(cesit!=0){
    cout << cesit << " Çeþit Ürün Stoða Girildi.." << endl;}
}

void stokListeleme() {
    kirtasiyeUrunu* yedek = head;
    int index = 1;

    if (yedek == NULL) {
        cout << "Stok Bulunamadý" << endl;
        return;
    }

    while (yedek != NULL) {
        cout << index++ << ". Ürünün Bilgileri" << endl;
        cout << "Ürünün Adý: " << yedek->urunAdi << endl;
        cout << "Ürünün Fiyatý: " << yedek->fiyat << endl;
        cout << "Ürünün Þuanki Stoðu: " << yedek->gelenAdet << endl;
        cout << "--------------------------------------" << endl;
		yedek = yedek->link;
    }
}

void urunSatis() {
    char urunAdi[80];
    cout << "Satýlacak Ürünün Adýný Giriniz" << endl;
    cin >> urunAdi;

    kirtasiyeUrunu* yedek = head;
    kirtasiyeUrunu* once = NULL;

    while (yedek != NULL && strcasecmp(yedek->urunAdi, urunAdi) != 0) {
        once = yedek;
        yedek = yedek->link;
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamadý" << endl;
        return;
    }

    cout << "Satýlacak Ürünün Bilgileri" << endl;
    cout << "Ürünün Adý: " << yedek->urunAdi << endl;
    cout << "Ürünün Fiyatý: " << yedek->fiyat << endl;
    cout << "Ürünün Þuanki Stoðu: " << yedek->gelenAdet << endl;
    cout << endl;

    int satis;
    cout << "Kaç Adet Satýlacaðýný Giriniz: ";
    cin >> satis;
    cout << endl;

    int ucret = 0;

    if (satis > yedek->gelenAdet) {
        cout << "Ýstenilen adetten az stok var. Tüm stok satýldý." << endl;
        ucret = yedek->gelenAdet * yedek->fiyat;
        cout << "Satýþ Tutarý: " << ucret << endl;
        yedek->gelenAdet = 0;
        dosyayaKaydet();
    } else {
        ucret = satis * yedek->fiyat;
        cout << "Satýþ Tutarý: " << ucret << endl;
        yedek->gelenAdet -= satis;
        dosyayaKaydet();
    }

    if (yedek->gelenAdet == 0) {
        cout << "Stok sýfýrlandýðý için ürün silindi." << endl;
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
    cout << "Silinecek Ürünün Adýný Giriniz" << endl;
    cin >> urunAdi;

    kirtasiyeUrunu* yedek = head;
    kirtasiyeUrunu* once = NULL;

    while (yedek != NULL && strcasecmp(yedek->urunAdi, urunAdi) != 0) {
        once = yedek;
        yedek = yedek->link;
        system("cls");
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamadý" << endl;
        return;
    }
    cout << "Silinecek Ürünün Bilgileri" << endl;
    cout << "Ürünün Adý: " << yedek->urunAdi << endl;
    cout << "Ürünün Fiyatý: " << yedek->fiyat << endl;
    cout << "Ürünün Þuanki Stoðu: " << yedek->gelenAdet << endl;
    cout << endl;

    char secim;
    cout << "Stoktan Silinecek Ürün bu mu? (e/h)" << endl;
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
        cout << "Stok Silme Ýptal Edildi" << endl;
    }
}

void stokDuzenle() {
    char urunAdi[80];
    cout << "Düzeltilecek Ürünün Adýný Giriniz" << endl;
    cin >> urunAdi;

    kirtasiyeUrunu* yedek = head;

    while (yedek != NULL && strcasecmp(yedek->urunAdi, urunAdi) != 0) {
        yedek = yedek->link;
        system("cls");
    }

    if (yedek == NULL) {
        cout << "Stok Bulunamadý" << endl;
        return;
    }

    cout << "Düzeltilecek Ürünün Bilgileri" << endl;
    cout << "Ürünün Adý: " << yedek->urunAdi << endl;
    cout << "Ürünün Fiyatý: " << yedek->fiyat << endl;
    cout << "Ürünün Þuanki Stoðu: " << yedek->gelenAdet << endl;
    cout << endl;

    char secim;
    cout << "Düzeltilecek Ürün Bu mu? (e/h)" << endl;
    secim = getche();
    cout << endl;

    if (secim == 'e' || secim == 'E') {
        cout << "Yeni Ürünün Adýný Giriniz" << endl;
        cin >> yedek->urunAdi;
        cout << "Yeni Ürünün Adetini Giriniz" << endl;
        cin >> yedek->gelenAdet;
        cout << "Yeni Ürünün 1 Adedinin Fiyatýný Giriniz" << endl;
        cin >> yedek->fiyat;
        yedek->kalanAdet = yedek->gelenAdet;
        cout << "Stok Düzeltildi" << endl;
        dosyayaKaydet();
    } else {
        cout << "Stok Düzeltme Ýptal Edildi" << endl;
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
    bosluk(); cout << "          KIRTASÝYE OTOMASYONU       "  << endl;
    bosluk(); cizgi();
	bosluk(); cout << " /*          Ana Menü               *\\ " << endl;
	bosluk(); cout << " \\*          1.Ürün Giriþi          */ " << endl;               
	bosluk(); cout << " /*          2.Stok Listesi          *\\ " << endl;
	bosluk(); cout << " \\*          3.Ürün Satýþý          */ " << endl;
	bosluk(); cout << " /*          4.Ürün Silme         *\\" << endl;
	bosluk(); cout << " \\*          5.Stok Düzeltme         */ " << endl;
    bosluk(); cout << " \\*          6.Ürün Arama           */ " << endl;
	bosluk(); cout << " \\*          7.Çýkýþ                 *\\ " << endl;
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
                cout << "Programdan Çýktýnýz!" << endl;
				break;
			}
        }
        if(islemSecme!='7'){
        cout << "Ana menüye dönmek istiyorsanýz (e), Çýkmak istiyorsanýz (h) basýnýz." << endl;
        menu = getche();
		}
    } while (menu == 'e' || menu == 'E');
    
    dosyadanYukle();
    return 0;
}

