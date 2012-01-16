/*
** tc_tools.c<3> for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Thu May 22 12:56:06 2008 arnaud sellier
** Last update Fri Jun 13 12:40:12 2008 arnaud sellier
*/

#include "42sh.h"

int	n_tc_getattr(int fd, struct termios *t)
{
  return (ioctl(fd, TIOCGETA, t));
}

int			n_tc_setattr(int fd, int opt, struct termios *t)
{
  if (opt == TCSANOW)
    return (ioctl(fd, TIOCSETA, t));
  return (-1);
}

int	n_tc_restore_ld(struct termios *oldline)
{
  if (n_tc_setattr(0, TCSANOW, oldline) < 0)
    return (0);
  return (1);
}

void			uncanonical(struct termios *saveline)
{
  struct termios	line;

  if (n_tc_getattr(0, saveline) < 0)
    exit(1);
  memcpy(&line, saveline, sizeof (line));
  line.c_lflag &= ~(ICANON|ECHO);
  line.c_cc[VMIN] = 1;
  line.c_cc[VTIME] = 0;
  if (n_tc_setattr(0, TCSANOW, &line) < 0)
    exit(1);
}

