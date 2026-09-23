#include <iostream>
#include <string>

using namespace std;

string encrypt(string text, int k) {
    string result = text;
    for (int i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = (result[i] - 'A' + k) % 26 + 'A';
        else if (result[i] >= 'a' && result[i] <= 'z')
            result[i] = (result[i] - 'a' + k) % 26 + 'a';
    }
    return result;
}

string decrypt(string text, int k) {
    string result = text;
    for (int i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = (result[i] - 'A' - k + 26) % 26 + 'A';
        else if (result[i] >= 'a' && result[i] <= 'z')
            result[i] = (result[i] - 'a' - k + 26) % 26 + 'a';
    }
    return result;
}

int main() {
    int choice, k;
    string text;
    
    cout << "1. Ma hoa (Encrypt)\n2. Giai ma (Decrypt)\nChon chuc nang (1 hoac 2): ";
    cin >> choice;
    
    cout << "Nhap khoa k (tu 1 den 25): ";
    cin >> k;
    
    cin.ignore(); 
    cout << "Nhap chuoi van ban: ";
    getline(cin, text);
    
    if (choice == 1) {
        cout << "Ma hoa : " << encrypt(text, k) << endl;
    } else if (choice == 2) {
        cout << "Giai ma: " << decrypt(text, k) << endl;
    }
    
    return 0;
}