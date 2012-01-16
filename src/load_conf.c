/*
** load_conf.c for 42sh in /home/farges_y/link/42sh/mysh
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Sun Jun  1 15:49:10 2008 yoam farges
** Last update Thu Jun 12 15:04:34 2008 yoam farges
*/

#include "42sh.h"

void	parse_file_conf(t_param *param, char *get, int fd)
{
  while ((get = my_fgets(fd)) != NULL)
    {
      if (my_strlen(get) > 0)
	{
	  if (get[0] != '#')
	    {
	      param->line = get;
	      if (param->line[my_strlen(param->line) - 1] == '\n')
		param->line[my_strlen(param->line) - 1] = 0;
	      if (check_entry(param, my_strlen(param->line),
			      param->line) == -1)
		continue;
	      my_memset(param->inhib, 4, BUF);
	      main_launch_exec(param);
	    }
	}
    }
}

int	creat_default_conf(t_param *param, char *path)
{
  int	fd;

  param = param;
  if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
    {
      xsfree(path);
      return (1);
    }
  xsfree(path);
  my_fprintf(fd, "set prompt \"%s\"\nset history %d\nset savehist %d\n",
	     PROMPT, HISTORY, SAVEHIST);
  close(fd);
  return (1);
}

void	modif_param_after_load(t_param *param)
{
  char	*get;

  if ((get = my_getvar(param->var, "prompt")) != 0)
    {
      param->prompt_conf = my_strdup(get);
      if (param->prompt_conf != NULL)
	if (my_strlen(param->prompt_conf) > 50)
	  param->prompt_conf[50] = 0;
    }
  if (my_getvar(param->var, "history") != 0)
    HIST.vhist = my_getnbr(my_getvar(param->var, "history"));
  if (my_getvar(param->var, "savehist") != 0)
    HIST.savehist = my_getnbr(my_getvar(param->var, "savehist"));
  if (HIST.vhist < 0)
    HIST.vhist = 0;
  if (HIST.savehist < 0)
    HIST.savehist = 0;
}

int	load_conf(t_param *param)
{
  char	*get;
  char	*path;
  int	fd;

  param->prompt_conf = NULL;
  param->prompt = NULL;
  HIST.vhist = HISTORY;
  HIST.savehist = SAVEHIST;
  if ((get = my_getenv(param->env, "HOME")) == 0)
    return (1);
  path = xsmalloc(sizeof(*path) * (my_strlen(get) + my_strlen(FILECONF) + 2));
  path = my_strcpy(path, get);
  path = my_strcat(my_strcat(path, "/"), FILECONF);
  if ((fd = open(path, O_RDONLY)) == -1)
    return (creat_default_conf(param, path));
  xsfree(path);
  parse_file_conf(param, get, fd);
  modif_param_after_load(param);
  close(fd);
  return (0);
}
