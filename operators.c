#include <string.h>
#include <stdlib.h>
#include "operators.h"

char    *mult(const char *s1, const char *s2)
{
  char    *res;
  int     size1, size2, size3;
  int     x, y;

  if (!s1 || !s2)
    return 0;
  size1 = strlen(s1);
  size2 = strlen(s2);
  size3 = size1 + size2;
  if (!(res = malloc(sizeof(*res) * (size3 + 1)))) {
      return 0;
    }
  memset(res, 0, size3 + 1);
  for (x = size1 - 1; x >= 0; --x) {
      for (y = size2 - 1; y >= 0; --y) {
          int tmp = (s1[x] - '0') * (s2[y] - '0');

          if (tmp > 9) {
              res[x + y] += tmp / 10;
              tmp = tmp % 10;
            }
          res[x + y + 1] += tmp;
          if (res[x + y + 1] > 9) {
              res[x + y] += res[x + y + 1] / 10;
              res[x + y + 1] %= 10;
            }
        }
    }
  for (x = 0; x < size3; ++x) {
      if (res[x] > 9) {
          res[x - 1] += res[x] % 10;
          res[x] %= 10;
          x = -1;
        }
    }
  for (x = 0; x < size3; ++x) {
      res[x] += '0';
    }
  while (res[0] == '0' && res[1]) {
      for (x = 0; x < size3; ++x) {
          res[x] = res[x + 1];
        }
    }
  return res;
}

char    *add(const char *n1, const char *n2)
{
  if (!n1 || !n2)
    return 0;
  int     size1 = strlen(n1), size2 = strlen(n2), x, y;
  char    *res;

  if (size2 > size1)
    return add(n2, n1);

  if (!(res = malloc(sizeof(*res) * (size1 + 2))))
    return 0;
  memset(res, '0', size1 + 1);
  res[size1 + 1] = 0;
  y = size1 - 1;
  for (x = size2 - 1; x >= 0; --x) {
      res[y + 1] += (n1[y] - '0') + (n2[x] - '0');
      if (res[y + 1] > '9') {
          res[y] += 1;
          res[y + 1] = (res[y + 1] - '0') % 10 + '0';
        }
      --y;
    }
  for (;y >= 0; --y) {
      res[y + 1] += (n1[y] - '0');
      if (res[y + 1] > '9') {
          res[y] += 1;
          res[y + 1] = (res[y + 1] - '0') % 10 + '0';
        }
    }
  for (x = 0; res[x]; ++x) {
      if (res[x] < '0')
        res[x] += '0';
    }
  if (res[0] == '0') {
      for (x = 0; res[x] == '0' && res[x + 1]; ++x);
      for (y = 0; res[x]; ++x) {
          res[y++] = res[x];
        }
      res[y] = 0;
    }
  return res;
}

int   check_biggest(int s1, int s2, const char *n1, const char *n2)
{
  if (s1 > s2)
    return 0;
  if (s1 < s2)
    return 1;
  while (*n1 == *n2 && *n1 && *n2) {
      n1++;
      n2++;
    }
  if (!*n1 && !*n2)
    return 2;
  return *n1 < *n2;
}

char    *substract(const char *n1, const char *n2)
{
  int size1, size2, ori;
  char  *ret;

  if (!n1 || !n2)
    return strdup("0");
  size1 = strlen(n1);
  size2 = strlen(n2);
  switch (check_biggest(size1, size2, n1, n2)) {
    case 1:
      return substract(n2, n1);
    case 2:
      return strdup("0");
    default:
      break;
    }
  if (!(ret = malloc(sizeof(*ret) * (size1 + 1)))) {
      return 0;
  }
  memset(ret, '0', size1);
  ret[size1] = 0;
  ori = size1;
  --size1;
  --size2;
  while (size2 >= 0) {
      ret[size1] += (n1[size1] - '0') - (n2[size2] - '0');
      if (ret[size1] < '0') {
          ret[size1 - 1] -= 1;
          ret[size1] += 10;
        }
      --size1;
      --size2;
    }
  while (size1 >= 0) {
      ret[size1] += (n1[size1] - '0');
      --size1;
    }
  while (ret[++size1] == '0');
  if (size1)
    memmove(ret, ret + size1, ori - size1 + 1);
  return ret;
}

int isBigger(const char *n1, const char *n2, int s1, int s2)
{
  if (s1 > s2)
    return 1;
  if (s1 < s2)
    return 0;
  while (*n1 && *n2 && *n1 > *n2 && s1 >= 0) {
      n1++;
      n2++;
      --s1;
    }
  if (!*n1 && !*n2)
    return 2;
  return *n1 >= *n2;
}

int isBigger2(const char *n1, const char *n2, int s1, int s2)
{
  if (s1 > s2)
    return 1;
  if (s1 < s2)
    return 0;
  while (*n1 && *n2 && *n1 == *n2 && s1 > 0) {
      n1++;
      n2++;
      --s1;
    }
  if (!*n1 && !*n2)
    return 2;
  return *n1 >= *n2;
}

int getSuperior(int s1, int s2, const char *n1, const char *n2)
{
  int size = 1, ret;

  while (size < s1 && !(ret = isBigger(n1, n2, size, s2)))
    size++;
  return size;
}

char *getDivider(int portion, char *n1, const char *n2)
{
  char  *multiplier = strdup("0");
  char  *tmp = 0;
  int   ret;

  do {
      free(tmp);
      tmp = multiplier;
      multiplier = add(tmp, "1");
      free(tmp);
      tmp = mult(multiplier, n2);
    } while (!(ret = isBigger2(tmp, n1, strlen(tmp), portion)));
  if (!strncmp(tmp, n1, portion)) {
    free(tmp);
    return multiplier;
  }
  free(tmp);
  tmp = substract(multiplier, "1");
  free(multiplier);
  if (!strcmp(tmp, "0") && portion + 1 <= strlen(n1)) {
    free(tmp);
    return getDivider(portion + 1, n1, n2);
  }
  return tmp;
}

char  *getSubstractNumber(char *n, char *n2)
{
  int size1 = strlen(n), size2 = strlen(n2), add;
  char  *ret;

  if (size1 == size2) {
      return strdup(n2);
    }
  if (*n < *n2) {
      add = size1 - size2 - 1;
    }
  else {
      add = size1 - size2;
    }
  if (add <= 0) {
      return strdup(n2);
    }
  if (!(ret = malloc(sizeof(*ret) * (size2 + add + 1))))
    return 0;
  size2 = 0;
  while (*n2) {
      ret[size2++] = *n2;
      n2++;
    }
  while (add-- > 0) {
      ret[size2++] = '0';
    }
  ret[size2] = 0;
  return ret;
}

char  *divide(const char *n1, const char *n2)
{
  int   size1, size2, pos = 0, sup, x, tmp_size, old_size;
  char  *ret, *tmp, *tmp2, *multi;

  if (!n1 || !n2)
    return 0;
  if (!strcmp(n2, "0")) {
      return strdup("null");
    }
  if (!strcmp(n2, "1")) {
      return strdup(n1);
    }
  size1 = strlen(n1);
  size2 = strlen(n2);
  if (size1 < size2) {
      return strdup("0");
    }
  if (!strcmp(n1, n2)) {
      return strdup("1");
    }
  ret = malloc(sizeof(*ret) * (size1 + 2));
  memset(ret, 0, size1 + 2 * sizeof(*ret));
  tmp = strdup(n1);

  while (strcmp(tmp, "0") && isBigger2(tmp, n2, size1, size2)) {
      sup = getSuperior(size1, size2, tmp, n2);
      multi = getDivider(sup, tmp, n2);
      x = 0;
      while (multi[x])
	ret[pos++] = multi[x++];
      tmp2 = mult(multi, n2);
      tmp_size = strlen(tmp2) - 1;
      free(multi);
      multi = getSubstractNumber(tmp, tmp2);
      free(tmp2);
      tmp2 = multi;
      multi = substract(tmp, tmp2);

      sup = strlen(multi);
      old_size = size1;
      x = 0;
      while (x++ < old_size - sup - size2 - tmp_size) {
          ret[pos++] = '0';
        }

      free(tmp);
      free(tmp2);
      tmp = multi;
      size1 = strlen(tmp);
    }
  free(tmp);
  tmp = mult(ret, n2);
  sup = strlen(n1) - strlen(tmp);
  while (sup-- > 0)
    ret[pos++] = '0';
  free(tmp);

  --pos;
  while (pos >= 0) {
      if (ret[pos] > '9') {
          if (!pos) {
              memcpy(ret + 1, ret, size1 + 1);
              ret[0] = '0';
              pos += 1;
            }
          ret[pos - 1] += 1;
          ret[pos] -= 10;
        }
      --pos;
    }
  if (!ret[0])
    ret[0] = '0';
  return ret;
}

char  *modulo(const char *n1, const char *n2)
{
  int   size1, size2, sup;
  char  *tmp, *tmp2, *multi;

  if (!n1 || !n2)
    return 0;
  if (!strcmp(n2, "0")) {
      return strdup("null");
    }
  if (!strcmp(n2, "1")) {
    return strdup("0");
  }
  size1 = strlen(n1);
  size2 = strlen(n2);
  if (size1 < size2) {
      return strdup(n1);
    }
  if (!strcmp(n1, n2)) {
      return strdup("0");
    }
  tmp = strdup(n1);
  while (strcmp(tmp, "0") && isBigger2(tmp, n2, size1, size2)) {
      sup = getSuperior(size1, size2, tmp, n2);
      multi = getDivider(sup, tmp, n2);
      tmp2 = mult(multi, n2);
      free(multi);
      multi = getSubstractNumber(tmp, tmp2);
      free(tmp2);
      tmp2 = multi;
      multi = substract(tmp, tmp2);
      free(tmp);
      free(tmp2);
      tmp = multi;
      size1 = strlen(tmp);
      if (!strcmp(tmp, n2)) {
	free(tmp);
	return strdup("0");
      }
    }
  return tmp;
}
