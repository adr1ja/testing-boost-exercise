#define BOOST_TEST_MODULE MyIOTest
#include <boost/test/unit_test.hpp>
#include "matrixIO.hpp"
#include <fstream>
#include <cstdio>

BOOST_AUTO_TEST_CASE(test_openData)
{
    // 1. Create dummy file 
    std::string filename = "test_matrix.txt";
    std::ofstream outfile(filename);
    outfile << "1.0, 2.0" << std::endl; 
    outfile << "3.0, 4.0" << std::endl; 
    outfile.close();

    // 2. Call function (filename, matrixSize)
    auto matrix = matrixIO::openData(filename, 2);

    // 3. Assertions
    BOOST_CHECK_EQUAL(matrix.rows(), 2);
    BOOST_CHECK_EQUAL(matrix.cols(), 2);
    BOOST_CHECK_CLOSE(matrix(0,0), 1.0, 0.001);
    BOOST_CHECK_CLOSE(matrix(1,1), 4.0, 0.001);
    
    // 4. Cleanup
    std::remove(filename.c_str());
}