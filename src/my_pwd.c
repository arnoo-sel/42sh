/*
** my_pwd.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src
**
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
**
** Started on  Thu May 22 14:47:16 2008 jocelyn de-la-rosa
** Last update Thu Jun  5 11:11:35 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	read_dir_pwd(t_pwd *pwd, char *name)
{
  char	*sl = "/";

  while ((pwd->dp = readdir(pwd->dir)) != NULL)
    {
      stat(pwd->dp->d_name, &(pwd->dd));
      if ((pwd->dd.st_ino == (unsigned)pwd->d_ino) &&
	  (pwd->dd.st_dev == (unsigned)pwd->d_dev))
	{
	  pwd->cursor = pwd->cursor - my_strlen(pwd->dp->d_name);
	  memcpy(name + pwd->cursor, pwd->dp->d_name,
		 my_strlen(pwd->dp->d_name));
	  pwd->cursor -= 1;
	  memcpy(name + pwd->cursor, sl, 1);
	  closedir(pwd->dir);
	  break;
	}
    }
  return (0);
}

t_pwd	*init_pwd(char **name)
{
  t_pwd	*pwd;

  *name = xsmalloc(sizeof(**name) * 1025);
  memset(*name, 0, 1024);
  pwd = xsmalloc(sizeof(*pwd));
  pwd->cursor = 1023;
  stat("/", &(pwd->root));
  pwd->r_ino = pwd->root.st_ino;
  pwd->r_dev = pwd->root.st_dev;
  return (pwd);
}

char	*my_pwd(void)
{
  char	*name;
  int	i;
  char	*sl = "/";
  t_pwd	*pwd;

  i = 0;
  pwd = init_pwd(&name);
  while (42)
    {
      stat(".", &(pwd->d));
      pwd->d_ino = pwd->d.st_ino;
      pwd->d_dev = pwd->d.st_dev;
      if ((pwd->r_ino == pwd->d_ino) && (pwd->r_dev == pwd->d_dev))
	{
	  if (!i)
	    return (sl);
	  return (name + pwd->cursor);
	}
      i = 42;
      chdir("..");
      pwd->dir = opendir(".");
      read_dir_pwd(pwd, name);
    }
  xsfree(pwd);
  return (0);
}
