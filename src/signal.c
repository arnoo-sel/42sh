/*
** signal.c for 42sh in /u/epitech_2012/jartho_d/cu/public/perso/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Wed Jun 11 15:34:57 2008 adrien1 jarthon
** Last update Wed Jun 11 15:36:04 2008 adrien1 jarthon
*/

#include "42sh.h"

void		init_sig()
{
  signal(SIGINT, catch);
  signal(SIGSEGV, catch);
  signal(SIGFPE, catch);
  signal(SIGBUS, catch);
  signal(SIGQUIT, catch);
  signal(SIGHUP, catch);
  signal(SIGILL, catch);
  signal(SIGABRT, catch);
  signal(SIGSYS, catch);
  signal(SIGALRM, catch);
  signal(SIGUSR1, catch);
  signal(SIGUSR2, catch);
}

void		uninit_sig()
{
  signal(SIGINT, SIG_DFL);
  signal(SIGSEGV, SIG_DFL);
  signal(SIGFPE, SIG_DFL);
  signal(SIGBUS, SIG_DFL);
  signal(SIGQUIT, SIG_DFL);
  signal(SIGHUP, SIG_DFL);
  signal(SIGILL, SIG_DFL);
  signal(SIGABRT, SIG_DFL);
  signal(SIGSYS, SIG_DFL);
  signal(SIGALRM, SIG_DFL);
  signal(SIGUSR1, SIG_DFL);
  signal(SIGUSR2, SIG_DFL);
}
