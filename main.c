#include <stdio.h>
#include <stdlib.h>

#include "operators.h"
#include "convert.h"

void    do_mult(const char *s1, const char *s2)
{
  char *s = mult(s1, s2);
  printf("%s * %s = %s\n", s1, s2, s);
  free(s);
  s = add(s1, s2);
  printf("=> %s + %s = %s\n", s1, s2, s);
  free(s);
}

void  do_convert(const char *n, const char *base)
{
  char *s = convert_from(n, base), *tmp;

  printf("from: %s -> %s\n", n, s);
  tmp = s;
  s = convert_to(tmp, base);
  printf("to:   %s -> %s\n", tmp, s);
  free(tmp);
  free(s);
}

void  do_substract(const char *n, const char *n2)
{
  char *s = substract(n, n2);
  printf("%s - %s = %s\n", n, n2, s);
  free(s);
}

void  do_divide(const char *n, const char *n2)
{
  char *s = divide(n, n2);
  printf("%s / %s = %s\n", n, n2, s);
  free(s);
}

void  do_mod(const char *n1, const char *n2)
{
  char *s = modulo(n1, n2);
  printf("%s %% %s = %s\n", n1, n2, s);
  free(s);
}

void  converter(const char *n, const char *from, const char *to)
{
  char  *tmp;

  tmp = convert(n, from, to);
  printf("%s -> %s\n", n, tmp);
  free(tmp);
}

int main(void)
{
  do_mult("1", "3");
  do_mult("9", "2");
  do_mult("10", "42");
  do_mult("9", "99");
  do_convert("101010", "01");
  do_convert("2A", "0123456789ABCDEF");
  do_substract("10", "5");
  do_substract("11", "9");
  do_substract("100", "99");
  do_divide("10", "2");
  do_divide("21", "2");
  do_divide("500", "4");
  do_divide("500", "25");
  do_divide("500000000000000005", "5");
  do_divide("500000000500000005", "5");
  do_divide("500000000500000005", "2");
  do_divide("833", "42");
  do_divide("50458", "357");
  do_divide("80303", "42");
  do_mod("10", "2");
  do_mod("11", "2");
  do_mod("50", "4");
  do_mod("50000", "7");
  do_mod("50000", "365");
  converter("101010", "01", "0123456789ABCDEF");
  converter("101010", "01", "0123456789");
  converter("11101110", "01", "abcdefghij");
  converter("99989998", "89", "abcdefghij");
  return 0;
}
