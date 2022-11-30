#include <iostream>
using std::cout, std::cin, std::endl;
using std::string;

static char vignere_table[26][26];

void init_table()
{
    // generates the vignere table
    for (int i = 0; i < 26; ++i)
    {
        char first = 'a' + i;
        for (int j = 0; j < 26; ++j)
        {
            int val = first + j;
            bool mod = val > 122;

            vignere_table[i][j] = 'a' * mod + val % 123;
        }
    }
}

void message_replace(const string& message, const string& key, string& msg_replace)
{
    // make the exact replacement of message 
    // filled with the letters from the key
    int key_len = key.length();
    int idx = 0;
    for (char ch: message)
    {
        if (!isalpha(ch)) 
        {
            msg_replace += ch;
            continue;
        }

        msg_replace += key[idx];
        idx = (idx + 1) % key_len;
    }
}

void encrypt(const string& message, const string& msg_replace, string& cipher_text)
{
    // for encryption, look at the tile in vignere_table
    // corresponding to col (indexed with respect to message letter)
    // and row (indexed with respect to message replaced with key letters letter)
    for (int i = 0; i < message.length(); ++i)
    {
        if (!isalpha(msg_replace[i]))
        {
            cipher_text += msg_replace[i];
            continue;
        }

        int row = msg_replace[i] - 'a';
        int col = message[i] - 'a';
        cipher_text += vignere_table[row][col];
    }
}

void decrypt(const string& msg_replace, const string& cipher_text, string& plain_text)
{
    // for decryption, look at the row (indexed with respect to message replaced with key letters letter)
    // and search in what position in that row does the letter at cipher text fall.
    // corresponding column index of that position in the original message letter
    for (int i = 0; i < cipher_text.length(); ++i)
    {
        if (!isalpha(cipher_text[i]))
        {
            plain_text += cipher_text[i];
            continue;
        }

        int offset {};
        if (cipher_text[i] < msg_replace[i])
            offset = 'z' - msg_replace[i] + (cipher_text[i] - 'a' + 1);
        else
            offset = cipher_text[i] - msg_replace[i];

        plain_text += 'a' + offset;
    }
}

void print_table()
{
    for (int i = 0; i < 26; ++i)
    {
        for (int j = 0; j < 26; ++j)
            cout << vignere_table[i][j] << " ";
        cout << endl;
    }
}


int main()
{
    string input;
    cout << "Enter your message: \f";
    getline(cin, input);

    string key;
    cout << "\nEnter Key: \f";
    cin >> key;

    init_table();

    string msg_replace {}; 
    message_replace(input, key, msg_replace);
    cout << "\n===================Message replaced with key===================\n" << msg_replace << endl;

    string cipher_text {};
    encrypt(input, msg_replace, cipher_text);
    cout << "\n===================Encrypted Message=================== \n" << cipher_text << endl;

//    printf("\n\n");
//    print_table();

    string plain_text {};
    decrypt(msg_replace, cipher_text, plain_text);
    cout << "\n\tDecryption Sucessful.";
    cout << "\n===================Original message=================== \n" << plain_text << endl;

    return 0;
}
