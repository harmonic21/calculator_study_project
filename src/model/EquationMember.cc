#include "EquationMember.h"

namespace s21 {

    long double EquationMember::s21_sum(long double a, long double b) {
        return a + b;
    }

    long double EquationMember::s21_sub(long double a, long double b) {
        return a - b;
    }

    long double EquationMember::s21_mul(long double a, long double b) {
        return a * b;
    }

    long double EquationMember::s21_del(long double a, long double b) {
        return a / b;
    }

    long double EquationMember::s21_pow(long double a, long double b) {
        return powl(a, b);
    }

    long double EquationMember::s21_mod(long double a, long double b) {
        return fmodl(a, b);
    }

    long double EquationMember::s21_cos(long double a) {
        return cosl(a);
    }

    long double EquationMember::s21_sin(long double a) {
        return sinl(a);
    }

    long double EquationMember::s21_tan(long double a) {
        return tanl(a);
    }

    long double EquationMember::s21_acos(long double a) {
        return acosl(a);
    }

    long double EquationMember::s21_asin(long double a) {
        return asinl(a);
    }

    long double EquationMember::s21_atan(long double a) {
        return atanl(a);
    }

    long double EquationMember::s21_sqrt(long double a) {
        return sqrtl(a);
    }

    long double EquationMember::s21_ln(long double a) {
        return logl(a);
    }

    long double EquationMember::s21_log(long double a) {
        return log10l(a);
    }

    void EquationMember::s21_priority_selection() noexcept {
        int priority;
        if (_operationType == Utility::NUMBER || _operationType == Utility::X) {
            priority = 0;
        } else if (_operationType == Utility::RIGHT_BRACKET) {
            priority = -1;
        } else if (_operationType == Utility::LEFT_BRACKET) {
            priority = 1;
        } else if (_operationType == Utility::UNARY_PLUS  || _operationType == Utility::PLUS ||
                   _operationType == Utility::UNARY_MINUS || _operationType == Utility::MINUS) {
            priority = 2;
        } else if (_operationType == Utility::MULTIPLY || _operationType == Utility::DIVIDE ||
                   _operationType == Utility::MOD) {
            priority = 3;
        } else if (_operationType == Utility::POW) {
            priority = 4;
        } else {
            priority = 5;
        }
        this->_priority = priority;
    }

    void EquationMember::s21_operation_selection() noexcept {
        switch (_operationType) {
            case Utility::PLUS:
            case Utility::UNARY_PLUS:
                operation = s21_sum;
                break;
            case Utility::MINUS :
            case Utility::UNARY_MINUS :
                operation = s21_sub;
                break;
            case Utility::MULTIPLY :
                operation = s21_mul;
                break;
            case Utility::DIVIDE :
                operation = s21_del;
                break;
            case Utility::POW :
                operation = s21_pow;
                break;
            case Utility::MOD :
                operation = s21_mod;
                break;
            default:
                break;
        }
    }

    void EquationMember::s21_function_selection() noexcept {
        switch (_operationType) {
            case Utility::COS :
                function = s21_cos;
                break;
            case Utility::SIN :
                function = s21_sin;
                break;
            case Utility::TAN :
                function = s21_tan;
                break;
            case Utility::ACOS :
                function = s21_acos;
                break;
            case Utility::ASIN :
                function = s21_asin;
                break;
            case Utility::ATAN :
                function = s21_atan;
                break;
            case Utility::SQRT :
                function = s21_sqrt;
                break;
            case Utility::LN :
                function = s21_ln;
                break;
            case Utility::LOG :
                function = s21_log;
                break;
            default:
                break;
        }
    }


    bool EquationMember::s21_is_sign(EquationMember *member) {
        return member->s21_get_value_type() == Utility::MINUS
               || member->s21_get_value_type() == Utility::PLUS
               || member->s21_get_value_type() == Utility::MULTIPLY
               || member->s21_get_value_type() == Utility::DIVIDE
               || member->s21_get_value_type() == Utility::MOD
               || member->s21_get_value_type() == Utility::POW
               || member->s21_get_value_type() == Utility::UNARY_PLUS
               || member->s21_get_value_type() == Utility::UNARY_MINUS;
    }

    bool EquationMember::s21_is_function(EquationMember *member) {
        return member->s21_get_value_type() == Utility::COS
               || member->s21_get_value_type() == Utility::SIN
               || member->s21_get_value_type() == Utility::TAN
               || member->s21_get_value_type() == Utility::ACOS
               || member->s21_get_value_type() == Utility::ASIN
               || member->s21_get_value_type() == Utility::ATAN
               || member->s21_get_value_type() == Utility::SQRT
               || member->s21_get_value_type() == Utility::LN
               || member->s21_get_value_type() == Utility::LOG;
    }
}