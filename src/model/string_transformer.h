#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H

#include <cstring>
#include <list>
#include <vector>

#include "equation_member.h"

namespace s21 {

class StringTransformer {
 public:
  StringTransformer() = default;

  ~StringTransformer() {
    stack_operation_.clear();
    polish_notation_.clear();
  }

  std::list<EquationMember *> StringProcessing(std::string &prepared_string);

 private:
  static bool IsLeftAssociative(EquationMember *member) noexcept;

  static void CheckX(std::list<EquationMember *> &list, const char *str);

  static void CheckNumber(std::list<EquationMember *> &list, std::string &str);

  static Utility::OperationType CheckUnary(
      const std::string &str2, Utility::OperationType type) noexcept;

  static void CheckBracket(std::list<EquationMember *> &list, const char *str);

  void CheckFunction(std::list<EquationMember *> &list, const std::string &str);

  void CheckSign(std::list<EquationMember *> &list, const char *str,
                 const std::string &str2);

  void SortingStation(EquationMember *member);

  void PolishNotationProcess(EquationMember *new_member);

  void FlushStack();

  void FlushUntilParentheses();

  void DeletedNode();

  std::vector<EquationMember *> stack_operation_;

  std::list<EquationMember *> polish_notation_;

  Utility utility_;
};

}  // namespace s21

#endif  //  MODEL_MODEL_H
