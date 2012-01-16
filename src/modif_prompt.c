/*
** modif_prompt.c for 42sh in /home/farges_y/link/42sh/mysh
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Sun Jun  1 18:45:54 2008 yoam farges
** Last update Sun Jun  8 18:45:22 2008 yoam farges
*/

#include "42sh.h"

void	creat_prompt(t_param *param)
{
  char	*stoc;

  if (param->prompt_conf == NULL)
    param->prompt = PROMPT;
  else
    {
      stoc = my_strdup(param->prompt_conf);
      if (param->prompt != NULL)
	xsfree(param->prompt);
      stoc = modif_prompt(stoc, param);
      param->prompt = stoc;
    }
}

char	*replace_modif_prompt(char *prompt, int i, char *stoc, int flag)
{
  char	*new;

  new = xsmalloc(sizeof(*new) * (my_strlen(prompt) - 1 + my_strlen(stoc)));
  new = my_memset(new, 0, (my_strlen(prompt) - 1 + my_strlen(stoc)));
  new = my_strncpy(new, prompt, i);
  new = my_strcat(new, stoc);
  new = my_strcat(new, (prompt + i + 2));
  xsfree(prompt);
  prompt = new;
  if (flag == 1)
    xsfree(stoc);
  return (prompt);
}

char	*modif_prompt(char *prompt, t_param *param)
{
  int	i;

  i = 0;
  while (prompt[i] != 0)
    {
      if (prompt[i] == '%')
	{
	  if ((prompt[i + 1] == 'p') || (prompt[i + 1] == 'u')
	      || (prompt[i + 1] == 'h'))
	    return (prompt_puh(prompt, param, i));
	  if (prompt[i + 1] == '~')
	    return (prompt_tild(prompt, param, i));
	  if (prompt[i + 1] == 'n')
	    return (prompt_n(prompt, param, i));
	}
      i++;
    }
  return (prompt);
}
