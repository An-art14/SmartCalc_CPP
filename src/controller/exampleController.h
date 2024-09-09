#ifndef EXAMPLECONTROLLER_H
#define EXAMPLECONTROLLER_H

#include "../model/exampleModel.h"

namespace s21 {
/**
 * @brief Class controller, выступает связующим элементом между интерфейсом и
 * моделью
 */
class ExampleController {
 public:
  /**
   * @brief конструктор по умолчанию
   */
  ExampleController() : model(){};

  /**
   * @brief Конструктор с передачей экземпляра модели
   * @param m экземпляр модели, которую нужно использовать
   */
  ExampleController(const ExampleModel& m) : model(m){};

  /**
   * @brief Деструктор
   */
  ~ExampleController(){};

  /**
   * @brief вычисляет результат на основе инфиксного выражения и значения
   * переменной x
   * @param infix инфиксное выражение для вычисления
   * @param x_value значение переменной x
   * @return результат вычисления
   */
  double calculate(const std::string& infix, double x_value);

  /**
   * @brief получает последний вычисленный результат
   * @return последний вычисленный результат
   */
  double get_result() const;

 private:
  ExampleModel model;
};
};  // namespace s21

#endif