#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H

#include "../model/CalculateModel.h"

namespace s21 {

    class CalculationController {
    public:
        explicit CalculationController(CalculateModel* model) : _calculateModel(model) {}

        ~CalculationController() = default;

        long double s21_calculation(std::string equation_string);

        std::string s21_add_member(std::string str);

        std::string s21_delete_member();

        std::string s21_delete_all();

        bool s21_validate_equation();

    private:
        CalculateModel* _calculateModel;
    };

};  //  namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H
