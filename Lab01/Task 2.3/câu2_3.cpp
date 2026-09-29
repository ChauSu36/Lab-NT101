#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <utility>

using namespace std;

const double ENGLISH_FREQ[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702,
    2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507,
    1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974,
    0.074
};

const string COMMON_BIGRAMS[] = {
    "TH", "HE", "IN", "ER", "AN",
    "RE", "ON", "AT", "EN", "ND",
    "TI", "ES", "OR", "TE", "OF",
    "ED", "IS", "IT", "AL", "AR",
    "ST", "TO", "NT", "NG", "SE",
    "HA", "AS", "OU", "IO", "LE",
    "VE", "CO", "ME", "DE", "HI",
    "RI", "RO", "IC", "NE", "EA",
    "RA", "CE", "LI", "CH", "LL",
    "BE", "MA", "SI", "OM", "UR"
};

const int BIGRAM_COUNT = 50;

const string COMMON_TRIGRAMS[] = {
    "THE", "AND", "ING", "HER", "ERE",
    "ENT", "THA", "NTH", "WAS", "ETH",
    "FOR", "DTH", "HAT", "SHE", "ION",
    "TIO", "VER", "EST", "ERS", "ATI",
    "HIS", "ALL", "ITH", "TER", "CON",
    "THI", "YOU", "ARE", "NOT", "BUT",
    "HAD", "HEN", "OFT", "STH", "OTH",
    "RES", "REA", "ONE", "OUR", "OUT",
    "EVE", "WHO", "WIT", "FRO"
};

const int TRIGRAM_COUNT = 44;

const string COMMON_WORDS[] = {
    "THE", "OF", "AND", "TO", "IN",
    "IS", "YOU", "THAT", "IT", "HE",
    "WAS", "FOR", "ON", "ARE", "AS",
    "WITH", "HIS", "THEY", "I", "AT",
    "BE", "THIS", "HAVE", "FROM", "OR",
    "ONE", "HAD", "BY", "WORD", "BUT",
    "NOT", "WHAT", "ALL", "WERE", "WE",
    "WHEN", "YOUR", "CAN", "SAID", "THERE",
    "USE", "AN", "EACH", "WHICH", "SHE",
    "DO", "HOW", "THEIR", "IF", "WILL",
    "UP", "OTHER", "ABOUT", "OUT", "MANY",
    "THEN", "THEM", "THESE", "SO", "SOME",
    "HER", "WOULD", "MAKE", "LIKE", "HIM",
    "INTO", "TIME", "HAS", "LOOK", "TWO",
    "MORE", "WRITE", "GO", "SEE", "NUMBER",
    "NO", "WAY", "COULD", "PEOPLE", "MY",
    "THAN", "FIRST", "WATER", "BEEN", "CALL",
    "WHO", "OIL", "ITS", "NOW", "FIND",
    "LONG", "DOWN", "DAY", "DID", "GET",
    "COME", "MADE", "MAY", "PART"
};

const int COMMON_WORD_COUNT = 100;

string normalizeText(const string& input)
{
    string result = "";

    for (size_t i = 0; i < input.length(); i++)
    {
        unsigned char c = input[i];

        if (isalpha(c))
        {
            result += (char)toupper(c);
        }
        else
        {
            result += input[i];
        }
    }

    return result;
}

string decryptText(const string& ciphertext,
                   const vector<char>& key)
{
    string plaintext = ciphertext;

    for (size_t i = 0; i < ciphertext.length(); i++)
    {
        char c = ciphertext[i];

        if (c >= 'A' && c <= 'Z')
        {
            plaintext[i] = key[c - 'A'];
        }
        else
        {
            plaintext[i] = c;
        }
    }

    return plaintext;
}

double unigramScore(const string& text)
{
    int count[26] = {0};
    int total = 0;

    for (size_t i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (c >= 'A' && c <= 'Z')
        {
            count[c - 'A']++;
            total++;
        }
    }

    if (total == 0)
    {
        return -1000000000.0;
    }

    double chiSquare = 0.0;

    for (int i = 0; i < 26; i++)
    {
        double expected =
            total * ENGLISH_FREQ[i] / 100.0;

        if (expected > 0)
        {
            double difference =
                count[i] - expected;

            chiSquare +=
                (difference * difference) / expected;
        }
    }
    return -chiSquare;
}

double bigramScore(const string& text)
{
    double score = 0.0;

    for (size_t i = 0; i + 1 < text.length(); i++)
    {
        char c1 = text[i];
        char c2 = text[i + 1];

        if (c1 >= 'A' && c1 <= 'Z' &&
            c2 >= 'A' && c2 <= 'Z')
        {
            string bigram = "";
            bigram += c1;
            bigram += c2;

            for (int j = 0; j < BIGRAM_COUNT; j++)
            {
                if (bigram == COMMON_BIGRAMS[j])
                {
                    score +=
                        (double)(BIGRAM_COUNT - j);

                    break;
                }
            }
        }
    }

    return score;
}

double trigramScore(const string& text)
{
    double score = 0.0;

    for (size_t i = 0; i + 2 < text.length(); i++)
    {
        char c1 = text[i];
        char c2 = text[i + 1];
        char c3 = text[i + 2];

        if (c1 >= 'A' && c1 <= 'Z' &&
            c2 >= 'A' && c2 <= 'Z' &&
            c3 >= 'A' && c3 <= 'Z')
        {
            string trigram = "";

            trigram += c1;
            trigram += c2;
            trigram += c3;

            for (int j = 0; j < TRIGRAM_COUNT; j++)
            {
                if (trigram == COMMON_TRIGRAMS[j])
                {
                    score +=
                        (double)(TRIGRAM_COUNT - j) * 2.0;

                    break;
                }
            }
        }
    }

    return score;
}

double wordScore(const string& text)
{
    double score = 0.0;

    string word = "";

    for (size_t i = 0; i <= text.length(); i++)
    {
        if (i < text.length() &&
            text[i] >= 'A' &&
            text[i] <= 'Z')
        {
            word += text[i];
        }
        else
        {
            if (!word.empty())
            {
                for (int j = 0;
                     j < COMMON_WORD_COUNT;
                     j++)
                {
                    if (word == COMMON_WORDS[j])
                    {
                        score +=
                            20.0 +
                            word.length() * 5.0;

                        break;
                    }
                }

                word = "";
            }
        }
    }

    return score;
}

double scoreText(const string& text)
{
    double score = 0.0;

    score += unigramScore(text) * 0.8;
    score += bigramScore(text) * 0.05;
    score += trigramScore(text) * 0.10;
    score += wordScore(text);

    return score;
}

vector<char> randomKey(mt19937& rng)
{
    vector<char> key;

    for (char c = 'A'; c <= 'Z'; c++)
    {
        key.push_back(c);
    }

    shuffle(key.begin(), key.end(), rng);

    return key;
}

vector<char> mutateKey(const vector<char>& key,
                       mt19937& rng)
{
    vector<char> newKey = key;

    uniform_int_distribution<int> dist(0, 25);

    int a = dist(rng);
    int b = dist(rng);

    while (a == b)
    {
        b = dist(rng);
    }

    swap(newKey[a], newKey[b]);

    return newKey;
}

pair<vector<char>, double>
hillClimbing(const string& ciphertext,
             vector<char> key,
             mt19937& rng)
{
    string plaintext =
        decryptText(ciphertext, key);

    double currentScore =
        scoreText(plaintext);

    double bestScore =
        currentScore;

    vector<char> bestKey =
        key;

    uniform_real_distribution<double>
        probability(0.0, 1.0);

    double temperature = 20.0;

    const int MAX_ITERATIONS = 15000;

    for (int iteration = 0;
         iteration < MAX_ITERATIONS;
         iteration++)
    {
        vector<char> newKey =
            mutateKey(key, rng);

        string newPlaintext =
            decryptText(ciphertext, newKey);

        double newScore =
            scoreText(newPlaintext);

        double difference =
            newScore - currentScore;

        bool accept = false;
        if (difference > 0)
        {
            accept = true;
        }
        else
        {
            double probabilityValue =
                exp(difference / temperature);

            if (probability(rng) <
                probabilityValue)
            {
                accept = true;
            }
        }

        if (accept)
        {
            key = newKey;
            currentScore = newScore;
        }
        if (currentScore > bestScore)
        {
            bestScore = currentScore;
            bestKey = key;
        }
        temperature *= 0.9995;

        if (temperature < 0.05)
        {
            temperature = 0.05;
        }
    }

    return make_pair(bestKey, bestScore);
}

bool readFromFile(const string& filename,
                  string& text)
{
    ifstream file(filename.c_str());

    if (!file)
    {
        return false;
    }

    string line;

    while (getline(file, line))
    {
        text += line;
        text += '\n';
    }

    file.close();

    return true;
}

void printKey(const vector<char>& key)
{
    cout << "\nKey tim duoc:\n\n";

    cout << "Cipher : ";

    for (char c = 'A'; c <= 'Z'; c++)
    {
        cout << c << ' ';
    }

    cout << "\n";

    cout << "Plain  : ";

    for (size_t i = 0; i < key.size(); i++)
    {
        cout << key[i] << ' ';
    }

    cout << "\n";
}

int main()
{
    cout << "=============================================\n";
    cout << " TASK 2.3 - GIAI MA MONO-ALPHABETIC CIPHER\n";
    cout << "=============================================\n";

    cout << "\nChon cach nhap ciphertext:\n";
    cout << "1. Nhap truc tiep\n";
    cout << "2. Doc tu file\n";
    cout << "Lua chon: ";

    int choice;
    cin >> choice;

    cin.ignore(10000, '\n');

    string ciphertext = "";
    if (choice == 1)
    {
        cout << "\nNhap ciphertext:\n";
        getline(cin, ciphertext);
    }
    else if (choice == 2)
    {
        string filename;

        cout << "\nNhap ten file: ";
        getline(cin, filename);

        if (!readFromFile(filename, ciphertext))
        {
            cout << "\nLOI: Khong the mo file!\n";
            return 1;
        }
    }

    else
    {
        cout << "\nLOI: Lua chon khong hop le!\n";
        return 1;
    }
    if (ciphertext.empty())
    {
        cout << "\nLOI: Ciphertext rong!\n";
        return 1;
    }
    ciphertext =
        normalizeText(ciphertext);

    cout << "\n=============================================\n";
    cout << "CIPHERTEXT SAU KHI CHUAN HOA\n";
    cout << "=============================================\n";

    cout << ciphertext << "\n";
    random_device rd;
    mt19937 rng(rd());
    const int RESTARTS = 30;

    vector<char> globalBestKey;

    double globalBestScore =
        -1000000000000.0;

    cout << "\n=============================================\n";
    cout << "BAT DAU QUA TRINH TIM KIEM\n";
    cout << "=============================================\n";

    cout << "So lan Random Restart: "
         << RESTARTS << "\n";

    for (int restart = 0;
         restart < RESTARTS;
         restart++)
    {
        vector<char> initialKey =
            randomKey(rng);

        pair<vector<char>, double> result =
            hillClimbing(
                ciphertext,
                initialKey,
                rng
            );

        cout << "Restart "
             << setw(2)
             << restart + 1
             << "/"
             << RESTARTS
             << " -> Score = "
             << fixed
             << setprecision(2)
             << result.second;

        if (result.second >
            globalBestScore)
        {
            globalBestScore =
                result.second;

            globalBestKey =
                result.first;

            cout << "  <-- BEST";
        }

        cout << "\n";
    }

    string bestPlaintext =
        decryptText(
            ciphertext,
            globalBestKey
        );

    cout << "\n\n=============================================\n";
    cout << "              KET QUA GIAI MA\n";
    cout << "=============================================\n";

    printKey(globalBestKey);

    cout << "\nScore tot nhat: "
         << fixed
         << setprecision(2)
         << globalBestScore
         << "\n";

    cout << "\nPlaintext tot nhat tim duoc:\n";
    cout << "---------------------------------------------\n";
    cout << bestPlaintext << "\n";
    cout << "---------------------------------------------\n";
    cout << "\nPhuong phap da su dung:\n";
    cout << "1. Chuan hoa ciphertext\n";
    cout << "2. Phan tich tan suat unigram\n";
    cout << "3. Danh gia bigram\n";
    cout << "4. Danh gia trigram\n";
    cout << "5. Kiem tra tu tieng Anh pho bien\n";
    cout << "6. Hill Climbing\n";
    cout << "7. Simulated Annealing\n";
    cout << "8. Random Restart\n";

    cout << "\n=============================================\n";
    cout << "             HOAN THANH TASK 2.3\n";
    cout << "=============================================\n";

    return 0;
}