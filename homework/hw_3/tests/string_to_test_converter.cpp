#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <climits>


int main() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<std::mt19937::result_type> rand_num(-50, 50);

    std::string randomchars = " !#%&*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz'{|}~";
    std::shuffle(randomchars.begin(), randomchars.end(), g);

    std::vector<int> rand_numbers(30000);
    std::iota(rand_numbers.begin(), rand_numbers.end(), -15000);
    std::shuffle(rand_numbers.begin(), rand_numbers.end(), g);


    std::string str;
    getline(std::cin, str);
    std::cout << str << std::endl;

    std::vector<bool> v(500, false);
    std::string unique_chars;
    for (auto c : str) {
        //std::cout << (int)c << std::endl;
        if (not v[c]) {
            v[c] = true;
            unique_chars.push_back(c);
        }
    }

    std::shuffle(unique_chars.begin(), unique_chars.end(), g);

    // -------------------------- charReplaceEncryption
    randomchars = randomchars.substr(0, unique_chars.size());

    std::string charencrypted_str;
    for (auto c : str) {
        charencrypted_str.push_back(randomchars[unique_chars.find(c)]);
    }

    std::cout << "charReplaceEncryption " << str.size()
              << ' ' << unique_chars.size()
              << ' ' << unique_chars << randomchars
              << ' ' << charencrypted_str << std::endl;


    // -------------------------- intReplaceEncryption
    rand_numbers.resize(unique_chars.size());

    std::vector<int> intencrypted_str;
    for (auto c : str) {
        intencrypted_str.push_back(rand_numbers[unique_chars.find(c)]);
    }

    std::cout << "intReplaceEncryption " << str.size()
              << ' ' << unique_chars.size()
              << ' ' << unique_chars << ' ';


    for (auto i : rand_numbers) {
        std::cout << i << ' ';
    }
    for (auto i : intencrypted_str) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    // -------------------------- cycleEncryption
    int shift = (static_cast<int>(rand_num(g)) % 100) - 50;

    std::string cycleencrypted_str;
    for (auto c : str) {
        cycleencrypted_str.push_back(
            static_cast<char>((static_cast<int>(c) + (CHAR_MAX + 1) + shift) % (CHAR_MAX + 1))
        );
    }

    std::cout << "cycleEncryption " << str.size()
              << ' ' << shift
              << ' ' << cycleencrypted_str;
    return 0;
}
