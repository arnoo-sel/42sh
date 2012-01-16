/*
** globing.c for 42sh in /home/jartho_d/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Fri May 23 17:05:57 2008 adrien1 jarthon
** Last update Thu Jun  5 11:31:04 2008 adrien1 jarthon
*/

#include "42sh.h"

t_vector	*find_all_matching_files(char **str)
{
  t_vector	*stack;
  t_vector	*dirs;

  stack = vector_init();
  dirs = vector_init();
  add_matching_files(str[0], stack, dirs);
  vector_free(dirs);
  return (stack);
}

int		add_files_to_arg_tab(t_cmd *cmd, int iarg, t_vector *vect)
{
  int		i, j;
  char		**new_arg;

  i = -1;
  while (cmd->arg[++i]);
  new_arg = xsmalloc(sizeof(*new_arg) * (vector_size(vect) + i));
  i = -1;
  while (++i < iarg)
    new_arg[i] = cmd->arg[i];
  j = iarg;
  while (vector_size(vect))
    new_arg[i++] = vector_pop(vect);
  while (cmd->arg[j++])
    new_arg[i++] = cmd->arg[j];
  xsfree(cmd->arg);
  cmd->arg = new_arg;
  return (0);
}

int		brace_parse(char **string, t_cmd *cmd,
			    int iarg, t_vector *new_args)
{
  if (is_in(string[0], OPEN_BRACE))
    {
      new_args = find_all_pattern(string);
      vector_rev(new_args);
      add_files_to_arg_tab(cmd, iarg, new_args);
      vector_free(new_args);
      return (1);
    }
  return (0);
}

int		globing_substitution(t_cmd *cmd)
{
  int		iarg;
  t_vector	*new_files;
  int		state;
  char		**string;

  state = (cmd->arg[iarg = 1]) ? 0 : 1;
  while (cmd->arg[iarg])
    if (is_globbing(string = clear_inhib_str(cmd->arg[iarg])))
      {
	if (brace_parse(string, cmd, iarg, new_files))
	  continue;
	new_files = find_all_matching_files(string);
	qsort(new_files->data, vector_size(new_files),
	      sizeof(void *), my_globcmp);
	state = vector_size(new_files);
	add_files_to_arg_tab(cmd, iarg, new_files);
	vector_free(new_files);
	iarg += state;
      }
    else if ((state = 1))
      cmd->arg[(iarg += state) - state] = string[0];
  if (state == 0)
    my_fprintf(2, "%s: No match.\n", cmd->arg[0]);
  return ((state == 0) ? 1 : 0);
}
