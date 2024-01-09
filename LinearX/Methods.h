#pragma once
template<typename field>
LX::Matrix<field> forward_sub(LX::Matrix<field> L, LX::Matrix<field> Pb) {
    if (!(L.is_lower()) && (Pb.nrows() != L.nrows()))
        throw std::invalid_argument("Inadequate system.");
    LX::Matrix<field> y(L.size(), std::vector<field>(1, 0));
    for (size_t i{ 0 }; i < L.nrows(); i++) {
        field sum = 0;
        for (size_t j{ 0 }; j < i; j++)
            sum += L[i][j] * y[j][0];
        y[i][0] = Pb[i][0] - sum;
    }
    return y;
}

template<typename field>
LX::Matrix<field> backward_sub(LX::Matrix<field> U, LX::Matrix<field> y) {
    if (!(U.is_upper()) && (y.nrows() != U.nrows()))
        throw std::invalid_argument("Inadequate system.");
    LX::Matrix<field> x(U.size(), std::vector<field>(1, 0));
    for (int i = (int)U.nrows() - 1; i >= 0; i--) {
        field sum = 0;
        for (int j = i + 1; j < U.nrows(); j++)
            sum += U[i][j] * x[j][0];
        auto temp = (y[i][0] - sum) / U[i][i];
        x[i][0] = temp;
    }
    return x;
}

template<typename field>
LX::Matrix<field> top_left_pad(LX::Matrix<field> A, LX::Matrix<field> A_0) {
    for (size_t i{ 1 }; i < A.size(); i++) {
        for (size_t j{ 1 }; j < A.size(); j++)
            A[i][j] = A_0[i - 1][j - 1];
    }
    return  A;
}

template<typename field>
std::vector<LX::Matrix<field>> LUP_DEC(LX::Matrix<field> A) {
    if (A.det() == static_cast<field>(0))
        throw std::invalid_argument("Singular Matrix Passed.");
    LX::Matrix<field> L(A.size(), A.size());
    LX::Matrix<field> U(A.size(), A.size());
    LX::Matrix<field> P(A.size(), A.size());
    //Base Case.
    if (A.size() == 1) {
        L = { {static_cast<field>(1)} };
        U = A;
        P = { {static_cast<field>(1)} };
        return { L, U, P };
    }
    //Get the index of the maximum element in the first column.
    size_t max_index = A.max_column(0);
    //Prepare an adequate permutation matrix Q, which represents the swapping of the first row with the row containing the maximum element.
    LX::Matrix<field> Q(A.size(), std::vector<field>(A.size(), 0));
    for (size_t i{ 0 }; i < Q.size(); i++) Q[i][i] = static_cast<field>(1);
    std::swap(Q[0], Q[max_index]);
    //Swap the rows and store the result in a new matrix.
    LX::Matrix<field> QA = Q * A;
    //Partition the matrix as described in the factorization step of the LUP algorithm.
    field A_11 = QA[0][0];
    LX::Matrix<field> w(1, std::vector<field>(QA.size() - 1));
    LX::Matrix<field> v(QA.size() - 1, std::vector<field>(1));
    LX::Matrix<field> A_0(A.size() - 1, A.size() - 1);
    for (size_t i{ 1 }; i < QA.size(); i++)
        for (size_t j{ 1 }; j < QA.size(); j++)
            A_0[i - 1][j - 1] = QA[i][j];
    for (size_t k{ 1 }; k < QA.size(); k++)
        v[k - 1][0] = QA[k][0];
    for (size_t l{ 1 }; l < QA.size(); l++)
        w[0][l - 1] = QA[0][l];
    //Calculate schur_complement.
    LX::Matrix<field> vw = (v * w) * (static_cast<field>(1) / A_11);
    LX::Matrix<field> schur_complement = A_0 - (vw);
    //Prepare L, U, and P.
    P = LX::Matrix<field>(A.size(), std::vector<field>(A.size(), 0)); P[0][0] = static_cast<field>(1);
    L = LX::Matrix<field>(A.size(), std::vector<field>(A.size(), 0)); L[0][0] = static_cast<field>(1);
    U = LX::Matrix<field>(A.size(), std::vector<field>(A.size(), 0)); U[0][0] = A_11;
    //Recurse: Find an LUP decomposition for schur_complement.
    std::vector<LX::Matrix<field>> LUP_0 = LX::LUP_DEC<field>(schur_complement);
    //Combine and prepare L, U, and P.
    LX::Matrix<field> L_v = LUP_0[2] * v * (static_cast<field>(1) / A_11);
    for (size_t i{ 1 }; i < L.size(); i++)
        L[i][0] = L_v[i - 1][0];
    for (size_t i{ 1 }; i < U.size(); i++)
        U[0][i] = w[0][i - 1];
    L = LX::top_left_pad<field>(L, LUP_0[0]);
    U = LX::top_left_pad<field>(U, LUP_0[1]);
    P = LX::top_left_pad<field>(P, LUP_0[2]) * Q;
    //Return.
    return { L, U, P };
}

template<typename field>
LX::Matrix<field> SYSTEM_SOLVE(LX::Matrix<field> A, LX::Matrix<field> b) {
    auto lup = LX::LUP_DEC<field>(A);
    b = lup[2] * b;
    auto y = LX::forward_sub(lup[0], b);
    auto x = LX::backward_sub(lup[1], y);
    return x;
}
inline double abs(const double& a) { return std::abs(a); }
inline LX::Complex make_complex(double a, double b) { return LX::Complex(a, b); }




