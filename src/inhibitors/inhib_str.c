/*
** inhib_str.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/inhibitors
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Fri May 30 11:26:16 2008 jocelyn de-la-rosa
** Last update Fri May 30 11:32:45 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

char	*inhib_str(char *str, char *inhib)
{
  char	*str_inhib;
  int	i;

  str_inhib = xsmalloc(sizeof(*str_inhib) * (2 * my_strlen(str) + 1));
  i = 0;
  while (str[i])
    {
      if (inhib[i])
	{
	  str_inhib[i] = '\\';
	  i++;
	}
      str_inhib[i] = str[i];
      i++;
    }
  str_inhib[i] = '\0';
  return (str_inhib);
}
