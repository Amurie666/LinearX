#pragma once
//Exercise 31 of section1.3
//This needs a ton of editing
template<typename field, template <typename field> typename vector>
class QuotientSpace {
private:
    vector<field> v;
    std::set<vector<field>> coset;
    std::set<vector<field>> subspace;
   
public:
    //Constructors...
    QuotientSpace(){}
    QuotientSpace(const std::set<vector<field>>& elements = std::set<vector<field>>(), const vector<field>& v_0 = vector<field>()) : subspace(elements), v(v_0) { 
        //prepare subspace...
        subspace.insert(vector<field>());
        std::set<vector<field>> temp = subspace;
        for (const auto& elem : subspace) 
            for (const auto& elem2 : subspace)
                temp.insert(elem + elem2);
        subspace = temp;
        //prepare the corresponding coset...
        for (const auto& elem3 : subspace)
            coset.insert(elem3 + v);
    }
    QuotientSpace(const QuotientSpace& other) : subspace(other.subspace), coset(other.coset), v(other.v) {}
    
    //Create a new coset...
    QuotientSpace operator+(const vector<field>& v_0) {
        return QuotientSpace(subspace, v_0);
    }
    //Add cosets...
    QuotientSpace operator+(const QuotientSpace& other) {
        if (subspace != other.subspace)
            throw std::invalid_argument("Cannot add cosets of different subspaces.");
        return QuotientSpace(subspace, v + other.v);
    }
    //Cosets scalar-multiplication...
    QuotientSpace operator*(const field& c) {
        return QuotientSpace(subspace, v * c);
    }
    //Overloaded addition...
    friend QuotientSpace<field, vector> operator+(const vector<field>& v_0, const QuotientSpace<field, vector>& other) {
        return other + v_0;
    }
    //Overloaded multiplication...
    friend QuotientSpace<field, vector> operator*(const field& c, const QuotientSpace<field, vector>& other) {
        return other * c;
    }
    //For testing purposes only... .
    friend std::ostream& operator<<(std::ostream& out, const QuotientSpace& other) {
        out << "\n Coset: {";
        for (const auto& elem : other.coset)
            out << elem << " ";
        out << "}";
        return out;
   }
};
