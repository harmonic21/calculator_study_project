#include "equation_member.h"

namespace s21 {

    bool EquationMember::IsSign(EquationMember *member) {
        return member->GetValueType() == Utility::kMinus
               || member->GetValueType() == Utility::kPlus
               || member->GetValueType() == Utility::kMultiply
               || member->GetValueType() == Utility::kDivide
               || member->GetValueType() == Utility::kMod
               || member->GetValueType() == Utility::kPow
               || member->GetValueType() == Utility::kUnaryPlus
               || member->GetValueType() == Utility::kUnaryMinus;
    }

    bool EquationMember::IsFunction(EquationMember *member) {
        return member->GetValueType() == Utility::kCos
               || member->GetValueType() == Utility::kSin
               || member->GetValueType() == Utility::kTan
               || member->GetValueType() == Utility::kAcos
               || member->GetValueType() == Utility::kAsin
               || member->GetValueType() == Utility::kAtan
               || member->GetValueType() == Utility::kSqrt
               || member->GetValueType() == Utility::kLn
               || member->GetValueType() == Utility::kLog;
    }

    bool EquationMember::IsX(EquationMember* member) {
        return member->GetValueType() == Utility::kX;
    }

    long double EquationMember::Sum(long double a, long double b) {
        return a + b;
    }

    long double EquationMember::Sub(long double a, long double b) {
        return a - b;
    }

    long double EquationMember::Mul(long double a, long double b) {
        return a * b;
    }

    long double EquationMember::Del(long double a, long double b) {
        return a / b;
    }

    long double EquationMember::Pow(long double a, long double b) {
        return powl(a, b);
    }

    long double EquationMember::Mod(long double a, long double b) {
        return fmodl(a, b);
    }

    long double EquationMember::Cos(long double a) {
        return cosl(a);
    }

    long double EquationMember::Sin(long double a) {
        return sinl(a);
    }

    long double EquationMember::Tan(long double a) {
        return tanl(a);
    }

    long double EquationMember::Acos(long double a) {
        return acosl(a);
    }

    long double EquationMember::Asin(long double a) {
        return asinl(a);
    }

    long double EquationMember::Atan(long double a) {
        return atanl(a);
    }

    long double EquationMember::Sqrt(long double a) {
        return sqrtl(a);
    }

    long double EquationMember::Ln(long double a) {
        return logl(a);
    }

    long double EquationMember::Log(long double a) {
        return log10l(a);
    }

    void EquationMember::PrioritySelection() noexcept {
        int priority;
        if (value_type_ == Utility::kNumber || value_type_ == Utility::kX) {
            priority = 0;
        } else if (value_type_ == Utility::kRightBracket) {
            priority = -1;
        } else if (value_type_ == Utility::kLeftBracket) {
            priority = 1;
        } else if (value_type_ == Utility::kUnaryPlus || value_type_ == Utility::kPlus ||
                   value_type_ == Utility::kUnaryMinus || value_type_ == Utility::kMinus) {
            priority = 2;
        } else if (value_type_ == Utility::kMultiply || value_type_ == Utility::kDivide ||
                   value_type_ == Utility::kMod) {
            priority = 3;
        } else if (value_type_ == Utility::kPow) {
            priority = 4;
        } else {
            priority = 5;
        }
        this->priority_ = priority;
    }

    void EquationMember::OperationSelection() noexcept {
        switch (value_type_) {
            case Utility::kPlus:
            case Utility::kUnaryPlus:
                operation = Sum;
                break;
            case Utility::kMinus :
            case Utility::kUnaryMinus :
                operation = Sub;
                break;
            case Utility::kMultiply :
                operation = Mul;
                break;
            case Utility::kDivide :
                operation = Del;
                break;
            case Utility::kPow :
                operation = Pow;
                break;
            case Utility::kMod :
                operation = Mod;
                break;
            default:
                break;
        }
    }

    void EquationMember::FunctionSelection() noexcept {
        switch (value_type_) {
            case Utility::kCos :
                function = Cos;
                break;
            case Utility::kSin :
                function = Sin;
                break;
            case Utility::kTan :
                function = Tan;
                break;
            case Utility::kAcos :
                function = Acos;
                break;
            case Utility::kAsin :
                function = Asin;
                break;
            case Utility::kAtan :
                function = Atan;
                break;
            case Utility::kSqrt :
                function = Sqrt;
                break;
            case Utility::kLn :
                function = Ln;
                break;
            case Utility::kLog :
                function = Log;
                break;
            default:
                break;
        }
    }

}  //  namespace s21