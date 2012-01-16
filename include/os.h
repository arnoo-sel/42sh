/*
** os.h for minishell1 in /home/sellie_a/rendu.local/c/minishell1
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Mon Feb 28 01:31:30 2008 arnaud sellier
** Last update Mon May  5 10:20:05 2008 adrien1 jarthon
*/

#ifndef __OS_SRC__
# define __OS_SRC__

#define	BSD	1
#define	NUX	2
#define	SUN	3

#if defined(sun) || defined(__sun)
#define OS	SUN
#elif defined(__FreeBSD__)
#define OS	BSD
#elif defined(linux) || defined(__linux)
#define OS	NUX
#endif

#endif
