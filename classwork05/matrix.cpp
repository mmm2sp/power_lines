#include <iostream>
using namespace std;

template<typename Field, size_t M, size_t N>
struct Matrix {
    Field mat[M][N];

    Matrix(Field arr[M][N]){
        for (int i = 0; i < M; i++){
            for (int j = 0; j < N; j++)
                mat[i][j] = arr[i][j];
        }
    }

    Matrix operator+(const Matrix& other) {
        Field arr[M][N];
        for (int i = 0; i < M; i++){
            for (int j = 0; j < N; j++)
                arr[i][j] = this->mat[i][j] + other.mat[i][j];
        }
        Matrix<Field, M, N> res (arr);
        return res;
    }

    Matrix operator-(const Matrix& other) {
        Field arr[M][N];
        for (int i = 0; i < M; i++){
            for (int j = 0; j < N; j++)
                arr[i][j] = this->mat[i][j] - other.mat[i][j];
        }
        Matrix<Field, M, N> res (arr);
        return res;
    }

    void printMatrix() {
        for(int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++)
                cout << mat[i][j] << ' ';
            cout << endl;
        }
    }
};

template<typename Field, size_t M, size_t N, size_t K>
Matrix<Field, M, K> operator*(const Matrix<Field, M, N>& lha, const Matrix<Field, N, K>& rha) {
    Field arr[M][K];
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            Field ij = 0;
            for(int k = 0; k < N; k++)
                ij += lha.mat[i][k] * rha.mat[k][j];
            arr[i][j] = ij;
        }
    }
    Matrix<Field, M, K> res (arr);
    return res;
}

int main(){
    int arr1[4][3] = {1, 2, 4,
                      -3, 6, 0,
                      20, -6, 33,
                      -5, -3, 5};

    int arr2[4][3] = {1, 1, 1,
                      1, 1, 1,
                      1, 1, 1,
                      1, 1, 1};

    Matrix<int, 4, 3> m1 (arr1);
    Matrix<int, 4, 3> m2 (arr2);
    Matrix<int, 4, 3> sum = m1 + m2;
    sum.printMatrix();

    std::cout << "-----------------\n" ;

    int arr3[2][3] = {1 , 1, 3,
                      4, -2, 6};
    int arr4[3][2] = {5, 3,
                      4, 9,
                      -10, 15};
    Matrix<int, 2, 3> m3 (arr3);
    Matrix<int, 3, 2> m4 (arr4);
    (m3 * m4).printMatrix();
}
