/*
** go_complete.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Thu Jun 12 15:04:52 2008 arnaud sellier
** Last update Fri Jun 13 12:29:04 2008 arnaud sellier
*/

#include "42sh.h"

int	find_same_begin(t_vector *mylist)
{
  int	nb, j;
  char	tmp[BUF];

  nb = 0;
  while (42)
    {
      memset(tmp, 0, BUF);
      strncpy(tmp, mylist->data[0], nb + 1);
      j = 1;
      while (j < mylist->nb_elem)
	{
	  if (strncmp(tmp, mylist->data[j], nb + 1))
	    return (nb);
	  j++;
	}
      nb++;
    }
}

void	several_completion(t_param *param, t_bindkeys *bind,
			   t_complete *complete)
{
  DING;
  my_putchar(10);
  complete->same = find_same_begin(complete->mylist);
  memset(complete->first_chars, 0, BUF);
  memcpy(complete->first_chars, complete->mylist->data[0], complete->same);
  insert_in_buf(param, bind, complete->first_chars +
		strlen(complete->tmp + complete->pos));
  aff_completion_possibilities(param, complete->mylist);
  my_printf(param->prompt);
  get_coords(&bind->cur_start, &bind->y_start);
  my_tputs(param->cap.ksstr);
  my_tputs(param->cap.scstr);
  aff_refresh(param, bind->buf, bind->cursor_pos, bind);
}

void	go_complete(t_param *param, t_bindkeys *bind, t_complete *complete)
{
  if (complete->mylist->nb_elem == 0)
    DING;
  else if (complete->mylist->nb_elem == 1)
    {
      my_strcpy(complete->first_chars, complete->mylist->data[0]
	     + strlen(complete->tmp + complete->pos));
      insert_in_buf(param, bind, complete->first_chars);
      if (complete->first_chars[strlen(complete->first_chars) - 1] != '/')
	insert_in_buf(param, bind, " ");
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
    }
  else
    several_completion(param, bind, complete);
}
