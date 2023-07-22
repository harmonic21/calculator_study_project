#include <gtest/gtest.h>

#include "../model/calculate_model.h"

TEST(CalculateModel, s21_calc_one) {
  std::string str = "5.0 + 345.1";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 350.1;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val) {
  std::string str = "5.345";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 5.345;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val_negate) {
  std::string str = " 0 - 5.345";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -5.345;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_unary) {
    std::string str = " - 5.345";
    s21::CalculateModel calculateModel;
    long double res = calculateModel.Calculate(str);
    long double test = -5.345;
    EXPECT_DOUBLE_EQ(res, test);
}

TEST(CalculateModel, s21_unary_1) {
    std::string str = " - 5. ";
    s21::CalculateModel calculateModel;
    long double res = calculateModel.Calculate(str);
    long double test = -5.;
    EXPECT_DOUBLE_EQ(res, test);
}

TEST(CalculateModel, s21_unary_2) {
    std::string str = " - .4 ";
    s21::CalculateModel calculateModel;
    long double res = calculateModel.Calculate(str);
    long double test = -0.4;
    EXPECT_DOUBLE_EQ(res, test);
}

TEST(CalculateModel, s21_calc_one_val_unary) {
  std::string str = " 0 + 5.345";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 5.345;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val_sum) {
  std::string str = " 0 + 5.345 + ( 245 + 12 ) + 134 + 234 + ( 235 + ( 123.4 + ( 1234.0 + 1 ) ) )";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 2223.745;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val_sub) {
  std::string str = " 12234567.1 - 232455353.2 ";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -220220786.1;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val_mul) {
  std::string str = " ( 0 - 1 ) * 2 ";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -2;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val_del) {
  std::string str = "( ( 5 / 1 ) / 2 ) / 5";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 0.5;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val_pow_two) {
  std::string str = "( 0 - 1 ) ^ 2";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 1;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val_pow_two_neg) {
  std::string str = "0 - ( 1  ^ 2 )";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -1;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_one_val_pow_three) {
  std::string str = "( 0 - 1 ) ^ 3";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -1;
  EXPECT_DOUBLE_EQ(res, test);

}

TEST(CalculateModel, s21_calc_sin) {
  std::string str = "sin ( 5 * 4 - 2 )";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -0.75098724677;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);
}

TEST(CalculateModel, s21_calc_cos) {
  std::string str = "cos ( 5.42 / 4.12 - 2.123 )";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 0.6913315469;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);
}

TEST(CalculateModel, s21_calc_acos) {
  std::string str = "acos ( 5.42 / 9.12 ) / 15";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 0.0622935681;
    EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);
}

TEST(CalculateModel, s21_calc_asin) {
  std::string str = "asin ( 1.42 / 9.12 ) * 5 - 2";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -1.2183108389;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);
}

TEST(CalculateModel, s21_calc_tan) {
  std::string str = " 5 * ( 5 - tan ( 5 * 0.2 ) )";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 17.21296137;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);

}

TEST(CalculateModel, s21_calc_atan) {
  std::string str = " 0 - ( 5 - atan ( 5 / 11.2 ) )";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -4.580120;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);

}

TEST(CalculateModel, s21_calc_sqrt) {
  std::string str = " 0 - ( 5 + sqrt ( 9.123 ) )";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = -8.02043043;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);

}

TEST(CalculateModel, s21_calc_ln) {
  std::string str = "10 * ln ( 345 / 2 ) ";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 51.5039723647;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);

}

TEST(CalculateModel, s21_calc_log) {
  std::string str = "log ( 1 / 2.234 ) ^ 2 ";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 0.121859;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);

}

TEST(CalculateModel, s21_calc_mod) {
  std::string str = "5 mod 9 * ( 1 / 2.234 ) ^ 2 ";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 1.0018522243;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);

}

TEST(CalculateModel, s21_calc_oper) {
  std::string str = "7 - 6 + 5 / 9 - 1";
  s21::CalculateModel calculateModel;
  long double res = calculateModel.Calculate(str);
  long double test = 0.5555555555;
  EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);

}

TEST(CalculateModel, s21_calc_smart_bracket_one) {
    std::string str = "( 7 - ( 6 + ( 5 / ( 9 - 1 ) ) ) )";
    s21::CalculateModel calculateModel;
    long double test = 0.375;
    long double res = calculateModel.Calculate(str);
    EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);
}

TEST(CalculateModel, s21_calc_smart_bracket_two) {
    std::string str = "( ( ( ( 7 - 6 ) + 5 ) / 9 ) - 1 )";
    s21::CalculateModel calculateModel;
    long double test = -0.3333333333;
    long double res = calculateModel.Calculate(str);
    EXPECT_NEAR(test, res, std::abs(test - res) < 1e-7);
}

//
//TEST(CalculateModel, s21_graph_one_x) {
//  std::string str = "kX";
//  long double value = 0.01;
//  for (long double i = 0.01; i <= 15.05; i++) {
//    long double result = s21_set_graph(str, value);
//    EXPECT_DOUBLE_EQ(result, value, 1e-06);
//  }
//}
//
//TEST(CalculateModel, s21_graph_x) {
//  std::string str = "kX";
//  for (long value = 0.01; value <= 15.05; value++) {
//    long double result = s21_set_graph(str, value);
//    EXPECT_DOUBLE_EQ(result, value, 1e-06);
//  }
//}
//
//
//TEST(CalculateModel, s21_valid_bracket) {
//  std::string str = " ( ( 7 - 6 + 5 ) / 9 - 1";
//  int res = s21_is_not_valid(str);
//  int test = 1;
//  ck_assert_int_eq(res, test);
//}
//
//
//TEST(CalculateModel, s21_valid_operation) {
//  std::string str = " ( ( -  +  ) ) /";
//  int res = s21_is_not_valid(str);
//  int test = 1;
//  ck_assert_int_eq(res, test);
//}
//
//TEST(CalculateModel, s21_valid_operation_x) {
//  std::string str = " ( ( kX -  +  ) ) /";
//  int res = s21_is_not_valid(str);
//  int test = 1;
//  ck_assert_int_eq(res, test);
//}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

