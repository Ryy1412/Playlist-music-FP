// Playlist Music.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

struct Lagu {
    int id;
    string judul;
    string artis;
};

struct Node {
    Lagu lagu;
    Node* next;
};

class Playlist {
private:
    Node* head;
    Node* tail;
    int ukuran;
    int plays[100];

public:
    Playlist() : head(nullptr), tail(nullptr), ukuran(0) {
        for (int i = 0; i < 100; i++) {
            plays[i] = 0;
        }
    }

    void tambahLagu(int id, string judul, string artis) {
        if (cariLaguByID(id) != nullptr) {
            cout << "Lagu dengan ID " << id << " sudah ada\n";
            return;
        }
        Node* newNode = new Node;
        newNode->lagu.id = id;
        newNode->lagu.judul = judul;
        newNode->lagu.artis = artis;
        newNode->next = nullptr;

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        ukuran++;
    }

    void tampilkanLagu() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->lagu.id << ", Judul: " << temp->lagu.judul << ", Artis: " << temp->lagu.artis << ", Plays: " << plays[temp->lagu.id] << "x" << endl;
            temp = temp->next;
        }
    }

    void perbaruiLagu(int id, string judulBaru, string artisBaru) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->lagu.id == id) {
                temp->lagu.judul = judulBaru;
                temp->lagu.artis = artisBaru;
                plays[id] = 0;
                return;
            }
            temp = temp->next;
        }
        cout << "Lagu dengan ID " << id << " tidak ditemukan." << endl;
    }

    void hapusLagu(int id) {
        Node* temp = head;
        Node* prev = nullptr;

        if (temp != nullptr && temp->lagu.id == id) {
            head = temp->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
            ukuran--;
            cout << "Lagu dengan ID " << id << " Telah dihapus " << endl;
            return;
        } while (temp != nullptr && temp->lagu.id != id) {
            prev = temp;
            temp = temp->next;
        } if (temp == nullptr) {
            cout << "Lagu dengan ID " << id << " tidak ditemukan." << endl;
            return;
        }

        prev->next = temp->next;
        if (prev->next == nullptr) {
            tail = prev;
        }
        delete temp;
        ukuran--;
    }

    Node* cariLaguByID(int id) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->lagu.id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    Node* cariLaguByJudulArtis(string query) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->lagu.judul.find(query) != string::npos || temp->lagu.artis.find(query) != string::npos) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void urutkanLagu() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            Node* prev = nullptr;
            Node* next = nullptr;

            while (current->next != nullptr) {
                next = current->next;

                if (plays[current->lagu.id] < plays[next->lagu.id]) {                   
                    if (prev == nullptr) {
                        head = next;
                    }
                    else {
                        prev->next = next;
                    }
                    current->next = next->next;
                    next->next = current;

                    swapped = true;
                    prev = next;
                }
                else {
                    prev = current;
                    current = next;
                }
            }
            tail = current;
        } while (swapped);
    }

    void tambahPutaran(int id) {
        if (id >= 0 && id < 100) {
            plays[id]++;
        }
        else {
            cout << "ID lagu tidak valid." << endl;
        }
    }

    int getUkuran() {
        return ukuran;
    }

    Node* getHead() {
        return head;
    }

    Node* getTail() {
        return tail;
    }
};

void tampilkanMenu() {
    cout << "\n<+SELAMAT DATANG DI MUSIC+>";
    cout << "\nMenu Pilihan:\n";
    cout << "[1] Tambah lagu\n";
    cout << "[2] Tampilkan lagu\n";
    cout << "[3] Update lagu\n";
    cout << "[4] Hapus lagu\n";
    cout << "[5] Cari lagu\n";
    cout << "[6] Urutkan lagu\n";
    cout << "[7] Masukan play lagu\n";
    cout << "[8] Keluar\n";
    cout << "Masukkan pilihan Anda: ";
}

int main() {
    Playlist playlistSaya;
    int pilihan, id;
    string judul, artis, query;

    while (true) {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            cout << "Masukkan ID Lagu: ";
            cin >> id;
            cout << "Masukkan Judul Lagu: ";
            cin.ignore();
            getline(cin, judul);
            cout << "Masukkan Artis Lagu: ";
            getline(cin, artis);
            playlistSaya.tambahLagu(id, judul, artis);
            break;

        case 2:
            cout << "\nLagu yang ada :\n";
            playlistSaya.tampilkanLagu();
            break;

        case 3:
            cout << "Masukkan ID Lagu untuk diperbarui: ";
            cin >> id;
            cout << "Masukkan Judul Baru: ";
            cin.ignore();
            getline(cin, judul);
            cout << "Masukkan Artis Baru: ";
            getline(cin, artis);
            playlistSaya.perbaruiLagu(id, judul, artis);
            break;

        case 4:
            cout << "Masukkan ID Lagu untuk dihapus: ";
            cin >> id;
            playlistSaya.hapusLagu(id);
            break;

        case 5:
            cout << "Masukkan Judul atau Artis Lagu untuk dicari: ";
            cin.ignore();
            getline(cin, query);
            {

                Node* found = playlistSaya.cariLaguByJudulArtis(query);
                if (found != nullptr) {
                    cout << "Ditemukan Lagu - ID: " << found->lagu.id << ", Judul: " << found->lagu.judul << ", Artis: " << found->lagu.artis << endl;
                }
                else {
                    cout << "Lagu dengan judul atau artis \"" << query << "\" tidak ditemukan." << endl;
                }
            }
            break;

        case 6:
            playlistSaya.urutkanLagu();
            cout << "Lagu sudah diurutkan berdasarkan jumlah plays.\n";
            break;

        case 7:
            cout << "Masukkan ID Lagu untuk menambah putaran: ";
            cin >> id;
            playlistSaya.tambahPutaran(id);
            break;

        case 8:
            cout << "Terima Kasih Sudah Menggunakan Program ini dan Keluar ^^ \n";
            return 0;

        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }

    return 0;
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
