#include "string_transformer.h"

namespace s21 {

std::list<EquationMember *> StringTransformer::StringProcessing(
    std::string &prepared_string) {
  polish_notation_.clear();
  char *token = strtok(const_cast<char *>(prepared_string.c_str()), " ");
  std::string old_token;
  std::list<EquationMember *> mathematical_expression;

  while (token != nullptr) {
    std::string str = token;
    CheckNumber(mathematical_expression, str);
    CheckX(mathematical_expression, token);
    CheckFunction(mathematical_expression, token);
    CheckBracket(mathematical_expression, token);

    CheckSign(mathematical_expression, token, old_token);
    SortingStation(mathematical_expression.back());

    old_token = token;
    token = strtok(nullptr, " ");
  }
  if (!stack_operation_.empty()) {
    FlushStack();
  }
  mathematical_expression.erase(mathematical_expression.cbegin(),
                                mathematical_expression.cend());
  return polish_notation_;
}

bool StringTransformer::IsLeftAssociative(EquationMember *member) noexcept {
  return member->GetValueType() != Utility::kPow;
}

void StringTransformer::CheckX(std::list<EquationMember *> &list,
                               const char *str) {
  if (s21::Utility::IsX(str)) {
    list.push_back(new EquationMember(0, Utility::kX));
  }
}

void StringTransformer::CheckNumber(std::list<EquationMember *> &list,
                                    std::string &str) {
  if (s21::Utility::IsNumber(str) && !s21::Utility::IsUnaryOperation(str)) {
    std::string::size_type sz;
    long double value = s21::Utility::IsDot(str) ? 0 : std::stold(str, &sz);
    list.push_back(new EquationMember(value, Utility::kNumber));
  }
}

Utility::OperationType StringTransformer::CheckUnary(
    const std::string &str2, Utility::OperationType type) noexcept {
  Utility::OperationType new_type = type;
  if (str2.empty() ||
      !(s21::Utility::IsNumber(str2) || s21::Utility::IsRightBracket(str2))) {
    switch (type) {
      case Utility::kPlus:
        new_type = Utility::kUnaryPlus;
        break;
      case Utility::kMinus:
        new_type = Utility::kUnaryMinus;
        break;
      default:
        break;
    }
  }
  return new_type;
}

void StringTransformer::CheckBracket(std::list<EquationMember *> &list,
                                     const char *str) {
  if (s21::Utility::IsLeftBracket(str)) {
    list.push_back(new EquationMember(0, Utility::kLeftBracket));
  } else if (s21::Utility::IsRightBracket(str)) {
    list.push_back(new EquationMember(0, Utility::kRightBracket));
  }
}

void StringTransformer::CheckFunction(std::list<EquationMember *> &list,
                                      const std::string &str) {
  if (utility_.IsFunctionString(str)) {
    Utility::OperationType function_type = utility_.GetFunctionType(str);
    list.push_back(new EquationMember(0, function_type));
  }
}

void StringTransformer::CheckSign(std::list<EquationMember *> &list,
                                  const char *str, const std::string &str2) {
  if (utility_.IsOperationString(str)) {
    Utility::OperationType operation_type = utility_.GetOperationType(str);
    if (operation_type == Utility::kMinus || operation_type == Utility::kPlus) {
      operation_type = CheckUnary(str2, operation_type);
    }
    list.push_back(new EquationMember(0, operation_type));
  }
}

void StringTransformer::SortingStation(EquationMember *member) {
  if (member->GetValueType() == Utility::kNumber ||
      member->GetValueType() == Utility::kX) {
    polish_notation_.push_back(member);
  } else {
    if (stack_operation_.empty()) {
      stack_operation_.push_back(member);
    } else {
      PolishNotationProcess(member);
    }
  }
}

void StringTransformer::PolishNotationProcess(EquationMember *new_member) {
  if (!stack_operation_.empty()) {
    EquationMember *old_member = stack_operation_.back();
    if (new_member->GetValueType() == Utility::kLeftBracket) {
      stack_operation_.push_back(new_member);
    } else if (new_member->GetValueType() == Utility::kRightBracket) {
      FlushUntilParentheses();
      delete new_member;
    } else if (old_member->GetPriority() >= new_member->GetPriority() &&
               IsLeftAssociative(new_member)) {
      bool flag = false;
      while (!stack_operation_.empty()) {
        if (stack_operation_.back()->GetPriority() >=
            new_member->GetPriority()) {
          polish_notation_.push_back(stack_operation_.back());
          stack_operation_.pop_back();
        } else {
          stack_operation_.push_back(new_member);
          flag = true;
          break;
        }
      }
      if (!flag) {
        stack_operation_.push_back(new_member);
      }
    } else {
      stack_operation_.push_back(new_member);
    }
  }
}

void StringTransformer::FlushStack() {
  while (!stack_operation_.empty()) {
    polish_notation_.push_back(stack_operation_.back());
    stack_operation_.pop_back();
  }
}

void StringTransformer::FlushUntilParentheses() {
  while (stack_operation_.back()->GetValueType() != Utility::kLeftBracket) {
    polish_notation_.push_back(stack_operation_.back());
    stack_operation_.pop_back();
  }
  DeletedNode();
  if (!stack_operation_.empty()) {
    if (EquationMember::IsFunction(stack_operation_.back())) {
      polish_notation_.push_back(stack_operation_.back());
      stack_operation_.pop_back();
    }
  }
}

void StringTransformer::DeletedNode() {
  EquationMember *temp = stack_operation_.back();
  stack_operation_.pop_back();
  delete temp;
}

}  //  namespace s21
