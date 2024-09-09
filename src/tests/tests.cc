#include <gtest/gtest.h>

#include "../controller/exampleController.h"

constexpr double EPS = 1e-7;

TEST(CalcTest, Expression_1) {
  s21::ExampleController calc_controller;
  std::string expression = "2+2/2";
  double x_value = 0.0;
  double res = calc_controller.calculate(expression, x_value);
  double expected = 3.0;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expression_2) {
  s21::ExampleController calc_controller;
  std::string expression = "(2.4+1.3)*1.5";
  double x_value = 0.0;
  double res = calc_controller.calculate(expression, x_value);
  double expected = 5.55;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expession_3) {
  s21::ExampleController calc_controller;
  std::string expression = "sqrt(16)+10*1.6";
  double x_value = 0.0;
  double res = calc_controller.calculate(expression, x_value);
  double expected = 20.0;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expression_4) {
  s21::ExampleController calc_cntroller;
  std::string expression = "2^3-9";
  double x_value = 0.0;
  double res = calc_cntroller.calculate(expression, x_value);
  double expected = -1.0;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expression_5) {
  s21::ExampleController calc_controller;
  std::string expression = "2^2^3";
  double x_value = 0.0;
  double res = calc_controller.calculate(expression, x_value);
  double expected = 255.9999999;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_6) {
  s21::ExampleController calc_controller;
  std::string expression = "-208+12.5";
  double x_value = 0.0;
  double res = calc_controller.calculate(expression, x_value);
  double expected = -195.5;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expression_7) {
  s21::ExampleController calc_controller;
  std::string expression = "74%36";
  double x_value = 0.0;
  double res = calc_controller.calculate(expression, x_value);
  double expected = 2.0;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expression_8) {
  s21::ExampleController calc_controller;
  double x = 0.0;
  std::string expression = "cos(0.0)";
  double res = calc_controller.calculate(expression, x);
  double expected = 1.0;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expression_9) {
  s21::ExampleController calc_controller;
  std::string expression = "-2/(-1+3)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = -1.0;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expression_10) {
  s21::ExampleController calc_controller;
  std::string expression = "cos(sin(tan(0.5)))";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = 0.8680519;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_11) {
  s21::ExampleController calc_controller;
  std::string expression = "log(ln(10))";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = 0.36221568869;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_12) {
  s21::ExampleController calc_controller;
  std::string expresssion = "-5^(-5+3) + asin(1) - acos(0/5) + atan(-3.14/2)";
  double x = 0.0;
  double res = calc_controller.calculate(expresssion, x);
  double expected = -1.0436550;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_13) {
  s21::ExampleController calc_controller;
  std::string expression = "sin(0) + cos(0) + tan(0)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = 1.0;
  EXPECT_DOUBLE_EQ(res, expected);
}

TEST(CalcTest, Expression_14) {
  s21::ExampleController calc_controller;
  std::string expression = "acos(1/5)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = 1.3694384;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_15) {
  s21::ExampleController calc_controller;
  std::string expression = "log(1000) + sqrt(16)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = 7.0;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_16) {
  s21::ExampleController calc_controller;
  std::string expression = "sqrt(50) + 2^2 + ln(10) - tan(45)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = 11.7538777;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_17) {
  s21::ExampleController calc_controller;
  std::string expression = "-3^(-2 + 1) + asin(0.5) + acos(0.5) + atan(5)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = 2.6108637;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_18) {
  s21::ExampleController calc_controller;
  std::string expression = "-4^(-2 + 1) + asin(0.9) + acos(0.1) + atan(10)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double expected = 3.8115260;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_19) {
  s21::ExampleController calc_controller;
  std::string expresiion = "23.4512*x+2^3";
  double x = 2.0;
  double res = calc_controller.calculate(expresiion, x);
  double expected = 54.9024;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_20) {
  s21::ExampleController calc_controller;
  std::string expresiion = "log(1000)+4^x/2";
  double x = 2.0;
  double res = calc_controller.calculate(expresiion, x);
  double expected = 11.0;
  EXPECT_NEAR(res, expected, EPS);
}

TEST(CalcTest, Expression_21) {
  s21::ExampleModel model;
  std::string expression = "sqrt(16)+2^3";
  double x = 0.0;
  double result = model.evalute_postfix(expression, x);
  double res = model.get_data();
  EXPECT_DOUBLE_EQ(result, res);
}

TEST(Calc, Expression_22) {
  s21::ExampleController calc_controller;
  std::string expression = "sin(0) + cos(0) + tan(0)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  double result = calc_controller.get_result();
  EXPECT_DOUBLE_EQ(res, result);
}

TEST(CalcTest, Expression_error_1) {
  s21::ExampleController calc_controller;
  std::string expression = "2/0+34.5";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  EXPECT_TRUE(std::isnan(res));
}

TEST(CalcTest, Expression_error_2) {
  s21::ExampleController calc_controller;
  std::string expression = "123.6%0+sqrt(12)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  EXPECT_TRUE(std::isnan(res));
}

TEST(CalcTest, Expression_error_3) {
  s21::ExampleController calc_controller;
  std::string expression = "sqrt(-16)+cos(1)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  EXPECT_TRUE(std::isnan(res));
}

TEST(CalcTest, Expression_error_4) {
  s21::ExampleController calc_controller;
  std::string expression = "ln(-2)+sqrt(100.4)";
  double x = 0.0;
  double res = calc_controller.calculate(expression, x);
  EXPECT_TRUE(std::isnan(res));
}

TEST(CalcTest, Expression_error_5) {
  s21::ExampleController calc_controller;
  std::string expression = "2+(2+1";
  double x = 0.0;
  EXPECT_THROW(calc_controller.calculate(expression, x), std::invalid_argument);
}

TEST(CalcTest, Expression_error_6) {
  s21::ExampleController calc_controller;
  std::string expression = "2+";
  double x = 0.0;
  EXPECT_THROW(calc_controller.calculate(expression, x), std::invalid_argument);
}

TEST(CalcTest, Expression_error_7) {
  s21::ExampleController calc_controller;
  std::string expression = "sqrt";
  double x = 0.0;
  EXPECT_THROW(calc_controller.calculate(expression, x), std::invalid_argument);
}

TEST(CalcTest, Expression_error_8) {
  s21::ExampleController calc_controller;
  std::string expression = "";
  double x = 0.0;
  EXPECT_THROW(calc_controller.calculate(expression, x), std::invalid_argument);
}

int main() {
  ::testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}