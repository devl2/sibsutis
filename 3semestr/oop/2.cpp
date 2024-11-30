#include <iostream> 
#include <ctime> 
 
int** genRandMatrix(int size, int maxValue, int row){ 
    int** matrix = new int* [size]; 
  
    for(int i=0;i<=size;i++){ 
        matrix[i] = new int[row + 1]; 
        matrix[i][0] = row; 
        
        for(int j=1;j<=row; j++){ 
            matrix[i][j] = rand() % (maxValue + 1); 
        } 
    } 
  
    return matrix; 
} 
 
void print(int** matrix, int size, int row){ 
    for(int i=0;i<size;i++){ 
        int row = matrix[i][0]; 
        std::cout << row << std::endl; 

        for(int j=1;j<=row;j++){ 
            std::cout << matrix[i][j] << " ";
        } 
    } 
} 
 
int main(){ 
    srand(time(0));
    int row = rand() % 10; 
    int size = rand() % 10; 
    int maxValue = 100; 
    int** matrix = genRandMatrix(size, maxValue, row); 
    print (matrix, size, row); 
    for (int i = 0; i < size; i++){
        delete [] matrix[i];
    }
    return 0; 
}