#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <vector>

using namespace std;

class TokoElektronik {
private:

    array<string, 3> etalase;

public:
  
    TokoElektronik() {
        etalase[0] = "Laptop ASUS ROG";
        etalase[1] = "Smartphone Samsung S24";
        etalase[2] = "Smart TV LG 43 Inch";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
        
            throw runtime_error("Gagal Mengambil Barang : Rak nomor [" + to_string(nomorRak) + "] kosong atau tidak tersedia!");
        }
    }
};

const string FILE_GUDANG = "gudang.txt";

void tampilkanGudang() {
    ifstream file(FILE_GUDANG);
    string baris;
    int nomor = 1;
    
    cout << "\n=== DAFTAR BARANG DI GUDANG (gudang.txt) ===\n";
    if (file.is_open()) {
        bool adaBarang = false;
        while (getline(file, baris)) {
            if(!baris.empty()) {
                cout << nomor++ << ". " << baris << endl;
                adaBarang = true;
            }
        }
        if (!adaBarang) {
            cout << "[Gudang Kosong]\n";
        }
        file.close();
    } else {
        cout << "[Info] Belum ada file gudang.txt yang terbentuk. Membuat file baru...\n";
        ofstream fileBaru(FILE_GUDANG); // Otomatis buat file kalau belum ada
        fileBaru.close();
    }
    cout << "============================================\n";
}

void tambahBarang() {
    ofstream file(FILE_GUDANG, ios::app); 
    if (file.is_open()) {
        string namaBarang;
        cout << "Masukkan nama barang baru: ";
        cin.ignore();
        getline(cin, namaBarang);
        
        file << namaBarang << endl;
        file.close();
        cout << ">> Barang '" << namaBarang << "' berhasil ditambahkan ke gudang!\n";
    } else {
        cout << ">> Gagal membuka file gudang!\n";
    }
}

void updateBarang() {
    tampilkanGudang();
    ifstream fileInput(FILE_GUDANG);
    vector<string> listBarang;
    string baris;
    
    while (getline(fileInput, baris)) {
        if(!baris.empty()) listBarang.push_back(baris);
    }
    fileInput.close();

    if (listBarang.empty()) {
        cout << "Tidak ada barang yang bisa di-update.\n";
        return;
    }

    int pilihan;
    cout << "Pilih nomor barang yang ingin diubah: ";
    cin >> pilihan;

    if (pilihan > 0 && pilihan <= listBarang.size()) {
        string namaBaru;
        cout << "Masukkan nama baru untuk '" << listBarang[pilihan - 1] << "': ";
        cin.ignore();
        getline(cin, namaBaru);

        listBarang[pilihan - 1] = namaBaru;

        ofstream fileOutput(FILE_GUDANG);
        for (const auto& barang : listBarang) {
            fileOutput << barang << endl;
        }
        fileOutput.close();
        cout << ">> Barang berhasil diperbarui!\n";
    } else {
        cout << ">> Nomor tidak valid!\n";
    }
}

void hapusBarang() {
    tampilkanGudang();
    ifstream fileInput(FILE_GUDANG);
    vector<string> listBarang;
    string baris;
    
    while (getline(fileInput, baris)) {
        if(!baris.empty()) listBarang.push_back(baris);
    }
    fileInput.close();

    if (listBarang.empty()) {
        cout << "Tidak ada barang yang bisa dihapus.\n";
        return;
    }

    int pilihan;
    cout << "Pilih nomor barang yang ingin dihapus: ";
    cin >> pilihan;

    if (pilihan > 0 && pilihan <= listBarang.size()) {
        string barangDihapus = listBarang[pilihan - 1];
        listBarang.erase(listBarang.begin() + (pilihan - 1));

        // Tulis ulang ke file setelah dihapus
        ofstream fileOutput(FILE_GUDANG);
        for (const auto& barang : listBarang) {
            fileOutput << barang << endl;
        }
        fileOutput.close();
        cout << ">> Barang '" << barangDihapus << "' berhasil dihapus dari gudang!\n";
    } else {
        cout << ">> Nomor tidak valid!\n";
    }
}

void jalankanSimulasiEtalase(TokoElektronik& toko) {
    cout << "\n=== SIMULASI EXCEPTION HANDLING ETALASE ===\n";
    
    cout << "[Skenario 1] Mencoba mengambil barang di rak indeks 1...\n";
    try {
        string barang = toko.ambilProduk(1);
        cout << "Hasil: Sukses mengambil -> " << barang << "\n\n";
    } 
    catch (const runtime_error& e) {
        cout << "Hasil: Terjadi error -> " << e.what() << "\n\n";
    }

    cout << "[Skenario 2] Mencoba mengambil barang di rak indeks 5...\n";
    try {
        string barang = toko.ambilProduk(5);
        cout << "Hasil: Sukses mengambil -> " << barang << "\n\n";
    } 
    catch (const runtime_error& e) {
        cout << "Hasil: Terjadi error -> " << e.what() << "\n\n";
    }
    cout << "===========================================\n";
}

int main() {
    TokoElektronik tokoGibran;
    int pilihanMenu;

    do {
        tampilkanGudang();

        cout << "\n=== SISTEM MANAJEMEN TOKO \"GIBRAN JAYA\" ===\n";
        cout << "1. Tambah Barang Gudang (Create)\n";
        cout << "2. Update Barang Gudang (Update)\n";
        cout << "3. Hapus Barang Gudang (Delete)\n";
        cout << "4. Jalankan Simulasi Etalase (Exception Handling)\n";
        cout << "5. Keluar Aplikasi\n";
        cout << "Pilih menu [1-5]: ";
        cin >> pilihanMenu;

        switch (pilihanMenu) {
            case 1:
                tambahBarang();
                break;
            case 2:
                updateBarang();
                break;
            case 3:
                hapusBarang();
                break;
            case 4:
                jalankanSimulasiEtalase(tokoGibran);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan sistem Toko Gibran Jaya!\n";
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
        
        cout << "\n";
        system("pause");
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

    } while (pilihanMenu != 5);

    return 0;
}