#include <stdio.h>
#include <stdlib.h>

enum consts { STR_SIZE = 50, SUCC = 0, FAIL = 1 };

int read_str(char *str);
int str_ptrn(char *str1, char *str2);
int match_star(char *str1, char *str2);

int main(void) {
  char str1[STR_SIZE];
  char str2[STR_SIZE];

  read_str(str1);
  printf("String 1 is: %s\n", str1);
  
  read_str(str2);
  printf("String 2 is: %s\n", str2);

  if (str_ptrn(str1, str2) == SUCC)
    fputs("Strings are equal!\n", stdout);
  else
    fputs("Strings are different!\n", stdout);
}


int read_str(char *str) {
  if (!fgets(str, STR_SIZE - 1, stdin)) {
      if (ferror(stdin)) {
        perror("stdin");
        return FAIL;
      }
  }

  for (int i = 0; str[i]; i++) {
    if (str[i] == '\n') {
        str[i] = '\0';
        break;
    }
    else if (str[i] == ' ') {
        fprintf(stderr, "read_str: string should be one word!\n");
        exit(FAIL);
    }
  }
  return SUCC;
}

int str_ptrn(char *str1, char *str2) {
  if (!(*str1) && !(*str2))
    return SUCC;
  if ((!(*str1) ^ !(*str2)))
    return FAIL;
  else if (*str1 == *str2)
    return str_ptrn(str1+1, str2+1);
  else if (*str2 == '?')
    return str_ptrn(str1+1, str2+1);
  else if (*str2 == '*')
    return match_star(str1, str2+1);
  else
    return FAIL;
}

int match_star(char *str1, char *str2) {
  if (!(*str2))
    return SUCC;
  else if (*str1 == *str2)
    return str_ptrn(str1+1, str2+1);
  else if(!(*str1))
    return FAIL;
  else 
    return match_star(str1+1, str2);
}
