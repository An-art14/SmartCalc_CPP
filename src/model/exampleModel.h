#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>

namespace s21 {

/**
 * @brief Model class, включает в себя все алгоритмы и обработку информации
 */
class ExampleModel {
 public:
  /**
   * @brief Конструктор по умолчанию, инициализирует data нулем
   */
  ExampleModel() : data(0){};

  /**
   * @brief Деструктор
   */
  ~ExampleModel(){};

  /**
   * @brief Преобразует инфиксное выражение в постфиксное выражение
   * @param infix Входное инфиксное выражение
   * @return Возвращает строку как выражение в постфиксной нотации
   */
  std::string infix_postfix(const std::string& infix);

  /**
   * @brief Вычисляет значение постфиксного выражения
   * @param infix Входное инфиксное выражение
   * @param x_value Значение переменной x
   * @return возвращает результат вычисления
   */
  double evalute_postfix(const std::string& infix, double x_value);

  /**
   * @brief Возвращает текущее значение data
   * @return значение data
   */
  double get_data() const { return data; }

  /**
   * @brief Сохраняет результат вычислений
   */
 private:
  double data;

  /**
   * @brief Перечисление приоритета операторов
   * @param START Начальный приоритет
   * @param ADDSUB Приоритет сложения и вычитания
   * @param MULTDIV Приоритет умножения и деления
   * @param POWER Приоритет степени
   * @param FUNCT Приоритет функций
   */
  enum class priorities {
    START = 0,
    ADDSUB = 1,
    MULTDIV = 2,
    POWER = 3,
    FUNCT = 4
  };

  /**
   * @brief Обрабатывает число в строковом выражение
   * @param infix Входное инфиксное выражение
   * @param i Индекс текущего символа в строке
   * @return Обработанное инфиксное выражение
   */
  std::string process_number(const std::string& infix, std::size_t& i);

  /**
   * @brief Обрабатывает скобки в строковом выражении
   * @param stack_sym стек символов
   * @param output выходная строка
   */
  void process_parentheses(std::stack<char>& stack_sym, std::string& output);

  /**
   * @brief Обрабатывает оператор в строковом выражении
   * @param ch Текущий символ
   * @param stack_sym Стек символов
   * @param output Выходная строка
   */
  void process_operator(char ch, std::stack<char>& stack_sym,
                        std::string& output);

  /**
   * @brief Финальная обработка выражения
   * @param stack_sym Стек символов
   * @param output Выходная строка
   */
  void final(std::stack<char>& stack_sym, std::string& output);

  /**
   *  @brief Проверяет корректность скобок
   * @param open_br Число открывающих скобок
   * @param close_br Число закрывающих скобок
   */
  void check_brackets(int open_br, int close_br);

  /**
   * @brief Проверяет, является ли символ оператором
   * @param sym Символ для проверки
   * @return true если символ является оператором; false в противном случае
   */
  bool is_operator(char sym);

  /**
   * @brief Проверяет, является ли символ функцией
   * @param sym Символ для проверки
   * @return true если символ является функцией; false в противном случае
   */
  bool is_functions(char sym);

  /**
   * @brief Заменяет функции одним символом в выражении
   * @param infix Входное инфиксное выражение
   * @return Обработанное инфиксное выражение
   */
  std::string change_functions(const std::string& infix);

  /**
   * @brief Возвращает приоритет оператора
   * @param sym Символ для проверки
   * @return Приоритет оператора
   */
  priorities get_precedency(char sym);

  /**
   * @brief Выполняет унарную операцию
   * @param sym Символ для проверки
   * @param x_value Значение переменной x
   * @return Результат унарной операции
   */
  double unar_operator(char sym, double x);

  /**
   * @brief Выполняет бинарную операцию
   * @param sym Символ для проверки
   * @param a Первый операнд
   * @param b Второй операнд
   * @return Результат бинарной операции
   */
  double bin_operator(char sym, double a, double b);

  /**
   * @brief Статическая хеш-таблица для замены функций
   */
  static std::unordered_map<std::string, char> replacements;

  /**
   * @brief Обработка ошибок: пустое выражение
   */
  void error_empty();

  /**
   * @brief Обработка ошибок: пустой стек
   */
  void error_empty_stack();

  /**
   * @brief Обработка ошибок: недостаточно значений для унарного оператора
   */
  void error_bin_operator();
};
}  // namespace s21

#endif