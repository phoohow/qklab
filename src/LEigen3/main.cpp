#include "LEigen3.h"
#include <iostream>
#include <string>

#include <Eigen/Dense>

using namespace Eigen;

int main()
{
    MatrixXd m = MatrixXd::Random(3,3);
    m = (m + MatrixXd::Constant(3,3,1.2)) * 50;
    VectorXd v(3);
    v << 1, 2, 3;
    std::cout << "m =\n" << m << std::endl;
    std::cout << "v =\n" << v << std::endl;
    std::cout << "m * v =\n" << m * v << std::endl;
}
