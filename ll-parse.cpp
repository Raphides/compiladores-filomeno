#include <iostream>
#include <string>
#include <cctype>
#include <map>

class LL1Parser {
public:
    LL1Parser(const std::string& input) : input(input), index(0) {}

    void parse() {
        parseE();
        if (index == input.size()) {
            std::cout << "Parsing successful.\n";
        } else {
            std::cout << "Parsing failed. Remaining input: " << input.substr(index) << "\n";
        }
    }

private:
    std::string input;
    size_t index;

    void parseE() {
        parseT();
        parseEPrime();
    }

    void parseEPrime() {
        if (index < input.size() && input[index] == '+') {
            index++;
            parseT();
            parseEPrime();
        }
    }

    void parseT() {
        if (index < input.size() && input[index] == 'i' && index + 1 < input.size() && input[index + 1] == 'd') {
            index += 2;
            parseTPrime();
        } else {
            std::cout << "Parsing error: expected 'id'\n";
        }
    }

    void parseTPrime() {
        if (index < input.size() && input[index] == '*') {
            index++;
            if (index + 1 < input.size() && input[index] == 'i' && input[index + 1] == 'd') {
                index += 2;
                parseTPrime();
            } else {
                std::cout << "Parsing error: expected 'id'\n";
            }
        }
    }
};

int main() {
    std::string input = "id+id*id";
    LL1Parser parser(input);
    parser.parse();
    return 0;
}
