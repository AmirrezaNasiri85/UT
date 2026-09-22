#include <cctype>
#include <iostream>
#include <string>

const std::string ENCRYPT = "Encrypt";
const std::string DECRYPT = "Decrypt";
const int ALPHABET_SIZE = 26;
const int MIN_KEY = 1;
const int MAX_KEY = 25;
const char UPPER_BASE = 'A';
const char LOWER_BASE = 'a';

std::string caesarCipher(const std::string& text, int key, const std::string& operation) {
    std::string result = text;
    if (operation == DECRYPT) {
        key = -key;
    }

    for (char& ch : result) {
        if (std::isalpha(ch)) {
            char base = std::isupper(ch) ? UPPER_BASE : LOWER_BASE;
            ch = base + (ch - base + key + ALPHABET_SIZE) % ALPHABET_SIZE;
        }
    }
    return result;
}

int main() {
    std::string text, operation;
    int key;

    std::getline(std::cin, text);
    std::cin >> key >> operation;

    if (key < MIN_KEY || key > MAX_KEY || (operation != ENCRYPT && operation != DECRYPT)) {
        std::cerr << "Invalid input. Key must be between " << MIN_KEY << " and " << MAX_KEY
                  << ", and operation must be " << ENCRYPT << " or " << DECRYPT << "." << std::endl;
        return 1;
    }

    std::string result = caesarCipher(text, key, operation);

    std::cout << result << std::endl;
    return 0;
}
