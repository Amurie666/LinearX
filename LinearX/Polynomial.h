#pragma once

#include "Tuple.h"
template<typename field>
class Polynomial : public Tuple<field> {
public:
    using Tuple<field>::dimension;
    using Tuple<field>::entries;
    //Constructors
    Polynomial() : Tuple<field>() {}
    Polynomial(const Polynomial& other) : Tuple<field>(other) {}
    Polynomial(size_t n) : Tuple<field>(n + 1) { dimension = n; }
    Polynomial(Polynomial&& other) noexcept : Tuple<field>(other) {}
   
    //Assignement operators
    Polynomial operator=(std::initializer_list<field> entryini) {
        size_t i{ 0 };
        for (const auto& elem : entryini) {
            if (i < dimension + 1) {
                entries[i] = elem;
                i++;
            }
            else
                entries[i - 1] += elem;
        }
        return *this;
    }
    Polynomial& operator=(Polynomial&& other) noexcept {
        entries = std::move(other.entries);
        dimension = other.dimension;
        return *this;
    }  
    Polynomial operator=(const Polynomial& other) {
        dimension = other.dimension;
        entries = other.entries;
        return *this;
    }

    //Polynomial addition
    Polynomial operator+(const Polynomial& other) const {
        size_t deg = std::max(dimension, other.dimension);
        Polynomial result(deg);
        for (size_t i = 0; i <= dimension; i++) {
            result.entries[i + (deg - dimension)] = entries[i];
        }
        for (size_t i = 0; i <= other.dimension; i++) {
            result.entries[i + (deg - other.dimension)] += other.entries[i];
        }
        return result;
    }

    //Polynomial subtraction.
    Polynomial operator-(const Polynomial& other) const {
        size_t deg = std::max(dimension, other.dimension);
        Polynomial result(deg);

        for (size_t i = 0; i <= dimension; i++) {
            result.entries[i + (deg - dimension)] = entries[i];
        }

        for (size_t i = 0; i <= other.dimension; i++) {
            result.entries[i + (deg - other.dimension)] -= other.entries[i];
        }
        return result;
    }

    //Scalar multiplication.
    Polynomial operator*(field constant) const {
        Polynomial result(dimension);
        for (size_t i{ 0 }; i < dimension; i++)
            result.entries[i] = entries[i] * constant;
        return result;
    }
    friend Polynomial<field> operator*(field constant, const Polynomial<field>& other) {
        Polynomial result(other.dimension);
        for (size_t i{ 0 }; i < other.dimension; i++)
            result.entries[i] = constant * other.entries[i];
        return result;
    }
    //Print Polynomial.
    friend std::ostream& operator<<(std::ostream& out, const Polynomial<field>& other) {
        out << "(";
        for (size_t i{ 0 }; i <= other.dimension; i++) {
            if (i == other.dimension)
                out << other.entries[i];
            else
                out << other.entries[i] << "x^" << other.dimension - i << " + ";
        }
        out << ")";
        return out;
    }
};