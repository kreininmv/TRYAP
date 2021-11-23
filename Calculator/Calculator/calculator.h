#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <iostream>


struct syntax_error : public  std::runtime_error {
  const char* file_name;
  const char* function_name;
  int   num_line = -1;
  const char* type_error;
  const char* descr;

  syntax_error(const char* file, const char* function, int line, const char* err, char* des) :
    file_name(file),
    function_name(function),
    num_line(line),
    type_error(err),
    descr(des),
    std::runtime_error(err)
  {
  }

  virtual const char* what()
  {
    return type_error;
  }
};

#define ASSERT_ERROR(expr, err)                                         \
if (expr)                                                               \
{                                                                       \
  throw syntax_error(__FILE__, __func__, __LINE__, err, str);           \
}                                                              

//Just need to save it 
class calculator {

  char *str = nullptr;
  int len_str = 0;

public:

  double GetG(const char *s) {

    //Prepare for calculate
    ////////////////////////////////////
    len_str = strlen(s);
    str = new char[len_str];

    int i_sym = 0, cur_sym_str = 0;
    
    while (s[i_sym] != 0)
      if (s[i_sym] != ' ')
        str[cur_sym_str++] = s[i_sym++];
      else
        i_sym++;

    str[cur_sym_str] = 0;
    len_str = cur_sym_str;
    ////////////////////////////////////

    double val = GetE();

    ASSERT_ERROR(*str != 0, "Doesn't end in zero");
    
    //if (*str != 0){ ;  //ERROR("doesn't end in zero")}

    return val;
  }

private:
  double GetE(void) {
    char *unary_oper = str;
    
    double val = GetT();

    if (unary_oper == str)
      val = 0;

    while (*str == '+' || *str == '-') {
      char oper = *str;
      str++;
      double val2 = GetT();

      if (oper == '+')
        val += val2;
      else
        val -= val2;
    }

    return val;
  }

  double GetT(void) {

    double val = GetW();

    while (*str == '*' || *str == '/') {

      char oper = *str;
      str++;
      double val2 = GetW();

      if (oper == '*')
        val *= val2;
      else
        val /= val2;

    }

    return val;
  }

  double GetW(void) {
    double val = GetP();

    while (*str == '^') {

      str++;
      double val2 = GetP();

      val = pow(val, val2);
    }

    return val;
  }

  double GetP(void) {
    if (*str == '(') {
      str++;
      double val = GetE();

      ASSERT_ERROR(*str != ')', "Doesn't end in close bracket ')'");
      //if (*str != ')') { ;//ERROR; }
      str++;

      return val;
    }
    else
      return GetN();
  }

  double GetN(void) {

    double val = 0;
    char *p = str;

    while ('0' <= *str && *str <= '9') {
      val = val * 10 + *str - '0';
      str++;
    }

    ASSERT_ERROR((str == p) && (*p != '+') && (*p != '-'), "Doesn't read any number (maybe it's a symbol)");
    //if ((str == p) && (*p != '+') && (*p != '-')) {;//ERROR;}
    
    return val;
  }


};

#endif