/*
** refresh.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Sun Jun  1 23:16:05 2008 arnaud sellier
** Last update Wed Jun 11 14:01:58 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

/*
** Si on est sur le derniere ligne et qu'on va depasser, on
** fait des \n pour faire descendre le term.
** -rcstr remet de curseur a la position sauvegarder
** -cdstr efface du curseur jusko bout de l'ecran
** -{DO|RI|UP|LE}str deplace le curseur
*/

void	aff_refresh(t_param *p, char buf[], int cu_pos,
		    t_bindkeys *bind)
{
  int	old;

  old = bind->nb_line;
  bind->nb_line = (bind->cur_start - 1 + cu_pos) / p->cap.cols;
  if ((bind->y_start + bind->nb_line >= p->cap.line + 1) &&
      (old != bind->nb_line) && ((bind->y_start--) || 1))
    {
      my_putchar('\n');
      my_tputs(p->cap.rcstr);
      my_tputs_one(p->cap.UPstr, 1);
      my_tputs(p->cap.scstr);
    }
  my_tputs(p->cap.rcstr);
  my_tputs(p->cap.cdstr);
  my_putstr(buf);
  my_tputs(p->cap.rcstr);
  if (bind->nb_line)
    my_tputs_one(p->cap.DOstr, bind->nb_line);
  if ((bind->cur_start - 1 + cu_pos) % p->cap.cols - (bind->cur_start - 1) > 0)
    my_tputs_one(p->cap.RIstr, (bind->cur_start - 1 + cu_pos) % p->cap.cols -
		 (bind->cur_start - 1));
  else if ((bind->cur_start - 1 + cu_pos) % p->cap.cols -
	   (bind->cur_start - 1) < 0)
    my_tputs_one(p->cap.LEstr, -((bind->cur_start - 1 + cu_pos) % p->cap.cols -
				 (bind->cur_start - 1)));
}
