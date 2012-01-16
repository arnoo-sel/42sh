/*
** file_glob.c for 42sh in /home/jartho_d/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Fri May 23 17:05:57 2008 adrien1 jarthon
** Last update Tue Jun 10 13:11:18 2008 adrien1 jarthon
*/

#include "42sh.h"

int		trim_left_path(char *arg, t_vector *stack,
			       t_vector *dirs, char *path)
{
  if (!my_strncmp(arg, path, my_strlen(path)))
    {
      vector_push(dirs, path);
      add_matching_files(arg + my_strlen(path), stack, dirs);
      vector_pop(dirs);
      return (1);
    }
  return (0);
}

void		matching_file(char *arg, t_vector *stack,
			      t_vector *dirs, struct dirent *dp)
{
  char		*file_name;

  if (my_strstr(arg, "/"))
    {
      vector_push(dirs, (void *)complete_path(dp->d_name, "/"));
      add_matching_files(my_strstr(arg, "/") + 1, stack, dirs);
      xsfree(vector_pop(dirs));
    }
  else
    {
      file_name = dir_from_vector(dirs);
      vector_push(stack, (void *)complete_path(file_name, dp->d_name));
      xsfree(file_name);
    }
}

void		file_dfs(char *arg, t_vector *stack,
			 t_vector *dirs, char *name)
{
  struct stat	dd;
  struct dirent	*dp;
  char		*path_name;
  char		*dirname;
  DIR		*dir;

  dirname = (vector_size(dirs) ? dir_from_vector(dirs) : my_strdup("./"));
  if ((dir = opendir(dirname)))
    {
      while ((dp = readdir(dir)) != NULL)
	{
	  path_name = complete_path(dirname, dp->d_name);
	  if (lstat(path_name, &dd) == -1)
	    my_fprintf(2, "globbing: can't stat %s\n", path_name);
	  if ((name[0] != '.') && (dp->d_name[0] == '.'));
	  else if ((S_ISDIR(dd.st_mode) || (!my_strstr(arg, "/")))
		   && (match(dp->d_name, name)))
	    matching_file(arg, stack, dirs, dp);
	  xsfree(path_name);
	}
      closedir(dir);
    }
  xsfree(dirname);
}

int		add_matching_files(char *arg, t_vector *stack, t_vector *dirs)
{
  char		*name;

  if ((my_strlen(arg) == 0) &&
      !vector_push(stack, (void *)dir_from_vector(dirs)))
    return (0);
  if (trim_left_path(arg, stack, dirs, "/"))
    return (0);
  if (trim_left_path(arg, stack, dirs, "./"))
    return (0);
  if (trim_left_path(arg, stack, dirs, "../"))
    return (0);
  name = my_strdup(arg);
  if (my_strstr(arg, "/"))
    *(my_strstr(name, "/")) = 0;
  file_dfs(arg, stack, dirs, name);
  xsfree(name);
  return (0);
}
