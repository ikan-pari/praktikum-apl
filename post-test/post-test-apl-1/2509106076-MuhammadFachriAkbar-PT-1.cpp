#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    string nama;
    string password;
    string passwordBenar = "076";
    int kesempatan = 0;

    cout << "=====================================\n";
    cout << "        PROGRAM KONVERSI PANJANG     \n";
    cout << "=====================================\n\n";


    while (kesempatan < 3) {
        cout << "Masukkan Nama     : ";
        cin >> nama;
        cout << "Masukkan Password : ";
        cin >> password;

        if (password == passwordBenar) {
            cout << "\nLogin Berhasil! Selamat datang " << nama << endl;
            break;
        } else {
            kesempatan++;
            cout << "Password Salah! Sisa kesempatan: "
                 << 3 - kesempatan << endl;
        }
    }

    if (kesempatan == 3) {
        cout << "\nAnda salah 3 kali. Program berhenti.\n";
        return 0;
    }


    cout << fixed << setprecision(2);

    int pilihan;
    double nilai;

    
    do {
        cout << "\n=====================================\n";
        cout << "               MENU UTAMA            \n";
        cout << "=====================================\n";
        cout << "1. Meter -> Kilometer & Centimeter\n";
        cout << "2. Kilometer -> Meter & Centimeter\n";
        cout << "3. Centimeter -> Meter & Kilometer\n";
        cout << "4. Keluar\n";
        cout << "=====================================\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {

            case 1:
                cout << "Masukkan nilai Meter: ";
                cin >> nilai;
                cout << "Hasil Konversi:\n";
                cout << nilai / 1000 << " Kilometer\n";
                cout << nilai * 100 << " Centimeter\n";
                break;

            case 2:
                cout << "Masukkan nilai Kilometer: ";
                cin >> nilai;
                cout << "Hasil Konversi:\n";
                cout << nilai * 1000 << " Meter\n";
                cout << nilai * 100000 << " Centimeter\n";
                break;

            case 3:
                cout << "Masukkan nilai Centimeter: ";
                cin >> nilai;
                cout << "Hasil Konversi:\n";
                cout << nilai / 100 << " Meter\n";
                cout << nilai / 100000 << " Kilometer\n";
                break;

            case 4:
                cout << "Terima kasih telah menggunakan program.\n";
                break;

            default:
                cout << "Pilihan tidak tersedia!\n";
        }

    } while (pilihan != 4);

    return 0;
}