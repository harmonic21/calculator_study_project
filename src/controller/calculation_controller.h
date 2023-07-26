#ifndef CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H

#include "../model/calculate_model.h"

namespace s21 {

    class  CalculationController {
    public:
        explicit CalculationController(CalculateModel* model) : calculateModel_(model) {}

        CalculationController(const CalculationController& other) {
            calculateModel_ = other.calculateModel_;
        }

        CalculationController(CalculationController&& other)  noexcept : calculateModel_(nullptr) {
            *this = std::move(other);
        }

        CalculationController& operator=(const CalculationController& c) {
            if (this != &c) {
                delete calculateModel_;
                calculateModel_ = c.calculateModel_;
            }
            return *this;
        }

        CalculationController& operator=(CalculationController&& c) noexcept {
            if (this != &c) {
                delete calculateModel_;
                calculateModel_ = c.calculateModel_;
                delete c.calculateModel_;
                delete &c;
            }
            return *this;
        }

        ~CalculationController() { delete calculateModel_; }

        long double Calculation(std::string equation_string);

        std::string AddMember(const std::string& str);

        std::string DeleteMember();

        std::string DeleteAll();

        bool ValidateEquation();

        long double PrepareAxis(std::string equation, long double x);

    private:
        CalculateModel* calculateModel_;
    };

}  //  namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_CALCULATION_CONTROLLER_H
