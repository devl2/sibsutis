#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <windows.h>

struct chanceSymbol {
    unsigned char ch = 0;
    float chance = 0;
};

struct codeShannon {
    unsigned char ch = 0;
    float Pi = 0;
    float Qi = 0;
    unsigned short int Li = 0;
    char* codeword = nullptr;
};

void printChanceSymbols(chanceSymbol* A, unsigned int num, unsigned short int encoding[256]) {
    float totalChance = 0;
    for (unsigned int i = 0; i < num; i++) {
        if (encoding) {
            if (A[i].ch == '\n')
                std::cout << std::setw(4) << "\\n" << "(" << std::setw(3) << encoding[(int)A[i].ch] << ")" << " | " << std::fixed << A[i].chance << "\n";
            else
                std::cout << std::setw(4) << A[i].ch << "(" << std::setw(3) << encoding[(int)A[i].ch] << ")" << " | " << std::fixed << A[i].chance << "\n";
        } else {
            if (A[i].ch == '\n')
                std::cout << std::setw(4) << "\\n" << " | " << std::fixed << A[i].chance << "\n";
            else
                std::cout << std::setw(4) << A[i].ch << " | " << std::fixed << A[i].chance << "\n";
        }
        totalChance += A[i].chance;
    }
    std::cout << "sum: " << totalChance << "\n";
}

void quickSort(chanceSymbol* A, int R, int L, unsigned short int field, bool reverse) {
    while (L < R) {
        float x = (field == 0) ? A[L].ch : A[L].chance;
        int i = L;
        int j = R;
        while (i <= j) {
            if (field == 0) {
                if (reverse) {
                    while (A[i].ch > x) i++;
                    while (A[j].ch < x) j--;
                } else {
                    while (A[i].ch < x) i++;
                    while (A[j].ch > x) j--;
                }
            } else if (field == 1) {
                if (reverse) {
                    while (A[i].chance > x) i++;
                    while (A[j].chance < x) j--;
                } else {
                    while (A[i].chance < x) i++;
                    while (A[j].chance > x) j--;
                }
            }
            if (i <= j) {
                std::swap(A[i], A[j]);
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            quickSort(A, R, i, field, reverse);
            R = j;
        } else {
            quickSort(A, j, L, field, reverse);
            L = i;
        }
    }
}

float calculationEntropy(chanceSymbol* A, unsigned int nums) {
    float entropy = 0;
    for (unsigned int i = 0; i < nums; i++) {
        entropy += A[i].chance * log2(A[i].chance);
    }
    return -entropy;
}

float calculationAverageLength(codeShannon* A, unsigned int nums) {
    float avgLength = 0;
    for (unsigned int i = 0; i < nums; i++) {
        avgLength += A[i].Li * A[i].Pi;
    }
    return avgLength;
}

float Craft(codeShannon* A, unsigned int nums){
    float sum = 0;
    for (unsigned int i = 0; i < nums; i++){
        sum += pow(2, -A[i].Li);
    }
    
    return sum;
}

codeShannon* ShannonCode(chanceSymbol* chanceSymbols, short int numSymbols) {
    codeShannon* shannon = new codeShannon[numSymbols];

    quickSort(chanceSymbols, numSymbols - 1, 0, 1, true);

    shannon[0].ch = chanceSymbols[0].ch;
    shannon[0].Pi = chanceSymbols[0].chance;
    shannon[0].Li = ceil(-log2(shannon[0].Pi));
    shannon[0].Qi = 0;

    for (int i = 1; i < numSymbols; i++) {
        shannon[i].ch = chanceSymbols[i].ch;
        shannon[i].Pi = chanceSymbols[i].chance;
        shannon[i].Li = ceil(-log2(shannon[i].Pi));
        shannon[i].Qi = shannon[i - 1].Qi + shannon[i - 1].Pi;
    }

    for (int i = 0; i < numSymbols; i++) {
        float temp = shannon[i].Qi;
        shannon[i].codeword = new char[shannon[i].Li + 1];
        for (int j = 0; j < shannon[i].Li; j++) {
            temp *= 2;
            shannon[i].codeword[j] = (temp >= 1) ? '1' : '0';
            if (temp >= 1) temp -= 1;
        }
        shannon[i].codeword[shannon[i].Li] = '\0';
    }

    return shannon;
}

void printEncoded(const char* filename, codeShannon* code, int numsUnique) {
    FILE* base = fopen(filename, "rb");

    unsigned int originalSize = 0;
    unsigned int encodedSize = 0;
    char buffer[1024];
    unsigned int processedSymbols = 0;

    std::cout << "encoded: ";
    while (processedSymbols < 100) {
        int bytesRead = fread(buffer, sizeof(char), sizeof(buffer), base);
        if (bytesRead == 0) break;

        for (int i = 0; i < bytesRead && processedSymbols < 100; ++i) {
            unsigned char ucharCh = static_cast<unsigned char>(buffer[i]);
            originalSize += 8; 

            for (int j = 0; j < numsUnique; ++j) {
                if (code[j].ch == ucharCh) {
                    std::cout << code[j].codeword;
                    encodedSize += strlen(code[j].codeword);
                    break;
                }
            }

            processedSymbols++;
        }
    }

    fclose(base);

    float compressionRatio = static_cast<float>(originalSize) / encodedSize;

    std::cout << "\n\nlength: " << encodedSize << " bits\n";
    std::cout << "szatie " << compressionRatio << "\n";
}

int main() {
    SetConsoleOutputCP(866);
    SetConsoleCP(866);

    const char* filename = "D:/solutions/saod/kodirovka/file.txt";
    FILE* base = fopen(filename, "rb");
    unsigned int numSymbols = 0;
    unsigned int numUniqueSymbols = 0;

    unsigned short int kod866[256] = {0};
    unsigned char ch;

    while (fread(&ch, sizeof(ch), 1, base) == 1) {
        numSymbols++;
        kod866[ch]++;
    }

    for (int i = 0; i < 256; i++) {
        if (kod866[i] != 0)
            numUniqueSymbols++;
    }

    fclose(base);

    chanceSymbol* chanceSymbols = new chanceSymbol[numUniqueSymbols];
    unsigned short int temp = 0;
    for (int i = 0; i < 256; i++) {
        if (kod866[i] != 0) {
            chanceSymbols[temp].ch = (unsigned char)i;
            chanceSymbols[temp].chance = static_cast<float>(kod866[i]) / numSymbols;
            temp++;
        }
    }

    printChanceSymbols(chanceSymbols, numUniqueSymbols, kod866);

    float entropy = calculationEntropy(chanceSymbols, numUniqueSymbols);

    codeShannon* shannon = ShannonCode(chanceSymbols, numUniqueSymbols);
    float avgLengthShannon = calculationAverageLength(shannon, numUniqueSymbols);

    float nerav = Craft(shannon, numUniqueSymbols);
    bool valid = false;

    if (nerav <= 1){
        valid = true;
    } else{
        valid = false;
    }

    float R = avgLengthShannon - entropy;

    std::cout << "\nAi | Pi       | Qi     | Li |     Slovo    |\n";
    std::cout << "---------------------------------------------\n";
    for (int i = 0; i < numUniqueSymbols; i++) {
        std::cout << std::setw(6);
        if (shannon[i].ch == '\n') {
            std::cout << "\\n";
        } else {
            std::cout << shannon[i].ch;
        }
        std::cout << " | "
                  << std::setw(8) << std::fixed << std::setprecision(6) << shannon[i].Pi
                  << " | " << std::setw(6) << std::fixed << std::setprecision(2) << shannon[i].Qi
                  << " | " << std::setw(2) << shannon[i].Li
                  << " | " << shannon[i].codeword << "\n";
    }
    
    std::cout << "\n";
    std::cout << "Neravenstvo Krafta |" << "        Entropy     |" << "     Lcp:    " << "|       Izbitok code Shennona""\n";
    std::cout << "          " << valid << "        |        " << entropy << "        |    " << avgLengthShannon << "     |              " << R << " \n";
    std::cout << "\n";
    std::cout << "Lcp < H + 1\n";
    std::cout << avgLengthShannon << " < " << entropy << " + 1\n";
    

    std::cout << "\n";
    printEncoded(filename, shannon, numUniqueSymbols);

    for (int i = 0; i < numUniqueSymbols; i++) {
        delete[] shannon[i].codeword;
    }
    delete[] shannon;
    delete[] chanceSymbols;

    return 0;
}
