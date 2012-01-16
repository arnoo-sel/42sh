/*
** build_delimiters_tab.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/inhibitors
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Tue May 27 15:36:25 2008 jocelyn de-la-rosa
** Last update Tue May 27 15:59:17 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

char		**build_delimiters_tab(char *ptr, ...)
{
  va_list	va;
  char		*p;
  int		n;
  char		**pastab;

  n = 0;
  va_start(va, ptr);
  while (va_arg(va, void*))
    n++;
  pastab = xsmalloc(sizeof(*pastab) * (n + 2));
  va_end(va);
  va_start(va, ptr);
  n = 0;
  p = ptr;
  pastab[n++] = p;
  while ((p = va_arg(va, void*)))
    {
      pastab[n] = p;
      n++;
    }
  pastab[n] = 0;
  va_end(va);
  return (pastab);
}
