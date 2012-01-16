/*
** exec_pipeline.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Tue May  6 10:54:42 2008 adrien1 jarthon
** Last update Fri Jun 13 13:07:53 2008 yoam farges
*/

#include "42sh.h"

void		set_cmd_io_fd(t_pipeline *pipeline, t_cmd *cmds, int i_cmd)
{
  if (i_cmd == 0)
    cmds[i_cmd].in = pipeline->input;
  else
    {
      cmds[i_cmd].in.type = PIPE;
      cmds[i_cmd].in.fd = pipeline->lp[0];
    }
  if (i_cmd == pipeline->nb_pipe)
    cmds[i_cmd].out = pipeline->output;
  else
    {
      cmds[i_cmd].out.type = PIPE;
      cmds[i_cmd].out.fd = pipeline->rp[1];
    }
  cmds[i_cmd].err = cmds[i_cmd].error;
}

int		exec_cmds(t_param *param, t_cmd *cmds,
			  t_pipeline *pipeline, int j)
{
  int		i;

  i = -1;
  while (++i < (pipeline->nb_pipe + 1))
    {
      if (pipeline->cmd[i + 1])
	pipe(pipeline->rp);
      cmds[i].arg = my_str_to_wordtab_light(pipeline->cmd[i],
				 build_delimiters_tab(" ", "\t", 0));
      cmds[i].error.type = NONE;
      cmds[i].error.fd = 2;
      set_cmd_io_fd(pipeline, cmds, i);
      open_file(&cmds[i].in);
      open_file(&cmds[i].out);
      exec_cmd(param, &cmds[i]);
      if (pipeline->cmd[i + 1])
	close(pipeline->rp[1]);
      pipeline->lp[0] = pipeline->rp[0];
      pipeline->lp[1] = pipeline->rp[1];
      j = 1;
      while (cmds[i].arg[j])
	xsfree(cmds[i].arg[j++]);
      xsfree(cmds[i].arg);
    }
  return (0);
}

void		set_cmd_state(t_param *param, int type, int status)
{
  param->cmd_state = 0;
  if (type)
    {
      param->cmd_state |= STATE_BUILT;
      param->cmd_state |= status;
      set_last_state(param, status);
    }
  else
    {
      if (WIFSIGNALED(status))
	{
	  param->cmd_state |= STATE_KILL;
	  param->cmd_state |= WTERMSIG(status);
	  set_last_state(param, WTERMSIG(status) + 128);
	}
      if (WIFEXITED(status))
	{
	  param->cmd_state |= STATE_EXIT;
	  param->cmd_state |= WEXITSTATUS(status);
	  set_last_state(param, WEXITSTATUS(status));
	}
    }
}

char		*disp_signal_name(int sig)
{
  static char	out[100];

  memset(out, 0, 100);
  if (sig == SIGSEGV)
    my_strcpy(out, KILL_SEGV);
  else if (sig == SIGINT)
    my_strcpy(out, KILL_INT);
  else if (sig == SIGFPE)
    my_strcpy(out, KILL_FPE);
  else if (sig == SIGBUS)
    my_strcpy(out, KILL_BUS);
  else if (sig == SIGQUIT)
    my_strcpy(out, KILL_QUIT);
  else
    sprintf(out, "Killed by signal %d", sig);
  my_strcat(out, " [");
  return ((char *)out);
}

void		exec_pipeline(t_param *param, t_pipeline *pipeline)
{
  t_cmd		*cmds;
  int		i;
  int		status;

  status = 0;
  pipeline->cmd = my_str_to_wordtab_light(pipeline->line,
					  build_delimiters_tab("|", 0));
  cmds = xsmalloc(sizeof(*cmds) * (pipeline->nb_pipe + 2));
  variables_substitution(param, pipeline);
  exec_cmds(param, cmds, pipeline, (i = -1) + 1);
  while (++i < (pipeline->nb_pipe + 1))
    if (cmds[i].pid != PID_BUILTIN)
      {
	waitpid(cmds[i].pid, &status, 0);
	pipeline->status = WEXITSTATUS(status);
	set_cmd_state(param, 0, status);
	if (WIFSIGNALED(status) && (!param->forked))
	  my_printf("%s%d]\n",disp_signal_name(WTERMSIG(status)), cmds[i].pid);
      }
    else
      {
	pipeline->status = cmds[i].status;
	set_cmd_state(param, 1, status);
      }
  msfree(pipeline->cmd, cmds, 0);
}
