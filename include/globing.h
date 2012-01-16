/*
** globing.h for 42sh in /home/jartho_d/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Fri May 23 18:22:16 2008 adrien1 jarthon
** Last update Mon Jun  9 12:56:18 2008 adrien1 jarthon
*/

struct		s_cmd;
struct		s_param;
struct		dirent;
struct		_dirdesc;
struct		s_vector;

#define		STAR		-127
#define		ANY		-126
#define		OPEN_BRACKET	-125
#define		CLOSE_BRACKET	-124
#define		OPEN_BRACE	-123
#define		CLOSE_BRACE	-122
#define		HAT		-121
#define		DASH		-120
#define		DOLLAR		-119
#define		AND		-118

/* file_glob.c */
int		trim_left_path(char *arg, struct s_vector *stack,
			       struct s_vector *dirs, char *path);
void		matching_file(char *arg, struct s_vector *stack,
			      struct s_vector *dirs, struct dirent *dp);
int		add_matching_files(char *arg, struct s_vector *stack,
				   struct s_vector *dirs);
void		file_dfs(char *arg, t_vector *stack,
			 t_vector *dirs, char *name);

/* globing.c */
struct s_vector	*find_all_matching_files(char **str);
int		add_files_to_arg_tab(struct s_cmd *cmd, int iarg, struct s_vector *vect);
int		brace_parse(char **string, struct s_cmd *cmd,
			    int iarg, struct s_vector *new_args);
int		globing_substitution(struct s_cmd *cmd);

/* match.c */
char		undash(char c);
int		add_range(char *pattern, char *index);
char		*char_list(char *pattern, int end);
int		range_match(char *str1, char *str2);
int		match(char *str1, char *str2);

/* pattern_sub.c */
int		pre_pattern_dump(char **str, char **name,
				 char **inhib, struct s_vector **stack);
void		post_pattern_dump(char **str, char *name, char *inhib, int end);
struct s_vector	*find_all_pattern(char **str);

/* str.c */
char		*dir_from_vector(struct s_vector *dirs);
char		*complete_path(char *dir, char *file);
int		is_globbing(char **str);
char		globbed_to_std(char c);
int		my_globcmp(const void *d1, const void *d2);

/* tild.c */
int		replace_tild(struct s_param *param, struct s_cmd *cmd);
