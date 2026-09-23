#include <iostream>
#include <string>

using namespace std;

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
    string ciphertext;
    
    cout << "Nhap doan ciphertext can giai ma: ";
    getline(cin, ciphertext);
    
    cout << "\nKET QUA BRUTE-FORCE" << endl;
    for (int k = 1; k <= 25; k++) {
        cout << "Khoa k = " << k << ": " << decrypt(ciphertext, k) << endl;
    }
    
    return 0;
}
