#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "convert.h"
#include "operators.h"

int     c_find(char c, const char *s)
{
  int x;

  if (!s)
    return -1;
  for (x = 0; s[x] && s[x] != c; x++);
  return s[x] ? x : -1;
}

char  *revert_string(char *s, int size)
{
  int   i = 0;
  char  tmp;

  if (!s)
    return s;
  --size;
  while (i < size) {
      tmp = s[i];
      s[i++] = s[size];
      s[size--] = tmp;
    }
  return s;
}

char    *convert_from(const char *s, const char *base)
{
  if (!s || !base)
    return 0;

  int         size = strlen(base), size2 = strlen(s), x, pos;
  char        b_size[10] = {0};
  char        *res = 0;
  char        *pow = 0;
  char        *tmp, *tmp2;
  char        container[10] = {0};

  if (!size || !size || !(res = malloc(sizeof(*res) * 2))
      || !(pow = malloc(sizeof(*pow) * 2)))
    return 0;
  sprintf(b_size, "%d", size);
  res[0] = '0';
  res[1] = 0;
  pow[0] = '1';
  pow[1] = 0;
  for (x = size2 - 1; x >= 0; --x) {
      if ((pos = c_find(s[x], base)) == -1) {
          free(res);
          free(pow);
          return 0;
        }
      sprintf(container, "%d", pos);
      if ((tmp = mult(pow, container))) {
          tmp2 = add(tmp, res);
          free(res);
          res = tmp2;
          free(tmp);
          tmp = mult(pow, b_size);
          free(pow);
          pow = tmp;
        }
    }
  free(pow);
  return res;
}

char    *convert_to(const char *s, const char *to_base)
{
  char  *tmp, *copy, length_base[10] = {0}, *ret;
  int   size, i = 0, integ;

  if (!s || !to_base)
    return 0;
  copy = strdup(s);
  size = 10;
  if (!(ret = malloc(sizeof(*ret) * size)))
    return 0;
  sprintf(length_base, "%d", strlen(to_base));
  while (strcmp(copy, "0")) {
      tmp = modulo(copy, length_base);
      integ = atoi(tmp);
      free(tmp);
      ret[i++] = to_base[integ];
      if (i > size - 1) {
          size += 10;
          ret = realloc(ret, size);
        }
      tmp = divide(copy, length_base);
      free(copy);
      copy = tmp;
    }
  free(copy);
  ret[i] = 0;
  return revert_string(ret, strlen(ret));
}

char  *convert(const char *number, const char *from_base, const char *to_base)
{
  char  *tmp, *tmp2;

  tmp = convert_from(number, from_base);
  tmp2 = convert_to(tmp, to_base);
  free(tmp);
  return tmp2;
}
