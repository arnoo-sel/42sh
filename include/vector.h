/*
** vector.h for vector in /home/jartho_d/rendu.local/lib/vector
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Wed Apr  2 10:06:17 2008 adrien1 jarthon
** Last update Sun Jun  1 23:32:27 2008 adrien1 jarthon
*/

/*
** vector structure like in c++
*/

#ifndef __VECTOR_H__
# define __VECTOR_H__

#include "stdlib.h"
#include "unistd.h"

typedef	struct	s_vector
{
  int		exp_size;
  int		real_size;
  int		nb_elem;
  void		**data;
}		t_vector;

/* add elem to the back of the vector, reallocating if nessesary */
int		vector_push(t_vector *vector, void *elem);
/* get the last elem and delete it */
void		*vector_pop(t_vector *vector);
/* realloc the vector (to waste less time during push) */
int		vector_resize(t_vector *vector, int size);
/* reverse elems */
void		vector_rev(t_vector *vector);
/* elem number */
int		vector_size(t_vector *vector);

/* init */
t_vector	*vector_init();
/* free */
void		vector_free(t_vector *vector);

#endif
