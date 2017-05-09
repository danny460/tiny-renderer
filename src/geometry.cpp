#include <vector>
#include <iostream>
#include <cmath>
#include "geometry.h"

Matrix::Matrix(int r, int c) : m(std::vector<std::vector<float>>(r, std::vector<float>(c, 0.f))), rows(r), cols(c) { }

int Matrix::nrows(){
    return rows;
}

int Matrix::ncols(){
    return cols;
}

Matrix Matrix::indentity(int dimension){
    Matrix I(dimension, dimension);
    for(int i = 0 ; i < dimension; i++){
        for(int j = 0 ; j < dimension; j++){
            I[i][j] = (i == j ? 1.f : 0.f);
        }
    }
    return I;
}

Matrix Matrix::transpose(){
    Matrix T(rows, cols);
    for(int i = 0 ; i < dimension; i++){
        for(int j = 0 ; j < dimension; j++){
            T[i][j] = m[j][i];
        }
    }
    return T;
}

Matrix Matrix::inverse(){
    //
}



