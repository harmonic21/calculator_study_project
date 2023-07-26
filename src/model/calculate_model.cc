#include "calculate_model.h"

namespace s21 {

    std::string CalculateModel::Add(const std::string& str) {
        return validator_->AddMember(str);
    }

    std::string CalculateModel::DeleteOneMember() {
        return validator_->RemoveOneMember();
    }

    std::string CalculateModel::DeleteAllMembers() {
        return validator_->RemoveAll();
    }

    bool CalculateModel::ValidateEquation() {
        return validator_->ValidateResultString();
    }

    long double CalculateModel::Calculate(std::string equation) {
        polish_notation_ = transformer_->StringProcessing(equation);
        return CalculationProcess();
    }

    long double CalculateModel::CalculationProcess() {
        auto iter = polish_notation_.begin();
        while (iter != polish_notation_.end()) {
            if (EquationMember::IsSign(*iter) || EquationMember::IsFunction(*iter)) {
                iter = OperatorProcess(iter);
                continue;
            }
            iter++;
        }
        return polish_notation_.back()->GetValue();
    }

    std::list<EquationMember *>::iterator
    CalculateModel::OperatorProcess(std::list<EquationMember *>::iterator member) {
        long double result = 0.0;
        bool res_modification = false;
        auto iter = member;

        if (EquationMember::IsSign(*member)) {
            EquationMember *sign = *member;
            EquationMember *first = *(--member);
            if (sign->GetValueType() == Utility::kUnaryMinus ||
                sign->GetValueType() == Utility::kUnaryPlus) {
                result = sign->operation(0, first->GetValue());
            } else {
                EquationMember *second = *(--member);
                if (first->GetValueType() == Utility::kNumber && second->GetValueType() == Utility::kNumber) {
                    result = sign->operation(second->GetValue(), first->GetValue());
                }
            }
            iter = DeleteAfterCalculate(member, iter);
            res_modification = true;
        } else if (EquationMember::IsFunction(*member)) {
            EquationMember *function = *member;
            EquationMember *number = *(--member);
            if (number->GetValueType() == Utility::kNumber) {
                result = function->function(number->GetValue());
                iter = DeleteAfterCalculate(member, iter);
                res_modification = true;
            }
        }
        if (res_modification) {
            iter = polish_notation_.emplace(iter, new EquationMember(result, Utility::kNumber));
        }
        return iter;
    }

    std::list<EquationMember *>::iterator
    CalculateModel::DeleteAfterCalculate(std::list<EquationMember *>::iterator first_number,
                                         std::list<EquationMember *>::iterator sign) {
        auto after_member = ++sign;
        polish_notation_.erase(first_number, sign);
        return after_member;
    }

    long double CalculateModel::CalculateAxis(std::string equation, long double x) {
        polish_notation_ = transformer_->StringProcessing(equation);
        auto iter = polish_notation_.begin();
        while (iter != polish_notation_.end()) {
                if (EquationMember::IsX(*iter)) {
                    (*iter)->SetValue(x);
                    (*iter)->SetValueType(Utility::kNumber);
                }
                iter++;
            }
        return CalculationProcess();
    }

}  //  namespace s21