/*
** tools_subs_hist.c for 42sh in /home/farges_y/link/42sh/mysh/src/history
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Sun Jun  1 23:16:04 2008 yoam farges
** Last update Sun Jun  1 23:19:38 2008 yoam farges
*/

#include "42sh.h"

void	mix_str_subs_hist(char *subs, t_param *param, int i1, int len)
{
  char	*stoc;
  int	pos;
  int	st;

  stoc = xsmalloc(sizeof(*stoc) * ((my_strlen(param->line) - (len)) +
				   my_strlen(subs) + 1));
  stoc = my_memset(stoc, 0, ((my_strlen(param->line) - (len)) +
			     my_strlen(subs) + 1));
  pos = -1;
  st = -1;
  while (++pos != i1)
    stoc[++st] = param->line[pos];
  pos = -1;
  while (subs[++pos] != 0)
    stoc[++st] = subs[pos];
  pos = i1 + 1;
  while (endsubs(param->line[pos]) == 0)
    pos++;
  pos--;
  while (param->line[++pos] != 0)
    stoc[++st] = param->line[pos];
  stoc[++st] = 0;
  xsfree(param->line);
  param->line = stoc;
}

void	mix_str_exclam_mark(char *subs, t_param *param, int i1, int len)
{
  char	*stoc;
  int	pos;
  int	st;

  stoc = xsmalloc(sizeof(*stoc) * ((my_strlen(param->line) - (len)) +
				   my_strlen(subs) + 1));
  stoc = my_memset(stoc, 0, ((my_strlen(param->line) - (len)) +
			     my_strlen(subs) + 1));
  pos = -1;
  st = -1;
  while (++pos != i1)
    stoc[++st] = param->line[pos];
  pos = -1;
  while (subs[++pos] != 0)
    stoc[++st] = subs[pos];
  pos = i1 + 1;
  while ((endsubs(param->line[pos]) == 0) && (param->line[pos] != '!'))
    pos++;
  pos--;
  while (param->line[++pos] != 0)
    stoc[++st] = param->line[pos];
  stoc[++st] = 0;
  xsfree(param->line);
  param->line = stoc;
}

void	saveprev(t_param *param, char *subs)
{
  if (HIST.prevsearch != NULL)
    xsfree(HIST.prevsearch);
  HIST.prevsearch = my_strdup(subs);
}

int	endsubs(char c)
{
  if ((c == 0) || (c == '"') || (c == '\'') || (c == '<')
      || (c == '>') || (c == '\\') || (c == '|') || (c == '&')
      || (c == ')') || (c == '(') || (c == '{') || (c == '}')
      || (c == ' ') || (c == ';'))
    return (1);
  return (0);
}
