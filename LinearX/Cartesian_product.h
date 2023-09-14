#pragma once
// Ex 21 of section 1.2
template<typename field, template<typename field> typename V, template<typename field> typename W>
class CartesianProduct {
private:
    V<field> v;
    W<field> w;
public:
    //Cartesian Product...
    CartesianProduct() {}
    CartesianProduct(V<field> vector1, W<field> vector2) : v(vector1), w(vector2) {}
    CartesianProduct(const CartesianProduct& other) : v(other.v), w(other.w) {}
    CartesianProduct(CartesianProduct&& other) noexcept : v(std::move(other.v)), w(std::move(other.w)) {}
    //Assignments...
    CartesianProduct operator=(const CartesianProduct& other) {
        v = other.v;
        w = other.w;
        return *this;
    }
    CartesianProduct& operator=(CartesianProduct&& other) noexcept {
        v = std::move(other.v);
        w = std::move(other.w);
        return *this;
    }
    CartesianProduct operator+(const CartesianProduct& vector) const {
        return CartesianProduct(v + vector.v, w + vector.w);
    }
    CartesianProduct operator*(const field& scalar) const {
        return CartesianProduct(v * scalar, w * scalar);
    }
    //Print...
    friend std::ostream& operator<<(std::ostream& out, const CartesianProduct<field, V, W>& temp) {
        out << "(" << temp.v << ", " << temp.w << ")" << std::endl;
        return out;
    }

};