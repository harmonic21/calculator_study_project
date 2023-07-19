#include "CalculationController.h"

#include <utility>

namespace s21 {

    long double CalculationController::s21_calculation(std::string equation_string) {
        return _calculateModel->s21_calculate(std::move(equation_string));
    }

    std::string CalculationController::s21_add_member(std::string str) {
        return _calculateModel->s21_add(std::move(str));
    }

    std::string CalculationController::s21_delete_member() {
        return _calculateModel->s21_delete_one_member();
    }

    std::string CalculationController::s21_delete_all() {
        return _calculateModel->s21_delete_all_members();
    }

}
