#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H

#include "../model/calculate_model.h"

namespace s21 {

    class  CalculationController {
    public:
        explicit CalculationController(CalculateModel* model) : calculateModel_(model) {}

        ~CalculationController() = default;

        long double Calculation(std::string equation_string);

        std::string AddMember(const std::string& str);

        std::string DeleteMember();

        std::string DeleteAll();

        bool ValidateEquation();

    private:
        CalculateModel* calculateModel_;
    };

}  //  namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H
