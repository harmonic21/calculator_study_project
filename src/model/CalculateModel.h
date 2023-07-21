#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATE_MODEL_H
#define CPP3_SMARTCALC_V2_0_1_CALCULATE_MODEL_H

#include "StringTransformer.h"
#include "Validator.h"

namespace s21 {

    class CalculateModel {
    public:
        CalculateModel() {}

        ~CalculateModel() {
            polishNotation.clear();
        }

        std::string s21_add(std::string);

        std::string s21_delete_one_member();

        std::string s21_delete_all_members();

        bool s21_validate_equation();

        long double s21_calculate(std::string equation);

    private:

        Validator validator;

        StringTransformer transformer;

        std::list<EquationMember *> polishNotation;

        std::list<EquationMember *>::iterator s21_operator_process(std::list<EquationMember *>::iterator member);

        std::list<EquationMember *>::iterator
        s21_delete_after_calculate(std::list<EquationMember *>::iterator first_number,
                                   std::list<EquationMember *>::iterator sign);

    };

}; //  namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_CALCULATE_MODEL_H
