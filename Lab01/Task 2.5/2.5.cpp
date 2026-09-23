#include <iostream>
#include <string>
#include <cctype> 

using namespace std;

string encrypt(string text, string key) {
    string result = text;
    int j = 0;
    int m = key.length();
    
    for (int i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            int k_val = toupper(key[j % m]) - 'A';
            result[i] = (result[i] - 'A' + k_val) % 26 + 'A';
            j++;
        }
        else if (result[i] >= 'a' && result[i] <= 'z') {
            int k_val = toupper(key[j % m]) - 'A';
            result[i] = (result[i] - 'a' + k_val) % 26 + 'a';
            j++;
        }
    }
    return result;
}

string decrypt(string text, string key) {
    string result = text;
    int j = 0;
    int m = key.length();
    
    for (int i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            int k_val = toupper(key[j % m]) - 'A';
            result[i] = (result[i] - 'A' - k_val + 26) % 26 + 'A';
            j++;
        }
        else if (result[i] >= 'a' && result[i] <= 'z') {
            int k_val = toupper(key[j % m]) - 'A';
            result[i] = (result[i] - 'a' - k_val + 26) % 26 + 'a';
            j++;
        }
    }
    return result;
}

int main() {
    int choice;
    string text, key;
    
    cout << "1. Ma hoa (Encrypt)\n2. Giai ma (Decrypt)\nChon chuc nang (1 hoac 2): ";
    cin >> choice;
    
    cout << "Nhap tu khoa (vd: KEY): ";
    cin >> key;
    
    cin.ignore(); 
    cout << "Nhap chuoi van ban: ";
    getline(cin, text);
    
    if (choice == 1) {
        cout << "Ma hoa : " << encrypt(text, key) << endl;
    } else if (choice == 2) {
        cout << "Giai ma: " << decrypt(text, key) << endl;
    }
    
    return 0;
}