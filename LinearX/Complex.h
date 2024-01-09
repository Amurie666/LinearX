#pragma once
class Complex {
private:
    double real;
    double imag;
public: 
    //Constructors
    Complex();
    Complex(double a, double b);
    Complex(double a);
    Complex(const Complex& other);
    Complex(Complex&& other) noexcept;
    //Assignment operators
    Complex operator=(const Complex& other);
    Complex& operator=(Complex&& other) noexcept;
    Complex operator+(const Complex& complex) const;
    Complex operator-(const Complex& complex) const;
    Complex operator*(const Complex& complex) const;
    Complex operator/(const Complex& complex) const;
    friend Complex operator/(double& a, const Complex& rhs);
    friend Complex operator*(double& a, const Complex& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Complex& obj);
    void operator+=(const Complex& rhs);
    //Comparision operators... (unimportant for now...)
    bool operator==(const Complex& rhs) const noexcept;
    bool operator!=(const Complex& rhs) const noexcept;
    bool operator<(const Complex& rhs) const noexcept;
    bool operator>(const Complex& rhs) const noexcept;
    friend double abs(const Complex& a);
};
