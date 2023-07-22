#include "s21_smart_calc.h"

long double s21_set_graph(char* work_str, double val) {
    int size = strlen(work_str);
    char* copy_str = (char*) calloc(size + 1, sizeof(char));
    snprintf(copy_str, size + 1, "%s", work_str);
    t_db_linked_list* result = s21_string_processing(copy_str);
    free(copy_str);
    t_node* temp = result->head;
     while (temp != NULL) {
        if (temp->data.label == X) {
            temp->data.number = val;
            temp->data.label = NUMBER;
         }
        temp = temp->next;
     }
    long double res = s21_calculate(result);
    free(result);
    return res;
}

static int s21_check_symb(char symb) {
  return symb == '+' || symb == '-' || symb == '(' || symb == 's'
  || symb == 'c' || symb == 'a' || symb == 'l' || symb == 't' || symb == 'x' || symb == 'X';
}

int s21_is_not_valid(char* str) {
  int result = 0;
  int count_x = 0;
  int size = strlen(str);
  int sum_bracket = 0;
  int count_number = 0;

  for (int i = 0; i < size; i++) {
    if (str[i] == '(') {
      sum_bracket++;
    } else if (str[i] == ')') {
      sum_bracket--;
    }
    if (str[i] >= '0' && str[i] <= '9') {
      count_number++;
    }
    if (str[i] == 'x' || str[i] == 'X') {
        count_x++;
    }
  }
  if (!(str[0] >= '0' && str[0] <= '9') && !s21_check_symb(str[0])) {
    result = 1;
  }
  if (sum_bracket != 0 || (count_number == 0 && count_x == 0)) {
    result = 1;
  }
  return result;
}
