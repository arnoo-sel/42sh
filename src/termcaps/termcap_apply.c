/*
** termcap_apply.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Fri May 23 11:09:37 2008 arnaud sellier
** Last update Fri Jun 13 11:26:18 2008 arnaud sellier
*/

#include "42sh.h"

void	my_tputs(char *cap)
{
  tputs(cap, 0, outc);
}

void	my_tputs_one(char *cap, int p)
{
  tputs(tparm(cap ,p), 0, outc);
}

