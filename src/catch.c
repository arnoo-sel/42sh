/*
** catch.c<2> for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Sun Jun  1 17:27:38 2008 arnaud sellier
** Last update Tue Jun 10 13:08:53 2008 adrien1 jarthon
*/

#include "42sh.h"

void	get_new_dimension(t_param *param)
{
  char	*term;
  char	bp[1024];
  char	t[4096];
  char	*area;

  if ((term = getenv("TERM")) == NULL)
    {
      my_putstr("Can't determine terminal\n");
      my_putstr("Run ./42sh for non-termcaps mode\n");
      xsfree_all();
      exit(1);
    }
  if (tgetent(bp, term) == ERR)
    {
      my_putstr("Can't get the termcaps base\n");
      my_putstr("Run ./42sh for non-termcaps mode\n");
      xsfree_all();
      exit(1);
    }
  area = t;
  param->cap.cols = tgetnum("co");
  param->cap.line = tgetnum("li");
}

void		catch(int sig)
{
  t_param	*param;

  init_sig();
  param = creat_param();
  if (sig == SIGWINCH)
    get_new_dimension(param);
  else
    {
      creat_bind(1);
      my_putchar('\n');
      my_putstr(param->prompt);
    }
}
