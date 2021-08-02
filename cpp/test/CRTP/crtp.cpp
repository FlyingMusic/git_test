//  The Curiously Recurring Template Pattern (CRTP)

#include <iostream>
#include <cmath>
#include <cassert>
#include <string>
using namespace std;

template <class T>
struct Expression
{
    const T& cast() const {
        return static_cast<const T&>(*this);
    }

    T& cast() {
        return static_cast<T&>(*this);
    }
    // expands derived class interface by inheriting from the base class
    void set_absolute_value() {
        cast().set_value(abs(cast().get_value()));
    }

    double value() const {
        return cast().get_value();
    }

    double result() const {
        return cast().get_result();
    }

    void calc() {
        cast().sub_calc();
    }

    Expression& operator=(const Expression&) = delete;

private:
    Expression(){}
    friend T;
};

struct Square : public Expression<Square>
{
    Square(double val = 0, double res = 0):val_(val),result_(res){}
    void set_value(const double& val) {
        val_ = val;
    }
    double get_value() const {
        return val_;
    }

    double get_result() const {
        return result_;
    }

    void sub_calc() {
        result_ = val_*val_;
    }
private:
    double val_;
    double result_;
};

struct Sqrt : public Expression<Sqrt>
{
    Sqrt(double val = 0, double res = 0) :val_(val), result_(res) {}
    void set_value(const double& val) {
        val_ = val;
    }
    double get_value() const {
        return val_;
    }

    double get_result() const {
        return result_;
    }

    void sub_calc() {
        assert(val_>=0);
        result_ = sqrt(val_);
    }
private:
    double val_;
    double result_;
};

// Static interfaces
template<class T> // T is deduced at compile-time
void OP(Expression<T> &sq, const string& op) {
    // will do static dispatch
    cout << "Berfore OP this expression's value is:" << sq.value() << "\n";
    sq.calc();
    cout << "After OP "<< op <<\
        ",  this expression's result is:" << sq.result() << "\n";
}

int main() {
    Sqrt sqr(-2);
    cout << "this expression's value is:" << sqr.value() << "\n";
    // Adding functionality
    sqr.set_absolute_value();
    cout << "After set absolute,  this expression's value is:" << sqr.value() << "\n";
    OP(sqr, "Sqrt");
    cout << "---------------------------\n";
    Square sq(-2);
    OP(sq, "Square");

    return 0;
}
