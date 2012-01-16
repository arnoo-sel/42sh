/*
** file_handling.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Fri May  9 10:13:56 2008 jocelyn de-la-rosa
** Last update Thu Jun  5 11:21:36 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	open_file_access(t_redir *redir)
{
  if (redir->type == LEFT)
    {
      if (access(redir->file, R_OK) == -1)
	my_fprintf(2, "%s: %s", redir->file, NO_PERMISSION);
      if ((redir->fd = open(redir->file, O_RDONLY)) == -1)
	return (1);
    }
  else if (redir->type == RIGHT)
    {
      if ((access(redir->file, W_OK) == -1)
	  && (access(redir->file, F_OK) == 0))
	my_fprintf(2, "%s: %s", redir->file, NO_PERMISSION);
      if ((redir->fd = open(redir->file, O_TRUNC | R_OPEN, 0644)) == -1)
	return (1);
    }
  else if (redir->type == D_RIGHT)
    {
      if ((access(redir->file, W_OK) == -1)
	  && (access(redir->file, F_OK) == 0))
	my_fprintf(2, "%s: %s", redir->file, NO_PERMISSION);
      if ((redir->fd = open(redir->file, O_APPEND | R_OPEN, 0644)) == -1)
	return (1);
    }
  return (0);
}

int	open_file(t_redir *redir)
{
  if ((redir->type == LEFT) && (access(redir->file, F_OK) == -1))
    {
      my_fprintf(2, "%s: %s", redir->file, NO_EXIST_FILE);
      return (0);
    }
  return (open_file_access(redir));
}
