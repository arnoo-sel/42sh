/*
** bindkey.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Tue May 27 13:50:24 2008 arnaud sellier
** Last update Sun Jun  1 14:57:57 2008 arnaud sellier
*/

#include "42sh.h"

int	b_bindkey(t_param *param, char **cmd)
{
  param = param;
  cmd = cmd;
  my_printf("Default bindkeys :\n");
  my_printf("\"^A\"          -> beginning-of-line\n");
  my_printf("\"^D\"          -> delete-char-or-list-or-eof\n");
  my_printf("\"^E\"          -> end-of-line\n");
  my_printf("\"^G\"          -> bell\n");
  my_printf("\"^H\"          -> backward-delete-char\n");
  my_printf("\"^J\"          -> newline\n");
  my_printf("\"^K\"          -> kill-line\n");
  my_printf("\"^L\"          -> clear-screen\n");
  my_printf("\"^N\"          -> down-history\n");
  my_printf("\"^P\"          -> up-history\n");
  my_printf("\"^T\"          -> transpose-chars\n");
  my_printf("\"^U\"          -> kill-whole-line\n");
  my_printf("\"^W\"          -> yank\n");
  my_printf("down-arrow    -> down-history\n");
  my_printf("up-arrow      -> up-history\n");
  my_printf("left-arrow    -> backward-char\n");
  my_printf("right-arrow   -> forward-char\n");
  my_printf("tab           -> completion\n");
  my_printf("home          -> beginning-of-line\n");
  my_printf("end           -> end-of-line\n");
  return (0);
}
