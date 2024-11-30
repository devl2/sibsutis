#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <cstring> 

struct chanceSymbol {
    unsigned char ch = 0;
    float chance = 0;
};

struct codeFano {
    unsigned char ch = 0;
    float Pi = 0;
    unsigned short int Li = 0;
    char* codeword = nullptr;
};

void printChanceSymbols(chanceSymbol* A, unsigned int num, unsigned short int encoding[256]) {
    float totalChance = 0;
    for (unsigned int i = 0; i < num; i++) {
        if (A[i].ch == '\n') {
            std::cout << "\\n";
        } else {
            std::cout << A[i].ch;
        }
        std::cout << " | " << std::fixed << std::setprecision(4) << A[i].chance << "\n";
        totalChance += A[i].chance;
    }
    std::cout << "Total probability: " << totalChance << "\n";
}

float calculationEntropy(chanceSymbol* A, unsigned int nums) {
    float entropy = 0;
    for (unsigned int i = 0; i < nums; i++) {
        if (A[i].chance > 0) {
            entropy += A[i].chance * log2(A[i].chance);
        }
    }
    return -entropy;
}

float calculationAverageLength(codeFano* A, unsigned int nums) {
    float avgLength = 0;
    for (unsigned int i = 0; i < nums; i++) {
        avgLength += A[i].Li * A[i].Pi;
    }
    return avgLength;
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

int med(codeFano *fano, int borderL, int borderR) {

	float SumL = 0;
	for (int i = borderL; i < borderR; i++) {
		SumL = SumL + fano[i].Pi;
	}
	float SumR = fano[borderR].Pi;
	int m = borderR;
	while (SumL >= SumR) {
		m = m - 1;
		SumL = SumL - fano[m].Pi;
		SumR = SumR + fano[m].Pi;
	}
	return m;
}

void FanoCode(codeFano * &fano, int borderL, int borderR, int k) {

	if (borderL < borderR) {
		k = k + 1;
		int m = med(fano, borderL, borderR);
        // std::cout << std::endl << borderL << " " << borderR << " | " << "k=" << k << " | "<< "m=" << m;
		for (int i = borderL; i <= borderR; i++) {
            if (fano[i].codeword != nullptr){
                char *temp = new char[k];
                for(int j = 0; j < k - 1; j++)
                    temp[j] = fano[i].codeword[j];
                delete[] fano[i].codeword;
                fano[i].codeword = temp;
            } 
            else
                fano[i].codeword = new char[k];

			if (i <= m) {
				fano[i].codeword[k - 1] = '0';
				fano[i].Li = fano[i].Li + 1;
			}
			else {
				fano[i].codeword[k - 1] = '1';
				fano[i].Li = fano[i].Li+ 1;
			}
		}
		FanoCode(fano, borderL, m, k);
		FanoCode(fano, m + 1, borderR, k);
	}
	else {

	}

}

codeFano * FanoCode(chanceSymbol *chanceSymbols, short int numSymbols){
    codeFano *fano = new codeFano[numSymbols];
    quickSort(chanceSymbols, numSymbols - 1, 0, 1, 1);

    for(int i = 0; i < numSymbols; i++){
        fano[i].ch = chanceSymbols[i].ch;
        fano[i].Pi = chanceSymbols[i].chance;
    }

    FanoCode(fano, 0, numSymbols - 1, 0);

    return fano;
}

void generateFanoCode(codeFano* fano, int numSymbols) {
    for (int i = 0; i < numSymbols; i++) {
        fano[i].codeword = new char[numSymbols + 1]();
        std::fill(fano[i].codeword, fano[i].codeword + numSymbols, '\0');
    }
    FanoCode(fano, 0, numSymbols - 1, 0);
}

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

int main() {
    SetConsoleOutputCP(866);
    SetConsoleCP(866);

    std::string filename = "D:/solutions/saod/kodirovka/file.txt";
    unsigned short int kod866[256] = {0};

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    unsigned char ch;
    unsigned int numSymbols = 0;
    while (file.get(reinterpret_cast<char&>(ch))) {
        numSymbols++;
        kod866[ch]++;
    }
    file.close();

    unsigned int numUniqueSymbols = 0;
    for (int i = 0; i < 256; i++) {
        if (kod866[i] != 0) {
            numUniqueSymbols++;
        }
    }

    chanceSymbol* chanceSymbols = new chanceSymbol[numUniqueSymbols];
    codeFano* fano = new codeFano[numUniqueSymbols];

    unsigned short int temp = 0;
    for (int i = 0; i < 256; i++) {
        if (kod866[i] != 0) {
            chanceSymbols[temp].ch = (unsigned char)i;
            chanceSymbols[temp].chance = static_cast<float>(kod866[i]) / numSymbols;

            fano[temp].ch = (unsigned char)i;
            fano[temp].Pi = static_cast<float>(kod866[i]) / numSymbols;
            temp++;
        }
    }

    generateFanoCode(fano, numUniqueSymbols);
    printChanceSymbols(fano, numUniqueSymbols);

    float entropy = calculationEntropy(chanceSymbols, numUniqueSymbols);
    float avgLength = calculationAverageLength(fano, numUniqueSymbols);

    std::cout << "\nEntropy: " << entropy << "\n";
    std::cout << "Average code length: " << avgLength << "\n";

    for (int i = 0; i < numUniqueSymbols; i++) {
        delete[] fano[i].codeword;
    }
    delete[] chanceSymbols;
    delete[] fano;

    return 0;
}
