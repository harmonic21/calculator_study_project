#include "CalculateModel.h"

#include <utility>

namespace s21 {

    std::string CalculateModel::s21_add(std::string str) {
        return validator.s21_add_member(std::move(str));
    }

    std::string CalculateModel::s21_delete_one_member() {
        return validator.s21_remove_one_member();
    }

    std::string CalculateModel::s21_delete_all_members() {
        return validator.s21_remove_all();
    }

    bool CalculateModel::s21_validate_equation() {
        return validator.s21_validate_result_string();
    }

    long double CalculateModel::s21_calculate(std::string equation) {
        long double calculation_result = 0.0;
        polishNotation = transformer.s21_string_processing(equation);
        auto iter = polishNotation.begin();

        while (iter != polishNotation.end()) {
            if (EquationMember::s21_is_sign(*iter) || EquationMember::s21_is_function(*iter)) {
                iter = s21_operator_process(iter);
                continue;
            }
            iter++;
        }
        calculation_result = polishNotation.back()->s21_get_value();
        return calculation_result;
    }

    std::list<EquationMember *>::iterator
    CalculateModel::s21_operator_process(std::list<EquationMember *>::iterator member) {
        long double result = 0.0;
        bool res_modification = false;
        auto iter = member;

        if (EquationMember::s21_is_sign(*member)) {
            EquationMember *sign = *member;
            EquationMember *first = *(--member);
            if (sign->s21_get_value_type() == Utility::UNARY_MINUS ||
                sign->s21_get_value_type() == Utility::UNARY_PLUS) {
                result = sign->operation(0, first->s21_get_value());
            } else {
                EquationMember *second = *(--member);
                if (first->s21_get_value_type() == Utility::NUMBER && second->s21_get_value_type() == Utility::NUMBER) {
                    result = sign->operation(second->s21_get_value(), first->s21_get_value());
                }
            }
            iter = s21_delete_after_calculate(member, iter);
            res_modification = true;
        } else if (EquationMember::s21_is_function(*member)) {
            EquationMember *function = *member;
            EquationMember *number = *(--member);
            if (number->s21_get_value_type() == Utility::NUMBER) {
                result = function->function(number->s21_get_value());
                iter = s21_delete_after_calculate(member, iter);
                res_modification = true;
            }
        }
        if (res_modification) {
            iter = polishNotation.emplace(iter, new EquationMember(result, Utility::NUMBER));
        }
        return iter;
    }


    std::list<EquationMember *>::iterator
    CalculateModel::s21_delete_after_calculate(std::list<EquationMember *>::iterator first_number,
                                               std::list<EquationMember *>::iterator sign) {
        auto after_member = ++sign;
        polishNotation.erase(first_number, sign);
        return after_member;
    }

}