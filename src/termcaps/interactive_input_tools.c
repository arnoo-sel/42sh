/*
** interactive_input_tools.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Sun Jun  1 21:16:37 2008 arnaud sellier
** Last update Sun Jun  1 21:19:40 2008 arnaud sellier
*/

#include "42sh.h"

int	iskey(char try[], char *ref)
{
  if (my_strcmp(try, ref) == 0)
    return (1);
  return (0);
}

/*
** Deplace la chaine dans le buffer
*/

void	to_right(char buf[], int cursor_pos, int nb_read, int len)
{
  while (nb_read + len - 1 > cursor_pos)
    {
      buf[nb_read + len - 1] = buf[nb_read - 1];
      nb_read--;
    }
}

void	to_left(char buf[], int cursor_pos, int nb_read)
{
  while (cursor_pos < nb_read)
    {
      buf[cursor_pos] = buf[cursor_pos + 1];
      cursor_pos++;
    }
}

/*
** Return 1 pour CTRL_A, 2 pour CTRL_B, etc ...
*/

int	ctrl_key(char buf[])
{
  if (buf[1] == 0)
    return (buf[0]);
  return (-1);
}
