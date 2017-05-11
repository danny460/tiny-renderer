#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
#include "geometry.h"

Matrix::Matrix(int r, int c) : m(std::vector< std::vector<float> >(r, std::vector<float>(c, 0.f))), rows(r), cols(c) { }

int Matrix::nrows(){
    return rows;
}

int Matrix::ncols(){
    return cols;
}

Matrix Matrix::identity(int dimension) {
    Matrix I(dimension, dimension);
    for(int i = 0 ; i < dimension; i++){
        for(int j = 0 ; j < dimension; j++){
            I[i][j] = (i == j ? 1.f : 0.f);
        }
    }
    return I;
}

std::vector<float>& Matrix::operator[](const int i){
    //make sure in range
    assert(i > 0 && i < rows);
    return m[i];
}

Matrix Matrix::operator*(const Matrix& a){
    //make sure (m x n) (n x p)

    assert(cols == a.rows);
    Matrix product(rows, a.cols);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < a.cols; j++){
            float temp {};
            for(int k = 0; k < cols; k++){
                temp += m[i][k] * a.m[k][j];
            }
            product[i][j] = temp;
        }
    }
    return product;
}


Matrix Matrix::transpose(){
    Matrix T(rows, cols);
    for(int i = 0 ; i < rows; i++){
        for(int j = 0 ; j < cols; j++){
            T[i][j] = m[j][i];
        }
    }
    return T;
}

Matrix Matrix::inverse(){
    //must be square matrix
    assert(rows == cols);
    
    Matrix augmented(rows,  cols * 2);
    Matrix result(rows, cols);

    for(int i = 0 ; i < rows; i++){
        for(int j = 0 ; j < cols; j++){
            augmented[i][j] = m[i][j];
        }
    }
    for(int i = 0 ; i < cols; i++){
        augmented[i][i + cols] = 1.f;
    }
    //
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){

        }
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            result[i][j] = augmented[i][j + cols];
        }
    }
    
    return result;
}



