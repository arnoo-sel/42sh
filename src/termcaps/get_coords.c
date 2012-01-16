/*
** get_coords.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Sun Jun  1 21:07:03 2008 arnaud sellier
** Last update Mon Jun  2 00:14:13 2008 arnaud sellier
*/

#include "42sh.h"

void	parse_device_answer(char buf[], int *x, int *y)
{
  int	i;
  int	save;

  save = 0;
  i = 1;
  while (buf[i])
    {
      if (buf[i] == ';')
	{
	  buf[i] = 0;
	  *y = atoi(buf + 2);
	  save = i + 1;
	}
      else if (buf[i] == 'R')
	{
	  buf[i] = 0;
	  *x = atoi(buf + save);
	}
      i++;
    }
}

void		get_coords(int *x, int *y)
{
  static int	init = 0;
  static int	fd = 0;
  char		buf[400];
  char		pattern[8];

  my_strcpy(pattern, "**;*R*");
  pattern[0] = STAR;
  pattern[2] = STAR;
  pattern[4] = STAR;
  pattern[6] = STAR;
  if (!init)
    if ((fd = open("/dev/tty", O_RDWR)) < 0)
      return;
  init = 1;
  memset(buf, 0, 400);
  write(fd, "[6n", 4);
  read(fd, buf, 400);
  while (!match(buf, pattern))
    {
      memset(buf, 0, 400);
      read(fd, buf, 400);
    }
  parse_device_answer(buf, x, y);
}
