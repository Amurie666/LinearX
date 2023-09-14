#include <iostream>
#include "Matrix.h"
#include "Tuple.h"
#include "Polynomial.h"
#include "Complex.h"
#include "Modulo.h"
#include "QuotientSpace.h"
#include "Cartesian_product.h"

int main() {
    //Usage...

    //Matrices...
    Matrix<int> A(2, 3), B(3, 3);
    Matrix<int> F(2, 3);
    Matrix<Complex> W(2, 2);                    
    A = { {1, 2, 3}, {4, 5, 6}, {1, 2, 3} };    //This will change the dimensions of matrix A.
    B = { {1, 2, 3}, {4, 5, 6}, {4, 5, 6} };
    F = std::move(A);
    std::cout << F * 2 << std::endl;
    std::cout << 2 * F << std::endl;
    std::cout << F + B << std::endl;
    std::cout << F.transpose().trace() << std::endl;

    //Tuples...
    Tuple<int> t1(3), t2(3);
    t1 = { 1, 2, 3 };
    t2 = { 1, 1, 1 };
    Tuple<int> t3 = std::move(t1);
    Tuple<int> t4(t2);
    std::cout << t3 + t4 << std::endl;
    std::cout << 2 * t4 << "   " << t4 * 2 << std::endl;

    //Polynomials...
    Polynomial<int> p1(3);         
    Polynomial<int> p2(4);          
    Polynomial<int> p3(4);
    p3 = std::move(p2);
    p1 = { 1, 2, 3 };
    p3 = { 1, 1, 1, 1 };
    p3 = { 2, 1, 1, 3, 1, 1, 1 };      //This will generate the polynomial: (2x^4 + x^3 + x^2 + 3x +1) + 1 + 1 = (2x^4 + x^3 + x^2 + 3x + 3)
    std::cout << p3 << std::endl;
    std::cout << "+      " << p1 << std::endl;
    std::cout << "= " << p3 + p1 << std::endl;
    
    //Complex numbers...
    Complex y(3, 4);
    Complex x(1, 2);    //1+2i
    Complex x_0(3, 4);
    Complex x_1(4, 4);
    Complex x_2(5, 4);
    Complex z = std::move(y);
    Complex w(1, 2);
    std::cout << w / z << "    " << w * z << "    " << w + z << std::endl;

    //Numbers in Z_7...
    Zmod<7> n(3);
    Zmod<7> m(5);
    std::cout << n * m << "     " << n / m << "       " << n + m;


    //QuotientSpace and subspaces...
    Matrix<Complex> K = { {x_0, x}, {x_0, x} };
    Matrix<Complex> L = { {x, x_1}, {x, x_0} };
    Matrix<Complex> M = { {x_1, x_0}, {x, x} };
    Matrix<Complex> N = { {x_2, x}, {x_0, x_0} };


    //You can skip this part for now... :
    //Subspaces and Cosets...
    std::set<Matrix<Complex>> subspace = { K, L, M, N };    
    QuotientSpace<Complex, Matrix> QS(subspace, N);         //Initialize the subspace along with the coset: (subspace + N)
    auto newcoset = QS + L;
    auto somecoset = newcoset + (QS + M);                   //somecoset = QS + (L+M)
    return 0;
}