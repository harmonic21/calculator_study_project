#include "validator.h"

namespace s21 {

    std::string Validator::AddMember(const std::string &str) {
        CheckStateDigit(str);
        if (stateDigit_[kDigit] == 1) {
            CheckConsistencyNumber(str);
        } else {
            CheckMember(str);
        }
        InitLast();
        return ResultEquationToString();
    }

    std::string Validator::RemoveOneMember() {
        if (!result_equation_.empty()) {
            result_equation_.pop_back();
            InitLast();
        }
        return ResultEquationToString();
    }

    std::string Validator::RemoveAll() {
        result_equation_.clear();
        last_member_.clear();
        return ResultEquationToString();
    }

    bool Validator::ValidateResultString() noexcept {
        std::string equation = ResultEquationToString();
        bool result = true;
        int count_x = 0;
        int count_number = 0;
        int sum_bracket = 0;
        int count_exp = 0;

        for (char i: equation) {
            std::string member;
            member.push_back(i);
            if (s21::Utility::IsLeftBracket(member)) {
                sum_bracket++;
            } else if (s21::Utility::IsRightBracket(member)) {
                sum_bracket--;
            }
            if (s21::Utility::IsNumber(member)) {
                count_number++;
            }
            if (s21::Utility::IsX(member)) {
                count_x++;
            }
            if (s21::Utility::IsExp(member)) {
                count_exp++;
            }
            member.clear();
        }

        if (sum_bracket != 0 || (count_number == 0 && count_x == 0)) {
            result = false;
        }
        if (equation.size() > 400) {
            result = false;
        }
        if (count_exp == 1 && equation.size() == 1) {
            result = false;
        }
        FreshMap();
        return result;
    }

    std::string Validator::S21Trim(const std::string &str) noexcept {
        std::string result;
        for (auto i: str) {
            if (i != ' ') {
                result += i;
            }
        }
        return result;
    }

    std::string Validator::ResultEquationToString() noexcept {
        std::string result;
        for (const auto &item: result_equation_) {
            if (!item.empty()) {
                result += item;
            }
        }
        return result;
    }

    void Validator::CheckMember(const std::string &current) noexcept {
        if (result_equation_.empty()) {
            ValidateFirst(current);
        } else if (s21::Utility::IsLeftBracket(last_member_)) {
            ValidateAfterLeftBracket(current);
        } else if (s21::Utility::IsRightBracket(last_member_)) {
            ValidateAfterRightBracket(current);
        } else if (s21::Utility::IsDigit(last_member_)) {
            ValidateAfterNumber(current);
        } else if (s21::Utility::IsX(last_member_)) {
            ValidateAfterX(current);
        } else if (utility_.IsOperationString(last_member_) || last_member_ == "d") {
            ValidateAfterOperator(current);
        } else if (s21::Utility::IsDot(last_member_)) {
            ValidateAfterDot(current);
        } else if (s21::Utility::IsExp(last_member_)) {
            ValidateAfterExp(current);
        }
    }

    void Validator::CheckConsistencyNumber(const std::string &current) noexcept {
        if (s21::Utility::IsDot(current) && stateDigit_[kDot] == 0) {
            stateDigit_[kDot] = 1;
            InsertMember(current, "");
        } else if (s21::Utility::IsDigit(current)) {
            InsertMember(current, "");
        } else if (s21::Utility::IsExp(current) && stateDigit_[kExp] == 0 && s21::Utility::IsDigit(last_member_)) {
            stateDigit_[kExp] = 1;
            InsertMember(current, "");
        } else if (s21::Utility::IsExp(last_member_) && current == "-") {
            stateDigit_[kExp] = 1;
            InsertMember(current, "");
        }
    }

    void Validator::InitLast() {
        if (!result_equation_.empty()) {
            std::string last = S21Trim(result_equation_.back());
            last_member_ = last.back();
        }
    }

    void Validator::ValidateFirst(const std::string &current) {
        if (!utility_.IsOperationString(current)) {
            if (utility_.IsFunctionString(current)) {
                InsertMember(current + " (", " ");
            } else {
                InsertMember(current, " ");
            }
        }
    }

    void Validator::ValidateAfterLeftBracket(const std::string &current) {
        if (s21::Utility::IsUnaryOperation(current) || !utility_.IsOperationString(current)) {
            if (utility_.IsFunctionString(current)) {
                InsertMember(current + " (", " ");
            } else {
                InsertMember(current, " ");
            }
        }
    }

    void Validator::ValidateAfterRightBracket(const std::string &current) {
        if (utility_.IsFunctionString(current)) {
            InsertMember("* " + current + " (", " ");
        } else if ((s21::Utility::IsNumber(current) || s21::Utility::IsX(current)) && !s21::Utility::IsExp(current)) {
            InsertMember("* " + current, " ");
        } else {
            InsertMember(current, " ");
        }
    }

    void Validator::ValidateAfterNumber(const std::string &current) {
        if (s21::Utility::IsLeftBracket(current)) {
            InsertMember(" * " + current, " ");
        } else if (utility_.IsFunctionString(current)) {
            InsertMember(" * " + current + " (", " ");
        } else if (s21::Utility::IsX(current)) {
            InsertMember(" * " + current, " ");
        } else {
            InsertMember(" " + current, " ");
        }
    }

    void Validator::ValidateAfterX(const std::string &current) {
        if (!s21::Utility::IsX(current) && !s21::Utility::IsNumber(current)) {
            if (s21::Utility::IsLeftBracket(current)) {
                InsertMember("* " + current, " ");
            } else if (utility_.IsFunctionString(current)) {
                InsertMember("* " + current + " (", " ");
            } else {
                InsertMember(current, " ");
            }
        }
    }

    void Validator::ValidateAfterOperator(const std::string &current) {
        if (!utility_.IsOperationString(current)) {
            if (utility_.IsFunctionString(current)) {
                InsertMember(current + " (", " ");
            } else {
                InsertMember(current, " ");
            }
        }
    }

    void Validator::ValidateAfterDot(const std::string &current) {
        if (s21::Utility::IsNumber(current) && !s21::Utility::IsExp(current)) {
            InsertMember(current, "");
        }
    }

    void Validator::ValidateAfterExp(const std::string &current) {
        if (s21::Utility::IsDigit(current)) {
            InsertMember(current, "");
        } else if (current == "-") {
            InsertMember(current, "");
        }
    }

    void Validator::InsertMember(const std::string &str, const std::string &del) {
        result_equation_.push_back(str + del);
    }

    void Validator::CheckStateDigit(const std::string &str) {
        if (s21::Utility::IsNumber(str) && str != "-") {
            stateDigit_[kDigit] = 1;
        } else if (str == "-" && last_member_ == "E") {
            stateDigit_[kDigit] = 1;
        } else {
            FreshMap();
        }
    }

    void Validator::FreshMap() {
        stateDigit_[kDot] = 0;
        stateDigit_[kDigit] = 0;
        stateDigit_[kExp] = 0;
    }

}  // namespace s21
