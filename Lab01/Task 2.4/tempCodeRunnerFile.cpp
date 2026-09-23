#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const string ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
string normalizeKey(string key)
{
    string result = "";

    for (char ch : key)
    {
        ch = toupper(ch);
        if (ch == ' ')
            continue;

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z')
        {
            bool existed = false;
            for (char x : result)
            {
                if (x == ch)
                {
                    existed = true;
                    break;
                }
            }

            if (!existed)
                result += ch;
        }
    }

    return result;
}

void createMatrix(string key, char matrix[5][5])
{
    string keyPart = normalizeKey(key);

    string fullKey = keyPart;
    for (char ch : ALPHABET)
    {
        bool existed = false;

        for (char x : fullKey)
        {
            if (x == ch)
            {
                existed = true;
                break;
            }
        }

        if (!existed)
            fullKey += ch;
    }
    int index = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matrix[i][j] = fullKey[index++];
        }
    }
}

void printMatrix(char matrix[5][5])
{
    cout << "\n===== PLAYFAIR MATRIX =====\n";

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }
}

void findPosition(
    char matrix[5][5],
    char ch,
    int &row,
    int &col
)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string preparePlaintext(string text)
{
    string clean = "";
    for (char ch : text)
    {
        ch = toupper(ch);

        if (ch == ' ')
            continue;

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z')
            clean += ch;
    }

    string result = "";

    int i = 0;

    while (i < clean.length())
    {
        char first = clean[i];
        if (i + 1 >= clean.length())
        {
            result += first;
            result += 'X';
            i++;
        }
        else
        {
            char second = clean[i + 1];
            if (first == second)
            {
                result += first;
                result += 'X';

                i++;
            }
            else
            {
                result += first;
                result += second;

                i += 2;
            }
        }
    }

    return result;
}
string encryptPair(
    char a,
    char b,
    char matrix[5][5]
)
{
    int row1, col1;
    int row2, col2;

    findPosition(matrix, a, row1, col1);
    findPosition(matrix, b, row2, col2);

    string result = "";
    if (row1 == row2)
    {
        char newA = matrix[row1][(col1 + 1) % 5];
        char newB = matrix[row2][(col2 + 1) % 5];

        result += newA;
        result += newB;
    }
    else if (col1 == col2)
    {
        char newA = matrix[(row1 + 1) % 5][col1];
        char newB = matrix[(row2 + 1) % 5][col2];

        result += newA;
        result += newB;
    }
    else
    {
        char newA = matrix[row1][col2];
        char newB = matrix[row2][col1];

        result += newA;
        result += newB;
    }

    return result;
}

string encrypt(
    string plaintext,
    char matrix[5][5]
)
{
    string prepared = preparePlaintext(plaintext);

    string ciphertext = "";

    for (int i = 0; i < prepared.length(); i += 2)
    {
        char a = prepared[i];
        char b = prepared[i + 1];

        ciphertext += encryptPair(a, b, matrix);
    }

    return ciphertext;
}

string decryptPair(
    char a,
    char b,
    char matrix[5][5]
)
{
    int row1, col1;
    int row2, col2;

    findPosition(matrix, a, row1, col1);
    findPosition(matrix, b, row2, col2);

    string result = "";
    if (row1 == row2)
    {
        char newA = matrix[row1][(col1 - 1 + 5) % 5];
        char newB = matrix[row2][(col2 - 1 + 5) % 5];

        result += newA;
        result += newB;
    }
    else if (col1 == col2)
    {
        char newA = matrix[(row1 - 1 + 5) % 5][col1];
        char newB = matrix[(row2 - 1 + 5) % 5][col2];

        result += newA;
        result += newB;
    }
    else
    {
        char newA = matrix[row1][col2];
        char newB = matrix[row2][col1];

        result += newA;
        result += newB;
    }

    return result;
}

string decrypt(
    string ciphertext,
    char matrix[5][5]
)
{
    string clean = "";

    for (char ch : ciphertext)
    {
        ch = toupper(ch);

        if (ch == ' ')
            continue;

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z')
            clean += ch;
    }

    string plaintext = "";

    for (int i = 0; i < clean.length(); i += 2)
    {
        char a = clean[i];
        char b = clean[i + 1];

        plaintext += decryptPair(a, b, matrix);
    }

    return plaintext;
}

int main()
{
    char matrix[5][5];

    cout << "=====================================\n";
    cout << "       PLAYFAIR CIPHER - C++\n";
    cout << "=====================================\n";
    string key;

    cout << "\nEnter key: ";
    getline(cin, key);
    createMatrix(key, matrix);
    printMatrix(matrix);

    int choice;

    do
    {
        cout << "\n========== MENU ==========\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            string plaintext;

            cout << "\nEnter plaintext: ";
            getline(cin, plaintext);

            string prepared = preparePlaintext(plaintext);

            cout << "\nPrepared plaintext: ";
            cout << prepared << endl;

            string ciphertext = encrypt(plaintext, matrix);

            cout << "Ciphertext: ";
            cout << ciphertext << endl;
        }
        else if (choice == 2)
        {
            string ciphertext;

            cout << "\nEnter ciphertext: ";
            getline(cin, ciphertext);

            string plaintext = decrypt(ciphertext, matrix);

            cout << "\nPlaintext: ";
            cout << plaintext << endl;
        }
        else if (choice == 3)
        {
            cout << "\nProgram finished.\n";
        }

        else
        {
            cout << "\nInvalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}