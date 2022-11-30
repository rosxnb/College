#include <iostream>
using std::cin, std::cout, std::endl;
using std::string;

string clean_str(const string& message)
{
    // removes characters which are not letter from set [a-zA-Z]
    string temp{};
    for (char ch: message)
        if (isalpha(ch)) temp += ch;

    return temp;
}

void encrypt(const string& message, const int32_t key, string& cipher)
{
    char first_letter = 'a';
    char last_letter = 'z';

    // to encrypt, add key to each character
    // if the result of addition fall outside the range
    // make it wrap around the valid range
    for(char ch: message)
    {
        ch += key;
        if (ch > last_letter)
            ch = ch % (last_letter + 1) + first_letter;

        cipher += ch;
    }
}

void decrypt(const string& cipher, const int32_t key, string& plaintext)
{
    char first_letter = 'a';
    char last_letter = 'z';

    // subtract letter in cipher text with key
    // is out of range, wrap it to make it bound in valid range
    for(char ch: cipher)
    {
        ch -= key;
        if (ch < first_letter)
        {
            int mod = first_letter - ch - 1;
            ch = last_letter - mod;
        }

        plaintext += ch;
    }
}

int main()
{
    string text;
    getline(cin, text);

    int32_t key;
    cin >> key;

    string message = clean_str(text);
    cout << "\n===================text cleaned================== \n" << message << endl;

    string cipher{};
    encrypt(message, key, cipher);
    cout << "\n==================cipher generated================== \n" << cipher << endl;

    string plaintext{};
    decrypt(cipher, key, plaintext);
    cout << "\n==================cipher decrypted================== \n" << plaintext << endl;

    cout << std::boolalpha << "\nmessage retrived correctly? \f" << (message == plaintext) << endl;
    return 0;
}
