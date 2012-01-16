/*
** create_tab.c for 42sh.h in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Wed Jun 11 15:27:14 2008 arnaud sellier
** Last update Thu Jun 12 16:38:24 2008 arnaud sellier
*/

#include "42sh.h"

void	free_completion_tab(t_vector *target)
{
  int	i;

  i = 0;
  while (vector_size(target))
    xsfree(vector_pop(target));
  vector_free(target);
}

void		create_local_tab(t_param *param)
{
  DIR		*dir;
  struct dirent *dp;
  struct stat	s;
  char		buf[1024];

  param->local_tab = vector_init();
  if ((dir = opendir(".")) == NULL)
    return;
  while ((dp = readdir(dir)) != NULL)
    {
      strcpy(buf, dp->d_name);
      stat(buf, &s);
      if (S_ISDIR(s.st_mode))
	strcat(buf, "/");
      vector_push(param->local_tab, my_strdup(buf));
    }
  closedir(dir);
}

int		create_files_tab(t_param *param, t_vector *filehist,
				 char *begin)
{
  DIR		*dir;

  read_tild(param, begin);
  if ((dir = opendir(begin)) == NULL)
    {
      if (access(begin, F_OK))
	{
	  my_printf("\n%s: no such file or directory.\n\n", begin);
	  return (1);
	}
      else if (access(begin, R_OK) || access(begin, X_OK))
	{
	  my_printf("\n%s unreadable.\n\n", begin);
          return (1);
	}
    }
  read_this_folder(filehist, dir, begin);
  closedir(dir);
  return (0);
}

void		create_cmd_tab(t_param *param)
{
  char		*path;
  DIR		*dir;

  param->cmd_tab = vector_init();
  while ((path = get_next_path(param->env)))
    {
      if ((dir = opendir(path)) == NULL)
	continue;
      read_this_path(param->cmd_tab, dir, path);
      closedir(dir);
    }
  if ((dir = opendir(".")) == NULL)
    return;
  read_local_cmd(param->cmd_tab, dir);
  closedir(dir);
}
