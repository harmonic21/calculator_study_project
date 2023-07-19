#ifndef CPP3_SMARTCALC_V2_0_1_VALIDATOR_H
#define CPP3_SMARTCALC_V2_0_1_VALIDATOR_H

#include <string>
#include <vector>

#include "Utility.h"

namespace s21 {

    class Validator {
    public:
        Validator() {}

        ~Validator() {}

        std::string s21_add_member(std::string str);

        std::string s21_remove_one_member();

        std::string s21_remove_all();

        std::string s21_result_equation_to_string();

    private:
        std::string _last_member;

        std::vector<std::string> _result_equation;

        Utility utility;

        bool s21_check_last(std::string next);

        bool s21_check_next(std::string next);


        };

};  //  namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_VALIDATOR_H
