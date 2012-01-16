/*
** functions_line.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Sun Jun  1 23:46:13 2008 arnaud sellier
** Last update Sun Jun  1 23:48:21 2008 arnaud sellier
*/

#include "42sh.h"

void	beginning_of_line(t_param *param, t_bindkeys *bind)
{
  my_tputs(param->cap.rcstr);
  bind->cursor_pos = 0;
}

void	end_of_line(t_param *param, t_bindkeys *bind)
{
  if (bind->cursor_pos < bind->nb_read)
    {
      my_tputs(param->cap.rcstr);
      if (bind->nb_line)
	my_tputs_one(param->cap.DOstr, bind->nb_line);
      if ((bind->cur_start - 1 + bind->nb_read) % param->cap.cols -
	  (bind->cur_start - 1) > 0)
	my_tputs_one(param->cap.RIstr, (bind->cur_start - 1 + bind->nb_read) %
		     param->cap.cols - (bind->cur_start - 1));
      else if ((bind->cur_start - 1 + bind->nb_read) % param->cap.cols -
	       (bind->cur_start - 1) < 0)
	my_tputs_one(param->cap.LEstr,
		     -((bind->cur_start - 1 + bind->nb_read) %
		       param->cap.cols - (bind->cur_start - 1)));
    }
   bind->cursor_pos = bind->nb_read;
}

void	kill_line(t_param *param, t_bindkeys *bind)
{
  memset(bind->clipboard, 0, BUF);
  my_strcpy(bind->clipboard, bind->buf + bind->cursor_pos);
  my_tputs(param->cap.cdstr);
  bind->nb_read = bind->cursor_pos;
  bind->buf[bind->nb_read] = 0;
}

void	kill_whole_line(t_param *param, t_bindkeys *bind)
{
  if (bind->nb_read)
    {
      memset(bind->clipboard, 0, BUF);
      my_strcpy(bind->clipboard, bind->buf);
      my_tputs(param->cap.rcstr);
      my_tputs(param->cap.cdstr);
      memset(bind->buf, 0, BUF);
      bind->cursor_pos = 0;
      bind->nb_read = 0;
    }
}

void	my_clear_screen(t_param *param, t_bindkeys *bind)
{
  my_tputs(param->cap.clstr);
  my_putstr(param->prompt);
  my_tputs(param->cap.scstr);
  aff_refresh(param, bind->buf, bind->cursor_pos, bind);
}
