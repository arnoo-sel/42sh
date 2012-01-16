/*
** functions_bind.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Thu May 29 10:51:52 2008 arnaud sellier
** Last update Mon Jun  2 01:00:26 2008 arnaud sellier
*/

#include "42sh.h"

void	delete_char_or_list_or_eof(t_param *param, t_bindkeys *bind)
{
  if (bind->cursor_pos < bind->nb_read)
    {
      to_left(bind->buf, bind->cursor_pos, bind->nb_read);
      bind->nb_read -= 1;
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
    }
  else
    DING;
}

void	bell_bell(t_param *param, t_bindkeys *bind)
{
  param = param;
  bind = bind;
  DING;
}

void		backward_delete_char(t_param *param, t_bindkeys *bind)
{
  if (bind->cursor_pos > 0)
    {
      my_tputs(param->cap.lestr);
      bind->cursor_pos -= 1;
      to_left(bind->buf, bind->cursor_pos, bind->nb_read);
      bind->nb_read -= 1;
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
    }
  else
    DING;
}

void	transpose_chars(t_param *param, t_bindkeys *bind)
{
  if (bind->cursor_pos && bind->cursor_pos < bind->nb_read)
    {
      bind->swap_tmp = bind->buf[bind->cursor_pos];
      bind->buf[bind->cursor_pos] = bind->buf[bind->cursor_pos - 1];
      bind->buf[bind->cursor_pos - 1] = bind->swap_tmp;
      bind->cursor_pos += 1;
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
    }
  else if (bind->cursor_pos && bind->nb_read > 1)
    {
      bind->swap_tmp = bind->buf[bind->cursor_pos - 1];
      bind->buf[bind->cursor_pos - 1] = bind->buf[bind->cursor_pos - 2];
      bind->buf[bind->cursor_pos - 2] = bind->swap_tmp;
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
    }
  else
    DING;
}

void	yank(t_param *param, t_bindkeys *bind)
{
  if (my_strlen(bind->clipboard))
    {
      bind->nb_read += my_strlen(bind->clipboard);
      to_right(bind->buf, bind->cursor_pos, bind->nb_read,
	       my_strlen(bind->clipboard));
      memcpy(bind->buf + bind->cursor_pos, bind->clipboard,
	     my_strlen(bind->clipboard));
      bind->cursor_pos += my_strlen(bind->clipboard);
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
    }
  else
    DING;
}
