/*
** which_function.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Mon Jun  2 00:23:28 2008 arnaud sellier
** Last update Thu Jun 12 16:54:49 2008 arnaud sellier
*/

#include "42sh.h"

int	which_bindkey(t_param *param, t_bindkeys *bind)
{
  param = param;
  if ((bind->tmp[0] == 127 && bind->tmp[1] == 0) ||
      (bind->nb_read && ctrl_key(bind->tmp) == CTRL_D))
    return (DEL_CHAR);
  else if ((ctrl_key(bind->tmp) == CTRL_A))
    return (BEG_OF_LINE);
  else if (ctrl_key(bind->tmp) == CTRL_E)
    return (END_OF_LINE);
  else if (ctrl_key(bind->tmp) == CTRL_G)
    return (BELL_BELL);
  else if (ctrl_key(bind->tmp) == CTRL_L)
    return (CLS);
  else if (ctrl_key(bind->tmp) == CTRL_K)
    return (KILL_LINE);
  else if (ctrl_key(bind->tmp) == CTRL_T)
    return (TRANSPOSE);
  else if (ctrl_key(bind->tmp) == CTRL_U)
    return (KILL_WHOLE);
  else if (ctrl_key(bind->tmp) == CTRL_W)
    return (YANK);
  return (-1);
}

int	which_key(t_param *param, t_bindkeys *bind)
{
  if (iskey(bind->tmp, param->cap.kdstr) || (ctrl_key(bind->tmp) == CTRL_N))
    return (DOWN_HISTORY);
  else if (iskey(bind->tmp, param->cap.kustr) ||
	   (ctrl_key(bind->tmp) == CTRL_P))
    return (UP_HISTORY);
  else if (iskey(bind->tmp, param->cap.klstr) ||
	   (ctrl_key(bind->tmp) == CTRL_B))
    return (BACKWARD);
  else if (iskey(bind->tmp, param->cap.krstr) ||
	   (ctrl_key(bind->tmp) == CTRL_F))
    return (FORWARD);
  else if (iskey(bind->tmp, param->cap.kbstr) ||
	   (ctrl_key(bind->tmp) == CTRL_H))
    return (BACK_DEL);
  else if (iskey(bind->tmp, "\t"))
    return (COMPLETE);
  return (-1);
}
