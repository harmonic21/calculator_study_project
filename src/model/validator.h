#ifndef CPP3_SMARTCALC_V2_0_1_VALIDATOR_H
#define CPP3_SMARTCALC_V2_0_1_VALIDATOR_H

#include <string>
#include <vector>

#include "utility.h"

namespace s21 {

class Validator {
 public:
  Validator() = default;

  ~Validator() {
    last_member_.clear();
    result_equation_.clear();
  }

  std::string AddMember(const std::string &str);

  std::string RemoveOneMember();

  std::string RemoveAll();

  bool ValidateResultString() noexcept;

 private:
  enum DigitMod { kDigit, kDot, kExp };

  std::map<DigitMod, int> stateDigit_ = {{kDigit, 0}, {kDot, 0}, {kExp, 0}};

  static std::string S21Trim(const std::string &str) noexcept;

  std::string ResultEquationToString() noexcept;

  void CheckMember(const std::string &current) noexcept;

  void CheckConsistencyNumber(const std::string &current) noexcept;

  void InitLast();

  void ValidateFirst(const std::string &current);

  void ValidateAfterLeftBracket(const std::string &current);

  void ValidateAfterRightBracket(const std::string &current);

  void ValidateAfterNumber(const std::string &current);

  void ValidateAfterX(const std::string &current);

  void ValidateAfterOperator(const std::string &current);

  void ValidateAfterDot(const std::string &current);

  void ValidateAfterExp(const std::string &current);

  void InsertMember(const std::string &str, const std::string &del);

  void CheckStateDigit(const std::string &str);

  void FreshMap();

  std::string last_member_;

  std::vector<std::string> result_equation_;

  Utility utility_;
};

}  //  namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_VALIDATOR_H
