#ifndef CPP3_SMARTCALC_V2_0_1_EQUATIONMEMBER_H
#define CPP3_SMARTCALC_V2_0_1_EQUATIONMEMBER_H

#include <string>
#include <cmath>

#include "../model/Utility.h"

namespace s21 {
    class EquationMember {
    public:

        long double (*operation)(long double a, long double b);

        long double (*function)(long double a);

        EquationMember() = delete;

        EquationMember(long double value, Utility::OperationType type) : _value(value),
                                                                _operationType(type),
                                                                operation(nullptr),
                                                                function(nullptr),
                                                                _priority(-2) {
            s21_priority_selection();
            s21_function_selection();
            s21_operation_selection();
        }

        Utility::OperationType s21_get_value_type() { return _operationType; }

        long double s21_get_value() const { return _value; }

        int s21_get_priority() const { return _priority; }

        static bool s21_is_sign(EquationMember *member);

        static bool s21_is_function(EquationMember *member);

        static long double s21_sum(long double a, long double b);

        static long double s21_sub(long double a, long double b);

        static long double s21_mul(long double a, long double b);

        static long double s21_del(long double a, long double b);

        static long double s21_pow(long double a, long double b);

        static long double s21_mod(long double a, long double b);

        static long double s21_cos(long double a);

        static long double s21_sin(long double a);

        static long double s21_tan(long double a);

        static long double s21_acos(long double a);

        static long double s21_asin(long double a);

        static long double s21_atan(long double a);

        static long double s21_sqrt(long double a);

        static long double s21_ln(long double a);

        static long double s21_log(long double a);

    private:
        long double _value;

        Utility::OperationType _operationType;

        int _priority;

        void s21_priority_selection() noexcept;

        void s21_function_selection() noexcept;

        void s21_operation_selection() noexcept;
    };

}  // namespace s21

#endif //CPP3_SMARTCALC_V2_0_1_EQUATIONMEMBER_H
