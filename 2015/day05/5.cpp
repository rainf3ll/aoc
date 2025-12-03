#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> getInput() {
    std::vector<std::string> ret;
    std::ifstream f("in.txt");
    std::string line;

    while(std::getline(f, line)) {
        ret.push_back(line);
    }

    f.close();
    return ret;
}

unsigned long long silver(const std::vector<std::string> in) {
    std::vector<std::string> illegal = {"xy", "ab", "cd", "pq"};
    std::string vowels = "aeiou";
    unsigned long long niceStringCounter = 0;

    for(auto line : in) {
        bool foundIllegal = false;
        bool foundDoubleLetter = false;
        char lastChar = '\0';
        unsigned long long vowelCount = 0;

        for(auto str : illegal) {
            if(line.find(str) != std::string::npos) {
                foundIllegal = true;
                break;
            }
        }

        if(foundIllegal) {
            continue;
        }

        for(auto c : line) {
            if(vowels.find(c) != std::string::npos) {
                vowelCount++;
            }

            if(lastChar == c) {
                foundDoubleLetter = true;
            }

            lastChar = c;
        }

        if(foundDoubleLetter && vowelCount >= 3) {
            niceStringCounter++;
        }
    }

    return niceStringCounter;
}

unsigned long long gold(const std::vector<std::string> in) {
    unsigned long long niceStringCounter = 0;

    for(auto line : in) {
        char lastToggledChar = 1;
        char lastUntoggledChar = 2;
        bool toggle = true; // We use this to toggle between the two chars above.
        bool hasTwoIdentCharsSeparatedByOneChar = false;
        bool hasASeparatedPairOfLetters = false;

        for(auto c = line.begin(); c != line.end(); c++) {
            toggle = !toggle;

            if(toggle) {
                if(lastToggledChar == *c) {
                    hasTwoIdentCharsSeparatedByOneChar = true;
                }

                lastToggledChar = *c;
            } else {
                if(lastUntoggledChar == *c) {
                    hasTwoIdentCharsSeparatedByOneChar = true;
                }

                lastUntoggledChar = *c;
            }

            if(c != line.end()-1) {
                std::size_t index = c - line.begin();
                std::string key = std::string(1, *c) + *(c+1);
                // PRAISE BE! THE SCHNITZEL GUIDES ME TO A SOLUTION!
                if(line.find(key, index+2) != std::string::npos) {
                    hasASeparatedPairOfLetters = true;
                }
            }

        }

        if(hasTwoIdentCharsSeparatedByOneChar && hasASeparatedPairOfLetters) {
            niceStringCounter++;
        }
    }

    return niceStringCounter;
}

int main() {
    std::vector<std::string> input = getInput();
    std::cout << "Silver: " << silver(input) << '\n';
    std::cout << "Gold: " << gold(input) << '\n';
    return 0;
}
