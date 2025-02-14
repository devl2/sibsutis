#pragma once
#include "func.h"
#include <ctype.h>

void countingSortByDigit(Gilbert* A, int size, int exp) {
    Gilbert* output = new Gilbert[size];
    int count[256] = {0};

    for (int i = 0; i < size; i++) {
        unsigned char digit = static_cast<unsigned char>(A[i].ch) / exp % 256;
        count[digit]++;
    }

    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        unsigned char digit = static_cast<unsigned char>(A[i].ch) / exp % 256;
        output[count[digit] - 1] = A[i];
        count[digit]--;
    }

    for (int i = 0; i < size; i++) {
        A[i] = output[i];
    }

    delete[] output;
}


void digitalSort(Gilbert* A, int size) {
    int maxExp = 255;
    for (int exp = 1; maxExp / exp > 0; exp *= 256) {
        Gilbert* output = new Gilbert[size];
        int count[256] = {0};

            for (int i = 0; i < size; i++) {
                unsigned char digit = static_cast<unsigned char>(A[i].ch) / exp % 256;
                count[digit]++;
            }

            for (int i = 1; i < 256; i++) {
                count[i] += count[i - 1];
            }

            for (int i = size - 1; i >= 0; i--) {
                unsigned char digit = static_cast<unsigned char>(A[i].ch) / exp % 256;
                output[count[digit] - 1] = A[i];
                count[digit]--;
            }

            for (int i = 0; i < size; i++) {
                A[i] = output[i];
            }

            delete[] output;
    }
}

void GilbertMurCode(Gilbert* code, int L, int R) {
    float sumProb = 0;
    for (int i = L; i <= R; ++i) {
        sumProb += code[i].Pi;
    }

    float currentProb = 0.0;
    for (int i = L; i <= R; ++i) {
        currentProb += code[i].Pi;
        code[i].Qi = sumProb - currentProb;
        code[i].Li = std::ceil(-std::log2(code[i].Pi)); 

        unsigned int codeValue = static_cast<unsigned int>(currentProb * (1 << code[i].Li));

        code[i].codeword = new char[code[i].Li + 1];

        for (int j = 0; j < code[i].Li; ++j) {
            if (codeValue & (1 << (code[i].Li - j - 1))) {
                code[i].codeword[j] = '1';
            } else {
                code[i].codeword[j] = '0';
            }
        }

        code[i].codeword[code[i].Li] = '\0';
    }
}

void printEncodedDataFromFile(const char* filename, Gilbert* code, int numsUnique) {
    FILE* base = fopen(filename, "rb");

    int linesPerPage = 10;
    int linesPrinted = 0;
    bool continuePrinting = true;
    char buffer[1024];

    while (continuePrinting) {
        int bytesRead = fread(buffer, sizeof(char), sizeof(buffer), base);
        if (bytesRead == 0) break;

        for (int i = 0; i < bytesRead; ++i) {
            unsigned char ucharCh = static_cast<unsigned char>(buffer[i]);

            for (int j = 0; j < numsUnique; ++j) {
                if (code[j].ch == buffer[i]) {
                    std::cout << code[j].codeword;
                    break;
                }
            }
        }

        linesPrinted++;
        if (linesPrinted % linesPerPage == 0) {
            std::cout << "\ncontinue? (y/n)? ";
            char choice;
            std::cin >> choice;

            if (choice != 'y' && choice != 'Y') {
                continuePrinting = false;
            }
        }
    }

    fclose(base);
}

void tableSymbols(Gilbert* code, int& numsUnique) {
    int windows866[256] = {0};    
    int totalNums = 0;            
    char ch;


    const char* filename = "D:/solutions/kurs/testBase4.dat";
    FILE* base = fopen(filename, "rb");
    if (!base) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    while (fread(&ch, sizeof(ch), 1, base) == 1) {
        totalNums++;
        unsigned char ucharCh = static_cast<unsigned char>(ch);
        windows866[ucharCh]++;
    }

    fclose(base);

    numsUnique = 0;
    for (int i = 0; i < 256; i++) {
        if (windows866[i] != 0) {
            numsUnique++;
        }
    }

    int temp = 0;
    float entropy = 0.0f;
    float avgCodeLength = 0.0f;

    for (int i = 0; i < 256; i++) {
        if (windows866[i] != 0) {
            code[temp].ch = static_cast<char>(i);
            code[temp].Pi = static_cast<float>(windows866[i]) / static_cast<float>(totalNums);
            temp++;

            entropy -= code[temp - 1].Pi * log2(code[temp - 1].Pi);
        }
    }

    digitalSort(code, numsUnique);

    GilbertMurCode(code, 0, numsUnique - 1);

    for (int i = 0; i < numsUnique; i++) {
        avgCodeLength += code[i].Pi * code[i].Li;
    }

    for (int i = 0; i < numsUnique; i++) {
        std::cout << "Symbol: " << code[i].ch 
                  << ", Probability: " << code[i].Pi 
                  << ", Codeword: " << code[i].codeword 
                  << ", Length: " << code[i].Li << "\n";
    }
    
    std::cout << "\navg length: " << avgCodeLength << "\n";
    std::cout << "entropy: " << entropy << "\n";
    std::cout << "unique: " << numsUnique << "\n";
    std::cout << "num symbols: " << totalNums << "\n";

    std::cout << "\nLcp < H + 2\n";
    std::cout << avgCodeLength << " < " << entropy << " + 2\n";

    std::cout << "\nEncoded Data from File:\n";
    //printEncodedDataFromFile("D:/solutions/kurs(ne robit)/testBase4.dat", code, numsUnique);

    for (int i = 0; i < numsUnique; i++) {
        delete[] code[i].codeword;
    }
}