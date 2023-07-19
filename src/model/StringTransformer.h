#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H

#include <stack>
#include <vector>
#include <list>
#include <map>
#include <cstring>

#include "EquationMember.h"

namespace s21 {
    class StringTransformer {
    public:

        StringTransformer() = default;

        ~StringTransformer() {
            stack_operation.clear();
            polishNotation.clear();
        }

        std::list<EquationMember *>  s21_string_processing(std::string& prepared_string);

    private:
        Utility utility;

        void s21_flush_stack();

        void s21_flush_until_parentheses();

        void s21_check_number(std::list<EquationMember *>& list, std::string& str);

        void s21_check_x(std::list<EquationMember *>& list, const char *str);

        void s21_check_function(std::list<EquationMember *>& list, const std::string& str);

        void s21_check_sign(std::list<EquationMember *>& list, const char *str, const std::string& str2);

        Utility::OperationType s21_check_unary(const std::string& str2, Utility::OperationType);

        void s21_check_bracket(std::list<EquationMember *>& list, const char *str);

        void s21_sorting_station(EquationMember *member);

        void s21_polish_notation_process(EquationMember *new_member);

        static bool s21_is_left_associative(EquationMember *member);

        std::vector<EquationMember *> stack_operation;

        std::list<EquationMember *> polishNotation;

    };

}  // namespace s21

#endif  //  MODEL_MODEL_H
