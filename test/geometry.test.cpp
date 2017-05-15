#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "geometry.h"

float matrix_0_data[3][3] = {
    {   3.0f,     0.0f,     2.0f  },
    {   2.0f,     0.0f,     -2.0f },
    {   0.0f,     1.0f,     1.0f  },
};
float transp_0_data[3][3] = {
    {   3.0f,     2.0f,     0.0f  },
    {   0.0f,     0.0f,     1.0f },
    {   2.0f,     -2.0f,     1.0f  },
};
float invert_0_data[3][3] = {
    {   0.2f,     0.2f,     0.0f    },
    {   -0.2f,    0.3f,     1.0f    },
    {   0.2f,     -0.3f,    0.0f    },
};
float det_0 = 10.f;
float minor_0_data[3][3] = {
    {   2.0f,   2.0f,   2.0f},
    {   -2.0f,  3.0f,   3.0f},
    {   0.0f,   -10.0f,  0.0f},
};

Matrix matrix_0{3,3};
Matrix transp_0{3,3};
Matrix invert_0{3,3};


void setup(){
    for(int i = 0 ; i < matrix_0.nrows(); i++){
        for(int j = 0 ; j < matrix_0.ncols(); j++){
            matrix_0[i][j] = matrix_0_data[i][j];
        }
    }
}

TEST_CASE( "Setting up", "[matrix]" ) {
    setup();
    SECTION("SETUP"){
        REQUIRE(matrix_0.nrows() == 3);
        REQUIRE(matrix_0.ncols() == 3);

        for(int i = 0 ; i < matrix_0.nrows(); i++){
            for(int j = 0 ; j < matrix_0.ncols(); j++){
                REQUIRE(matrix_0[i][j] == matrix_0_data[i][j]);
            }
        }
    }
}

TEST_CASE( "Matrix Transpose", "[matrix]" ) {
    SECTION("TEST CASE 1: should be equal"){
        transp_0 = matrix_0.transpose();
        for(int i = 0 ; i < transp_0.nrows(); i++){
            for(int j = 0 ; j < transp_0.ncols(); j++){
                REQUIRE(transp_0[i][j] == transp_0_data[i][j]);
            }
        }   
    }
}

TEST_CASE("Matrix Determinant, Minor, Cofactor", "[matrix]"){
    SECTION("TEST CASE 1: determinant"){
        REQUIRE(matrix_0.det() == det_0);
    }
    
    SECTION("TEST CASE 2: minors"){
        for(int i = 0 ; i < matrix_0.nrows(); i++){
            for(int j = 0 ; j < matrix_0.ncols(); j++){
                REQUIRE(matrix_0.minor(i, j) == minor_0_data[i][j]);
            }   
        }
    }
}

TEST_CASE( "Matrix Inverse", "[matrix]" ) {
    SECTION("TEST CASE 1: should be equal"){
        invert_0 = matrix_0.inverse();
        for(int i = 0 ; i < invert_0.nrows(); i++){
            for(int j = 0 ; j < invert_0.ncols(); j++){
                REQUIRE(invert_0[i][j] == invert_0_data[i][j]);
            }
        }   
    }
}

TEST_CASE("MINOR", "[matrix][minor]"){
    Matrix dim2(2, 2);
    int count = 1;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++, count++){
            dim2[i][j] = count;
        }
    }

    SECTION("1"){
        REQUIRE(dim2.minor(0, 0) == 4);
        REQUIRE(dim2.minor(0, 1) == 3);
        REQUIRE(dim2.minor(1, 0) == 2);
        REQUIRE(dim2.minor(1, 1) == 1);
    }
}
