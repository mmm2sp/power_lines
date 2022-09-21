#include <iostream>
#include <cmath>
using namespace std;

class Matrix {
public:
    Matrix(int arr[], size_t n_elements) {
        size = int(pow(n_elements, 1.f/2.f));
        mat = new int*[size];
        for(int i = 0; i < size; i++){
            mat[i] = new int[size];
            for (int j = 0; j < size; j++)
                mat[i][j] = arr[i*size + j];
        }
    }

    Matrix(int element, size_t n_elements) {
        size = int(pow(n_elements, 1.f / 2.f));
        mat = new int *[size];
        for (int i = 0; i < size; i++) {
            mat[i] = new int[size];
            for (int j = 0; j < size; j++)
                mat[i][j] = element;
        }
    }

    Matrix(){
        size = 1;
        mat = new int*;
        int *elem = new int;
        *mat = elem;
        *elem = 1;
    }

    Matrix(const Matrix& other) {
        size = other.size;
        mat = new int*[size];
        for(int i = 0; i < size; i++) {
            mat[i] = new int[size];
            for (int j = 0; j < size; j++)
                mat[i][j] = other.mat[i][j];
        }
    }

    void printMatrix() {
        for(int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                cout << mat[i][j] << ' ';
            cout << endl;
        }
    }

    int calcDeterminant() {
        if (size == 1)
            return **mat;
        int det = 0;
        for (int i = 0; i < size; i++){
            Matrix m(0, (size-1)*(size-1));
            for(int j = 0; j < size - 1; j++){
                for(int k = 0; k < size; k ++){
                    if(k < i)
                        m.mat[j][k] = mat[j+1][k];
                    if(k > i)
                        m.mat[j][k-1] = mat[j+1][k];
                }
            }
            det = det + m.calcDeterminant() * mat[0][i] * pow(-1, i);
        }
        return det;
    }

    void Delete(){
        for (int i = 0; i < size; i++)
            delete [] mat[i];
        delete [] mat;
        mat = nullptr;
    }

    ~Matrix() {
        for (int i = 0; i < size; i++)
            delete [] mat[i];
        delete [] mat;
    }

    void calcSquare() {
        auto m = new int*[size];
        for(int i = 0; i < size; i++)
            m[i] = new int[size];


        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                int ij = 0;
                for(int k = 0; k < size; k++){
                    ij += mat[i][k]*mat[k][j];
                }
                m[i][j] = ij;
            }
        }

        Delete();
        mat = m;
    }
    void matTranspose() {
        for (int i = 0; i < size; i++) {
            for (int j = i + 1 ; j < size; j++){
                swap(mat[i][j], mat[j][i]);
            }
        }
    }

private:
    int** mat;
    int size;
};

int main(){
    int array[4] = {1, 2, 3, 4 };
    Matrix m1(array, 4);
    m1.printMatrix();

    std::cout << "------------" << std::endl;

    Matrix m2(5, 4);
    m2.printMatrix();

    std::cout << "------------" << std::endl;

    Matrix m3;
    m3.printMatrix();

    std::cout << "------------" << std::endl;

    const Matrix& p = m2;

    Matrix m4(p);
    m4.printMatrix();

    std::cout << "------------" << std::endl;

    cout << m1.calcDeterminant() << endl;

    std::cout << "------------" << std::endl;

    m1.calcSquare();
    m1.printMatrix();

    std::cout << "------------" << std::endl;

    m1.matTranspose();
    m1.printMatrix();
    return 0;
}