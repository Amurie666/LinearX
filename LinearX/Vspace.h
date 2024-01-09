//Ignore this! just an idea for now.
#pragma once
class Matrix;
template<typename field>
class Vspace {
public:
	virtual Vspace* operator+(const Vspace& rhs) = 0;
	virtual Vspace* operator-(const Vspace& rhs) = 0;
	virtual Vspace* operator+(field& rhs) = 0;
	virtual Matrix<field> equate(Vspace) = 0;
	bool is_combo(const Vspace& vec1, const Vspace& vec2) {
	//	equate(vec1 + vec2);
	}
};
