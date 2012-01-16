/*
** complete_word.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Wed Jun 11 14:18:10 2008 arnaud sellier
** Last update Fri Jun 13 11:39:12 2008 arnaud sellier
*/

#include "42sh.h"

int	find_start_of_word(t_bindkeys *bind, char tmp[])
{
  int	i;

  i = bind->cursor_pos;
  tmp[i] = 0;
  while ((i >= 0) && (tmp[i] != ' ') && (tmp[i] != '|') &&
	 (tmp[i] != ';') && (tmp[i] != '&') && (tmp[i] != '/'))
    i--;
  i++;
  return (i);
}

/*
** -CONGRATULATION ! It's a nice file ! 
** -How can you say that Doctor ?
** -The small '/' on the front of ...
** -Hoooo yes I see !
*/

int	its_a_file(t_param *param, t_bindkeys *bind, t_complete *cp)
{
  cp->is_file = 1;
  cp->j = cp->pos - 1;
  while ((cp->j >= 0) && (cp->tmp[cp->j] != ' ') && (cp->tmp[cp->j] != '|') &&
	 (cp->tmp[cp->j] != ';') && (cp->tmp[cp->j] != '&'))
    cp->j--;
  memset(cp->begin_path, 0, BUF);
  strncpy(cp->begin_path, cp->tmp + cp->j + 1,
	  cp->pos - cp->j + 1);
  cp->j = strlen(cp->begin_path) - 1;
  while (cp->begin_path[cp->j] != '/')
    cp->j--;
  cp->begin_path[cp->j + 1] = 0;
  cp->filelist = vector_init();
  if (create_files_tab(param, cp->filelist, cp->begin_path))
    {
      my_printf(param->prompt);
      get_coords(&bind->cur_start, &bind->y_start);
      my_tputs(param->cap.ksstr);
      my_tputs(param->cap.scstr);
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
      return (1);
    }
  return (0);
}

int	find_completion_type(t_param *param, t_bindkeys *bind, t_complete *cp)
{
  if (cp->pos == 0)
    cp->is_first_word = 1;
  else if ((cp->tmp[cp->pos - 1] == ';') || (cp->tmp[cp->pos - 1] == '|') ||
	   (cp->tmp[cp->pos - 1] == '&'))
    cp->is_first_word = 1;
  else if (cp->tmp[cp->pos - 1] == ' ')
    {
      cp->j = cp->pos - 1;
      while (cp->tmp[cp->j] == ' ')
	cp->j--;
      if ((cp->tmp[cp->j] == ';') || (cp->tmp[cp->j] == '|') ||
	  (cp->tmp[cp->j] == '&'))
	cp->is_first_word = 1;
    }
  else if (cp->tmp[cp->pos - 1] == '/')
    return (its_a_file(param, bind, cp));
  return (0);
}
