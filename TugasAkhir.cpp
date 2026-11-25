#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Fitur 6: Pengelolaan data pengguna menggunakan struct
struct DataPengguna {
    string nama;
    int usia;
    int penyakit;
    int batuk;
    int sesak;
    int iritasiMata;
    int sakitTenggorokan; // Perbaikan: variabel terpisah agar tidak menimpa 'batuk'
    int gejalaBerat;      // Penanda kondisi darurat (Fitur 3 & 11)
    string wilayah;
    int ispu;
    int skorUsia;
    int skorPenyakit;
    int skorKeluhan;
    int skorISPU;
    int totalSkor;
    string kategori;
    bool statusDarurat;
};

// =========================================================================
// FITUR 15: Validasi Input Numerik (Menolak huruf & angka di luar rentang)
// =========================================================================
int inputAngka(string pesan, int minVal, int maxVal) {
    int nilai;
    bool valid = false;

    do {
        cout << pesan;
        cin >> nilai;

        if (cin.fail()) {
            // Jika user memasukkan huruf/simbol
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[Error] Input harus berupa angka! Silakan coba lagi.\n";
        } else if (nilai < minVal || nilai > maxVal) {
            // Jika angka di luar batas minVal - maxVal
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[Error] Pilihan harus di antara " << minVal << " sampai " << maxVal << "!\n";
        } else {
            // Input valid, bersihkan sisa newline di buffer agar getline() aman
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            valid = true;
        }
    } while (!valid);

    return nilai;
}

// =========================================================================
// FUNGSI BANTU & FITUR 7 - 10 (Perhitungan Skor per Faktor)
// =========================================================================
string namaPenyakit(int penyakit) {
    if (penyakit == 1) return "Asma";
    else if (penyakit == 2) return "Penyakit jantung";
    else if (penyakit == 3) return "Penyakit paru kronis";
    else return "Tidak ada";
}

// Fitur 7: Perhitungan skor usia
int hitungSkorUsia(int usia) {
    if (usia < 5 || usia >= 60) {
        return 2; // Kelompok rentan (balita & lansia)
    } else if (usia <= 17) {
        return 1; // Anak & remaja
    } else {
        return 0; // Usia produktif
    }
}

// Fitur 8: Perhitungan skor riwayat penyakit
int hitungSkorPenyakit(int penyakit) {
    if (penyakit == 0) {
        return 0; // Tidak ada riwayat
    } else if (penyakit == 1) {
        return 2; // Asma
    } else {
        return 3; // Penyakit jantung atau paru kronis
    }
}

// Fitur 9: Perhitungan skor keluhan (mengambil skor tertinggi, tidak dihitung ganda)
int hitungSkorKeluhan(int batuk, int sesak, int iritasiMata, int sakitTenggorokan, int gejalaBerat) {
    int skorTertinggi = 0;

    if (batuk == 1 && 1 > skorTertinggi) skorTertinggi = 1;
    if (iritasiMata == 1 && 1 > skorTertinggi) skorTertinggi = 1;
    if (sakitTenggorokan == 1 && 1 > skorTertinggi) skorTertinggi = 1;
    if (sesak == 1 && 2 > skorTertinggi) skorTertinggi = 2;
    if (gejalaBerat == 1 && 3 > skorTertinggi) skorTertinggi = 3;

    return skorTertinggi;
}

// Fitur 10: Perhitungan skor kualitas udara (ISPU)
int hitungSkorISPU(int ispu) {
    if (ispu <= 50) {
        return 0; // Baik
    } else if (ispu <= 100) {
        return 1; // Sedang
    } else if (ispu <= 200) {
        return 2; // Tidak Sehat
    } else if (ispu <= 300) {
        return 3; // Sangat Tidak Sehat
    } else {
        return 4; // Berbahaya (> 300)
    }
}

// =========================================================================
// FITUR 11: Penentuan Kategori Risiko (Memisahkan Aturan Darurat)
// =========================================================================
string tentukanKategori(int totalSkor, int ispu, bool statusDarurat) {
    if (statusDarurat) {
        return "DARURAT MEDIS (Risiko Sangat Tinggi)";
    } else if (ispu > 300 || totalSkor > 7) {
        return "Risiko Tinggi";
    } else if (totalSkor >= 4) {
        return "Risiko Sedang";
    } else {
        return "Risiko Rendah";
    }
}

// =========================================================================
// FITUR 12: Pemberian Saran Sesuai Kategori & Penanda Darurat
// =========================================================================
void tampilkanSaran(string kategori, bool statusDarurat) {
    cout << "Saran Edukatif : ";
    if (statusDarurat) {
        cout << "[PERINGATAN DARURAT] Gejala berat terdeteksi! Segera hentikan aktivitas, "
             << "evakuasi ke ruangan bersih udara, dan segera cari pertolongan medis/IGD terdekat." << endl;
    } else if (kategori == "Risiko Rendah") {
        cout << "Pertahankan pola hidup sehat, perbanyak minum air putih, dan tetap pantau perkembangan kualitas udara." << endl;
    } else if (kategori == "Risiko Sedang") {
        cout << "Kurangi aktivitas berat di luar ruangan, gunakan masker standar (minimal N95/KN95) saat keluar, dan pantau kondisi tubuh." << endl;
    } else {
        cout << "Hindari paparan asap secara langsung, tutup ventilasi ruangan, gunakan penjernih udara jika ada, dan segera konsultasi ke fasilitas kesehatan." << endl;
    }
}

// =========================================================================
// FITUR 14: Menampilkan Hasil Pemeriksaan per Pengguna
// =========================================================================
void tampilkanHasilPemeriksaan(DataPengguna p, int nomor) {
    cout << "\n======== Data Pengguna ke-" << nomor << " ========" << endl;
    cout << "Nama                    : " << p.nama << endl;
    cout << "Usia                    : " << p.usia << " tahun" << endl;
    cout << "Wilayah Tempat Tinggal  : " << p.wilayah << endl;
    cout << "Riwayat Penyakit        : " << namaPenyakit(p.penyakit) << endl;
    cout << "Nilai ISPU              : " << p.ispu << endl;

    cout << "\n--- Rincian Skor ---" << endl;
    cout << "Skor Usia               : " << p.skorUsia << endl;
    cout << "Skor Riwayat Penyakit   : " << p.skorPenyakit << endl;
    cout << "Skor Keluhan            : " << p.skorKeluhan << endl;
    cout << "Skor ISPU               : " << p.skorISPU << endl;

    cout << "\nTotal Skor              : " << p.totalSkor << endl;
    cout << "Status Darurat          : " << (p.statusDarurat ? "YA (Gejala Berat Terdeteksi)" : "Tidak") << endl;
    cout << "Kategori Risiko         : " << p.kategori << endl;

    tampilkanSaran(p.kategori, p.statusDarurat);
}

// =========================================================================
// PROGRAM UTAMA (Mengintegrasikan Fitur 1 - 15)
// =========================================================================
int main() {
    int jumlahPengguna;

    cout << "======== Sistem Penilaian Risiko Kesehatan ========" << endl;
    cout << "======== Akibat Paparan Asap Kebakaran Hutan =======" << endl;

    // Fitur 13 & 15: Input jumlah pengguna dengan validasi
    jumlahPengguna = inputAngka("\nMasukkan Jumlah Pengguna (1-10): ", 1, 10);

    // Array dinamis untuk menampung banyak pengguna
    DataPengguna* data = new DataPengguna[jumlahPengguna];

    // Fitur 13: Perulangan pemeriksaan untuk setiap pengguna
    for (int i = 0; i < jumlahPengguna; i++) {
        cout << "\n======== Input Data Pengguna ke-" << i + 1 << " ========" << endl;

        // Fitur 1: Identitas pengguna
        cout << "Nama: ";
        getline(cin, data[i].nama);

        data[i].usia = inputAngka("Usia (0-200): ", 0, 200);

        // Fitur 2: Riwayat penyakit
        cout << "\nRiwayat Penyakit:" << endl;
        cout << "0. Tidak ada" << endl;
        cout << "1. Asma" << endl;
        cout << "2. Penyakit jantung" << endl;
        cout << "3. Penyakit paru kronis" << endl;
        data[i].penyakit = inputAngka("Pilihan (0-3): ", 0, 3);

        // Fitur 3: Keluhan kesehatan & gejala darurat
        cout << "\nKeluhan yang Dialami (0 = Tidak ada, 1 = Ada):" << endl;
        data[i].batuk            = inputAngka("1. Apakah mengalami Batuk? (0/1)                  : ", 0, 1);
        data[i].iritasiMata      = inputAngka("2. Apakah mengalami Iritasi Mata? (0/1)           : ", 0, 1);
        data[i].sakitTenggorokan = inputAngka("3. Apakah mengalami Sakit Tenggorokan? (0/1)      : ", 0, 1);
        data[i].sesak            = inputAngka("4. Apakah mengalami Mengi / Sesak Napas? (0/1)    : ", 0, 1);
        data[i].gejalaBerat      = inputAngka("5. Apakah mengalami Gejala Berat / Nyeri Dada / Pingsan? (0/1): ", 0, 1);

        // Fitur 4: Wilayah
        cout << "\nWilayah Tempat Tinggal: ";
        getline(cin, data[i].wilayah);

        // Fitur 5: Kualitas udara (ISPU)
        data[i].ispu = inputAngka("Masukkan Nilai ISPU (0-5000): ", 0, 5000);

        // Fitur 7 - 10: Perhitungan skor tiap faktor
        data[i].skorUsia     = hitungSkorUsia(data[i].usia);
        data[i].skorPenyakit = hitungSkorPenyakit(data[i].penyakit);
        data[i].skorKeluhan  = hitungSkorKeluhan(
            data[i].batuk,
            data[i].sesak,
            data[i].iritasiMata,
            data[i].sakitTenggorokan,
            data[i].gejalaBerat
        );
        data[i].skorISPU     = hitungSkorISPU(data[i].ispu);

        // Fitur 11: Penjumlahan skor & penentuan kategori risiko + penanda darurat
        data[i].totalSkor     = data[i].skorUsia + data[i].skorPenyakit + data[i].skorKeluhan + data[i].skorISPU;
        data[i].statusDarurat = (data[i].gejalaBerat == 1);
        data[i].kategori      = tentukanKategori(data[i].totalSkor, data[i].ispu, data[i].statusDarurat);

        cout << "\n-> Data Pengguna ke-" << i + 1 << " Berhasil Diproses!" << endl;
    }

    // Fitur 13 & 14: Menampilkan hasil pemeriksaan seluruh pengguna
    cout << "\n================ HASIL PEMERIKSAAN ================" << endl;
    for (int i = 0; i < jumlahPengguna; i++) {
        tampilkanHasilPemeriksaan(data[i], i + 1);
    }

    // Membersihkan memori array dinamis
    delete[] data;

    cout << "\n===================================================" << endl;
    cout << "          Seluruh Pengecekan Telah Selesai         " << endl;
    cout << "===================================================" << endl;

    return 0;
}