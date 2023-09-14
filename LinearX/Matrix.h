#pragma once
#include<vector>
template<typename field>
class Matrix {
protected:
    std::vector<std::vector<field>> entries;
    size_t rows;
    size_t columns;
public:
    //Matrices...
    //Constructors
    Matrix() : rows(0), columns(0) {}
    Matrix(size_t n, size_t m) : rows(n), columns(m), entries(n, std::vector<field>(m)) {}
    Matrix(const Matrix& other) : rows(other.rows), columns(other.columns), entries(other.entries) {}
    Matrix(Matrix&& other) noexcept : rows(other.rows), columns(other.columns), entries(std::move(other.entries)) {}
    Matrix(std::initializer_list<std::initializer_list<field>> entryini)
        : rows(entryini.size()), columns(entryini.begin()->size()), entries(entryini.size(), std::vector<field>(entryini.begin()->size())) {
        size_t i = 0;
        for (const auto& row : entryini) {
            if (row.size() != columns)
                throw std::invalid_argument("Dimensions didn't match.");
            entries[i] = row;
            i++;
        }
    }
    //Assignment operators
    Matrix<field>& operator=(Matrix&& other) noexcept {
        rows = other.rows;
        columns = other.columns;
        entries = std::move(other.entries);
        return *this;
    }
    Matrix<field> operator=(std::initializer_list<std::initializer_list<field>> entryini) {
        rows = entryini.size();
        columns = entryini.begin()->size();
        size_t i{ 0 };
        for (auto& elem : entryini) {
            if (elem.size() != columns)
                throw std::invalid_argument("Dimensions didn't match.");
            entries.emplace_back(std::vector<field>());
            entries[i] = elem;
            i++;
        }
        return *this;
    }
    Matrix<field> operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            columns = other.columns;
            entries = other.entries;
        }
        return *this;
    }
    //Matrix addition.
    Matrix<field> operator+(const Matrix& other) const {
        if ((rows != other.rows) || (columns != other.columns))
            throw std::invalid_argument("Dimensions didn't match.");
        Matrix result(rows, columns);
        for (size_t i{ 0 }; i < rows; i++)
            for (size_t j{ 0 }; j < columns; j++)
                result.entries[i][j] = entries[i][j] + other.entries[i][j];
        return result;
    }
    //Matrix subtraction.
    Matrix<field> operator-(const Matrix& other) const {
        if ((rows != other.rows) || (columns != other.columns))
            throw std::invalid_argument("Dimensions didn't match.");
        Matrix result(rows, columns);
        for (size_t i{ 0 }; i < rows; i++)
            for (size_t j{ 0 }; j < columns; j++)
                result.entries[i][j] = entries[i][j] - other.entries[i][j];
        return result;
    }
    //Scalar multiplication.
    Matrix<field> operator*(const field& constant) const {
        Matrix result(rows, columns);
        for (size_t i{ 0 }; i < rows; i++)
            for (size_t j{ 0 }; j < columns; j++)
                result.entries[i][j] = constant * entries[i][j];

        return result;
    }

    //Method to compute the trace of a square matrix (i.e the sum of diagonal entries)
    field trace() const {
        field trace{};
        if (rows != columns)    //Check if the matrix is squared
            throw std::invalid_argument("No trace.");
        for (size_t i{ 0 }; i < rows; i++)
            trace += entries[i][i];
        return trace;
    }

    //Method to compute the transpose of matrices
    Matrix<field> transpose() const {
        Matrix trans(rows, columns);
        for (size_t i{ 0 }; i < rows; i++)
            for (size_t j{ 0 }; j < columns; j++)
                trans.entries[i][j] = entries[j][i];
        return trans;
    }
    //Overloaded Matrix-scalar multiplication.
    friend Matrix<field> operator*(const field& constant, const Matrix<field>& other) {
        Matrix result(other.rows, other.columns);
        for (size_t i{ 0 }; i < other.rows; i++)
            for (size_t j{ 0 }; j < other.columns; j++)
                result.entries[i][j] = constant * other.entries[i][j];
        return result;
    }
    //Print Matrix
    friend std::ostream& operator<<(std::ostream& out, const Matrix<field>& other) {
        out << std::endl;
        for (size_t i{ 0 }; i < other.rows; i++) {
            out << "{ ";
            for (size_t j{ 0 }; j < other.columns; j++) {
                if (j != other.columns - 1)
                    out << other.entries[i][j] << "  ";
                else
                    out << other.entries[i][j];
            }
            out << " }" << std::endl;
        }
        return out;
    }

    //Comparision operators... (Unimportant for now...)
    bool operator==(const Matrix& other) const {
        if ((rows != other.rows) || (columns != other.columns))
            return false;
        return (entries == other.entries);
    }
    bool operator<(const Matrix& rhs) const noexcept {
        if ((rows != rhs.rows) || (columns != rhs.columns))
            return false;
        return (entries[0][0] < rhs.entries[0][0]);
    }

};
