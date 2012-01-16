/*
** subs_search_hist.c for 42sh in /home/farges_y/link/42sh/mysh/src/history
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Sun Jun  1 23:14:23 2008 yoam farges
** Last update Sun Jun  1 23:15:33 2008 yoam farges
*/

#include "42sh.h"

int	subs_search_history(int i, t_param *param, char *subs)
{
  int	idx;
  int	nbr;
  int	pos;

  saveprev(param, subs);
  idx = -1;
  while (endsubs(subs[++idx]) == 0)
    if ((subs[idx] < '0') || (subs[idx] > '9'))
      return (subs_startstr_history(i, param, subs));
  nbr = my_getnbr(subs);
  pos = search_nbr_history(param, nbr);
  if (pos == -1)
    {
      my_printf("%s: Event not found.\n", subs);
      subs[0] = 0;
      mix_str_subs_hist(subs, param, i, 0);
      xsfree(subs);
      return (1);
    }
  mix_str_subs_hist(HIST.history[pos], param, i, my_strlen(subs));
  xsfree(subs);
  if ((pos = history_substitution(param)) == 2)
    return (0);
  return (pos);
}

int	subs_prev_command(int i, t_param *param, char *subs)
{
  char	*str;

  str = xsmalloc(sizeof(*str) * 4);
  str[0] = '!';
  str[1] = '-';
  str[2] = '1';
  str[3] = 0;
  param->line[i + 1] = '0';
  mix_str_exclam_mark(str, param, i, 1);
  xsfree(subs);
  xsfree(str);
  str = xsmalloc(sizeof(*str) * 3);
  str[0] = '-';
  str[1] = '1';
  str[2] = 0;
  return (subs_backsearch_history(i, param, str, 1));
}

int	err_backsearch(int i, t_param *param, char *subs, int flag)
{
  int	idx;

  idx = 0;
  while (endsubs(subs[++idx]) == 0)
    if ((subs[idx] < '0') || (subs[idx] > '9'))
      return (2);
  if ((idx == 1) || (HIST.nb_max_hist == 0))
    {
      if (idx == 1)
	my_printf("!: Event not found.\n");
      else if (HIST.nb_max_hist == 0)
	my_printf("!%d: Event not found.\n", (1 - my_getnbr(subs + 1)));
      subs[0] = 0;
      if (flag == 1)
	mix_str_exclam_mark(subs, param, i, 0);
      else
	mix_str_subs_hist(subs, param, i, 0);
      xsfree(subs);
      return (1);
    }
  return (0);
}

int	err_parse_backsearch(int i, t_param *param, char *subs, int flag)
{
  my_printf("%d: Event not found.\n",
	    (HIST.nbr_hist[HIST.pos_hist] - my_getnbr(subs + 1) + 1));
  subs[0] = 0;
  if (flag == 1)
    mix_str_exclam_mark(subs, param, i, 0);
  else
    mix_str_subs_hist(subs, param, i, 0);
  xsfree(subs);
  return (1);
}

int	subs_backsearch_history(int i, t_param *param, char *subs, int flag)
{
  int	nbr;
  int	pos;

  saveprev(param, subs);
  if ((pos = err_backsearch(i, param, subs, flag)) == 1)
    return (1);
  else if (pos == 2)
    return (subs_startstr_history(i, param, subs));
  nbr = (HIST.nbr_hist[HIST.pos_hist] - my_getnbr(subs + 1) + 1);
  pos = search_nbr_history(param, nbr);
  if (pos == -1)
    return (err_parse_backsearch(i, param, subs, flag));
  if (flag == 1)
    mix_str_exclam_mark(HIST.history[pos], param, i, my_strlen(subs));
  else
    mix_str_subs_hist(HIST.history[pos], param, i, my_strlen(subs));
  xsfree(subs);
  if ((pos = history_substitution(param)) == 2)
    return (0);
  return (pos);
}
