#include "calculator.h"

int main(void) {

  try {
    calculator my;
    std::string str_calc;
    std::getline(std::cin, str_calc);
    //std::cout << std::endl << str_calc << std::endl;
    std::cout << my.GetG(str_calc.c_str());
  }
  catch (syntax_error& error) {
    fprintf(stderr, "ACHTUNG!!!\n\n"
      "FILE: %s\n"
      "FUNCTION: %s\n"
      "LINE: %d\n"
      "ERROR TYPE: %s\n"
      "SYNTAX ERROR IN: %s",
      error.file_name, error.function_name, error.num_line, error.type_error, error.descr);
  }
  catch (std::exception& err) {
    fprintf(stderr, "PROBLEM: %s\n", err.what());
  }
  catch (...) {
    fprintf(stderr, "I don't know what is it\n");
  }

  return 0;
}