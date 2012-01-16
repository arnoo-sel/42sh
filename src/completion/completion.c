/*
** completion.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Sun Jun  1 14:53:18 2008 arnaud sellier
** Last update Fri Jun 13 12:41:41 2008 arnaud sellier
*/

#include "42sh.h"

int	my_compcmp(const void *d1, const void *d2)
{
  return (my_stricmp(*(char **)d1, *(char **)d2));
}

void	insert_in_buf(t_param *param, t_bindkeys *bind, char tmp2[])
{
  if (anti_segfault(param, bind, bind->buf, my_strlen(tmp2)))
    return;
  bind->nb_read += my_strlen(tmp2);
  to_right(bind->buf, bind->cursor_pos, bind->nb_read, my_strlen(tmp2));
  memcpy(bind->buf + bind->cursor_pos, tmp2, my_strlen(tmp2));
  bind->cursor_pos += my_strlen(tmp2);
}

int	find_longest(t_vector *mylist)
{
  int	j;
  int	max = 0;

  j = 0;
  while (j < mylist->nb_elem)
    {
      max = MAX(max, my_strlen(mylist->data[j]));
      j++;
    }
  return (max);
}

void		init_complete(t_complete *cp)
{
  cp->is_first_word = 0;
  cp->is_file = 0;
  cp->mylist = vector_init();
}

void		complete_word(t_param *param, t_bindkeys *bind)
{
  t_complete	cp;

  init_complete(&cp);
  strcpy(cp.tmp, bind->buf);
  cp.pos = find_start_of_word(bind, cp.tmp);
  if (find_completion_type(param, bind, &cp))
    return;
  if (cp.is_file)
    cp.thislist = cp.filelist;
  else if (cp.pos == bind->cursor_pos)
    cp.thislist = param->local_tab;
  else if (cp.is_first_word)
    cp.thislist = param->cmd_tab;
  else
    cp.thislist = param->local_tab;
  cp.j = -1;
  while (++cp.j < cp.thislist->nb_elem)
    if (strncmp(cp.thislist->data[cp.j], cp.tmp +
		cp.pos, strlen(cp.tmp + cp.pos)) == 0)
      vector_push(cp.mylist, cp.thislist->data[cp.j]);
  qsort(cp.mylist->data, cp.mylist->nb_elem, sizeof(void*), my_compcmp);
  go_complete(param, bind, &cp);
  if (cp.is_file)
    free_completion_tab(cp.filelist);
  vector_free(cp.mylist);
}
