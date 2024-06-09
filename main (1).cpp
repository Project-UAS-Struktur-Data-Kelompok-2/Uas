#include <iostream>
using namespace std;

void menu();
void header();
void bersih();

// Semua fungsi untuk pilihan switch case
void tambahProduk();
void tampilProduk();
void editProduk();
void hapusProduk();
void initQueue();
bool isQueueEmpty();
bool isQueueFull();
void enqueue();
void transaksi();

const int MAX_PRODUK = 100;
struct produk {
    string namaProduk;
    int harga;
};
produk daftarProduk[MAX_PRODUK];
int jumlahProduk = 0;

int main() {
    do {
        bersih();
        header();
        menu();
    } while (true);

    return 0;
}

void header() {
    cout << " \t\t\t Point of Sale\n\t\t     SUPERMARKET KElOMPOK 2\n";
    cout << "==============================================================\n";
}

void bersih() {
#ifdef _WIN32
    system("cls");  // For Windows
#else
    system("clear");  // For Unix-like systems
#endif
}

void menu() {
    bersih();
    header();
    int pilih;
    cout << "||                      MENU UTAMA                          ||\n";
    cout << "==============================================================\n";
    cout << "[1] Tambah Produk \n";
    cout << "[2] Lihat Semua Produk \n";
    cout << "[3] Cari & Edit Produk \n";
    cout << "[4] Hapus Produk\n";
    cout << "[5] Lakukan Transaksi\n";
    cout << "[6] Keluar\n";

    cout << "Pilih Menu: ";
    cin >> pilih;

    switch (pilih) {
        case 1:
            tambahProduk();
            break;
        case 2:
            tampilProduk();
            break;
        case 3:
            editProduk();
            break;
        case 4:
            hapusProduk();
            break;
        case 5:
            transaksi();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout << "Pilihan tidak valid! Coba lagi.\n";
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            break;
    }
}

void tambahProduk() {

    bersih();
    header();

    cout << "||                     TAMBAH PRODUK                        ||\n";
    cout << "==============================================================\n";

    if (jumlahProduk >= MAX_PRODUK) {
        cout << "Kapasitas produk penuh!\n";
        return;
    }

    produk p;
    cout << "Masukkan nama produk\t: ";
    cin.ignore();
    getline(cin, p.namaProduk);
    cout << "Masukkan harga produk\t: ";
    cin >> p.harga;

    daftarProduk[jumlahProduk++] = p;
    cout << "\nProduk berhasil ditambahkan!\n";

    cout << "Tekan ENTER untuk kembali ke menu utama." << endl;
    cin.ignore();
    cin.get();
}

void tampilProduk() {

    bersih();
    header();

    cout << "||                      SEMUA PRODUK                        ||\n";
    cout << "==============================================================\n";

    if (jumlahProduk == 0) {
        cout << "Tidak ada produk yang tersedia.\n";
    } else {
        cout << "Daftar Produk:\n";
        for (int i = 0; i < jumlahProduk; ++i) {
            cout << i + 1 << ". " << daftarProduk[i].namaProduk << " - Harga: " << daftarProduk[i].harga << "\n";

        }
    }

    cout << "Tekan ENTER untuk kembali ke menu utama." << endl;
    cin.ignore();
    cin.get();
}

void editProduk() {
    bersih();
    header();

    cout << "||                       EDIT PRODUK                        ||\n";
    cout << "==============================================================\n";

    if (jumlahProduk == 0) {
        cout << "Tidak ada produk yang tersedia.\n";
        cout << "Tekan ENTER untuk kembali ke menu utama." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    int indeks;
    cout << "Masukkan nomor produk yang ingin diedit: ";
    cin >> indeks;

    if (indeks > 0 && indeks <= jumlahProduk) {
        cout << "Masukkan nama produk baru: ";
        cin.ignore();
        getline(cin, daftarProduk[indeks - 1].namaProduk);
        cout << "Masukkan harga produk baru: ";
        cin >> daftarProduk[indeks - 1].harga;

        cout << "\nProduk berhasil diupdate!\n";
    } else {
        cout << "\nProduk tidak ditemukan.\n";
    }

    cout << "Tekan ENTER untuk kembali ke menu utama." << endl;
    cin.ignore();
    cin.get();
}

void hapusProduk() {
    bersih();
    header();

    cout << "||                       HAPUS PRODUK                        ||\n";
    cout << "==============================================================\n";

    if (jumlahProduk == 0) {
        cout << "Tidak ada produk yang tersedia.\n";
        cout << "Tekan ENTER untuk kembali ke menu utama." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    int indeks;
    cout << "Masukkan nomor produk yang ingin dihapus: ";
    cin >> indeks;

    if (indeks > 0 && indeks <= jumlahProduk) {
        for (int i = indeks - 1; i < jumlahProduk - 1; ++i) {
            daftarProduk[i] = daftarProduk[i + 1];
        }
        --jumlahProduk;
        cout << "\nProduk berhasil dihapus!\n";
    } else {
        cout << "\nProduk tidak ditemukan.\n";
    }

    cout << "Tekan ENTER untuk kembali ke menu utama." << endl;
    cin.ignore();
    cin.get();
}


const int MAX_QUEUE = 100;
struct Queue {
    produk data[MAX_QUEUE];
    int front;
    int rear;
    int count;
};

void initQueue(Queue &q) {
    q.front = 0;
    q.rear = -1;
    q.count = 0;
}

bool isQueueEmpty(Queue &q) {
    return q.count == 0;
}

bool isQueueFull(Queue &q) {
    return q.count == MAX_QUEUE;
}

void enqueue(Queue &q, produk p) {
    if (!isQueueFull(q)) {
        q.rear = (q.rear + 1) % MAX_QUEUE;
        q.data[q.rear] = p;
        q.count++;
    }
}

produk dequeue(Queue &q) {
    produk p = {"", 0};
    if (!isQueueEmpty(q)) {
        p = q.data[q.front];
        q.front = (q.front + 1) % MAX_QUEUE;
        q.count--;
    }
    return p;
}

void transaksi() {
    bersih();
    header();

    cout << "||                     TRANSAKSI BELANJA                    ||\n";
    cout << "==============================================================\n";

    if (jumlahProduk == 0) {
        cout << "Tidak ada produk yang tersedia.\n";
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
        return;
    }

    // Menampilkan semua produk yang tersedia tanpa memanggil fungsi tampilProduk
    cout << "Daftar Produk:\n";
    for (int i = 0; i < jumlahProduk; ++i) {
        cout << i + 1 << ". " << daftarProduk[i].namaProduk << " - Harga: " << daftarProduk[i].harga << "\n";
    }

    int total = 0;
    char beliLagi;
    Queue keranjang;
    initQueue(keranjang);  // Inisialisasi queue

    do {
        int indeks;
        int jumlah;
        cout << "\nMasukkan nomor produk yang ingin dibeli: ";
        cin >> indeks;

        if (indeks > 0 && indeks <= jumlahProduk) {
            cout << "Masukkan jumlah produk yang ingin dibeli: ";
            cin >> jumlah;

            // Menambahkan produk ke dalam keranjang
            for (int j = 0; j < jumlah; ++j) {
                enqueue(keranjang, daftarProduk[indeks - 1]);
            }

            total += daftarProduk[indeks - 1].harga * jumlah;
            cout << "Produk " << daftarProduk[indeks - 1].namaProduk << " sebanyak " << jumlah << " dengan total harga " << daftarProduk[indeks - 1].harga * jumlah << " ditambahkan ke keranjang.\n";
        } else {
            cout << "Produk tidak ditemukan. Silakan masukkan nomor produk yang valid.\n";
        }

        cout << "Ingin beli produk lain? (y/n): ";
        cin >> beliLagi;
    } while (beliLagi == 'y' || beliLagi == 'Y');

    cout << "\nProduk yang Anda beli:\n";
    while (!isQueueEmpty(keranjang)) {
        produk p = dequeue(keranjang);
        cout << p.namaProduk << " - Harga: " << p.harga << "\n";
    }

    cout << "\nTotal belanjaan: " << total << "\n";
    cout << "Terima kasih telah berbelanja di SUPERMARKET KELOMPOK 2!\n";
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}
