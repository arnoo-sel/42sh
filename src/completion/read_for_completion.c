/*
** read_for_completion.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Thu Jun 12 13:40:38 2008 arnaud sellier
** Last update Thu Jun 12 16:34:39 2008 arnaud sellier
*/

#include "42sh.h"

void		read_this_folder(t_vector *target, DIR *dir, char *begin)
{
  struct dirent *dp;
  struct stat	s;
  char		buf[1024];
  char		buf2[1024];

  while ((dp = readdir(dir)) != NULL)
    {
      strcpy(buf, begin);
      strcat(buf, dp->d_name);
      strcpy(buf2, dp->d_name);
      stat(buf, &s);
      if (S_ISDIR(s.st_mode))
	strcat(buf2, "/");
      vector_push(target, my_strdup(buf2));
    }
}

void	read_tild(t_param *param, char *begin)
{
  int	i;
  char	*home;

  i = 0;
  if (is_in(begin, '~'))
    {
      while (begin[i++] != '~');
      if ((i == 1) || (begin[i] == ' ') || (begin[i] == ';') ||
	  (begin[i] == '|') || (begin[i] == '&'))
	if ((home = my_getenv(param->env, "HOME")))
	  {
	    to_right(begin + i - 1, i, strlen(begin), strlen(home) - 1);
	    memcpy(begin + i - 1, home, my_strlen(home));
	  }
    }
}

void		read_this_path(t_vector *target, DIR *dir, char *path)
{
  int		already;
  int		j;
  char		buf[1024];
  struct stat	s;
  struct dirent	*dp;

  while ((dp = readdir(dir)) != NULL)
    {
      strcpy(buf, path);
      strcat(buf, "/");
      strcat(buf, dp->d_name);
      if ((access(buf, X_OK) != -1) && (stat(buf, &s) || 1))
	if (S_ISREG(s.st_mode))
	  {
	      j = -1;
	      already = 0;
	      while (++j < target->nb_elem)
		if (strcmp(target->data[j], dp->d_name) == 0)
		  already = 1;
	      if (already == 0)
		vector_push(target, my_strdup(dp->d_name));
	  }
    }
}

void		read_local_cmd(t_vector *target, DIR *dir)
{
  struct dirent	*dp;
  char		buf[1024];
  struct stat	s;
  int		already;
  int		j;

  while ((dp = readdir(dir)) != NULL)
    if (access(dp->d_name, X_OK) != -1)
      {
	stat(dp->d_name, &s);
	j = -1;
	already = 0;
	while (++j < target->nb_elem)
	  if (strcmp(target->data[j], dp->d_name) == 0)
	    already = 1;
	if (already == 0)
	  {
	    strcpy(buf, dp->d_name);
	    if (S_ISDIR(s.st_mode))
	      strcat(buf, "/");
	    vector_push(target, my_strdup(buf));
	  }
      }
}
