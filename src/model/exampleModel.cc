#include "exampleModel.h"

std::unordered_map<std::string, char> s21::ExampleModel::replacements = {
    {"sin", 's'},  {"cos", 'c'},  {"tan", 't'}, {"sqrt", 'q'}, {"asin", 'S'},
    {"acos", 'C'}, {"atan", 'T'}, {"log", 'g'}, {"ln", 'n'}};
bool s21::ExampleModel::is_operator(char sym) {
  std::string operators = "+-*/%^";
  return operators.find(sym) != std::string::npos;
}
bool s21::ExampleModel::is_functions(char sym) {
  std::string functions = "sctqSCTgn";
  return functions.find(sym) != std::string::npos;
}

std::string s21::ExampleModel::change_functions(const std::string& infix) {
  std::string result = infix;
  for (const auto& [key, value] : replacements) {
    std::string::size_type pos = 0;
    while ((pos = result.find(key, pos)) != std::string::npos) {
      result.replace(pos, key.length(), 1, value);
      pos += 1;
    }
  }
  return result;
}

s21::ExampleModel::priorities s21::ExampleModel::get_precedency(char sym) {
  priorities priority = priorities::START;
  if (sym == '+' || sym == '-') {
    priority = priorities::ADDSUB;
  } else if (sym == '*' || sym == '/' || sym == '%') {
    priority = priorities::MULTDIV;
  } else if (sym == '^') {
    priority = priorities::POWER;
  } else if (is_functions(sym)) {
    priority = priorities::FUNCT;
  }
  return priority;
}
std::string s21::ExampleModel::infix_postfix(const std::string& infix) {
  std::string modif_infix = change_functions(infix);
  int open_br = 0, close_br = 0;
  std::stack<char> stack_sym;
  std::string output = "";

  for (std::size_t i = 0; i < modif_infix.length(); i++) {
    char ch = modif_infix[i];
    if (isspace(ch)) {
      continue;
    } else if (isdigit(ch) || ch == '.') {
      output += process_number(modif_infix, i);
      continue;
    } else if (ch == 'x') {
      output += ch;
      output += ' ';
      continue;
    } else if (ch == '(') {
      if (i > 0 && (isdigit(modif_infix[i - 1]) || modif_infix[i - 1] == 'x')) {
        throw std::invalid_argument("Error: Implicit multiplication detected");
      }
      stack_sym.push(ch);
      open_br++;
      continue;
    } else if (ch == ')') {
      close_br++;
      process_parentheses(stack_sym, output);
      continue;
    } else if (is_operator(ch) || is_functions(ch)) {
      if ((i == 0 || modif_infix[i - 1] == '(') && ch == '-') {
        output += '0';
        output += ' ';
      }
      process_operator(ch, stack_sym, output);
    }
  }
  final(stack_sym, output);
  check_brackets(open_br, close_br);
  return output;
}
std::string s21::ExampleModel::process_number(const std::string& modif_infix,
                                              std::size_t& i) {
  std::string number;
  int dot_count = 0;
  while (i < modif_infix.length() &&
         (isdigit(modif_infix[i]) || modif_infix[i] == '.')) {
    if (modif_infix[i] == '.') {
      dot_count++;
      if (dot_count > 1) {
        throw std::invalid_argument("Error: Multiple decimal points in number");
      }
    }
    number += modif_infix[i++];
  }
  number += ' ';
  i--;
  return number;
}
void s21::ExampleModel::process_parentheses(std::stack<char>& stack_sym,
                                            std::string& output) {
  while (!stack_sym.empty() && stack_sym.top() != '(') {
    output += stack_sym.top();
    output += ' ';
    stack_sym.pop();
  }
  if (!stack_sym.empty()) {
    stack_sym.pop();
  }
  if (!stack_sym.empty() && is_functions(stack_sym.top())) {
    output += stack_sym.top();
    output += ' ';
    stack_sym.pop();
  }
}

void s21::ExampleModel::process_operator(char ch, std::stack<char>& stack_sym,
                                         std::string& output) {
  while (!stack_sym.empty() &&
         get_precedency(stack_sym.top()) >= get_precedency(ch) && ch != '^') {
    output += stack_sym.top();
    output += ' ';
    stack_sym.pop();
  }
  stack_sym.push(ch);
}

void s21::ExampleModel::final(std::stack<char>& stack_sym,
                              std::string& output) {
  while (!stack_sym.empty()) {
    output += stack_sym.top();
    output += ' ';
    stack_sym.pop();
  }
}

void s21::ExampleModel::check_brackets(int open_br, int close_br) {
  if (close_br != open_br) {
    throw std::invalid_argument("Error: Unmatched parentheses");
  }
}

double s21::ExampleModel::unar_operator(char sym, double x) {
  switch (sym) {
    case 's':
      return sin(x);
    case 'c':
      return cos(x);
    case 't':
      return tan(x);
    case 'q':
      return (x < 0) ? std::numeric_limits<double>::quiet_NaN() : std::sqrt(x);
    case 'S':
      return asin(x);
    case 'C':
      return acos(x);
    case 'T':
      return atan(x);
    case 'g':
      return log10(x);
    case 'n':
      return (x <= 0) ? std::numeric_limits<double>::quiet_NaN() : std::log(x);
    default:
      return std::numeric_limits<double>::quiet_NaN();
  }
}

double s21::ExampleModel::bin_operator(char sym, double a, double b) {
  switch (sym) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return (b == 0) ? std::numeric_limits<double>::quiet_NaN() : a / b;
    case '^':
      return pow(a, b);
    case '%':
      return (b == 0) ? std::numeric_limits<double>::quiet_NaN()
                      : std::fmod(a, b);
    default:
      return std::numeric_limits<double>::quiet_NaN();
  }
}
void s21::ExampleModel::error_empty() {
  throw std::invalid_argument("Error: Empty expression");
}

void s21::ExampleModel::error_empty_stack() {
  throw std::invalid_argument("Error: Not enough values for unary operator");
}

void s21::ExampleModel::error_bin_operator() {
  throw std::invalid_argument("Error: Not enough values for binary opearator");
}

double s21::ExampleModel::evalute_postfix(const std::string& infix,
                                          double x_value) {
  std::string postfix_exp = infix_postfix(infix);
  if (postfix_exp.empty()) {
    error_empty();
  }
  std::stack<double> num;
  std::istringstream is(postfix_exp);
  std::string token;

  while (is >> token) {
    if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
      num.push(std::stod(token));
    } else if (token == "x") {
      num.push(x_value);
    } else if (is_functions(token[0])) {
      if (num.empty()) {
        error_empty_stack();
      }
      double val = num.top();
      num.pop();
      double res = unar_operator(token[0], val);
      num.push(res);
    } else {
      if (num.size() < 2) {
        error_bin_operator();
      }
      double b = num.top();
      num.pop();
      double a = num.top();
      num.pop();
      double res = bin_operator(token[0], a, b);
      num.push(res);
    }
  }
  data = num.top();
  return num.top();
}