#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<unsigned long long>> getInput() {
    std::vector<std::vector<unsigned long long>> ret;
    std::ifstream f("in.txt");
    std::string str;
    // Parsing is my greatest enemy I swear
    while(std::getline(f, str)) {
        std::vector<unsigned long long> miniret;
        int x1 = str.find('x');
        int x2 = str.find('x', x1+1);
        miniret.push_back(std::stoi(str.substr(0, x1)));
        miniret.push_back(std::stoi(str.substr(x1+1, x2-x1-1)));
        miniret.push_back(std::stoi(str.substr(x2+1)));
        ret.push_back(miniret);
    }
    f.close();
    return ret;
}

void solve(const std::vector<std::vector<unsigned long long>> in) {
    unsigned long long wrap = 0;
    unsigned long long ribbon = 0;

    for(auto arr : in) {
        unsigned long long length = arr[0];
        unsigned long long width = arr[1];
        unsigned long long height = arr[2];

        unsigned long long area1 = length*width;
        unsigned long long area2 = length*height;
        unsigned long long area3 = width*height;

        unsigned long long volume = length*width*height;
        unsigned long long perimeter = 0;

        short selectedArea = 1;
        unsigned long long smallestArea = area1;

        if(smallestArea > area2) {
            smallestArea = area2;
            selectedArea = 2;
        }

        if(smallestArea > area3) {
            smallestArea = area3;
            selectedArea = 3;
        }

        switch(selectedArea) {
            case 1: perimeter = 2*length + 2*width; break;
            case 2: perimeter = 2*length + 2*height; break;
            case 3: perimeter = 2*width + 2*height; break;
            default: std::cout << "What?" << '\n'; break;
        }

        wrap += 2*(area1 + area2 + area3) + smallestArea;
        ribbon += volume + perimeter;
    }
    std::cout << "Silver: " << wrap << '\n';
    std::cout << "Gold: " << ribbon << '\n';
}

int main() {
    solve(getInput());
    return 0;
}
