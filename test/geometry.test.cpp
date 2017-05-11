#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "geometry.h"

const float matrix_0_data[3][3] = {
    {   3.0f,     0.0f,     2.0f  },
    {   2.0f,     0.0f,     -2.0f },
    {   0.0f,     1.0f,     1.0f  },
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

TEST_CASE( "Setting up", "" ) {
    setup();

    SECTION("SETUP 1"){
        for(int i = 0 ; i < matrix_0.nrows(); i++){
            for(int j = 0 ; j < matrix_0.ncols(); j++){
                REQUIRE(matrix_0[i][j] == matrix_0_data[i][j]);
            }
        }
    }
}



TEST_CASE( "Matrix Transpose", "[matrix]" ) {

    SECTION("TEST CASE 1"){
        transp_0 = matrix_0.transpose();
        for(int i = 0 ; i < transp_0.nrows(); i++){
            for(int j = 0 ; j < transp_0.ncols(); j++){
                REQUIRE(transp_0[i][j] == matrix_0_data[i][j]);
            }
        }   
    }
}

TEST_CASE( "Matrix Inverse", "[matrix]" ) {
    REQUIRE(1==0);
}
