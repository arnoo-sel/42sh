/*
** verify_pipeline.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Tue May  6 10:45:02 2008 arnaud sellier
** Last update Fri Jun 13 15:00:20 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	empty(char *pipeline)
{
  int	i;

  if ((!pipeline) || (pipeline[0] == 0))
    return (1);
  i = 0;
  while ((pipeline[i] == ' ') || (pipeline[i] == '\t'))
    {
      if (pipeline[i + 1] == 0)
	return (1);
      i++;
    }
  return (0);
}

/*
** Verifie >>> et <<< ou +
*/

int	verify_nbr(t_pipeline *line)
{
  int	i;
  char	*inhib;

  inhib = xmalloc((strlen(line->line) + 1) * sizeof(*inhib));
  memset(inhib, 4, (strlen(line->line) + 1));
  i = 0;
  while (i < my_strlen(line->line) - 1)
    {
      if ((is_inhibited(line->line, inhib, i) == 0) && (line->line[i] == '>')
	  && (line->line[i + 1] == '>') && (line->line[i + 2] == '>'))
	{
	  my_putstr(BAD_R);
	  FREE_RETURN(inhib, 0);
	}
      else if ((is_inhibited(line->line, inhib, i) == 0) &&
	       (line->line[i] == '<') && (line->line[i + 1] == '<') &&
	       (line->line[i + 2] == '<'))
	{
	  my_putstr(BAD_L);
	  FREE_RETURN(inhib, 0);
	}
      i++;
    }
  FREE_RETURN(inhib, 1);
}

/*
** Verifie que les redir ne soient pas en conflit
** avec les pipes.
*/

int	verify_amb(t_pipeline *line)
{
  int	pipe_found;
  int	i;
  char  *inhib;

  inhib = xmalloc((strlen(line->line) + 1) * sizeof(*inhib));
  memset(inhib, 4, (strlen(line->line) + 1 + (pipe_found = 0)));
  i = -1;
  while (line->line[++i])
    {
      if ((line->line[i] == '|') && (is_inhibited(line->line, inhib, i) == 0))
	pipe_found++;
      if ((line->line[i] == '<') && (pipe_found) &&
	  (is_inhibited(line->line, inhib, i) == 0))
	{
	  my_putstr(AMB_L);
	  FREE_RETURN(inhib, 0);
	}
      if ((line->line[i] == '>') && (pipe_found < line->nb_pipe) &&
	  (is_inhibited(line->line, inhib, i) == 0))
	{
	  my_putstr(AMB_R);
	  FREE_RETURN(inhib, 0);
	}
    }
  FREE_RETURN(inhib, 1);
}

int	verify_pipe(char *s)
{
  int	i;
  int	j;
  char	*inhib;

  inhib = xmalloc((strlen(s) + 1) * sizeof(*inhib));
  memset(inhib, 4, (strlen(s) + 2 + (i = -1)));
  while (s[++i])
    if ((s[j = i] == '|') && (is_inhibited(s, inhib, i) == 0))
      {
	while ((j >= 0) && ((s[j] == ' ') || (s[j] == '\t') || (s[j] == '|')))
	  j--;
	if (j == -1)
	  {
	    my_putstr(BAD_P);
	    FREE_RETURN(inhib, 0);
	  }
	while ((s[++i]) && ((s[i] == ' ') || (s[i] == '\t')));
	if (((s[i] == '|') || (s[i] == '\n') || (s[i] == 0))
	    && (!is_inhibited(s, inhib, i) == 0))
	  {
	    my_putstr(BAD_P);
	    FREE_RETURN(inhib, 0);
	  }
      }
  FREE_RETURN(inhib, 1);
}

int	verify(t_pipeline *line)
{
  if ((verify_r(line->line, '>', AMB_R)) && (verify_r(line->line, '<', AMB_L))
      && (verify_nbr(line)) && (verify_amb(line)) && (verify_pipe(line->line)))
    return (1);
  return (0);
}
