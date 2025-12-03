#include <iostream>
#include <vector>

void whatever() {
    std::vector<std::vector<unsigned long long>> diagonals(1, std::vector<unsigned long long>(1, 1));

    int biggestRow = 0;
    unsigned long long currentValue = 20151125;
    bool ENDTHISCRAP = false;

    for(int i = biggestRow; i < diagonals.size();) {
        std::vector<unsigned long long> newRow;
        for(int j = 0; j < biggestRow+1; j++, i--, currentValue = (currentValue*252533)%33554393) {
            diagonals[i][j] = currentValue;
            diagonals[i].push_back(0);
            //std::cout << currentValue << ", i = " << i << ", j = " << j << '\n';
            if(i == 0) {
                currentValue = (currentValue*252533)%33554393;
                newRow.push_back(currentValue);
                break;
            }
            if(i == 2978-1 && j == 3083-1) {
                ENDTHISCRAP = true;
                break;
            }
        }
        if(ENDTHISCRAP) {
            break;
        }
        diagonals.push_back(newRow);
        i = ++biggestRow;
    }

    std::cout << "Silver: " << currentValue << "\n";
}

int main() {
    whatever();
    return 0;
}
