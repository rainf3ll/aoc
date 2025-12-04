#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> getData(std::string filename) {
    std::vector<std::string> data;
    std::ifstream f(filename);
    std::string whatever;
    while(std::getline(f, whatever)) {
        data.push_back(whatever);
    }
    f.close();
    return data;
}

unsigned int solve1(std::vector<std::string>& data) {
    unsigned int result = 0;

    for(int y = 0; y < data.size(); y++) {
        for(int x = 0; x < data.size(); x++) {
            if(data[y][x] != '@') {
                continue;
            }

            int neighbours = 0;
            // cancer
            if(y-1 >= 0 && x-1 >= 0 && data[y-1][x-1] == '@') {
                neighbours++;
            }
            if(y-1 >= 0 && data[y-1][x] == '@') {
                neighbours++;
            }
            if(y-1 >= 0 && x+1 < data.size() && data[y-1][x+1] == '@') {
                neighbours++;
            }
            if(x-1 >= 0 && data[y][x-1] == '@') {
                neighbours++;
            }
            if(x+1 < data.size() && data[y][x+1] == '@') {
                neighbours++;
            }
            if(x-1 >= 0 && y+1 < data.size() && data[y+1][x-1] == '@') {
                neighbours++;
            }
            if(y+1 < data.size() && data[y+1][x] == '@') {
                neighbours++;
            }
            if(y+1 < data.size() && x+1 < data.size() && data[y+1][x+1] == '@') {
                neighbours++;
            }

            if (neighbours < 4) {
                result++;
            }
        }
    }

    return result;
}

unsigned int solve2(std::vector<std::string>& data) {
    unsigned int result = 0;
    // mega cancer
    while(true) {
        bool shouldBreak = true;
        for(int y = 0; y < data.size(); y++) {
            for(int x = 0; x < data.size(); x++) {
                if(data[y][x] != '@') {
                    continue;
                }

                int neighbours = 0;
                if (y - 1 >= 0 && x - 1 >= 0 && data[y - 1][x - 1] == '@') {
                    neighbours++;
                }
                if(y-1 >= 0 && data[y-1][x] == '@') {
                    neighbours++;
                }
                if(y-1 >= 0 && x+1 < data.size() && data[y-1][x+1] == '@') {
                    neighbours++;
                }
                if(x-1 >= 0 && data[y][x-1] == '@') {
                    neighbours++;
                }
                if(x+1 < data.size() && data[y][x+1] == '@') {
                    neighbours++;
                }
                if(x-1 >= 0 && y+1 < data.size() && data[y+1][x-1] == '@') {
                    neighbours++;
                }
                if(y+1 < data.size() && data[y+1][x] == '@') {
                    neighbours++;
                }
                if(y+1 < data.size() && x+1 < data.size() && data[y+1][x+1] == '@') {
                    neighbours++;
                }

                if (neighbours < 4) {
                    data[y][x] = '.';
                    shouldBreak = false;
                    result++;
                }
            }
        }

        if(shouldBreak) {
            break;
        }
    }
    return result;
}

int main() {
    std::vector<std::string> data = getData("../in.txt");
    std::cout << "silver: " << solve1(data) << '\n';
    std::cout << "gold: " << solve2(data) << '\n';
    return 0;
}
