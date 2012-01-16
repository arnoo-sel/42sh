/*
** exec_line.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Tue May  6 10:54:42 2008 arnaud sellier
** Last update Fri Jun 13 14:52:01 2008 adrien1 jarthon
*/

#include "42sh.h"

int	get_nb_pipe(char *pipeline)
{
  int	i;
  int	out;
  char	**str;

  str = clear_inhib_str(pipeline);
  i = 0;
  out = 0;
  while (str[0][i])
    {
      if ((str[0][i] == '|') && (!str[1][i]))
	out++;
      i++;
    }
  msfree(str[0], str[1], str, 0);
  return (out);
}

int		do_exec_eval(t_param *param, char *seq, char **line)
{
  int		res;
  int		i;

  res = 0;
  seq = line[0];
  xsfree(line);
  line = my_str_to_wordtab_light(seq, build_delimiters_tab("&&", 0));
  i = -1;
  while (line[++i])
    {
      res = exec_line(param, line[i]);
      if (res)
	{
	  xsfree(line);
	  return (res);
	}
    }
  xsfree(line);
  return (res);
}

int		exec_evaluators(t_param *param, char *seq)
{
  char		**line;
  int		i;
  int		res;

  res = 0;
  line = my_str_to_wordtab_light(seq, build_delimiters_tab("||", 0));
  if (line[0] == 0)
    return (0);
  if (line[1] == 0)
    return (do_exec_eval(param, seq, line));
  else
    {
      i = -1;
      while (line[++i])
	{
	  res = exec_evaluators(param, line[i]);
	  if (!res)
	    {
	      xsfree(line);
	      return (res);
	    }
	}
    }
  xsfree(line);
  return (0);
}

int		exec_line(t_param *param, char *line)
{
  t_pipeline	pipeline;

  pipeline.line = line;
  pipeline.nb_pipe = get_nb_pipe(pipeline.line);
  if (!verify(&pipeline))
    return (-42);
  if ((param->tty) && (param->debug))
    my_fprintf(2, "%[6]Exec line `%S' (%d pipes)%[]\n",
	       pipeline.line, pipeline.nb_pipe);
  pipeline.input = extract_input(pipeline.line);
  pipeline.output = extract_output(pipeline.line);
  if (verify_pipe_redirless(pipeline.line) == -1)
   return (-42);
  if ((param->tty) && (param->debug))
    {
      if (pipeline.input.type != NONE)
	my_fprintf(2, "%[6]Input file : %S%[]\n", pipeline.input.file);
      if (pipeline.output.type != NONE)
	my_fprintf(2, "%[6]Output file : %S%[]\n", pipeline.output.file);
    }
  exec_pipeline(param, &pipeline);
  return (pipeline.status);
}
