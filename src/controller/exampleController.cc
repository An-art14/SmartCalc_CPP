#include "exampleController.h"
double s21::ExampleController::calculate(const std::string& infix,
                                         double x_value) {
  return model.evalute_postfix(infix, x_value);
}

double s21::ExampleController::get_result() const { return model.get_data(); }