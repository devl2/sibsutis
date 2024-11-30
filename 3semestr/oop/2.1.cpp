#include <iostream>
#include <cstdlib>
#include <ctime>

int** genRandMatrix(int N, int maxValue){ 
    int** matrix = new int* [N]; 
  
    for(int i = 0; i < N; i++){
        matrix[i] = new int[N]; // Исправлено на N, а не N + 1
        
        for(int j = 0; j < N; j++){ 
            matrix[i][j] = rand() % maxValue;
        } 
    } 
  
    return matrix; 
} 

void leftDiagonals(int** matrix, int* D, int& index, int N) {
    for (int start_col = 0; start_col < N; start_col++) {
        int j = start_col, i = 0;
        while (j >= 0 && i < N) {
            D[index++] = matrix[i][j];
            i++;
            j--;
        }
    }
    for (int row = 1; row < N; ++row) {
        int j = N - 1, i = row;
        while (i < N && j >= 0) {
            D[index++] = matrix[i][j];
            i++;
            j--;
        }
    }
}

void rightDiagonals(int** matrix, int* D, int& index, int N) {
   for (int start_col = N - 1; start_col >= 0; start_col--) {
        int j = start_col;
        int i = 0;
        while (j < N && i < N) {
            D[index++] = matrix[i][j];
            i++;
            j++;
        }
    }

    for (int start_row = 1; start_row < N; start_row++) {
        int j = 0;
        int i = start_row;
        while (j < N && i < N) {
            D[index++] = matrix[i][j];
            i++;
            j++;
        }
    }
}

void spiral_center(int** matrix, int* D, int& index, int N) {
    int x = N / 2, y = N / 2;
    D[index++] = matrix[x][y];

    for (int layer = 1; layer <= (N - 1) / 2; ++layer) {
        for (int i = 0; i < layer * 2; ++i) D[index++] = matrix[x - layer + i][y + layer]; // right
        for (int i = 0; i < layer * 2; ++i) D[index++] = matrix[x + layer][y + layer - i]; // down
        for (int i = 0; i < layer * 2; ++i) D[index++] = matrix[x + layer - i][y - layer]; // left
        for (int i = 0; i < layer * 2; ++i) D[index++] = matrix[x - layer][y - layer + i]; // up
    }
}

void spiral_left(int** matrix, int* D, int& index, int N) {
    int l = 0, r = N - 1, top = 0, bot = N - 1;

    while (l <= r && top <= bot) {
        for (int i = l; i <= r; ++i) D[index++] = matrix[top][i]; // top
        top++;
        for (int i = top; i <= bot; ++i) D[index++] = matrix[i][r]; // right
        r--;
        if (top <= bot) {
            for (int i = r; i >= l; --i) D[index++] = matrix[bot][i]; // bottom
            bot--;
        }
        if (l <= r) {
            for (int i = bot; i >= top; --i) D[index++] = matrix[i][l]; // left
            l++;
        }
    }
}

void print(int **matrix, int* D, int& index, int N){
    std::cout << "Матрица:" << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    index = 0;
    std::cout << std::endl;
    std::cout << "Элементы по правым диагоналям:" << std::endl;
    rightDiagonals(matrix, D, index, N);
    for (int i = 0; i < index; ++i) std::cout << D[i] << " ";
    std::cout << std::endl;
    
    index = 0;
    std::cout << std::endl;
    std::cout << "Элементы по левым диагоналям:" << std::endl;
    leftDiagonals(matrix, D, index, N);
    for (int i = 0; i < index; ++i) std::cout << D[i] << " ";
    std::cout << std::endl;

    index = 0;
    std::cout << std::endl;
    std::cout << "Элементы по спирали начиная с центрального элемента:" << std::endl;
    spiral_center(matrix, D, index, N);
    for (int i = 0; i < index; ++i) std::cout << D[i] << " ";
    std::cout << std::endl;

    index = 0;
    std::cout << std::endl;
    std::cout << "Элементы по спирали начиная с левого верхнего элемента:" << std::endl;
    spiral_left(matrix, D, index, N);
    for (int i = 0; i < index; ++i) std::cout << D[i] << " ";
    std::cout << std::endl;
}

int main() {
    srand(time(nullptr));
    
    int N;
    int maxValue = 100;
    std::cout << "Введите размер матрицы N: ";
    std::cin >> N;
    
    int* D = new int[N * N];
    int index;

    int **matrix = genRandMatrix(N, maxValue);
    
    print(matrix, D, index, N);

    delete[] D;
    
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

