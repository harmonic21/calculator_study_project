#ifndef CPP3_SMARTCALC_V2_0_1_UTILITY_H
#define CPP3_SMARTCALC_V2_0_1_UTILITY_H

#include <map>
#include <string>

namespace s21 {

    class Utility {
     public:
        enum OperationType {
            kNumber,
            kX,
            kRightBracket,
            kLeftBracket,
            kMinus,
            kUnaryMinus,
            kPlus,
            kUnaryPlus,
            kMultiply,
            kDivide,
            kMod,
            kPow,
            kCos,
            kSin,
            kTan,
            kAcos,
            kAsin,
            kAtan,
            kSqrt,
            kLn,
            kLog
        };

        Utility() = default;
        ~Utility() = default;

        static bool IsNumber(const std::string& str) {
            return str.find_first_not_of("1234567890.") == std::string::npos;
        }

        static bool IsX(const std::string& str) {
            return str == "x" || str == "kX";
        }

        static bool IsDot(const std::string& str) {
            return str == ".";
        }

        static bool IsLeftBracket(const std::string& str) {
            return str == "(";
        }

        static bool IsRightBracket(const std::string& str) {
            return str == ")";
        }

        static bool IsUnaryOperation(const std::string& str) {
            return str == "-" || str == "+";
        }

        OperationType GetOperationType(const std::string &operation_type) {
            return operation_[operation_type];
        }

        OperationType GetFunctionType(const std::string &function_type) {
            return function_[function_type];
        }

        bool IsFunctionString(const std::string &str) {
            return function_.count(str) > 0;
        }

        bool IsOperationString(const std::string &str) {
            return operation_.count(str) > 0;
        }

     private:
        std::map<std::string, OperationType> function_ = {
                {"cos",  kCos},
                {"sin",  kSin},
                {"tan",  kTan},
                {"acos", kAcos},
                {"asin", kAsin},
                {"atan", kAtan},
                {"ln",   kLn},
                {"log",  kLog},
                {"sqrt", kSqrt}
        };

        std::map<std::string, OperationType> operation_ = {
                {"+",   kPlus},
                {"-",   kMinus},
                {"*",   kMultiply},
                {"/",   kDivide},
                {"^",   kPow},
                {"mod", kMod}
        };
    };

}  // namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_UTILITY_H
