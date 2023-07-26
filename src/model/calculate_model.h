#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATE_MODEL_H
#define CPP3_SMARTCALC_V2_0_1_CALCULATE_MODEL_H

#include "string_transformer.h"
#include "validator.h"

namespace s21 {

    class CalculateModel {
    public:
        CalculateModel() : validator_(new Validator), transformer_(new StringTransformer) {}

        ~CalculateModel() {
            polish_notation_.clear();
            delete validator_;
            delete transformer_;
        }

        std::string Add(const std::string &str);

        std::string DeleteOneMember();

        std::string DeleteAllMembers();

        bool ValidateEquation();

        long double Calculate(std::string equation);

        long double CalculationProcess();

        long double CalculateAxis(std::string equation, long double x);

    private:
        std::list<EquationMember *>::iterator OperatorProcess(std::list<EquationMember *>::iterator member);

        std::list<EquationMember *>::iterator DeleteAfterCalculate(std::list<EquationMember *>::iterator first_number,
                                                                   std::list<EquationMember *>::iterator sign);

        Validator* validator_;

        StringTransformer* transformer_;

        std::list<EquationMember *> polish_notation_;
    };

} //  namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_CALCULATE_MODEL_H
