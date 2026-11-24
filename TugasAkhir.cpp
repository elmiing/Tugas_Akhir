#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct DataPengguna {
    string nama;
    int usia;
    int penyakit;
    int batuk;
    int sesak;
    int IritasiMata;
    string wilayah;
    int ispu;

    int SkorUsia;
    int SkorPenyakit;
    int SkorKeluhan;
    int SkorISPU;
    int totalSkor;

    string kategori;
};

string tentukanKategori(int totalSkor){
    if (totalSkor <= 3){
        return "Resiko Rendah";
    }
    else if (totalSkor <= 7){
        return "Resiko Sedang";
    }
    else{
        return "Resiko Tinggi";
    }
}

void tampilkanSaran(string kategori){
    if(kategori == "Resiko Rendah"){
        cout<<"Saran: Pertahankan Pola Hidup yang Sehat"<<"tetap pantau kualitas udara"<<endl;
    } else if(kategori == "Resiko Sedang"){
        cout<<"Saran: Kurangi Aktifitas di Luar Ruangan dan Perhatikan Kondisi Kesehatan"<<endl;
    }
    else{
        cout<<"Saran: Hindari Paparan Asap Segera Cari Bantuan Medis Jika Mengalami Keluhan Berat"<<endl;
}
}


int main() {

    int jumlahPengguna;

    cout<<"========Sistem Penilaian Resiko Kesehatan========"<<endl;
    cout<<"========Akibat Paparan Asap Kebakaran Hutan========"<<endl;

    //input jumlah pengguna yang memasukkan data
    jumlahPengguna = inputAngka(
        "Masukkan Jumlah pengguna (1-10):",1,10
    );

    //Array Dinamis
    DataPengguna* data = new DataPengguna[jumlahPengguna];

    //input data pengguna
    for(int i=0; i < jumlahPengguna; i++){
        cout<<"========Data Pengguna ke-"<<i+1<<"========"<<endl;
        cout<<"Nama: ";
        getline(cin, data[i].nama);
        
        data[i].usia = inputAngka("Usia: ", 0, 200);

        cout<<"\nRiwayat Penyakit:\n";
        cout<<"0. Tidak ada\n";
        cout<<"1. Ada\n";

        data[i].batuk = inputAngka("Apakah Mengalami Batuk? ", 0, 1);
        data[i].sesak = inputAngka("Apakah Mengalami Sesak Napas? ", 0, 1);
        data[i].IritasiMata = inputAngka("Apakah Mengalami Iritasi Mata? ", 0, 1);
        data[i].batuk = inputAngka("Apakah Mengalami Batuk? ", 0, 1);

        cout<<"\n Wilayah Tempat Tinggal: ";
        getline(cin, data[i].wilayah);

        data[i].ispu = inputAngka("Masukkan Nilai ISPU (0-5000):", 0, 5000);

        //Perhitungan Skor

        data[i].SkorUsia = hitungSkorUsia(data[i].usia);
        data[i].SkorPenyakit = hitungSkorPenyakit(data[i].penyakit);
        data[i].SkorKeluhan = hitungSkorKeluhan(data[i].batuk,data[i].sesak,data[i].IritasiMata);
        data[i].SkorISPU = hitungSkorISPU(data[i].ispu);

        //total skor
        data[i].totalSkor = data[i].SkorUsia + data[i].SkorPenyakit + data[i].SkorKeluhan + data[i].SkorISPU;

        data[i].kategori = tentukanKategori(data[i].totalSkor);

        cout<<"\nData Pengguna Berhasil Diproses!"<<endl;
    }
    //Menampilkan hasil pemeriksaan
    cout<<"\n========Hasil Pemeriksaan========"<<endl;

    for(int i=0; i<jumlahPengguna; i++){

        cout<<"\n========Data Pengguna ke-"<<i+1<<"========"<<endl;
        cout<<"Nama: "<<data[i].nama<<endl;
        cout<<"Usia: "<<data[i].usia<<endl;
        cout<<"Wilayah Tempat Tinggal: "<<data[i].wilayah<<endl;
        cout<<"Nilai ISPU: "<<data[i].ispu<<endl;
        //rincian skor
        cout<<"\nSkor Usia: "<<data[i].SkorUsia<<endl;
        cout<<"Skor Riwayat Penyakit: "<<data[i].SkorPenyakit<<endl;
        cout<<"Skor Keluhan: "<<data[i].SkorKeluhan<<endl;
        cout<<"Skor ISPU: "<<data[i].SkorISPU<<endl;

        cout<<"\nTotal Skor: "<<data[i].totalSkor<<endl;
        cout<<"Kategori Resiko Kesehatan: "<<data[i].kategori<<endl;

        tampilkanSaran(data[i].kategori);
    }
        //hapus array dinamis
        delete[] data;

        cout<<"\n========================================"<<endl;
        cout<<"Seluruh Pengecekan Telah Selesai"<<endl;
        cout<<"\n========================================"<<endl;

        return 0;
    

}