#pragma once
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
    Matrix(size_t n, std::vector<field> v) : rows(n), columns(v.size()), entries(n, v) {}
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
    size_t size() {
        if (rows == columns)
            return entries.size();
        return 0;
    }
    size_t max_column(size_t j) {
        std::vector<field> temp;
        for (size_t i{ 0 }; i < rows; i++) {
            temp.push_back(((*this)[i])[j]);
        }
        auto max = std::max_element(temp.begin(), temp.end(), [](field a, field b) {return abs(a) < abs(b); });
        if (max != temp.end())
            return std::distance(temp.begin(), max);
        return -1;
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
    Matrix<field> operator*(const Matrix<field>& rhs) const {
        if (columns != rhs.rows) throw std::invalid_argument("Error: Cannot perform multiplication.");
        Matrix<field> result(rows, rhs.columns);
        for (size_t i{ 0 }; i < rows; i++)
            for (size_t j{ 0 }; j < rhs.columns; j++) {
                result.entries[i][j] = static_cast<field>(0);
                for (size_t k{ 0 }; k < rhs.rows; k++)
                    result.entries[i][j] += entries[i][k] * rhs.entries[k][j];
            }
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
   
    typename std::vector<std::vector<field>>::iterator begin() { return entries.begin(); }
    typename std::vector<std::vector<field>>::iterator end() { return entries.end(); }

    inline std::vector<field>& operator[](size_t s) { return entries[s]; }
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
    Matrix<field> exclude() {

    }
    void erase_column(typename std::vector<field>::iterator it) {
        for (const auto& elem : entries) {
            elem.erase(it);
        }
        columns--;
    }
    void erase_column(size_t i) { 
        for (auto& elem : entries) {
            elem.erase(elem.begin() + i);
        }
        columns--; 
    }
    void erase_row(size_t i) { entries.erase(begin()+i); rows--; }
    void erase_row(typename std::vector<std::vector<field>>::iterator it) { entries.erase(it); rows--; }
    field det() {
        if (rows != columns)
            throw std::invalid_argument("Not a square matrix.");
        //Base case.
        if (rows == 2)
            return entries[0][0] * entries[1][1] - entries[0][1] * entries[1][0];
        if (rows == 1)
            return entries[0][0];
        //Recursion
        field sum{};
        for (size_t j{ 0 }; j < columns; j++) {
            Matrix<field> temp = *this;
            temp.erase_row(0);
            temp.erase_column(j);
            sum += ((j % 2) == 0) ? entries[0][j] * temp.det() : static_cast<field>(-1) * entries[0][j] * temp.det();
        }
        return sum;
    }
    bool is_lower() {
        if (rows != columns)
            return false;
        for (size_t i{ 0 }; i < rows; i++)
            for (size_t j{ i + 1 }; j < columns; j++)
                if (entries[i][j] != 0)
                    return false;
        return true; 
    }
    bool is_upper() {
        if (rows != columns)
            return false;
        for (size_t i{ 0 }; i < rows; i++)
            for (size_t j{ 0 }; j < i; j++)
                if (entries[i][j] != static_cast<field>(0))
                    return false;
        return true;
    }
    size_t nrows() { auto r = rows;  return r; }
    size_t ncolumns() { auto n = columns; return n; }


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
