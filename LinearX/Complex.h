#pragma once
#include<cmath>
class Complex {
private:
    double real;
    double imag;
public:
    //Constructors
    Complex() : real(0.0), imag(0.0) {}
    Complex(double a, double b) : real(a), imag(b) {}
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}
    Complex(Complex&& other) noexcept : real(other.real), imag(other.imag) {}
    //Assignment operators
    Complex operator=(const Complex& other) {
        real = other.real;
        imag = other.imag;
        return *this;
    }
    Complex& operator=(Complex&& other) noexcept {
        imag = other.imag;
        real = other.real;
        return *this;
    }
    Complex operator+(const Complex& complex) const {
        return Complex(real + complex.real, imag + complex.imag);
    }

    Complex operator-(const Complex& complex) const {
        return Complex(real - complex.real, imag - complex.imag);
    }

    Complex operator*(const Complex& complex) const {
        return Complex((real * complex.real) - (imag * complex.imag), (real * complex.imag) + (imag * complex.real));
    }
    Complex operator/(const Complex& complex) const {
        double denominator = (complex.real * complex.real) + (complex.imag * complex.imag);
        if (denominator == 0)
            throw std::invalid_argument("Cannot divide by 0.");
        const double constant = 1.0 / denominator;
        Complex conjugate = Complex(complex.real, -complex.imag);
        return Complex(((*this) * conjugate).real * constant, ((*this) * conjugate).imag * constant);
    }
    friend std::ostream& operator<<(std::ostream& out, const Complex& obj) {
        out << "(" << obj.real << " + " << obj.imag << "i" << ")";
        return out;
    }

    //Comparision operators... (unimportant for now...)
    bool operator==(const Complex& rhs) const noexcept {
        return ((real == rhs.real) && (imag == rhs.imag));
    }
    bool operator<(const Complex& rhs) const noexcept {
        return (std::sqrt(real * real + imag * imag) < std::sqrt(rhs.real * rhs.real + rhs.imag * rhs.imag));
    }
    bool operator>(const Complex& rhs) const noexcept {
        return (std::sqrt(real * real + imag * imag) > std::sqrt(rhs.real * rhs.real + rhs.imag * rhs.imag));
    }
};
