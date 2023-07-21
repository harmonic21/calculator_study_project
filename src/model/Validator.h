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

        std::string s21_add_member(const std::string& str);

        std::string s21_remove_one_member();

        std::string s21_remove_all();

        std::string s21_result_equation_to_string();

        bool s21_validate_result_string();

    private:
        std::string _last_member;

        std::vector<std::string> _result_equation;

        Utility utility;

        void s21_check_current(const std::string& current);

        void s21_validate_after_left_bracket(const std::string& current);

        void s21_validate_after_right_bracket(const std::string& current);

        void s21_validate_after_number(const std::string& current);

        void s21_validate_first(const std::string& current);

        void s21_validate_after_x(const std::string& current);

        void s21_validate_after_operator(const std::string& current);

        void s21_insert_member(const std::string& str);

        std::string s21_trim(std::string str);

        void s21_init_last();
        };

};  //  namespace s21


#endif //CPP3_SMARTCALC_V2_0_1_VALIDATOR_H
