#include"LinearX.h"
LX::Complex::Complex() : real(0.0), imag(0.0) {}
LX::Complex::Complex(double a, double b) : real(a), imag(b) {}
LX::Complex::Complex(double a) : Complex(a, 0) {}
LX::Complex::Complex(const Complex& other) : real(other.real), imag(other.imag) {}
LX::Complex::Complex(Complex&& other) noexcept : real(other.real), imag(other.imag) {}
LX::Complex LX::Complex::operator=(const Complex& other) {
    real = other.real;
    imag = other.imag;
    return *this;
}
LX::Complex& LX::Complex::operator=(Complex&& other) noexcept {
    imag = other.imag;
    real = other.real;
    return *this;
}
LX::Complex LX::Complex::operator+(const Complex& complex) const {
    return Complex(real + complex.real, imag + complex.imag);
}
LX::Complex LX::Complex::operator-(const Complex& complex) const {
    return Complex(real - complex.real, imag - complex.imag);
}
LX::Complex LX::Complex::operator*(const Complex& complex) const {
    return Complex((real * complex.real) - (imag * complex.imag), (real * complex.imag) + (imag * complex.real));
}
LX::Complex LX::Complex::operator/(const Complex& complex) const {
    double denominator = (complex.real * complex.real) + (complex.imag * complex.imag);
    if (denominator == 0)
        throw std::invalid_argument("Cannot divide by 0.");
    const double constant = 1.0 / denominator;
    Complex conjugate = Complex(complex.real, -complex.imag);
    return Complex(((*this) * conjugate).real * constant, ((*this) * conjugate).imag * constant);
}
LX::Complex LX::operator/(double& a, const LX::Complex& rhs) {
    return LX::Complex(a, 0) / rhs;
}
LX::Complex LX::operator*(double& a, const LX::Complex& rhs) {
    return LX::Complex(a, 0) * rhs;
}
std::ostream& LX::operator<<(std::ostream& out,  const LX::Complex& obj) {
    out << "(" << obj.real << " + " << obj.imag << "i" << ")";
    return out;
}
void LX::Complex::operator+=(const Complex& rhs) { *this = *this + rhs;}
bool LX::Complex::operator==(const Complex& rhs) const noexcept { return ((real == rhs.real) && (imag == rhs.imag));}
bool LX::Complex::operator!=(const Complex& rhs) const noexcept { return ((real != rhs.real) || (imag != rhs.imag)); }
bool LX::Complex::operator<(const Complex& rhs) const noexcept { return (std::sqrt(real * real + imag * imag) < std::sqrt(rhs.real * rhs.real + rhs.imag * rhs.imag));}
bool LX::Complex::operator>(const Complex& rhs) const noexcept { return (std::sqrt(real * real + imag * imag) > std::sqrt(rhs.real * rhs.real + rhs.imag * rhs.imag));}
double LX::abs(const LX::Complex& a) { return std::sqrt(a.real * a.real + a.imag * a.imag); }
