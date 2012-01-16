/*
** exit.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/builtins
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Tue May  6 10:31:12 2008 jocelyn de-la-rosa
** Last update Tue Jun 10 13:12:11 2008 adrien1 jarthon
*/

#include "42sh.h"

int	b_exit(t_param *param, char **cmd)
{
  put_hist_in_file(param);
  cmd = cmd;
  quit_ctrl_d(param);
  return (0);
}
