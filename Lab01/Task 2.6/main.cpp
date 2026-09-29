#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <algorithm>

// Bảng tần suất ký tự tiếng Anh chuẩn (%) theo Mayzner
const double ENG_FREQ[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

// Tính Index of Coincidence (IC) cho một chuỗi ký tự
double compute_ic(const std::string& text) {
    if (text.length() <= 1) return 0.0;
    std::vector<int> counts(26, 0);
    for (char c : text) counts[c - 'A']++;

    double num = 0.0;
    for (int i = 0; i < 26; ++i) {
        num += counts[i] * (counts[i] - 1);
    }
    double den = (double)text.length() * (text.length() - 1);
    return num / den;
}

// Tính IC trung bình cho một độ dài khóa key_len
double average_ic_for_key_length(const std::string& text, int key_len) {
    double total_ic = 0.0;
    for (int i = 0; i < key_len; ++i) {
        std::string slice = "";
        for (size_t j = i; j < text.length(); j += key_len) {
            slice += text[j];
        }
        total_ic += compute_ic(slice);
    }
    return total_ic / key_len;
}

// Tìm độ dài khóa có IC trung bình tốt nhất
int find_key_length(const std::string& text, int max_len = 16) {
    int best_len = 1;
    double min_diff = 1e9;

    std::cout << "\n--- PHAN TICH INDEX OF COINCIDENCE (IC) THEO DO DAI KHOA ---\n";
    std::cout << std::left << std::setw(12) << "Key Length" 
              << std::setw(16) << "Average IC" 
              << "Do chenh lech voi tieng Anh (0.0667)\n";
    std::cout << std::string(65, '-') << "\n";

    for (int len = 1; len <= max_len; ++len) {
        double avg_ic = average_ic_for_key_length(text, len);
        double diff = std::abs(avg_ic - 0.0667);
        std::cout << std::left << std::setw(12) << len 
                  << std::fixed << std::setprecision(5) << std::setw(16) << avg_ic 
                  << diff << "\n";

        if (avg_ic > 0.058 && diff < min_diff) {
            min_diff = diff;
            best_len = len;
        }
    }
    return best_len;
}

// Tìm chữ cái của khóa cho một lát cắt bằng kiểm định Chi-Square
char find_key_char(const std::string& slice) {
    int n = slice.length();
    if (n == 0) return 'A';

    double min_chi2 = 1e9;
    int best_shift = 0;

    for (int shift = 0; shift < 26; ++shift) {
        std::vector<int> counts(26, 0);
        for (char c : slice) {
            int decrypted = (c - 'A' - shift + 26) % 26;
            counts[decrypted]++;
        }

        double chi2 = 0.0;
        for (int i = 0; i < 26; ++i) {
            double observed = counts[i];
            double expected = n * (ENG_FREQ[i] / 100.0);
            chi2 += std::pow(observed - expected, 2) / expected;
        }

        if (chi2 < min_chi2) {
            min_chi2 = chi2;
            best_shift = shift;
        }
    }
    return 'A' + best_shift;
}

int main() {
    std::ifstream file("ciphertext.txt");
    if (!file.is_open()) {
        std::cerr << "Loi: Khong the mo tap tin ciphertext.txt\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string raw_cipher = buffer.str();

    // 1. Chuẩn hóa bản mã
    std::string clean_cipher = "";
    for (char c : raw_cipher) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            clean_cipher += std::toupper(static_cast<unsigned char>(c));
        }
    }

    std::cout << "[+] Tong so ky tu chu cai trong ciphertext: " << clean_cipher.length() << "\n";

    // 2. Tìm độ dài khóa
    int key_len = find_key_length(clean_cipher, 15);
    std::cout << "\n[+] Do dai khoa du doan co kha nang nhat: " << key_len << "\n";

    // 3. Tìm từng ký tự của khóa
    std::string key = "";
    for (int i = 0; i < key_len; ++i) {
        std::string slice = "";
        for (size_t j = i; j < clean_cipher.length(); j += key_len) {
            slice += clean_cipher[j];
        }
        key += find_key_char(slice);
    }
    std::cout << "[+] Khoa tim duoc: " << key << "\n";

    // 4. Giải mã và giữ nguyên cấu trúc văn bản gốc
    std::string plaintext = raw_cipher;
    int key_idx = 0;
    for (size_t i = 0; i < raw_cipher.length(); ++i) {
        char c = raw_cipher[i];
        if (std::isalpha(static_cast<unsigned char>(c))) {
            bool is_lower = std::islower(static_cast<unsigned char>(c));
            char base = is_lower ? 'a' : 'A';
            int shift = std::toupper(key[key_idx % key_len]) - 'A';
            char dec = (c - base - shift + 26) % 26 + base;
            plaintext[i] = dec;
            key_idx++;
        }
    }

    std::cout << "\n--- BAN RO (PLAINTEXT) TIM DUOC ---\n\n";
    std::cout << plaintext << "\n";
    std::cout << "\n------------------------------------\n";

    return 0;
}