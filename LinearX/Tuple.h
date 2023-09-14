#pragma once
#include<vector>
template<typename field>
class Tuple {
protected:
    size_t dimension;
    std::vector<field> entries;
public:
    //Constructors
    Tuple() : dimension(0) {}
    Tuple(size_t n) : dimension(n), entries(std::vector<field>(n)) {}
    Tuple(const Tuple& other) : dimension(other.dimension), entries(other.entries) {}
    Tuple(Tuple&& other) noexcept : dimension(other.dimension), entries(std::move(other.entries)) {}
    Tuple(std::initializer_list<field> entryini) : entries(entryini), dimension(entryini.size()) {}

    //Assignment operators
    
    Tuple& operator=(Tuple&& other) noexcept {
        dimension = other.dimension;
        entries = std::move(other.entries);
        return *this;
    }
    
    Tuple operator=(const Tuple& other) {
        dimension = other.dimension;
        entries = other.entries;
        return *this;
    }
    
    Tuple operator=(std::initializer_list<field> entryini) {
        entries = entryini;
        dimension = entryini.size();
        return *this;
    }
    //Tuple addition
    Tuple operator+(const Tuple& other) const {
        if (dimension != other.dimension)
            throw std::invalid_argument("Cannot add vectors of different dimensions.");
        Tuple result(dimension);
        for (size_t i{ 0 }; i < dimension; i++)
            result.entries[i] = entries[i] + other.entries[i];
        return result;
    }
    //Tuple subtraction
    Tuple operator-(const Tuple& other) const {
        if (dimension != other.dimension)
            throw std::invalid_argument("Cannot subtract vectors of different dimensions.");
        Tuple<field> result(dimension);
        for (size_t i{ 0 }; i < dimension; i++)
            result.entries[i] = entries[i] - other.entries[i];
        return result;
    }
    //Scalar multiplication.
    Tuple operator*(field constant) const {
        Tuple<field> result(dimension);
        for (size_t i{ 0 }; i < dimension; i++)
            result.entries[i] = entries[i] * constant;
        return result;
    }
    //Overloaded scalar multiplication.
    friend Tuple<field> operator*(field constant, const Tuple<field>& other) {
        Tuple<field> result(other.dimension);
        for (size_t i{ 0 }; i < other.dimension; i++)
            result.entries[i] = constant * other.entries[i];
        return result;
    }

    //Print tuple.
    friend std::ostream& operator<<(std::ostream& out, const Tuple<field>& other) {
        out << "(";
        for (size_t i{ 0 }; i < other.dimension; i++) {
            if (i == other.dimension - 1)
                out << other.entries[i];
            else
                out << other.entries[i] << ", ";
        }
        out << ")";
        return out;
    }
};