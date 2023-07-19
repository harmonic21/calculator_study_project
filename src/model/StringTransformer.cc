#include "StringTransformer.h"

namespace s21 {

    std::list<EquationMember *>  StringTransformer::s21_string_processing(std::string& prepared_string) {
        char *token = strtok(const_cast<char *>(prepared_string.c_str()), " ");
        std::string old_token;
        std::list<EquationMember *> mathematicalExpression;

        while (token != nullptr) {
            std::string str = token;
            s21_check_number(mathematicalExpression, str);
            s21_check_x(mathematicalExpression, token);
            s21_check_function(mathematicalExpression, token);
            s21_check_bracket(mathematicalExpression, token);

            s21_check_sign(mathematicalExpression, token, old_token);
            s21_sorting_station(mathematicalExpression.back());

            old_token = token;
            token = strtok(nullptr, " ");
        }
        if (!stack_operation.empty()) {
            s21_flush_stack();
        }
        return polishNotation;
    }

    void StringTransformer::s21_flush_stack() {
        while (!stack_operation.empty()) {
            polishNotation.push_back(stack_operation.back());
            stack_operation.pop_back();
        }
    }

    void StringTransformer::s21_check_number(std::list<EquationMember *>& list, std::string& str) {
        if (utility.s21_is_number(str)) {
            std::string::size_type sz;
            long double value = std::stold(str, &sz);
            list.push_back(new EquationMember(value, Utility::NUMBER));
        }
    }


    void StringTransformer::s21_check_x(std::list<EquationMember *>& list, const char *str) {
        if (utility.s21_is_x(str)) {
            list.push_back(new EquationMember(0, Utility::X));
        }
    }

    void StringTransformer::s21_check_function(std::list<EquationMember *>& list, const std::string& str) {
        if (utility.s21_is_function_string(str)) {
            Utility::OperationType function_type = utility.s21_get_function_type(str);
            list.push_back(new EquationMember(0, function_type));
        }
    }

    void StringTransformer::s21_check_sign(std::list<EquationMember *>& list, const char *str, const std::string& str2) {
        if (utility.s21_is_operation_string(str)) {
            Utility::OperationType operation_type = utility.s21_get_operation_type(str);
            if (operation_type == Utility::MINUS || operation_type == Utility::PLUS) {
                operation_type = s21_check_unary(str2, operation_type);
            }
            list.push_back(new EquationMember(0, operation_type));
        }
    }

    Utility::OperationType StringTransformer::s21_check_unary(const std::string& str2, Utility::OperationType operationType) {
        Utility::OperationType new_type = operationType;
        if (str2.empty() || !(utility.s21_is_number(str2) || utility.s21_is_right_bracket(str2))) {
            switch (operationType) {
                case Utility::PLUS:
                    new_type = Utility::UNARY_PLUS;
                    break;
                case Utility::MINUS:
                    new_type = Utility::UNARY_MINUS;
                    break;
                default:
                    break;
            }
        }
        return new_type;
    }

    void StringTransformer::s21_check_bracket(std::list<EquationMember *>& list, const char *str) {
        if (utility.s21_is_left_bracket(str)) {
            list.push_back(new EquationMember(0, Utility::LEFT_BRACKET));
        } else if (utility.s21_is_right_bracket(str)) {
            list.push_back(new EquationMember(0, Utility::RIGHT_BRACKET));
        }
    }

    void StringTransformer::s21_sorting_station(EquationMember *member) {
        if (member->s21_get_value_type() == Utility::NUMBER || member->s21_get_value_type() == Utility::X) {
            polishNotation.push_back(member);
        } else {
            if (stack_operation.empty()) {
                stack_operation.push_back(member);
            } else {
                s21_polish_notation_process(member);
            }
        }
    }

    void StringTransformer::s21_polish_notation_process(EquationMember *new_member) {
        if (!stack_operation.empty()) {
            EquationMember *old_member = stack_operation.back();
            if (new_member->s21_get_value_type() == Utility::LEFT_BRACKET) {
                stack_operation.push_back(new_member);
            } else if (new_member->s21_get_value_type() == Utility::RIGHT_BRACKET) {
                    s21_flush_until_parentheses();
            } else if (old_member->s21_get_priority() >= new_member->s21_get_priority() &&
                       s21_is_left_associative(new_member)) {
                bool flag = false;
                while (!stack_operation.empty()) {
                    if (stack_operation.back()->s21_get_priority() >= new_member->s21_get_priority()) {
                        polishNotation.push_back(stack_operation.back());
                        stack_operation.pop_back();
                    } else {
                         stack_operation.push_back(new_member);
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    stack_operation.push_back(new_member);
                }
            } else {
                stack_operation.push_back(new_member);
            }
        }
    }

    void StringTransformer::s21_flush_until_parentheses() {
        while (stack_operation.back()->s21_get_value_type() != Utility::LEFT_BRACKET) {
            polishNotation.push_back(stack_operation.back());
            stack_operation.pop_back();
        }
        stack_operation.pop_back();
        if (!stack_operation.empty()) {
            if (EquationMember::s21_is_function(stack_operation.back())) {
                polishNotation.push_back(stack_operation.back());
                stack_operation.pop_back();
            }
        }
    }

    bool StringTransformer::s21_is_left_associative(EquationMember *member) {
        return member->s21_get_value_type() != Utility::POW;
    }

};
