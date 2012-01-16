/*
** functions_arrows.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Sun Jun  1 23:40:44 2008 arnaud sellier
** Last update Mon Jun  2 00:49:51 2008 arnaud sellier
*/

#include "42sh.h"

void	down_history_first_position(t_param *param, t_bindkeys *bind)
{
     memset(bind->buf, 0, BUF);
     strcpy(bind->buf, bind->cur_save);
     bind->cursor_pos = 0;
     bind->nb_read = 0;
     bind->cursor_pos = strlen(bind->buf);
     bind->nb_read = bind->cursor_pos;
     aff_refresh(param, bind->buf, bind->cursor_pos, bind);
}

void	down_history(t_param *param, t_bindkeys *bind)
{
  int	in_tab;

  bind->history_pos -= 1;
  if (bind->history_pos == 0)
    {
      down_history_first_position(param, bind);
      return;
    }
  if ((in_tab = search_back_in_history(param, bind->history_pos)) == -1)
    {
      DING;
      bind->history_pos += 1;
    }
  else
    {
      memset(bind->buf, 0, BUF);
      strcpy(bind->buf, HIST.history[in_tab]);
      bind->cursor_pos = strlen(bind->buf);
      bind->nb_read = bind->cursor_pos;
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
    }
}

void	up_history(t_param *param, t_bindkeys *bind)
{
  int	in_tab;

  if (bind->history_pos == 0)
    {
      memset(bind->cur_save, 0, BUF);
      strcpy(bind->cur_save, bind->buf);
    }
  bind->history_pos += 1;
  if ((in_tab = search_back_in_history(param, bind->history_pos)) == -1)
    {
      DING;
      bind->history_pos -= 1;
    }
  else
    {
      memset(bind->buf, 0, BUF);
      strcpy(bind->buf, HIST.history[in_tab]);
      bind->cursor_pos = strlen(bind->buf);
      bind->nb_read = bind->cursor_pos;
      aff_refresh(param, bind->buf, bind->cursor_pos, bind);
    }
}

void	backward_char(t_param *param, t_bindkeys *bind)
{
  if (bind->cursor_pos > 0)
    {
      if (((bind->cur_start - 1 + bind->cursor_pos) % param->cap.cols + 1) ==
	  1)
	{
	  my_tputs_one(param->cap.UPstr, 1);
          my_tputs_one(param->cap.RIstr, param->cap.cols - 1);
	}
      else
	my_tputs(param->cap.lestr);
      bind->cursor_pos -= 1;
    }
  else
    DING;
}

void	forward_char(t_param *param, t_bindkeys *bind)
{
  if (bind->cursor_pos < bind->nb_read)
    {
      if (((bind->cur_start - 1 + bind->cursor_pos) % param->cap.cols + 1) ==
	  param->cap.cols)
	{
	  my_tputs_one(param->cap.DOstr, 1);
	  my_tputs_one(param->cap.LEstr, param->cap.cols - 1);
	}
      else
	my_tputs(param->cap.ristr);
      bind->cursor_pos += 1;
    }
  else
    DING;
}
