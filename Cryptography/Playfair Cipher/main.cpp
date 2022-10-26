#include <iostream>
#include <algorithm>
using std::cout, std::cin, std::endl;
using std::string;

#define MAX 5
static char matrix[MAX][MAX];
static int row = 0, col = 0;
static char filler_letter = 'x';

inline void fill_tile(char ch)
{
    matrix[row][col] = ch;

    col++;
    if (col == MAX)
    {
        row++;
        col = 0;
    }
}

bool search_char(char ch)
{
    int x = 0;
    int y = 0;

    while (y <= row)
    {
        if (matrix[y][x] == ch)
            return true;

        x++;
        if (x == MAX) 
        {
            y++;
            x = 0;
        }

        if (y == row and x > col) break;
    }
    
    return false;
}

void init_matrix(const string& key)
{
    row = 0;
    col = 0;

    // first fill the matrix with the
    // non-repeating letters in key
    for (int i = 0; i < key.length(); ++i)
    {
        int pos = key.find_first_of(key[i]);

        if (pos == i)
            fill_tile(key[i]);
    }

    // fill the other letter from alphabet
    // letter 'z' has be left out intensionally
    for (char i = 0; i < 25; ++i)
    {
        if (!search_char('a' + i))
            fill_tile('a' + i);
    }
}

void print_matrix()
{
    cout << endl;
    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; ++j)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

string clean_str(const string& message)
{
    // this function cleans the string 
    // removes characters which are not letters [a-zA-Z]
    string temp{};
    for (char ch: message)
        if (isalpha(ch)) temp += ch;

    return temp;
}

void generate_digram(const string& message, string& digram)
{
    int i;
    for (i = 1; i < message.length(); i += 2)
    {
        char first = message[i-1];
        char second = message[i];

        // if both letters are same, use filler letter
        // and only advance pointer by +1
        if (first == second)
        {
            digram += first;
            digram += filler_letter;
            i--;
            continue;
        }

        // if both letters are different,
        // make pair and advnce pointer by +2
        digram += first;
        digram += second;
    }

    // if a letter is left behind,
    // pair it up with filler letter
    if (i == message.length())
    {
        digram += message.back();
        digram += filler_letter;
    }
}

struct position
{
    int x;
    int y;
};

position find_pos(char ch)
{
    int x = 0;
    int y = 0;

    while (y < MAX and x < MAX)
    {
        if (ch == matrix[y][x]) break;

        x++;
        if (x == MAX)
        {
            y++;
            x = 0;
        }
    }

    return {x, y};
}

inline int round_pos(int pos)
{
    return pos < 0 ? MAX + pos : pos >= MAX ? pos % MAX : pos;
}

void encrypt(const string& digram, const string& key, string& cipher)
{
    for (int i = 0; i < digram.length(); i += 2)
    {
        position pos1 = find_pos(digram[i]);
        position pos2 = find_pos(digram[i + 1]);

        // for digram in same row
        if (pos1.y == pos2.y)
        {
            cipher += matrix[pos1.y][round_pos(pos1.x + 1)];
            cipher += matrix[pos2.y][round_pos(pos2.x + 1)];
            continue;
        }

        // for digram in same col
        if (pos1.x == pos2.x)
        {
            cipher += matrix[round_pos(pos1.y + 1)][pos1.x];
            cipher += matrix[round_pos(pos2.y + 1)][pos2.x];
            continue;
        }

        // when digram forms rectangle
        cipher += matrix[pos1.y][pos2.x];
        cipher += matrix[pos2.y][pos1.x];
    }
}

void decrypt(const string& cipher, const string& key, string& plaintext)
{
    for (int i = 0; i < cipher.length(); i += 2)
    {
        position pos1 = find_pos(cipher[i]);
        position pos2 = find_pos(cipher[i + 1]);

        // same row
        if (pos1.y == pos2.y)
        {
            plaintext += matrix[pos1.y][round_pos(pos1.x - 1)];
            plaintext += matrix[pos2.y][round_pos(pos2.x - 1)];
            continue;
        }

        // same column
        if (pos1.x == pos2.x)
        {
            plaintext += matrix[round_pos(pos1.y - 1)][pos1.x];
            plaintext += matrix[round_pos(pos2.y - 1)][pos2.x];
            continue;
        }

        // rectangle formed
        plaintext += matrix[pos1.y][pos2.x];
        plaintext += matrix[pos2.y][pos1.x];
    }
}

int main()
{
    string text{};
    getline(cin, text);

    string key{};
    cin >> key;

    string message = clean_str(text);
    cout << "\n================text cleaned=============== \n" << message << endl;

    init_matrix(key);
    print_matrix();

    string digram{};
    generate_digram(message, digram);
    cout << "\n===============digram generated=============== \n" << digram << endl;

    string cipher{};
    encrypt(digram, key, cipher);
    cout << "\n===============encryption sucessfull=============== \n" << cipher << endl;

    string plaintext{};
    decrypt(cipher, key, plaintext);
    cout << "\n===============decryption sucessfull=============== \n" << plaintext << endl;

    return 0;
}
