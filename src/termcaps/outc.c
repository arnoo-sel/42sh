/*
** outc.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Fri Jun 13 12:39:55 2008 arnaud sellier
** Last update Fri Jun 13 12:40:20 2008 arnaud sellier
*/

#include "42sh.h"

#if (OS==SUN)
int	outc(char c)
{
  my_putchar(c);
  return (1);
}
#else
int	outc(int c)
{
  my_putchar(c);
  return (1);
}
#endif
