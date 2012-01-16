/*
** background.c for 42sh in /u/epitech_2012/jartho_d/cu/public/perso/42sh/mysh/src/background
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Mon Jun  9 10:29:35 2008 adrien1 jarthon
** Last update Wed Jun 11 15:44:27 2008 adrien1 jarthon
*/

#include "42sh.h"

void		find_background_char(t_param *param)
{
  int		i;
  char		*inhib;
  char		*str;

  str = xsmalloc(sizeof(*str) * (my_strlen(param->line) + 2));
  my_strcpy(str, param->line);
  my_strcat(str, "\n");
  xsfree(param->line);
  param->line = str;
  inhib = xsmalloc(my_strlen(str) + 1);
  memset(inhib, 4, my_strlen(str) + 1);
  i = 0;
  while (str[++i])
    {
      if (((str[i] == '&') && !is_inhibited(str, inhib, i)) &&
	  ((str[i + 1] != '&') || is_inhibited(str, inhib, i + 1)) &&
	  ((str[i - 1] != '&') || is_inhibited(str, inhib, i - 1)))
	{
	  str[i] = AND;
	}
    }
}

void		exec_background(t_param *param, char *cmd)
{
  char		**cmds;
  char		*inhib;
  int		pos;

  pos = 0;
  inhib = xsmalloc(sizeof(*inhib) * (my_strlen(cmd) + 1));
  memset(inhib, 4, my_strlen(cmd) + 1);
  cmds = my_str_to_wordtab_inhibitor
    (cmd, inhib, build_delimiters_tab(";", "\n", 0));
  while (cmds[pos])
    {
      if (!(empty(cmds[pos])))
	exec_evaluators(param, cmds[pos]);
      pos++;
    }
  msfree(cmds, inhib, 0);
}

void		exit_state(t_param *param)
{
  int		state;

  state = param->cmd_state;
  free_all(param);
  if (state & STATE_KILL)
    kill(getpid(), state & 0xFF);
  else
    exit(state & 0xFF);
}

void		fork_background(t_param *param)
{
  int		current_cmd;
  int		pid;
  char		and[2] = {AND, 0};

  current_cmd = -1;
  find_background_char(param);
  param->cmd = my_str_to_wordtab_inhibitor
    (param->line, param->inhib, build_delimiters_tab(and, 0));
  while (param->cmd[++current_cmd])
    if (param->cmd[current_cmd + 1])
      if ((pid = fork()))
	bg_stack(param, pid, param->cmd[current_cmd]);
      else
	{
	  param->forked = 1;
	  uninit_sig();
	  exec_background(param, param->cmd[current_cmd]);
	  exit_state(param);
	}
    else
      exec_background(param, param->cmd[current_cmd]);
  xsfree(param->cmd);
  return;
}
