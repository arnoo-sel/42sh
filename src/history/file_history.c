/*
** file_history.c for 42sh in /home/farges_y/link/42sh/mysh
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Fri May 30 15:13:00 2008 yoam farges
** Last update Sun Jun  8 18:57:31 2008 yoam farges
*/

#include "42sh.h"

int	put_hist_in_file(t_param *param)
{
  int	pos;
  int	count;
  char	*home;
  char	*path;
  int	fd;

  if ((home = my_getenv(param->env, "HOME")) == 0)
    return (1);
  path = xsmalloc(sizeof(*path) * (my_strlen(home) + my_strlen(FILEHIST) + 2));
  path = my_strcpy(path, home);
  path = my_strcat(my_strcat(path, "/"), FILEHIST);
  if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
    return (1);
  count = 0;
  pos = HIST.pos_hist;
  while ((count != HIST.nb_max_hist) && (count < HIST.savehist))
    {
      pos++;
      if (HIST.history[pos] == NULL)
	pos = 0;
      my_fprintf(fd, "%d\n%s\n", HIST.time_hist[pos], HIST.history[pos]);
      count++;
    }
  close(fd);
  return (0);
}

void	parse_file_hist(t_param *param, char *get, int fd)
{
  int	pos;
  int	time;

  time = 0;
  pos = 0;
  while ((get = my_fgets(fd)) != NULL)
    {
      if ((pos % 2) == 0)
	time = my_getnbr(get);
      else
	add_line_in_history(get, param, time);
      pos++;
      xsfree(get);
    }
  close(fd);
}

int	get_hist_from_file(t_param *param)
{
  char	*get;
  char	*path;
  int	fd;

  if ((get = my_getenv(param->env, "HOME")) == 0)
    return (1);
  path = xsmalloc(sizeof(*path) * (my_strlen(get) + my_strlen(FILEHIST) + 2));
  path = my_strcpy(path, get);
  path = my_strcat(my_strcat(path, "/"), FILEHIST);
  if ((fd = open(path, O_RDONLY)) == -1)
    {
      xsfree(path);
      return (1);
    }
  xsfree(path);
  parse_file_hist(param, get, fd);
  return (0);
}
