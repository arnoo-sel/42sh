/*
** jobs.c for 42sh in /u/epitech_2012/jartho_d/cu/public/perso/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Thu Jun 12 14:02:22 2008 adrien1 jarthon
** Last update Fri Jun 13 14:33:30 2008 adrien1 jarthon
*/

#include "42sh.h"

int	b_jobs(t_param *param, char **cmd)
{
  int	len;
  int	pos;

  len = 0;
  while (cmd[len] != NULL)
    len++;
  if (len > 1)
    my_printf("jobs: Too many arguments.\n");
  else
    {
      pos = 0;
      while (pos < vector_size(param->bg_table))
	{
	  if (param->bg_table->data[pos])
	    my_printf("bg [%d] : '%s'\n", ((t_bg_item*)
					   param->bg_table->data[pos])->pid,
		      ((t_bg_item*)param->bg_table->data[pos])->cmd);
	  pos++;
	}
    }
  return (0);
}
