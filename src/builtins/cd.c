/*
** cd.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/modules/my_pwd
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Thu May 22 13:20:48 2008 jocelyn de-la-rosa
** Last update Mon Jun  2 00:12:55 2008 yoam farges
*/

#include "42sh.h"

int	test_cd_args(char **cmd)
{
  int	nb_para;

  nb_para = -1;
  while (cmd[++nb_para]);
  if (nb_para > 2)
    {
      my_fprintf(2, "cd: Too many arguments\n");
      return (-1);
    }
  return (nb_para);
}

int	test_cd_dir(char *path)
{
  if (access(path, F_OK))
    {
      my_fprintf(2, "cd: %s: %s", path, NO_EXIST_FILE);
      return (1);
    }
  if (access(path, X_OK))
    {
      my_fprintf(2, "cd: %s: %s", path, NO_PERMISSION);
      return (1);
    }
  return (0);
}

char	*test_cd_path(t_param *param, int nb_para, char **cmd)
{
  char	*path;

  if (nb_para == 1)
    {
      if ((path = my_getenv(param->env, "HOME")) == 0)
	{
	  my_fprintf(2, "cd: No home directory.\n");
	  return (0);
	}
    }
  else if (my_strcmp(cmd[1], "-"))
    path = cmd[1];
  else
    {
      if ((path = my_getenv(param->env, "OLD_PWD")) == 0)
	{
	  my_fprintf(2, "cd: No \"old pwd\" directory.\n");
	  return (0);
	}
    }
  if ((!path) || (test_cd_dir(path)))
    return (0);
  return (path);
}

int	b_cd(t_param *param, char **cmd)
{
  int	nb_para;
  char	*path;
  char	*para[4];

  if ((nb_para = test_cd_args(cmd)) == -1)
    return (1);
  if ((path = test_cd_path(param, nb_para, cmd)) == 0)
    return (1);
  para[0] = "setenv";
  para[1] = "OLD_PWD";
  para[2] = my_pwd();
  chdir(para[2]);
  para[3] = 0;
  chdir(path);
  b_setenv(param, para);
  xsfree(para[2]);
  para[1] = "PWD";
  para[2] = my_pwd();
  chdir(para[2]);
  b_setenv(param, para);
  xsfree(para[2]);
  return (0);
}
