#ifndef SRC_SMARTCALC_S21_SMART_CALC_H_
#define SRC_SMARTCALC_S21_SMART_CALC_H_

#include "./s21_polish_notation/polish_notation.h"
#include "./s21_collection/s21_linked_list.h"
#include "./s21_calculations/s21_calculate.h"

#include <stdlib.h>

long double s21_smart_calc(char* work_str);
long double s21_set_graph(char* work_str, double val);
int s21_is_not_valid(char* str);


#endif  //  SRC_SMARTCALC_S21_SMART_CALC_H_
