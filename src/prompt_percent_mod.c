/*
** prompt_percent_mod.c for 42sh in /home/farges_y/link/42sh/mysh/src
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Sun Jun  1 23:52:20 2008 yoam farges
** Last update Mon Jun  2 00:26:32 2008 yoam farges
*/

#include "42sh.h"

char	*prompt_puh(char *prompt, t_param *param, int i)
{
  char	*stoc;

  if (prompt[i + 1] == 'p')
    {
      if ((stoc = my_getenv(param->env, "PWD")) != 0)
	return (modif_prompt(replace_modif_prompt(prompt, i, stoc, 0), param));
      return (modif_prompt(replace_modif_prompt(prompt, i, "", 0), param));
    }
  if (prompt[i + 1] == 'u')
    {
      if ((stoc = my_getenv(param->env, "USER")) != 0)
	return (modif_prompt(replace_modif_prompt(prompt, i, stoc, 0), param));
      return (modif_prompt(replace_modif_prompt(prompt, i, "", 0), param));
    }
  if (prompt[i + 1] == 'h')
    {
      if ((stoc = my_getenv(param->env, "HOST")) != 0)
	return (modif_prompt(replace_modif_prompt(prompt, i, stoc, 0), param));
      return (modif_prompt(replace_modif_prompt(prompt, i, "", 0), param));
    }
  return (0);
}

char	*prompt_tild(char *prompt, t_param *param, int i)
{
  char	*mod;
  char	*stoc;
  char	*tild;

  if (((mod = my_getenv(param->env, "PWD")) != 0)
      && ((stoc = my_getenv(param->env, "HOME")) != 0))
    {
      if (my_strncmp(mod, stoc, my_strlen(stoc)) == 0)
	{
	  tild = xsmalloc(sizeof(*tild) *
			  (my_strlen(mod) - my_strlen(stoc) + 3));
	  tild = my_memset(tild, 0, my_strlen(mod) - my_strlen(stoc) + 2);
	  tild = my_strcat(tild, "~");
	  tild = my_strcat(tild, (mod + my_strlen(stoc)));
	  return (modif_prompt(replace_modif_prompt
			       (prompt, i, tild, 1), param));
	}
      return (modif_prompt(replace_modif_prompt(prompt, i, mod, 0), param));
    }
  return (modif_prompt(replace_modif_prompt(prompt, i, "", 0), param));
}

char	*prompt_n(char *prompt, t_param *param, int i)
{
  char	*stoc;

  if (HIST.history[HIST.pos_hist] == NULL)
    HIST.nbr_hist[HIST.pos_hist] = 0;
  stoc = xsmalloc(sizeof(*stoc) * 10);
  stoc = my_memset(stoc, 0, 10);
  my_putnbr_base((HIST.nbr_hist[HIST.pos_hist] + 1) , "0123456789", stoc);
  return (modif_prompt(replace_modif_prompt(prompt, i, stoc, 1), param));
}
