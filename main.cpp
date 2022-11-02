#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>


using namespace std;

class Complex{
private:
    double m_real, m_img;
public:
  explicit Complex(double real, char oper, double img) 
      : m_real(real), m_img(oper == '-' ? -img : img) {}

  friend ostream& operator<<(ostream& os, const Complex& num);

  Complex operator+(const Complex& add){
    double resImg = m_img + add.m_img;
    cout << "!!! " << (double)(m_real + add.m_real) << " " << (double)resImg << endl;
    return Complex(m_real + add.m_real, resImg < 0 ? '-' : '+', abs(resImg));
  }

  Complex operator-(const Complex& add){
    double resImg = m_img - add.m_img;
    return Complex(m_real - add.m_real, resImg < 0 ? '-' : '+', abs(resImg));
  }

  Complex operator*(const Complex& add){
    double resImg = m_real * add.m_img + add.m_real * m_img;
    return Complex(m_real * add.m_real - m_img * add.m_img, resImg < 0 ? '-' : '+', 
                      abs(resImg));
  }

  Complex operator/(const Complex& add){
    double resImg = (add.m_real * m_img - m_real * add.m_img)/
                    (add.m_real * add.m_real + add.m_img * add.m_img);

    return Complex((m_real * add.m_real + m_img * add.m_img)/
                    (add.m_real * add.m_real + add.m_img * add.m_img), 
                    resImg < 0 ? '-' : '+',
                    abs(resImg));
  }
};

template <typename T>
string roundDouble(T num, int precision = 2){
    string str(std::to_string(num));
    {
        auto dotIt = std::find(str.begin(), str.end(), '.');
        if((dotIt + precision) < str.end()){
            if((dotIt + precision + 1) != str.end() && 
                *(dotIt + precision + 1) > '4')
                if(*(dotIt + precision)
            str.erase(dotIt + precision, str.end());
        }
    }
    return str;
}

ostream& operator<<(ostream& os, const Complex& num){
    if(num.m_img == 0 && num.m_real == 0)
        os << 0;
    if(num.m_real != 0)
        os << roundDouble(num.m_real);
    if(num.m_img != 0){
        if(num.m_real != 0)
            os << (num.m_img > 0 ? " + " : " - ");
        os << (num.m_img > 0.0 ? roundDouble(num.m_img) : roundDouble(-num.m_img)) << "i";
    }
    return os;
}

int main(){
// Test input:
// 64.42 - 74.83i
// -55.85 + 55.34i

// Correct output:
// addition: 8.57 - 19.49i
// subtraction: 120.27 - 130.17i
// product: 543.24 + 7744.26i
// quotient: -1.25 + 0.1i

    Complex c1(64.44, '-', 74.84), c2(-55.87, '+', 55.35);
    cout << c1 << endl << c2 << endl;
    cout << "addition: " << c1 + c2 << "\nsubtraction: " << c1 - c2 << 
        "\nproduct: " << c1 * c2 << "\nquotient " << c1 / c2;
}