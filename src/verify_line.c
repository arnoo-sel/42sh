/*
** verify_line.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Tue May  6 10:33:53 2008 arnaud sellier
** Last update Tue May  6 10:59:02 2008 arnaud sellier
*/

#include "42sh.h"

int	too_big(char *line)
{
  if (my_strlen(line) >= BUF - 1)
    return (1);
  return (0);
}
