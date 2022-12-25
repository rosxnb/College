/* 
   the input is expected to be already filtered, that is no spaces, all small case letters and only chars from a - z.
*/

#include <iostream>
#include <vector>

using std::cout, std::cin, std::endl;
using std::string;
using vc = std::vector<char>;
using vvc = std::vector<vc>;


/*
   the plaintext is written downwards on successive "rails" moving down and up until text is exhaused.
   then the cipher text is constructed by moving along horizontally and store the formed result.
*/
void encrypt(const string message, int key, string& cipher_text)
{
    int len = message.length();
    vvc rails(key, vc(len, 0));
    int idx {0}, row {0}, col {0};
    bool go_down {false};

    while (idx != len)
    {
        if (row == 0 or row == key - 1)
            go_down = !go_down;

        rails[row][col++] = message[idx++];
        go_down ? row++ : row--;
    }

    cipher_text.clear();
    for (const auto& rail: rails)
        for (char ch: rail)
            if (ch) cipher_text.push_back(ch);

    return;
}


void decrypt(const string cipher_text, int key, string& plain_text)
{
    int len = cipher_text.length();
    vvc rails(key, vc(len, 0));
    int idx {0}, row {0}, col {0};
    bool go_down {false};

    // we basically are placing a mark so later we can re-fill the rails with cipher text
    // characters in same manner we used for creating the cipher text in first place
    while (idx++ != len)
    {
        if (row == 0 or row == key - 1)
            go_down = !go_down;

        rails[row][col++] = '$';
        go_down ? row++ : row--;
    }

    // here is that re-filling parts
    idx = 0;
    for (int r = 0; r < key; ++r)
        for (int c = 0; c < len; ++c)
            if (rails[r][c] == '$')
                rails[r][c] = cipher_text[idx++];

    // now we pick up the original message by going down, up, down, ...
    plain_text.resize(len);
    idx = row = col = 0;
    go_down = false;
    while (idx++ != len)
    {
        if (row == 0 or row == key - 1)
            go_down = !go_down;

        plain_text.push_back(rails[row][col++]);
        go_down ? row++ : row--;
    }

    return;
}

int main()
{
    string message; cin >> message;
    int key; cin >> key;

    string cipher_text;
    encrypt(message, key, cipher_text);
    cout << cipher_text << endl;

    string plain_text;
    decrypt(cipher_text, key, plain_text);
    cout << plain_text << endl;

    return 0;
}
