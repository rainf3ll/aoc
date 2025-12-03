#include <iostream>
#include <unordered_map> // You can easily use an unordered_set instead. I used map in case I needed to get the highest count of visits (I didn't).
#include <string>
#include <fstream>

std::string getInput() {
    std::ifstream f("in.txt");
    std::string ret;
    if(!std::getline(f, ret)) {
        std::cout << "hero...\n";
    }
    f.close();
    return ret;
}

long long silver(const std::string in) {
    std::unordered_map<std::string, unsigned long long> grid;
    grid["0,0"]++;

    long long x = 0;
    long long y = 0;

    for(auto c : in) {
        switch(c) {
            case 'v': y++; break;
            case '^': y--; break;
            case '>': x++; break;
            case '<': x--; break;
            default: std::cout << "Invalid input???\n"; break;
        }

        std::string key = std::to_string(x) + "," + std::to_string(y);
        grid[key]++;
    }

    return grid.size();
}

long long gold(const std::string in) {
    std::unordered_map<std::string, unsigned long long> grid;
    grid["0,0"] = 2;

    long long santaX = 0;
    long long santaY = 0;
    long long secondSecretSantaX = 0;
    long long secondSecretSantaY = 0;

    bool turn = true; // Whether it is Second Secret Santa's turn.
    for(auto it = in.begin(); it != in.end(); ++it) {
        turn = !turn; // This is quite possibly the second most horrifying thing I have written ever.

        switch(*it) {
            case 'v': turn ? secondSecretSantaY++ : santaY++; break;
            case '^': turn ? secondSecretSantaY-- : santaY--; break;
            case '>': turn ? secondSecretSantaX++ : santaX++; break;
            case '<': turn ? secondSecretSantaX-- : santaX--; break;
            default: std::cout << "Invalid input???\n"; break;
        }

        std::string key;
        turn 
            ? key = std::to_string(secondSecretSantaX) + "," + std::to_string(secondSecretSantaY) 
            : key = std::to_string(santaX) + "," + std::to_string(santaY);
        grid[key]++;
    }

    return grid.size();
}

int main() {
    std::string input = getInput();
    std::cout << "Silver: " << silver(input) << '\n';
    std::cout << "Gold: " << gold(input) << '\n';
    return 0;
}
