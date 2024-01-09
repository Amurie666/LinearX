#include "LinearX.h"

int main() {
    LX::Matrix<LX::Complex> A = { 
        {LX::make_complex(15,10), LX::make_complex(4.8,-7), LX::make_complex(3,0)},
        {LX::make_complex(-3,0), LX::make_complex(0,-4), LX::make_complex(-2, -2)},
        {LX::make_complex(3,-7), LX::make_complex(0,-9), LX::make_complex(-2,8)}
    };

    LX::Matrix<LX::Complex> b = { 
        {LX::make_complex(5,8)},
        {LX::make_complex(0,-1)},
        {LX::make_complex(2,0)}
    };
    std::cout << "\nSolving the system:\n" << A << "=" << b << "\nSolution:\n" << LX::SYSTEM_SOLVE(A, b);
    
    LX::Matrix<double> A_0 = {
        {3, -7, 4 },
        {1, -2, 1},
        {2, -1, -2}
    };

    LX::Matrix<double> b_0 = {
        {10},
        {3},
        {6}
    };
    std::cout << "\nSolving the system:\n" << A_0 << "=" << b_0 << "\nSolution:\n" << LX::SYSTEM_SOLVE(A_0, b_0);

}
