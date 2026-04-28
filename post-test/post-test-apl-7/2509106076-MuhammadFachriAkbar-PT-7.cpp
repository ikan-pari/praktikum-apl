#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include "Member.h"

using namespace std;

#define MAX_USER 100

User daftarUser[MAX_USER];
int jumlahUser = 0;

void validasiInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Input harus berupa angka!");
    }
}

string keKecil(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

User* cariUser(User* daftarUser, int jumlahUser, string nama) {
    for (int i = 0; i < jumlahUser; i++) {
        if (keKecil(daftarUser[i].nama) == keKecil(nama)) {
            return &daftarUser[i];
        }
    }
    return nullptr;
}

bool cekNama(User* daftarUser, int jumlahUser, string namaBaru) {
    return cariUser(daftarUser, jumlahUser, namaBaru) != nullptr;
}

void registerUser(User* daftarUser, int& jumlahUser) {
    if (jumlahUser >= MAX_USER) {
        throw overflow_error("Kapasitas user sudah penuh!");
    }

    string namaBaru;
    cout << "\n===== REGISTER =====\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Lengkap : ";
    getline(cin, namaBaru);

    if (cekNama(daftarUser, jumlahUser, namaBaru)) {
        throw runtime_error("Nama sudah digunakan!");
    }

    daftarUser[jumlahUser].nama = namaBaru;
    cout << "Masukkan NIM : ";
    cin >> daftarUser[jumlahUser].nim;
    daftarUser[jumlahUser].billing.jam = 0;
    daftarUser[jumlahUser].billing.masaAktif = 0;
    jumlahUser++;

    cout << "Register Berhasil!\n";
}

void sortByNim(User* daftarUser, int jumlahUser) {
    for (int i = 0; i < jumlahUser - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < jumlahUser; j++) {
            if (daftarUser[j].nim < daftarUser[minIdx].nim)
                minIdx = j;
        }
        if (minIdx != i)
            swap(daftarUser[i], daftarUser[minIdx]);
    }
}

void menuCariNim(User* daftarUser, int jumlahUser) {
    if (jumlahUser == 0) throw runtime_error("Data member masih kosong!");

    User tempDaftar[MAX_USER];
    for(int i = 0; i < jumlahUser; i++) tempDaftar[i] = daftarUser[i];

    sortByNim(tempDaftar, jumlahUser);

    string targetNim;
    cout << "\n===== CARI NIM (Binary Search) =====\n";
    cout << "Masukkan NIM : ";
    cin >> targetNim;

    int low = 0, high = jumlahUser - 1;
    User* hasil = nullptr;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (tempDaftar[mid].nim == targetNim) {
            hasil = &tempDaftar[mid];
            break;
        }
        else if (tempDaftar[mid].nim < targetNim) low = mid + 1;
        else high = mid - 1;
    }

    if (hasil != nullptr) {
        cout << "Member Ditemukan: " << hasil->nama << " (NIM: " << hasil->nim << ")\n";
    } else {
        cout << "NIM tidak ditemukan.\n";
    }
}

int main() {
    int menuAwal;
    do {
        try {
            cout << "\n===== MENU AWAL =====\n";
            cout << "1. Register\n";
            cout << "2. Cari NIM (Binary Search)\n";
            cout << "3. Keluar\n";
            cout << "Pilihan : ";
            cin >> menuAwal;
            validasiInput();

            switch (menuAwal) {
                case 1: 
                    registerUser(daftarUser, jumlahUser); 
                    break;
                case 2: 
                    menuCariNim(daftarUser, jumlahUser); 
                    break;
                case 3: 
                    break;
                default: 
                    throw out_of_range("Pilihan tidak tersedia!");
            }
        } 
        catch (const exception& e) {
            cout << "\n[!] ERROR: " << e.what() << endl;
        }
    } while (menuAwal != 3);

    cout << "Terimakasih Sudah Menggunakan Program!\n";
    return 0;
}