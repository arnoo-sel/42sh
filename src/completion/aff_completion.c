/*
** aff_completion.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Thu Jun 12 16:30:45 2008 arnaud sellier
** Last update Thu Jun 12 16:31:31 2008 arnaud sellier
*/

#include "42sh.h"

void	aff_completion_possibilities(t_param *param, t_vector *mylist)
{
  int	longest;
  int	nb_cols;
  int	large;
  int	j;
  int	i;

  longest = find_longest(mylist);
  nb_cols = param->cap.cols / (longest + 2);
  large = param->cap.cols / nb_cols;
  j = 0;
  while (j < mylist->nb_elem)
    {
      i = 0;
      while (i < nb_cols && j + i < mylist->nb_elem)
	{
	  my_printf("%s", mylist->data[j + i]);
	  my_tputs_one(param->cap.RIstr, large - strlen(mylist->data[j + i]));
	  i++;
	}
      my_putchar(10);
      j += nb_cols;
    }
}
