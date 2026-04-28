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
    if (jumlahUser >= MAX_USER) throw overflow_error("Kapasitas penuh!");

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
    daftarUser[jumlahUser].billing = {0, 0};
    jumlahUser++;
    cout << "Register Berhasil!\n";
}

bool login(User* daftarUser, int jumlahUser, bool& admin, int& userIndex) {
    string namaInput, nimInput;
    int percobaan = 0;

    while (percobaan < 3) {
        cout << "\n===== LOGIN =====\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Masukkan Nama : "; getline(cin, namaInput);
        cout << "Masukkan NIM : "; cin >> nimInput;

        if (namaInput == "Admin" && nimInput == "076") {
            admin = true; return true;
        }

        for (int i = 0; i < jumlahUser; i++) {
            if (namaInput == daftarUser[i].nama && nimInput == daftarUser[i].nim) {
                admin = false; userIndex = i; return true;
            }
        }
        percobaan++;
        cout << "Login gagal!\n";
    }
    throw runtime_error("Kesempatan login habis.");
}

void tampilkanMember(User* daftarUser, int jumlahUser) {
    if (jumlahUser == 0) {
        cout << "Belum ada member\n";
    } else {
        cout << "\n===== DATA MEMBER =====\n";
        cout << left << setw(5) << "No" << setw(25) << "Nama" << setw(15) << "NIM" 
             << setw(10) << "Jam" << setw(15) << "Masa Aktif" << endl;
        for (int i = 0; i < jumlahUser; i++) {
            cout << setw(5) << i + 1 << setw(25) << daftarUser[i].nama << setw(15) << daftarUser[i].nim 
                 << setw(10) << daftarUser[i].billing.jam << setw(10) << daftarUser[i].billing.masaAktif << " hari" << endl;
        }
    }
}

void updateIdentitas(User* daftarUser, int jumlahUser) {
    int index;
    cout << "Pilih nomor member : "; cin >> index;
    validasiInput();
    if (index > 0 && index <= jumlahUser) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nama baru : "; getline(cin, daftarUser[index-1].nama);
        cout << "NIM baru : "; cin >> daftarUser[index-1].nim;
        cout << "Data Member berhasil diubah\n";
    } else throw out_of_range("Nomor tidak valid");
}

void hapusMember(User* daftarUser, int& jumlahUser) {
    int index;
    cout << "Pilih nomor member : "; cin >> index;
    validasiInput();
    if (index > 0 && index <= jumlahUser) {
        for (int i = index - 1; i < jumlahUser - 1; i++) daftarUser[i] = daftarUser[i + 1];
        jumlahUser--;
        cout << "Member berhasil dihapus\n";
    } else throw out_of_range("Nomor tidak valid");
}

void sortByNim(User* daftarUser, int jumlahUser) {
    for (int i = 0; i < jumlahUser - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < jumlahUser; j++) {
            if (daftarUser[j].nim < daftarUser[minIdx].nim) minIdx = j;
        }
        swap(daftarUser[i], daftarUser[minIdx]);
    }
}

void menuCariNim(User* daftarUser, int jumlahUser) {
    if (jumlahUser == 0) throw runtime_error("Belum ada data!");
    User temp[MAX_USER];
    for(int i=0; i<jumlahUser; i++) temp[i] = daftarUser[i];
    sortByNim(temp, jumlahUser);
    
    string target;
    cout << "Masukkan NIM : "; cin >> target;
    int low = 0, high = jumlahUser - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (temp[mid].nim == target) {
            cout << "Ditemukan: " << temp[mid].nama << endl;
            return;
        }
        if (temp[mid].nim < target) low = mid + 1;
        else high = mid - 1;
    }
    cout << "Tidak ditemukan\n";
}

void menuAdmin(User* daftarUser, int& jumlahUser) {
    int pil;
    do {
        try {
            cout << "\n===== MENU ADMIN =====\n1. Tambah\n2. Lihat\n3. Update\n4. Hapus\n5. Cari NIM\n6. Logout\nPilihan : ";
            cin >> pil; validasiInput();
            switch (pil) {
                case 1: registerUser(daftarUser, jumlahUser); break;
                case 2: tampilkanMember(daftarUser, jumlahUser); break;
                case 3: updateIdentitas(daftarUser, jumlahUser); break;
                case 4: hapusMember(daftarUser, jumlahUser); break;
                case 5: menuCariNim(daftarUser, jumlahUser); break;
                case 6: break;
                default: throw out_of_range("Pilihan salah");
            }
        } catch (const exception& e) { cout << "Error: " << e.what() << endl; }
    } while (pil != 6);
}

void menuUser(User* daftarUser, int index) {
    int pil;
    do {
        try {
            cout << "\n===== MENU USER =====\n1. Profil\n2. Logout\nPilihan : ";
            cin >> pil; validasiInput();
            if(pil == 1) cout << "Nama: " << daftarUser[index].nama << "\nNIM: " << daftarUser[index].nim << endl;
        } catch (const exception& e) { cout << "Error: " << e.what() << endl; }
    } while (pil != 2);
}

int main() {
    int menuAwal;
    do {
        try {
            cout << "\n===== MENU AWAL =====\n1. Register\n2. Login\n3. Keluar\nPilihan : ";
            cin >> menuAwal;
            validasiInput();
            switch (menuAwal) {
                case 1: registerUser(daftarUser, jumlahUser); break;
                case 2: {
                    bool admin = false; int idx = -1;
                    if (login(daftarUser, jumlahUser, admin, idx)) {
                        if (admin) menuAdmin(daftarUser, jumlahUser);
                        else menuUser(daftarUser, idx);
                    }
                    break;
                }
                case 3: break;
                default: throw out_of_range("Pilihan salah");
            }
        } catch (const exception& e) { cout << "\n[!] ERROR: " << e.what() << endl; }
    } while (menuAwal != 3);
    return 0;
}