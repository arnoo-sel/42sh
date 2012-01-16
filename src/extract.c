/*
** extract.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Tue May  6 15:55:51 2008 jocelyn de-la-rosa
** Last update Mon Jun  2 03:46:26 2008 yoam farges
*/

#include "42sh.h"

int		go_to_delimiter(char *line, char del)
{
  int		pos;

  pos = -1;
  while ((line[++pos] != '\0') && (line[pos] != del));
  return (pos);
}

int		extract_delimiter(char *line, char del)
{
  int		pos;
  int		type;

  type = NONE;
  pos = go_to_delimiter(line, del);
  if (line[pos] == '\0')
    {
      type = NONE;
      return (type);
    }
  if (del == '<')
    type = LEFT;
  else if (del == '>')
    type = RIGHT;
  line[pos] = ' ';
  if (line[pos + 1] == del)
    {
      if (del == '<')
	type = D_LEFT;
      else if (del == '>')
	type = D_RIGHT;
      line[pos + 1] = ' ';
    }
  return (type);
}

int		extract_name(t_redir *redir, char *line, int pos)
{
  int		id;

  while ((line[++pos] == ' ') || (line[pos] == '\t'));
  id = -1;
  pos--;
  while ((++id < 256) && (line[++pos] != ' ') && (line[pos] != '\t') &&
	 (line[pos] != '\0') && (line[pos] != '|') && (line[pos] != '<')
	 && (line[pos] != '>'))
    {
      redir->file[id] = line[pos];
      line[pos] = ' ';
    }
  if (id < 256)
    redir->file[id] = '\0';
  else
    redir->file[id - 1] = '\0';
  return (0);
}

t_redir		extract_input(char *line)
{
  t_redir	input;
  int		pos;
  char		*inhib;

  input.fd = 0;
  pos = go_to_delimiter(line, '<');
  inhib = xsmalloc(sizeof(*inhib) * (my_strlen(line) + 1));
  my_memset(inhib, 4, my_strlen(line) + 1);
  if (is_inhibited(line, inhib, pos))
    {
      input.type = NONE;
      return (input);
    }
  if ((input.type = extract_delimiter(line, '<')) == D_LEFT)
    pos++;
  if (input.type == NONE)
    return (input);
  extract_name(&input, line, pos);
  return (input);
}

t_redir		extract_output(char *line)
{
  t_redir	output;
  int		pos;
  char		*inhib;

  output.fd = 1;
  pos = go_to_delimiter(line, '>');
  inhib = xsmalloc(sizeof(*inhib) * (my_strlen(line) + 1));
  my_memset(inhib, 4, my_strlen(line) + 1);
  if (is_inhibited(line, inhib, pos))
    {
      output.type = NONE;
      return (output);
    }
  if ((output.type = extract_delimiter(line, '>')) == D_RIGHT)
    pos++;
  if (output.type == NONE)
    return (output);
  extract_name(&output, line, pos);
  return (output);
}
