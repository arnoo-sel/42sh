/*
** init_termcaps.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Thu May 22 12:54:24 2008 arnaud sellier
** Last update Thu Jun 12 16:15:53 2008 arnaud sellier
*/

#include "42sh.h"

char	*xtgetstr(char *cap, char **area)
{
  char	*capstr;

  if ((capstr = tgetstr(cap, area)) == NULL)
    {
      my_putstr("Problem getting ");
      my_putstr(cap);
      my_putchar('\n');
      my_putstr("Run './42sh t' for non-termcaps mode\n");
      exit(1);
    }
  return (capstr);
}

void	load_capacities(t_param *param, char *area, char t[4096])
{
  area = t;
  param->cap.clstr = xtgetstr("cl", &area);
  param->cap.kustr = xtgetstr("ku", &area);
  param->cap.kdstr = xtgetstr("kd", &area);
  param->cap.klstr = xtgetstr("kl", &area);
  param->cap.krstr = xtgetstr("kr", &area);
  param->cap.kbstr = xtgetstr("kb", &area);
  param->cap.dostr = xtgetstr("do", &area);
  param->cap.DOstr = xtgetstr("DO", &area);
  param->cap.upstr = xtgetstr("up", &area);
  param->cap.UPstr = xtgetstr("UP", &area);
  param->cap.lestr = xtgetstr("le", &area);
  param->cap.LEstr = xtgetstr("LE", &area);
  param->cap.ristr = xtgetstr("nd", &area);
  param->cap.RIstr = xtgetstr("RI", &area);
  param->cap.cestr = xtgetstr("ce", &area);
  param->cap.scstr = xtgetstr("sc", &area);
  param->cap.rcstr = xtgetstr("rc", &area);
  param->cap.cdstr = xtgetstr("cd", &area);
  param->cap.ksstr = xtgetstr("ks", &area);
  param->cap.cols = tgetnum("co");
  param->cap.line = tgetnum("li");
}

void	init_tc(t_param *param)
{
  char	*term;
  char	bp[1024];
  char	t[4096];
  char	*area;

  if ((term = getenv("TERM")) == NULL)
    {
      my_putstr("Can't determine terminal\n");
      my_putstr("Run './42sh t' for non-termcaps mode\n");
      exit(1);
    }
  if (tgetent(bp, term) == ERR)
    {
      my_putstr("Can't get the termcaps base\n");
      my_putstr("Run './42sh t' for non-termcaps mode\n");
      exit(1);
    }
  area = t;
  load_capacities(param, area, t);
}
