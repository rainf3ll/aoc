#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

typedef struct inputLine {
    short instruction;
    short startX, startY;
    short endX, endY;
} inputLine;

typedef struct schnitzelStruct {
    bool onOrOff;
    int brightness;
} schnitzelStruct;

std::vector<inputLine> getInput() {
    std::vector<inputLine> ret;
    std::ifstream f("in.txt");
    std::string line;

    while(std::getline(f, line)) {
        inputLine parsed;

        // Replace every comma with a space for slightly less painful parsing
        for(auto& c : line) {
            if (c == ',') {
                c = ' ';
            }
        }

        std::string toParse;

        if(line.find("turn") != std::string::npos) {
            toParse = line.substr(4); // Omit any "Turn", again, for a slightly less painful parsing.
        } else {
            toParse = line;
        }

        std::istringstream iss(toParse);
        std::string instruction, fodder;

        iss >> instruction >> parsed.startX >> parsed.startY >> fodder >> parsed.endX >> parsed.endY;

        if(instruction == "on") {
            parsed.instruction = 0; // Turn on
        } else if (instruction == "off") {
            parsed.instruction = 1; // Turn off
        } else {
            parsed.instruction = 2; // Toggle
        }

        ret.push_back(parsed);
    }

    f.close();
    return ret;
}

void solve(const std::vector<inputLine> in) {
    int lightsLit = 0;
    int brightness = 0;
    std::vector<std::vector<schnitzelStruct>> grid(1000, std::vector<schnitzelStruct>(1000, {false, 0}));

    for(auto line : in) {
        for(auto i = line.startY; i <= line.endY; i++) {
            for(auto j = line.startX; j <= line.endX; j++) {
                schnitzelStruct& cell = grid[i][j];

                switch(line.instruction) {
                    case 0: 
                        cell.onOrOff = true;
                        cell.brightness++;
                        break;
                    case 1: 
                        cell.onOrOff = false;
                        cell.brightness--;
                        break;
                    case 2: 
                        cell.onOrOff = !cell.onOrOff;
                        cell.brightness += 2;
                        break;
                    default: break; // Never happens anyways
                }

                if(cell.brightness < 0) {
                    cell.brightness = 0;
                }
            }
        }
    }

    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            if(grid[i][j].onOrOff) {
                lightsLit++;
            }
            brightness += grid[i][j].brightness;
        }
    }

    std::cout << "Silver: " << lightsLit << '\n';
    std::cout << "Gold: " << brightness << '\n';
}

int main() {
    solve(getInput());
    return 0;
}
