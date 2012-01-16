/*
** termcap_entry.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Thu May 22 15:49:44 2008 arnaud sellier
** Last update Fri Jun 13 12:42:18 2008 arnaud sellier
*/

#include "42sh.h"

#define NEW_PROMPT {my_putchar('\n'); break;}

void	(*g_fbind[])(t_param *, t_bindkeys *) =
{
  beginning_of_line,
  end_of_line,
  delete_char_or_list_or_eof,
  bell_bell,
  backward_delete_char,
  kill_line,
  my_clear_screen,
  down_history,
  up_history,
  transpose_chars,
  kill_whole_line,
  yank,
  backward_char,
  forward_char,
  complete_word,
  0
};

int	anti_segfault(t_param *param, t_bindkeys *bind, char buf[], int addlen)
{
  if (strlen(buf) + addlen > BUF - 2)
    {
      my_tputs(param->cap.rcstr);
      my_tputs(param->cap.cdstr);
      memset(bind->buf, 0, BUF);
      bind->cursor_pos = 0;
      bind->nb_read = 0;
      my_putstr(WORD_TOO_LONG);
      my_putstr("\n");
      return (1);
    }
  return (0);
}

void	init_tc_entry(t_param *param, t_bindkeys *bind)
{
  create_cmd_tab(param);
  create_local_tab(param);
  memset(bind->clipboard, 0, BUF);
  memset(bind->buf, 0, BUF);
  memset(bind->cur_save, 0, BUF);
  bind->nb_read = 0;
  bind->cursor_pos = 0;
  bind->history_pos = 0;
  bind->nb_line = 0;
  uncanonical(&param->saveline);
  get_coords(&bind->cur_start, &bind->y_start);
  my_tputs(param->cap.ksstr);
  my_tputs(param->cap.scstr);
}

int	insert_new_caracters(t_param *param, t_bindkeys *bind)
{
  if (anti_segfault(param, bind, bind->buf, my_strlen(bind->tmp)))
    return (-1);
  bind->nb_read += my_strlen(bind->tmp);
  to_right(bind->buf, bind->cursor_pos, bind->nb_read, my_strlen(bind->tmp));
  memcpy(bind->buf + bind->cursor_pos, bind->tmp, my_strlen(bind->tmp));
  bind->cursor_pos += my_strlen(bind->tmp);
  aff_refresh(param, bind->buf, bind->cursor_pos, bind);
  return (0);
}

t_bindkeys		*creat_bind(int i)
{
  static t_bindkeys	out;

  if (!i)
    return (&out);
  else
    {
      out.nb_read = 0;
      out.cursor_pos = 0;
      memset(out.buf, 0, BUF);
    }
  return (&out);
}

int		termcap_entry(t_param *param, char buf[])
{
  t_bindkeys	*bind;
  int		bindkey;

  bind = creat_bind(0);
  init_tc_entry(param, bind);
  aff_refresh(param, bind->buf, bind->cursor_pos, bind);
  while (42)
    {
      my_memset(bind->tmp, 0, BUF);
      read(0, bind->tmp, BUF);
      if (iskey(bind->tmp, "\n") || (ctrl_key(bind->tmp) == CTRL_J))
	NEW_PROMPT;
      if ((bind->nb_read == 0) && (ctrl_key(bind->tmp) == CTRL_D))
	return (0);
      else if ((bindkey = which_bindkey(param, bind)) == -1)
	  bindkey = which_key(param, bind);
      if (bindkey != -1)
	g_fbind[bindkey](param, bind);
      else if (insert_new_caracters(param, bind) == -1)
	  break;
    }
  strcpy(buf, bind->buf);
  free_completion_tab(param->cmd_tab);
  free_completion_tab(param->local_tab);
  return (1);
}
