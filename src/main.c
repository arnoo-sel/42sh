/*
** main.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Mon May  5 10:21:36 2008 jocelyn de-la-rosa
** Last update Fri Jun 13 15:00:04 2008 arnaud sellier
*/

#include "42sh.h"

t_param			*creat_param(void)
{
  static t_param	*param = 0;

  if (param == 0)
    {
      param = xsmalloc(sizeof(*param));
      param->f_built = (t_builtin_func[NB_BUILTINS]){
	{b_exit, "exit"},
	{b_cd, "cd"},
	{b_env, "env"},
	{b_setenv, "setenv"},
	{b_unsetenv, "unsetenv"},
	{b_42sh, "42"},
	{b_history, "history"},
	{b_alias, "alias"},
	{b_unalias, "unalias"},
	{b_bindkey, "bindkey"},
	{b_set, "set"},
	{b_unset, "unset"},
	{b_jobs, "jobs"}};
    }
  return (param);
}

int		test_tty(t_param *param)
{
  if (!isatty(0))
    {
      param->tty = 0;
      if (param->debug)
	my_fprintf(2, "%[1]stdin is not a tty !%[]\n");
    }
  else
    {
      param->tty = 1;
      if (param->debug)
	my_fprintf(2, "%[2]stdin is a tty !%[]\n");
    }
  return (param->tty);
}

int		check_entry(t_param *param, int nb_read, char buf[BUF])
{
  if (nb_read == 0)
    {
      if (param->tty)
	my_putchar('\n');
      quit_ctrl_d(param);
    }
  if (too_big(buf))
    {
      my_putstr(WORD_TOO_LONG);
      return (-1);
    }
  memset(param->buf, 0, BUF);
  my_strcpy(param->buf, buf);
  return (0);
}

void	set_each_prompt(t_param *param, char *buf)
{
  bg_unstack(param);
  my_memset(buf, 0, BUF);
  my_memset(param->inhib, 4, BUF);
  aff_prompt(param);
}


int		main(int ac, char **av)
{
  t_param	*param;
  char		buf[BUF];
  int		nb_read;

  init_sig();
  param = creat_param();
  start_and_init_main(ac, av, param);
  while (42)
    {
      set_each_prompt(param, buf);
      if (((ac == 2) && (av[1][0] == 't')) || (param->tty == 0))
	nb_read = read(0, buf, BUF - 1);
      else
	nb_read = termcap_entry(param, buf);
      if (buf[my_strlen(buf) - 1] == '\n')
	buf[my_strlen(buf) - 1] = 0;
      if (check_entry(param, nb_read, buf) == -1)
      	continue;
      if (main_launch_history(param) == 1)
	continue;
      alias_substitution(param);
      main_launch_exec(param);
    }
  return (0);
}
