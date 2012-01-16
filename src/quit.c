/*
** quit.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Mon May  5 13:10:29 2008 arnaud sellier
** Last update Wed Jun 11 13:26:40 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

void		free_bg_table(t_param *param)
{
  t_bg_item	*item;

  while ((item = vector_pop(param->bg_table)))
    msfree(item->cmd, item, 0);
  vector_free(param->bg_table);
}

void		free_all(t_param *param)
{
  free_bg_table(param);
  xsfree_all();
}

void		quit_ctrl_d(t_param *param)
{
  free_all(param);
  exit(0);
}
