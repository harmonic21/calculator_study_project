#include <sstream>
#include "Validator.h"

namespace s21 {

    std::string Validator::s21_add_member(std::string str) {
        s21_check_last(str);

        s21_check_next(str);

        _last_member = str;
        return s21_result_equation_to_string();
    }

    bool Validator::s21_check_last(std::string next) {
        if (utility.s21_is_dot(_last_member)) {
        }
    }

    bool Validator::s21_check_next(std::string next) {
        if (utility.s21_is_function_string(next)) {
            _result_equation.push_back(utility.s21_is_function_string(_last_member) ? "" : " " + next + " ");
        } else if (utility.s21_is_operation_string(next)) {
            _result_equation.push_back(utility.s21_is_operation_string(_last_member) ? "" : " " + next + " ");
        } else if (utility.s21_is_number(next)) {
            _result_equation.push_back(next);
        } else if (utility.s21_is_x(next)) {
            _result_equation.push_back(utility.s21_is_x(_last_member) ? "" : " " + next + " ");
        }
    }

    std::string Validator::s21_remove_one_member() {
        if(!_result_equation.empty()) {
            _result_equation.pop_back();
            _last_member = _result_equation.back();
         }
        return s21_result_equation_to_string();
    }

    std::string Validator::s21_remove_all() {
        _result_equation.clear();
        _last_member.clear();
        return s21_result_equation_to_string();
    }

    std::string Validator::s21_result_equation_to_string() {
        std::string result;
        for (const auto& item : _result_equation) {
            if (!item.empty()) {
                result += item;
            }
        }
        return result;
    }


};  // namespace s21
