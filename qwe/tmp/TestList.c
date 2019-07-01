#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define START_SIZE 4

typedef struct 
{
  int size;
  int locate;
  const char **strings;
} TestList;


TestList* init_TestList()
{
  TestList* ret = (TestList*) malloc (sizeof(TestList));
  ret->size = 0;
  ret->locate = START_SIZE;
  ret->strings = (const char**) malloc (sizeof(char*) * START_SIZE);
  return ret;
}

void add_TestList(TestList* list, const char* newStr)
{
  const char **strings = list->strings;
  int size = list->size;
  if (size >= list->locate)
    {
      printf("size: %i\n", list->size);
      puts("RELOCATE\n");
      list->strings = realloc(list->strings, list->locate*2);
      list->locate = list->locate*2;
//      list->strings = relocate(list->locate*2);
    }
  
  *(strings+size) = newStr;

  list->size = size + 1;
}

int getSize_TestList(TestList* list)
{
  return list->size;
}
const char* getStr_TestList(TestList* list, int i)
{
  return *(list->strings + i);
}

int
main (int argc, char **argv)
{
  char *str1 = (char*) malloc(5);
  //char *str1 = 
  strcpy(str1, "str1");
  const char *str2 = "str2";
  const char *str3 = "str3";
  
  puts("Hello, world!");
  
  TestList* list = init_TestList();
  add_TestList(list, str1);
  add_TestList(list, str2);
  add_TestList(list, str3);
  add_TestList(list, str2);
  add_TestList(list, str1);
  add_TestList(list, str2);
  add_TestList(list, str3);
  add_TestList(list, str2);
  add_TestList(list, str1);
  add_TestList(list, str2);
  add_TestList(list, str3);
  add_TestList(list, str2);
  
  str1[1] = 'R';
//  puts(str3);
  
  printf("%i %s\n", list->size, getStr_TestList(list, 0));
  for (int i = 0; i < getSize_TestList(list); i++)
    printf("%i %s\n", i, getStr_TestList(list, i));
  
  return 0;
}
