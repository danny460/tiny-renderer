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
    assert(i >= 0 && i < rows);
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
    Matrix result(rows, cols);
    for(int i = 0 ; i < rows; i++){
        for(int j = 0 ; j < cols; j++){
            result[i][j] = m[j][i];
        }
    }
    return result;
}

//exploring cholskey decomposition

Matrix Matrix::inverse(){
    assert(rows == cols);
    float d = det();
    if(d == 0){
        throw "not invertible";
    }
    float denom = 1 / d;
    Matrix result(rows, cols);
    for(int i = 0 ; i < rows; i++){
        for(int j = 0 ; j < cols; j++){
            result.m[i][j] = denom * cofactor(j, i) * minor(j, i);
        }
    }
    return result;
}

int Matrix::cofactor(int r, int c){
    return (r + c) % 2 == 0 ? 1 : -1;
}

float Matrix::minor(int r, int c){
    assert(rows == cols);
    if(rows == 1){
        throw "cannot get minor of 1 X 1 matrix";
    }
    Matrix temp(rows - 1, cols - 1);
    int offset_r = 0;
    for(int i = 0 ; i < rows - 1; i++){
        int offset_c = 0;
        if( i == r) offset_r = 1;
        for(int j = 0 ; j < cols - 1; j++){
            if( j == c) offset_c = 1;
            temp[i][j] = m[i + offset_r][j + offset_c];
        }
    }
    return temp.det();
}

float Matrix::det(){
    assert(rows == cols && rows > 0);
    if(rows == 1){
        return m[0][0];
    }
    float d = 0.f;
    for(int i = 0 ; i < cols ; i++){
        d += m[0][i] * cofactor(0, i) * minor(0, i);
    }
    return d;
}



