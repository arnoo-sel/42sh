/*
** main_launch.c for 42sh in /home/farges_y/link/42sh/mysh
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Mon Jun  2 03:15:44 2008 yoam farges
** Last update Fri Jun 13 11:36:51 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

void		start_and_init_main(int nb, char **tab_av, t_param *param)
{
  param->debug = 0;
  if ((nb == 2) && (tab_av[1][0] == 'd'))
    param->debug = 1;
  if ((test_tty(param) == 1))
    {
      if ((nb == 2) && (tab_av[1][0] == 't'));
      else
	init_tc(param);
    }
  init_env(param);
  param->bg_table = vector_init();
  param->cmd_state = 0;
  param->forked = 0;
  param->inhib = xsmalloc(sizeof(*(param->inhib)) * BUF);
  param->alias = init_alias();
  param->var = init_var();
  if (load_conf(param) == 1)
    my_printf("Warning: 42shrc isn't load.\n");
  init_history(param);
}

int		main_launch_exec(t_param *param)
{
  if (check_quote(param->line, param->inhib))
    return (1);
  fork_background(param);
  return (0);
}

int		main_launch_history(t_param *param)
{
  int		nbr;

  param->line = my_strdup(param->buf);
  if ((nbr = history_substitution(param)) == 1)
    {
      add_line_in_history(param->line, param, 0);
      return (1);
    }
  else if (nbr == 0)
    my_printf("%s\n", param->line);
  add_line_in_history(param->line, param, 0);
  return (0);
}

void		aff_prompt(t_param *param)
{
  char		*get;

  get = my_getvar(param->var, "prompt");
  if (param->prompt_conf == 0)
    param->prompt_conf = NULL;
  if ((get == 0) || (my_strlen(get) == 0))
    {
      if (param->prompt_conf != NULL)
        xsfree(param->prompt_conf);
      param->prompt_conf = NULL;
    }
  else if (param->prompt_conf == NULL)
    param->prompt_conf = my_strdup(get);
  else if (my_strcmp(get, param->prompt_conf) != 0)
    {
      xsfree(param->prompt_conf);
      param->prompt_conf = my_strdup(get);
    }
  creat_prompt(param);
  if (param->tty)
    my_putstr(param->prompt);
}
