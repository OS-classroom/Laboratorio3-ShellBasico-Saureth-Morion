#define _POSIX_SOURCE
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "morion.h"

int main ()
{
  char ** items;
  int i, num, background;
  char expresion[TAM];

  printf ("teclea una orden$ ");
  fgets (expresion, TAM, stdin);

  num = separaItems (expresion, &items, &background);

  printf ("Numero de parametros: %d\n", num);

  if (num>0)
  {
    for (i=0; i<num; i++)
      printf ("%d \"%s\"\n", i+1, items[i]);

    printf ("Background: %d\n", background);

    liberaItems (items);
  }

  return 0;
}