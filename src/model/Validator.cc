#include "Validator.h"

namespace s21 {

    std::string Validator::s21_add_member(const std::string& current) {
        s21_check_current(current);

        s21_init_last();
        
        return s21_result_equation_to_string();
    }

    void Validator::s21_init_last() {
        if (!_result_equation.empty()) {
            _last_member = s21_trim(_result_equation.back());
        }

    }

    void Validator::s21_check_current(const std::string& current) {
        if (_result_equation.empty()) {
            s21_validate_first(current);
        } else if (utility.s21_is_left_bracket(_last_member)) {
            s21_validate_after_left_bracket(current);
        } else if (utility.s21_is_right_bracket(_last_member)) {
            s21_validate_after_right_bracket(current);
        } else if (utility.s21_is_number(_last_member)) {
            s21_validate_after_number(current);
        } else if (utility.s21_is_x(_last_member)) {
            s21_validate_after_x(current);
        } else if (utility.s21_is_operation_string(_last_member)) {
            s21_validate_after_operator(current);
        }
    }

   void  Validator::s21_validate_first(const std::string& current) {
        if (!utility.s21_is_operation_string(current)) {
            s21_insert_member(current);
            if (utility.s21_is_function_string(current)) {
                s21_insert_member("(");
            }
        }
    }

    void Validator::s21_validate_after_left_bracket(const std::string& current) {
        if (utility.s21_is_unary_operation(current) || !utility.s21_is_operation_string(current)) {
            s21_insert_member(current);
            if (utility.s21_is_function_string(current)) {
                s21_insert_member("(");
            }
        }
    }

    void Validator::s21_validate_after_right_bracket(const std::string& current) {
        if (utility.s21_is_function_string(current)) {
            s21_insert_member("*");
            s21_insert_member( current);
            s21_insert_member("(");
        } else if (utility.s21_is_number(current) || utility.s21_is_x(current)) {
            s21_insert_member("*");
            s21_insert_member(current);
        } else {
            s21_insert_member(current);
        }
    }

    void Validator::s21_validate_after_number(const std::string& current) {
        if (utility.s21_is_left_bracket(current)) {
            s21_insert_member("*");
            s21_insert_member(current);
        } else if (utility.s21_is_function_string(current)) {
            s21_insert_member("*");
            s21_insert_member(current);
        } else {
            s21_insert_member(current);
        }
    }

    void Validator::s21_validate_after_x(const std::string& current) {
        if (!utility.s21_is_x(current)) {
            if (utility.s21_is_left_bracket(current)) {
                s21_insert_member("*");
                s21_insert_member(current);
            } else if (utility.s21_is_function_string(current)) {
                s21_insert_member("*");
                s21_insert_member(current);
            } else {
                s21_insert_member(current);
            }
        }
    }

    void Validator::s21_validate_after_operator(const std::string& current) {
        if (!utility.s21_is_operation_string(current)) {
            s21_insert_member(current);
            if (utility.s21_is_function_string(current)) {
                s21_insert_member("(");
            }
        }
    }

    void Validator::s21_insert_member(const std::string& current) {
        _result_equation.push_back(current + " ");
    }

    std::string Validator::s21_remove_one_member() {
        if (!_result_equation.empty()) {
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
        for (const auto &item: _result_equation) {
            if (!item.empty()) {
                result += item;
            }
        }
        return result;
    }

    bool Validator::s21_validate_result_string() {
        std::string equation = s21_result_equation_to_string();
        bool result = true;
        int count_x = 0;
        int count_number = 0;
        int sum_bracket = 0;

        for (char i: equation) {
            std::string member;
            member.push_back(i);
            if (utility.s21_is_left_bracket(member)) {
                sum_bracket++;
            } else if (utility.s21_is_right_bracket(member)) {
                sum_bracket--;
            }
            if (utility.s21_is_number(member)) {
                count_number++;
            }
            if (utility.s21_is_x(member)) {
                count_x++;
            }
            member.clear();
        }

        if (sum_bracket != 0 || (count_number == 0 && count_x == 0)) {
            result = false;
        }
        return result;
    }

    std::string Validator::s21_trim(std::string str) {
        std::string result;
        for(auto i : str) {
            if (i != ' ') {
                result += i;
            }
        }
        return result;
    }


};  // namespace s21
