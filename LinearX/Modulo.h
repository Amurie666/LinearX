#pragma once
template<int N>
class Zmod {
private:
	int val;
public:
	Zmod() : val(0) {}
	Zmod(int v) : val(v) { if ((v > N) || (-1 * v > N)) throw std::invalid_argument("Invalid instantiation."); }
	Zmod(const Zmod<N>& other) : val(other.val) {}
	Zmod(Zmod&& other) noexcept : val(other.val) {}

	//Assignments
	Zmod<N>  operator=(int v) {
		if ((v > N) || (-v > N))
			throw std::invalid_argument("Invalid assignment.");
		val = v;
		return *this;
	}

	Zmod& operator=(int&& v) noexcept {
		if ((v > N) || (-v > N))
			val = v % N;
		else
			val = v;
		return *this;
	}

	Zmod operator=(const Zmod<N>& other) {
		if ((other.val > N) || (-1 * (other.val) > N))
			throw std::invalid_argument("Invalid assignment.");
		val = other.val;
		return *this;
	}

	Zmod& operator=(const Zmod<N>&& other) noexcept {
		if ((other.val > N) || (-1 * (other.val) > N))
			val = other.val % N;
		else
			val = other.val;
		return *this;
	}
	//Addition
	Zmod operator+(const Zmod<N>& other) const {
		return Zmod((val + other.val) % N);
	}
	//Subtraction
	Zmod operator-(const Zmod<N>& other) const {
		return Zmod((val - other.val) % N);
	}
	//Multiplication
	Zmod operator*(const Zmod<N>& other) const {
		return Zmod((val * other.val) % N);
	}
	//Division
	Zmod operator/(const Zmod<N>& other) const {
		if ((other.val == 0) || (MultiplicativeInverse(other.val) == 0))
			throw std::invalid_argument("Cannot perform division.");
		return Zmod((val * MultiplicativeInverse(other.val)) % N);
	}

	int gcd(int x, int y) const {
		for (int i{ std::max(x, y) }; i >= 1; i--) {
			if ((x % i == 0) && (y % i == 0))
				return i;
		}
		return 0;
	}
	//Compute the MultiplicativeInverse
	int MultiplicativeInverse(int n) const {
		int temp{ 0 };
		if ((gcd(n, N) != 1) || (gcd(n, N) == 0))
			throw std::invalid_argument("Cannot perform division.");
		for (int i{ 1 }; i < n; i++)
			if (((n * i) % N) == 1) {
				temp = i;
				break;
			}
		return temp;
	}

	friend std::ostream& operator<<(std::ostream& out, const Zmod<N>& obj) {
		out << obj.val;
		return out;
	}

	//Comparision operators... (unimportant for now...)
	bool operator==(const Zmod<N>& rhs) const noexcept {
		return (val == rhs.val);
	}
	bool operator<(const Zmod<N>& rhs) const noexcept {
		return (val < rhs.val);
	}
	friend double abs(const Zmod<N>& a) { return std::abs(a.val); }
};
