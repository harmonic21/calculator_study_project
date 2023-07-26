#ifndef CPP3_SMARTCALC_V2_0_1_EQUATION_MEMBER_H
#define CPP3_SMARTCALC_V2_0_1_EQUATION_MEMBER_H

#include <string>
#include <cmath>

#include "../model/utility.h"

namespace s21 {

    class EquationMember {
     public:
        EquationMember() : operation(nullptr), function(nullptr), value_(0), priority_(-2), value_type_() {}

        EquationMember(long double value, Utility::OperationType type) :  operation(nullptr),
                                                                          function(nullptr),
                                                                          value_(value),
                                                                          priority_(-2),
                                                                          value_type_(type) {
           SelectionProcess();
        }

        EquationMember(EquationMember&& other) noexcept : EquationMember() {
            *this = std::move(other);
        }

        EquationMember& operator=(EquationMember&& c) noexcept {
            if (this != &c) {
                operation = c.operation;
                function = c.function;
                value_ = c.value_;
                priority_ = c.priority_;
                value_type_ = c.value_type_;
                delete &c;
            }
            return *this;
        }

        ~EquationMember() { }

        static bool IsSign(EquationMember *member);

        static bool IsFunction(EquationMember *member);

        static bool IsX(EquationMember* member);

        Utility::OperationType GetValueType() { return value_type_; }

        long double GetValue() const { return value_; }

        int GetPriority() const { return priority_; }

        void SetValue(long double value) { value_ = value; }

        void SetValueType(Utility::OperationType type) { value_type_ = type; }

        long double (*operation)(long double a, long double b);

        long double (*function)(long double a);

     private:
        static long double Sum(long double a, long double b);

        static long double Sub(long double a, long double b);

        static long double Mul(long double a, long double b);

        static long double Del(long double a, long double b);

        static long double Pow(long double a, long double b);

        static long double Mod(long double a, long double b);

        static long double Cos(long double a);

        static long double Sin(long double a);

        static long double Tan(long double a);

        static long double Acos(long double a);

        static long double Asin(long double a);

        static long double Atan(long double a);

        static long double Sqrt(long double a);

        static long double Ln(long double a);

        static long double Log(long double a);

        void PrioritySelection() noexcept;

        void FunctionSelection() noexcept;

        void OperationSelection() noexcept;

        void SelectionProcess() noexcept;

        long double value_;

        int priority_;

        Utility::OperationType value_type_;
    };

}  // namespace s21

#endif //CPP3_SMARTCALC_V2_0_1_EQUATION_MEMBER_H
