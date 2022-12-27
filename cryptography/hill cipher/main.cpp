/*
   This program is has following limitations
    - it only works for 2x2 key matrx hence the key length must equal to 4
    - it doesn't check for whether the key matrix can be invertable or not
    - it doesn't handle any exceptions such as divided_by_zero exception
*/

#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl;
using std::string, std::vector;

// converts each character to its respective ascii value
vector<int> generate_key(const string& kstr)
{
    vector<int> res;
    for (char ch: kstr)
        res.push_back(ch - 'a');

    return res;
}

// simple vector-matrix multiplication
// vector ha order (1, 2)   --  block of size 2 since key matrix is 2x2
void generate_cipher(string& plaintext, const vector<int>& key, string& ciphertext)
{
    ciphertext.clear();
    int n = plaintext.length();

    // if length is not even make it even
    // because we will be making blocks of size 2
    // for matrix-vector multiplication and dimensions must match for that
    if (n % 2 != 0)
        plaintext.push_back('x');   // 'x' is the filler-letter

    vector<int> numeric_cipher;     // stores the ascii value for corresponding character
    for (int i = 0; i < n; i += 2)
    {
        int first = plaintext[i] - 'a';
        int second = plaintext[i+1] - 'a';

        // vector * matrix
        // (1, 2) * (2, 2)
        int f = first * key[0] + second * key[2];
        int s = first * key[1] + second * key[3];

        numeric_cipher.push_back(f % 26);
        numeric_cipher.push_back(s % 26);
    }

    // convert ascii code to corresponding character then store as ciphertext
    for (int code: numeric_cipher)
        ciphertext += static_cast<char>(code + 'a');
}

int determinant(const vector<int>& key)
{
    int val = key[0] * key[3] - key[1] * key[2];

    // c++ modulo operator doesn't work as expected for negative value
    // hence some extra work if the value is negative
    if (val < 0)
        val = 26 - (val * -1 % 26);

    return val % 26;
}

vector<int> adjoint(vector<int> key)
{
    std::swap(key[0], key[3]);
    key[1] *= -1;
    key[2] *= -1;
    return key;
}

// calculate modular multiplicative inverse of a modulo m
// using Extended Eulidean Algorithm
int find_multiplicative_inv(int a, int m)
{
    int mod = m;
    int x = 0;
    int y = 1;
    
    while (a > 1)
    {
        int q = a / m;
        int t = m;
      
        m = a % m;
        a = t;
        t = x;
      
        x = y - q * x;
        y = t;
    }
    
    // if negative, make it positive
    if (y < 0)
      y += mod;
    
    return y;
}

vector<int> calculate_inverse(const vector<int>& key)
{
    auto det = determinant(key);

    // since we are doing modular arithmetic in cryptography
    // we cannot use the floating point value resulting from 1/det
    // hence we rather use the modular multiplicative inverse of det
    // that is det * y = 1 (mod 26)
    auto modulo_multiplicative_inv = find_multiplicative_inv(det, 26);
    vector<int> adj = adjoint(key);

    for (int& num: adj)
    {
        int temp = num * modulo_multiplicative_inv;

        // c++ modulo operator doesn't work as expected for negative value
        // hence some extra work if the value is negative
        if (temp < 0)
            temp = 26 - (temp * -1 % 26);

        num = temp % 26;
    }

    return adj;
}

void decrypt_cipher(string& ciphertext, const vector<int>& key, string& plaintext)
{
    plaintext.clear();
    int n = ciphertext.length();

    vector<int> key_inv = calculate_inverse(key);
    vector<int> numeric_value;
    
    for (int i = 0; i < n; i += 2)
    {
        int first = ciphertext[i] - 'a';
        int second = ciphertext[i+1] - 'a';

        int f = first * key_inv[0] + second * key_inv[2];
        int s = first * key_inv[1] + second * key_inv[3];

        numeric_value.push_back(f % 26);
        numeric_value.push_back(s % 26);
    }

    for (int num: numeric_value)
        plaintext += static_cast<char>('a' + num);
}

int main()
{
    string message; 
    cout << "Enter message to encrypt: "; cin >> message;

    string key_str; 
    cout << "Enter key string: "; cin >> key_str;

    vector<int> key = generate_key(key_str);

    string ciphertext;
    generate_cipher(message, key, ciphertext);
    cout << "\nGenerated cipher text: \n\t" << ciphertext << endl;

    string plaintext;
    decrypt_cipher(ciphertext, key, plaintext);
    cout << "\nCipher text has been decrypted: \n\t" << plaintext << endl;

    return 0;
}
