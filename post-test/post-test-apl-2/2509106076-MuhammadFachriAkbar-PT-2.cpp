#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

#define MAX_USER 100

struct Billing{
    int jam;
    int masaAktif;
};

struct User{
    string nama;
    string nim;
    Billing billing;
};

User daftarUser[MAX_USER];
int jumlahUser = 0;

int main(){

    int menuAwal;

    do{

        cout << "\n===== MENU AWAL =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilihan : ";
        cin >> menuAwal;

        switch(menuAwal){

            case 1:
            {
                if(jumlahUser < MAX_USER){

                    cout << "\n===== REGISTER =====\n";

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Masukkan Nama Lengkap : ";
                    getline(cin, daftarUser[jumlahUser].nama);

                    cout << "Masukkan NIM : ";
                    cin >> daftarUser[jumlahUser].nim;

                    daftarUser[jumlahUser].billing.jam = 0;
                    daftarUser[jumlahUser].billing.masaAktif = 0;

                    jumlahUser++;

                    cout << "Register Berhasil!\n";
                }
                else{
                    cout << "Kapasitas penuh!\n";
                }

                break;
            }

            case 2:
            {
                string namaInput;
                string nimInput;

                int percobaan = 0;
                bool loginBerhasil = false;
                bool admin = false;
                int userIndex = -1;

                while(percobaan < 3 && loginBerhasil == false){

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nMasukkan Nama : ";
                    getline(cin,namaInput);

                    cout << "Masukkan NIM : ";
                    cin >> nimInput;

                    if(namaInput == "Admin" && nimInput == "076"){
                        loginBerhasil = true;
                        admin = true;
                    }

                    for(int i=0;i<jumlahUser;i++){
                        if(namaInput == daftarUser[i].nama &&
                           nimInput == daftarUser[i].nim){

                            loginBerhasil = true;
                            admin = false;
                            userIndex = i;
                        }
                    }

                    if(loginBerhasil == false){
                        percobaan++;
                        cout << "Login gagal!\n";
                    }
                }

                if(loginBerhasil == false){
                    cout << "Kesempatan login habis.\n";
                    break;
                }

                if(admin == true){

                    int menuAdmin;
                    int index;

                    do{

                        cout << "\n===== MENU ADMIN =====\n";
                        cout << "1. Tambah Member\n";
                        cout << "2. Lihat Semua Member\n";
                        cout << "3. Update Nama & NIM\n";
                        cout << "4. Update Billing & Masa Aktif\n";
                        cout << "5. Hapus Member\n";
                        cout << "6. Logout\n";
                        cout << "Pilihan : ";
                        cin >> menuAdmin;

                        switch(menuAdmin){

                            case 1:
                            {
                                if(jumlahUser < MAX_USER){

                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Nama : ";
                                    getline(cin, daftarUser[jumlahUser].nama);

                                    cout << "NIM : ";
                                    cin >> daftarUser[jumlahUser].nim;

                                    cout << "Billing Jam : ";
                                    cin >> daftarUser[jumlahUser].billing.jam;

                                    cout << "Masa Aktif : ";
                                    cin >> daftarUser[jumlahUser].billing.masaAktif;

                                    jumlahUser++;

                                    cout << "Member berhasil ditambahkan\n";
                                }
                                else{
                                    cout << "Kapasitas penuh\n";
                                }

                                break;
                            }

                            case 2:
                            {
                                if(jumlahUser == 0){
                                    cout << "Belum ada member\n";
                                }
                                else{

                                    cout << "\n===== DATA MEMBER =====\n";

                                    cout << left
                                    << setw(5) << "No"
                                    << setw(25) << "Nama"
                                    << setw(15) << "NIM"
                                    << setw(10) << "Jam"
                                    << setw(15) << "Masa Aktif"
                                    << endl;

                                    for(int i=0;i<jumlahUser;i++){
                                        cout << setw(5) << i+1
                                        << setw(25) << daftarUser[i].nama
                                        << setw(15) << daftarUser[i].nim
                                        << setw(10) << daftarUser[i].billing.jam
                                        << setw(10) << daftarUser[i].billing.masaAktif << " hari"
                                        << endl;
                                    }
                                }

                                break;
                            }

                            case 3:
                            {
                                cout << "Pilih nomor member : ";
                                cin >> index;

                                if(index > 0 && index <= jumlahUser){

                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                    cout << "Nama baru : ";
                                    getline(cin, daftarUser[index-1].nama);

                                    cout << "NIM baru : ";
                                    cin >> daftarUser[index-1].nim;

                                    cout << "Data Member berhasil diubah\n";
                                }
                                else{
                                    cout << "Nomor tidak valid\n";
                                }

                                break;
                            }

                            case 4:
                            {
                                cout << "Pilih nomor member : ";
                                cin >> index;

                                if(index > 0 && index <= jumlahUser){

                                    cout << "Billing Jam : ";
                                    cin >> daftarUser[index-1].billing.jam;

                                    cout << "Masa Aktif : ";
                                    cin >> daftarUser[index-1].billing.masaAktif;

                                    cout << "Data billing berhasil diubah\n";
                                }
                                else{
                                    cout << "Nomor tidak valid\n";
                                }

                                break;
                            }

                            case 5:
                            {
                                cout << "Pilih nomor member : ";
                                cin >> index;

                                if(index > 0 && index <= jumlahUser){

                                    for(int i=index-1;i<jumlahUser-1;i++){
                                        daftarUser[i] = daftarUser[i+1];
                                    }

                                    jumlahUser--;

                                    cout << "Member berhasil dihapus\n";
                                }
                                else{
                                    cout << "Nomor tidak valid\n";
                                }

                                break;
                            }

                            case 6:
                                break;

                            default:
                                cout << "Pilihan tidak valid\n";

                        }

                    }while(menuAdmin != 6);

                }
                else{

                    int menuUser;

                    do{

                        cout << "\n===== MENU USER =====\n";
                        cout << "1. Lihat Profil\n";
                        cout << "2. Update Nama\n";
                        cout << "3. Update NIM\n";
                        cout << "4. Logout\n";
                        cout << "Pilihan : ";
                        cin >> menuUser;

                        switch(menuUser){

                            case 1:
                            {
                                cout << "\nNama : " << daftarUser[userIndex].nama << endl;
                                cout << "NIM : " << daftarUser[userIndex].nim << endl;
                                cout << "Billing Jam : " << daftarUser[userIndex].billing.jam << endl;
                                cout << "Masa Aktif : " << daftarUser[userIndex].billing.masaAktif << " hari" << endl;
                                break;
                            }

                            case 2:
                            {
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Masukkan nama baru : ";
                                getline(cin, daftarUser[userIndex].nama);
                                cout << "Nama berhasil diperbarui\n";
                                break;
                            }

                            case 3:
                            {
                                cout << "Masukkan NIM baru : ";
                                cin >> daftarUser[userIndex].nim;
                                cout << "NIM berhasil diperbarui\n";
                                break;
                            }

                            case 4:
                                break;

                            default:
                                cout << "Pilihan tidak valid\n";

                        }

                    }while(menuUser != 4);

                }

                break;
            }

            case 3:
                break;

            default:
                cout << "Pilihan tidak valid\n";

        }

    }while(menuAwal != 3);

    cout << "Program selesai\n";

    return 0;
}