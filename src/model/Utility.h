#ifndef CPP3_SMARTCALC_V2_0_1_UTILITY_H
#define CPP3_SMARTCALC_V2_0_1_UTILITY_H

#include <map>
#include <string>

namespace s21 {
    class Utility {
    public:
        Utility() = default;
        ~Utility() = default;

        enum OperationType {
            NUMBER,
            X,
            RIGHT_BRACKET,
            LEFT_BRACKET,
            MINUS,
            UNARY_MINUS,
            PLUS,
            UNARY_PLUS,
            MULTIPLY,
            DIVIDE,
            MOD,
            POW,
            COS,
            SIN,
            TAN,
            ACOS,
            ASIN,
            ATAN,
            SQRT,
            LN,
            LOG
        };

        OperationType s21_get_operation_type(const std::string &operation_type) {
            return _operation[operation_type];
        }

        OperationType s21_get_function_type(const std::string &function_type) {
            return _function[function_type];
        }

        bool s21_is_function_string(const std::string &str) {
            return _function.count(str) > 0;
        }

        bool s21_is_operation_string(const std::string &str) {
            return _operation.count(str) > 0;
        }

        bool s21_is_number(const std::string& str) {
            return str.find_first_not_of("1234567890.") == std::string::npos;
        }

        bool s21_is_x(const std::string& str) {
            return str == "x" || str == "X";
        }

        bool s21_is_dot(const std::string& str) {
            return str == ".";
        }

        bool s21_is_left_bracket(const std::string& str) {
            return str == "(";
        }

        bool s21_is_right_bracket(const std::string& str) {
            return str == ")";
        }

    private:

        std::map<std::string, OperationType> _function = {
                {"cos",  COS},
                {"sin",  SIN},
                {"tan",  TAN},
                {"acos", ACOS},
                {"asin", ASIN},
                {"atan", ATAN},
                {"sqrt", SQRT},
                {"ln",   LN},
                {"log",  LOG},
                {"mod",  MOD}
        };

        std::map<std::string, OperationType> _operation = {
                {"+", PLUS},
                {"-", MINUS},
                {"*", MULTIPLY},
                {"/", DIVIDE},
                {"^", POW},
        };
    };

}  // namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_UTILITY_H
