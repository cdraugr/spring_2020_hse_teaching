#include <cstdint>
#include <iostream>
#include <numeric>  // for gcd
#include <stdexcept>

/* https://en.cppreference.com/w/cpp/language/operators */

class Rational {
public:
    using i32 = std::int32_t;

    Rational(i32 numerator = 0, i32 denominator = 1)
        : numerator_{denominator < 0 ? -numerator : numerator},
            denominator_{denominator < 0 ? -denominator : denominator} {
            if (!denominator) {
                throw std::overflow_error("Divide by zero.");
            }
            normalize();
        }

    i32 numerator() const noexcept {
        return numerator_;
    }

    i32 denominator() const noexcept {
        return denominator_;
    }

    Rational& operator+=(const Rational& other) noexcept {
        numerator_ = numerator() * other.denominator() +
                    other.numerator() * denominator();
        denominator_ *= other.denominator();
        normalize();
        return *this;
    }

    friend Rational operator+(Rational left, const Rational& right) noexcept {
        left += right;
        return left;
    }

    Rational& operator++() noexcept {  // ++rational;
        numerator_ += denominator();
        return *this;
    }

    Rational operator++(int) noexcept {  // rational++;
        Rational tmp(*this);
        operator++();
        return tmp;
    }

    Rational operator+() const noexcept {  // +rational;
        return *this;
    }

    Rational operator-() const noexcept {  // -rational;
        return {-numerator(), denominator()};
    }

private:
    void normalize() {
        auto gcd = std::gcd(numerator(), denominator());
        numerator_ /= gcd;
        denominator_ /= gcd;
    }

    i32 numerator_{}, denominator_{};
};

std::ostream& operator<<(std::ostream& out, const Rational& rational) noexcept {
   return out << rational.numerator() << " / " << rational.denominator() ;
}

bool operator==(const Rational& left, const Rational& right) noexcept {
    return left.numerator() == right.numerator() &&
            left.denominator() == right.denominator();
}

bool operator!=(const Rational& left, const Rational& right) noexcept {
    return !(left == right);
}
