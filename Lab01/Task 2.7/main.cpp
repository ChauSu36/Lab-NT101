#include <iostream>
#include <string>
#include <numeric>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m = 26) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

string encryptAffine(const string& plaintext, int a, int b) {
    string ciphertext = "";
    for (char ch : plaintext) {
        if (isupper(ch)) {
            ciphertext += (char)(((a * (ch - 'A') + b) % 26 + 26) % 26 + 'A');
        } else if (islower(ch)) {
            ciphertext += (char)(((a * (ch - 'a') + b) % 26 + 26) % 26 + 'a');
        } else {
            ciphertext += ch;
        }
    }
    return ciphertext;
}

string decryptAffine(const string& ciphertext, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) return "Loi: Khoa a khong hop le!";

    string plaintext = "";
    for (char ch : ciphertext) {
        if (isupper(ch)) {
            plaintext += (char)(((a_inv * (ch - 'A' - b)) % 26 + 26) % 26 + 'A');
        } else if (islower(ch)) {
            plaintext += (char)(((a_inv * (ch - 'a' - b)) % 26 + 26) % 26 + 'a');
        } else {
            plaintext += ch;
        }
    }
    return plaintext;
}

int main() {
    int choice, a, b;
    string text;

    cout << "===============================================\n";
    cout << "   CHUONG TRINH MAT MA AFFINE (TASK 2.7) - C++ \n";
    cout << "===============================================\n";

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Ma hoa van ban\n";
        cout << "2. Giai ma van ban\n";
        cout << "3. Thoat\n";
        cout << "Nhap lua chon (1/2/3): ";
        if (!(cin >> choice)) break;

        if (choice == 3) {
            cout << "Tam biet!\n";
            break;
        }

        if (choice != 1 && choice != 2) {
            cout << "Lua chon khong hop le!\n";
            continue;
        }

        cout << "Nhap khoa a (gcd(a, 26) = 1): ";
        cin >> a;
        if (gcd(a, 26) != 1) {
            cout << "Loi: a = " << a << " khong hop le. Chon a thuoc {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25}.\n";
            continue;
        }

        cout << "Nhap khoa b (0 <= b < 26): ";
        cin >> b;
        cin.ignore();

        if (choice == 1) {
            cout << "Nhap ban ro (Plaintext): ";
            getline(cin, text);
            cout << "\n--> Ban ma (Ciphertext): " << encryptAffine(text, a, b) << "\n";
        } else {
            cout << "Nhap ban ma (Ciphertext): ";
            getline(cin, text);
            cout << "\n--> Ban ro phuc hoi: " << decryptAffine(text, a, b) << "\n";
        }
    }
    return 0;
}