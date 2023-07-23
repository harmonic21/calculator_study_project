#include "calculation_controller.h"

#include <utility>

namespace s21 {

    long double CalculationController::Calculation(std::string equation_string) {
        return calculateModel_->Calculate(std::move(equation_string));
    }

    std::string CalculationController::AddMember(const std::string& str) {
        return calculateModel_->Add(str);
    }

    std::string CalculationController::DeleteMember() {
        return calculateModel_->DeleteOneMember();
    }

    std::string CalculationController::DeleteAll() {
        return calculateModel_->DeleteAllMembers();
    }

    bool CalculationController::ValidateEquation() {
        return calculateModel_->ValidateEquation();
    }

    long double CalculationController::PrepareAxis(std::string equation, long double x) {
        return calculateModel_->CalculateAxis(std::move(equation), x);
    }

}
