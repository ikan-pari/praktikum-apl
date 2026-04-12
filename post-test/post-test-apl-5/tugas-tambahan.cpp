#include <iostream>
#include <string>
using namespace std;

struct Bahan {
    string nama;
    int stok;
};

void insertionSort(Bahan gudang[], int n) {
    for (int i = 1; i < n; i++) {
        Bahan key = gudang[i];
        int j = i - 1;
        while (j >= 0 && gudang[j].stok > key.stok) {
            gudang[j + 1] = gudang[j];
            j--;
        }
        gudang[j + 1] = key;
    }
}

void tampilGudang(Bahan gudang[], int n) {
    cout << "\nNo  Bahan       Stok (ton)\n";
    cout << "----------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "   "
             << gudang[i].nama << "\t"
             << gudang[i].stok << " ton\n";
    }
}

int main() {
    Bahan gudang[] = {
        {"Beras",    45},
        {"Jagung",   60},
        {"Kentang",  15},
        {"Singkong", 20}
    };
    int n = sizeof(gudang) / sizeof(Bahan);

    cout << "=== Stok Sebelum Diurutkan ===";
    tampilGudang(gudang, n);

    insertionSort(gudang, n);

    cout << "\n=== Stok Setelah Diurutkan (Terkecil ke Terbesar) ===";
    tampilGudang(gudang, n);

    return 0;
}