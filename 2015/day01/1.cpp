#include <iostream>
#include <string>
#include <fstream>

std::string getInput() {
    std::ifstream f("in.txt");
    std::string ret;
    if(!std::getline(f, ret)) {
        std::cout << "forgot something?\n";
    }
    f.close();
    return ret;
}

void solve(const std::string in) {
    long long floor = 0;
    long long position = 1;
    bool triggered = false;
    for(char c : in) {
        c == ')' ? --floor : ++floor;
        if(!triggered && floor == -1) {
            triggered = true;
            std::cout << "Gold: " << position << '\n';
        } else {
            ++position;
        }
    }
    std::cout << "Silver: " << floor << '\n';
}

int main() {
    solve(getInput());
    return 0;
}
