/*
** 42sh.h for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Mon May  5 09:53:01 2008 arnaud sellier
** Last update Fri Jun 13 11:26:52 2008 arnaud sellier
*/

#ifndef __MYSH__
# define __MYSH__

#include "vector.h"
#include "globing.h"
#include "my.h"
#include "os.h"

#include "error_msg.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <dirent.h>
#include <time.h>

#if (OS==NUX)
#include <asm/ioctls.h>
#define TIOCGETA TCGETS
#define TIOCSETA TCSETS
#endif

#if (OS==SUN)
#define TIOCGETA TCGETS
#define TIOCSETA TCSETS
#endif

#if (OS==SUN)
//#include <ncurses/termcap.h>
#else
#include <sys/termios.h>
char    *tgetstr(const char *cap, char **area);
#endif

#ifndef TCSANOW
#define TCSANOW         0
#endif
#ifndef TCSADRAIN
#define TCSADRAIN       1
#endif
#ifndef TCSAFLUSH
#define TCSAFLUSH       2
#endif

#define BUF	42400
#define PROMPT	"$> "
#define MAX(a,b) ((a>b)?(a):(b))

#define	HISTORY		42
#define	SAVEHIST	42
#define FILEHIST	".42history"
#define	HIST		param->hist

#define FILECONF	".42shrc"

#define LEFT	0
#define RIGHT	1
#define D_LEFT	2
#define D_RIGHT	3
#define	PIPE	4
#define NONE	-4242

#define	STATE_EXIT	(1 << 10)
#define	STATE_KILL	(1 << 11)
#define	STATE_BUILT	(1 << 12)

#define SAVE_FD         save.in = dup(0); save.out = dup(1); save.err = dup(2)
#define DUP_FD          dup2(cmd->in.fd, 0); dup2(cmd->out.fd, 1); dup2(cmd->err.fd, 2)
#define RESTOR_FD       dup2(save.in, 0); dup2(save.out, 1); dup2(save.err, 2)

#define FREE_RETURN(a, b)	xfree(a); return (b);

#define	NB_BUILTINS	13
#define	PID_BUILTIN	-42

#define BELL	7
#define DING	my_putchar(BELL)
#define	R_OPEN	O_CREAT | O_WRONLY

#define CTRL_A	1
#define CTRL_B	2
#define CTRL_D	4
#define CTRL_E	5
#define CTRL_F	6
#define CTRL_G	7
#define CTRL_H	8
#define CTRL_J	10
#define CTRL_K	11
#define CTRL_L	12
#define CTRL_N	14
#define CTRL_P	16
#define CTRL_T	20
#define CTRL_U	21
#define CTRL_W	23

#define BEG_OF_LINE	0
#define END_OF_LINE	1
#define DEL_CHAR	2
#define BELL_BELL	3
#define BACK_DEL	4
#define KILL_LINE	5
#define CLS		6
#define DOWN_HISTORY	7
#define UP_HISTORY	8
#define TRANSPOSE	9
#define KILL_WHOLE	10
#define YANK		11
#define BACKWARD	12
#define FORWARD		13
#define COMPLETE	14

/* Msg */
#define KILL_SEGV	"Segmentation fault"
#define KILL_FPE	"Floating exception"
#define KILL_INT	"Interrupted"
#define KILL_BUS	"Bus error"
#define KILL_QUIT	"Quit"
#define KILL_SIGNAL	"Process kill by signal"

extern char	**environ;

typedef struct		s_bg_item
{
  int			pid;
  char			*cmd;
}			t_bg_item;

typedef struct		s_complete
{
  t_vector		*mylist;
  t_vector		*thislist;
  t_vector		*filelist;
  char			tmp[BUF];
  char			first_chars[BUF];
  char			begin_path[BUF];
  int			pos;
  int			j;
  int			same;
  int			is_first_word;
  int			is_file;
}			t_complete;

typedef struct		s_bindkeys
{
  char		buf[BUF];
  char		tmp[BUF];
  char		clipboard[BUF];
  char		swap_tmp;
  int		nb_read;
  int		cursor_pos;
  int		history_pos;
  char		cur_save[BUF];
  int		nb_line;
  int		cur_start;
  int		y_start;
}		t_bindkeys;

struct		s_builtin_func;
struct		s_param;

typedef struct	s_fd
{
  int		in;
  int		out;
  int		err;
}		t_fd;

typedef	struct	s_redir
{
  int		type;
  int		fd;
  char		file[256];
}		t_redir;

typedef	struct	s_cmd
{
  char		**arg;
  t_redir	in;
  t_redir	out;
  t_redir	err;
  int		pid;
  int		status;
  t_redir	error;
}		t_cmd;

typedef	struct	s_pipeline
{
  int		rp[2];
  int		lp[2];
  t_redir	input;
  t_redir	output;
  char		*line;
  char		**cmd;
  int		nb_pipe;
  int		status;
}		t_pipeline;

typedef struct	s_env
{
  char		*name;
  char		*value;
}		t_env;

typedef struct	s_pwd
{
  struct stat	 root;
  struct stat	 d;
  struct stat	 dd;
  int		r_ino;
  int		r_dev;
  int		d_dev;
  int		d_ino;
  DIR		*dir;
  struct dirent *dp;
  int		cursor;
}		t_pwd;

typedef struct		s_cap
{
  char			*term;
  char			bp[1024];
  char			t[4096];
  char			*area;
  char			*clstr;		//Clear screen
  char			*kustr;		//Key Up
  char			*kdstr;		//Key Down
  char			*klstr;		//Key Left
  char			*krstr;		//Key Right
  char			*kbstr;		//Key Backspace
  char			*dostr;		//Move Cursor 1 Down
  char			*DOstr;		//Move Cursor %1 Down
  char			*upstr;		//Move Cursor 1 Up
  char			*UPstr;		//Move Cursor %1 Up
  char			*lestr;		//Move Cursor 1 Left
  char			*LEstr;		//Move Cursor %1 Left
  char			*ristr;		//Move Cursor 1 Right
  char			*RIstr;		//Move Cursor %1 Right
  char			*cestr;		//Clear from cursor to end of line
  char			*cdstr;		//Clear from cursor to end of screen
  char			*scstr;		//Save Cursor position
  char			*rcstr;		//Restore Cursor position
  char			*ksstr;		//
  int			cols;
  int			line;
}			t_cap;

typedef struct		s_builtin_func
{
  int			(*func)(struct s_param *, char **);
  char			*name;
}			t_builtin_func;

typedef	struct		s_hist
{
  char			**history;
  int			*time_hist;
  int			*nbr_hist;
  int			pos_hist;
  int			nb_max_hist;
  int			vhist;
  int			savehist;
  char			*prevsearch;
}			t_hist;

typedef struct		s_param
{
  t_cap			cap;
  t_env			*env;
  t_env			*var;
  t_env			*alias;
  t_vector		*cmd_tab;
  t_vector		*local_tab;
  t_vector		*bg_table;
  char			*prompt;
  char			*prompt_conf;
  char			buf[BUF];
  char			*inhib;
  char			**cmd;
  char			*line;
  int			tty;
  int			debug;
  int			cmd_state;
  int			forked;
  struct s_hist		hist;
  struct termios	saveline;
  struct s_builtin_func	*f_built;
}			t_param;

/* ==================== [ Main shell ] ==================== */

/* main.c */
t_param                 *creat_param(void);
int			test_tty(t_param *param);
int			check_entry(t_param *param, int nb_read, char buf[BUF]);

/* signal.c */
void			init_sig();
void			uninit_sig();

/* main_launch.c */
void			start_and_init_main(int nb, char **tab_av, t_param *param);
int			main_launch_exec(t_param *param);
int			main_launch_history(t_param *param);
void			aff_prompt(t_param *param);

/* environ.c */
t_env			*malloc_env(void);
char			*env_var_value(char *line);
char			*env_var_name(char *line);
int			init_env(t_param *param);

/* variable.c */
char			*put_env_var(t_param *param, char *str);
char			*put_var(t_param *param, char *str);
void			variables_substitution(t_param *param, t_pipeline *pipeline);

/* path.c */
int			find_path_var(t_env *env);
char			*get_path_str(char *env_path, int i);
char			*get_next_path(t_env *env);

/* quit.c */
void			free_bg_table(t_param *param);
void			free_all(t_param *param);
void			quit_ctrl_d(t_param *param);

/* free.c */
int			free_env(t_env *env);
int			free_cmd(char **cmd);

/* file_handling.c */
int			open_file(t_redir *redir);

/* alias_substitution.c */
int			alias_substitution(t_param *param);

/* ==================== [ Builtins ] ==================== */

/* env.c */
int			b_env(t_param *param, char **cmd);

/* jobs.c */
int			b_jobs(t_param *param, char **cmd);

/* unsetenv.c */
int			b_unsetenv(t_param *param, char **cmd);
int			check_exist_unsetenv(char *str, t_env *env);
void			remove_unsetenv(t_param *param, int pos);

/* setenv.c */
int			b_setenv(t_param *param, char **cmd);
void			new_setenv(int len, int id, t_param *param, char **cmd);

/* alias.c */
void			disp_alias(t_env *alias);
int			b_alias(t_param *param, char **cmd);
t_env			*init_alias();

/* unalias.c */
int			check_exist_unalias(char *str, t_env *alias);
int			b_unalias(t_param *param, char **cmd);

/* disp_alias_value.c */
void			disp_alias_value(t_param *param, char *alias);

/* echo.c */
int			b_echo(t_param *param, char **cmd);

/* cd.c */
int			b_cd(t_param *param, char **cmd);

/* exit.c */
int			b_exit(t_param *param, char **cmd);

/* 42.c */
int			b_42sh(t_param *param, char **cmd);

/* bindkey.c */
int			b_bindkey(t_param *param, char **cmd);

/* b_history.c */
int			b_history(t_param *param, char **cmd);

/* b_set.c */
t_env			*init_var();
int			b_set(t_param *param, char **cmd);

/* b_unset.c */
int			b_unset(t_param *param, char **cmd);

/* ==================== [ Check code ] ==================== */

/* verify_line.c */
int			too_big(char *line);

/* verify_pipeline.c */
int			empty(char *pipeline);
int			verify(t_pipeline *line);

/* verify_pipe_rediless.c */
int			verify_pipe_redirless(char *str);

/* verify_redirect.c */
int			verify_r(char *s, char c, char *err);

/* ==================== [ Execution line ] ==================== */

/* extract.c */
t_redir			extract_input(char *line);
t_redir			extract_output(char *line);

/* exec_line.c */
int			exec_evaluators(t_param *param, char *seq);
int			exec_line(t_param *param, char *pipeline);

/* exec_pipeline.c */
void			set_cmd_io_fd(t_pipeline *pipeline, t_cmd *cmds, int i_cmd);
void			exec_pipeline(t_param *param, t_pipeline *pipeline);
void			set_cmd_state(t_param *param, int type, int status);
char			*disp_signal_name(int sig);

/* exec_cmd.c */
void			exec_cmd(t_param *param, t_cmd *cmd);
void			set_last_state(t_param *param, int state);

/* ==================== [ Others Tools ] ==================== */

/* tools.c */
int			n_is_char_in_str(char c, char *str);

/* clean_line.c */
void			clean_line(char buf[BUF], char out[BUF]);

/* my_getenv.c */
char			*my_getenv(t_env *env, char *str);
char			*my_getvar(t_env *var, char *str);

/* my_pwd.c */
char			*my_pwd(void);

/* ==================== [ Termcaps ] ======================== */

/* tc_tools.c */
#if (OS==SUN)
int			outc(char c);
#else
int			outc(int c);
#endif
int			n_tc_getattr(int fd, struct termios *t);
int			n_tc_setattr(int fd, int opt, struct termios *t);
int			n_tc_restore_ld(struct termios *oldline);
void			uncanonical(struct termios *saveline);

/* init_termcaps.c */
char			*xtgetstr(char *cap, char **area);
void			init_tc(t_param *param);

/* termcap_apply.c */
void			my_tputs(char *cap);
void			my_tputs_one(char *cap, int p);
void			advert_msg(t_param *param, char *msg,
				   char buf[], int cursor_pos);

/* temrcap_entry.c */
t_bindkeys		*creat_bind(int i);
int			termcap_entry(t_param *param, char buf[]);
void			to_right(char buf[], int cursor_pos, int nb_read, int len);
int			iskey(char try[], char *ref);
void			to_left(char buf[], int cursor_pos, int nb_read);
int			ctrl_key(char buf[]);
void			get_coords(int *x, int *y);
void			aff_refresh(t_param *param, char buf[], int cursor_pos,
				    t_bindkeys *bind);
int			anti_segfault(t_param *param, t_bindkeys *bind,
				      char buf[], int addlen);

/* funct */
void			beginning_of_line(t_param *param, t_bindkeys *bind);
void			delete_char_or_list_or_eof(t_param *param, t_bindkeys *bind);
void			end_of_line(t_param *param, t_bindkeys *bind);
void			bell_bell(t_param *param, t_bindkeys *bind);
void			backward_delete_char(t_param *param, t_bindkeys *bind);
void			kill_line(t_param *param, t_bindkeys *bind);
void			my_clear_screen(t_param *param, t_bindkeys *bind);
void			down_history(t_param *param, t_bindkeys *bind);
void			up_history(t_param *param, t_bindkeys *bind);
void			transpose_chars(t_param *param, t_bindkeys *bind);
void			kill_whole_line(t_param *param, t_bindkeys *bind);
void			yank(t_param *param, t_bindkeys *bind);
void			backward_char(t_param *param, t_bindkeys *bind);
void			forward_char(t_param *param, t_bindkeys *bind);
void			complete_word(t_param *param, t_bindkeys *bind);

/* which_function.c */
int			which_bindkey(t_param *param, t_bindkeys *bind);
int			which_key(t_param *param, t_bindkeys *bind);


/* ==================== [ History ] ========================= */

/* history.c */
void			init_history(t_param *param);
int			add_line_in_history(char *line, t_param *param, int ttime);
int			search_nbr_history(t_param *param, int nbr);
int			search_back_in_history(t_param *param, int nbr);

/* file_history.c */
int			put_hist_in_file(t_param *param);
int			get_hist_from_file(t_param *param);

/* history_subs.c */
int			history_substitution(t_param *param);
int			launch_hist(t_param *param, char *subs, int i);

/* tools_subs_hist.c */
void			mix_str_subs_hist(char *subs, t_param *param, int i1, int i2);
void			mix_str_exclam_mark(char *subs, t_param *param, int i1, int len);
void			saveprev(t_param *param, char *subs);
int			endsubs(char c);

/* subs_str_hist.c */
int			do_prev_search(int i, t_param *param, char *subs);
int			subs_startstr_history(int i, t_param *param, char *subs);
int			subs_strstr_history(int i, t_param *param, char *subs);

/* get_subs.c */
char			*get_subs_hist(char *str, int i);
char			*get_interrog_subs(char *str, int i);

/* subs_search_hist.c */
int			err_backsearch(int i, t_param *param, char *subs, int flag);
int			err_parse_backsearch(int i, t_param *param, char *subs, int flag);
int			subs_prev_command(int i, t_param *param, char *subs);
int			subs_search_history(int i, t_param *param, char *subs);
int			subs_backsearch_history(int i, t_param *param, char *subs, int flag);

/* ==================== [ Inhibitors ] ======================== */

/* is_inhibited.c */
int			is_between_quote(char *str, char * inhib, int pos);
int			is_inhibited(char *str, char *inhib, int pos);
int			check_quote(char *str, char *inhib);
char			**clear_inhib_str(char *str);
int			str_is_inhibited(char *str, char *inhib, int start, int end);

/* str_to_wordtab_inhibitor*/
char			**my_str_to_wordtab_inhibitor(char *str, char *inhib, char **cut);
char			**my_str_to_wordtab_light(char *str, char **cut);

/* build_delimiters_tab.c */
char			**build_delimiters_tab(char *ptr, ...);

/* inhib_str.c */
char			*inhib_str(char *str, char *inhib);

/* ===================== [ Signaux ] =============================*/

void			catch(int sig);

/* ==================== [ Fichier de conf ] ===================== */

/* load_conf.c */
void			parse_file_conf(t_param *param, char *get, int fd);
void			modif_param_after_load(t_param *param);
int			load_conf(t_param *param);
int			creat_default_conf(t_param *param, char *path);

/* ========================= [ Prompt ] ========================== */

/* modif_prompt.c */
char			*modif_prompt(char *prompt, t_param *param);
char			*replace_modif_prompt(char *prompt, int i, char *stoc, int flag);
void			creat_prompt(t_param *param);

/* prompt_percent_mod.c */
char			*prompt_puh(char *prompt, t_param *param, int i);
char			*prompt_tild(char *prompt, t_param *param, int i);
char			*prompt_n(char *prompt, t_param *param, int i);

/* ========================= [ Completion ] ====================== */
void			create_local_tab(t_param *param);
void			create_cmd_tab(t_param *param);
int			my_compcmp(const void *d1, const void *d2);
void			insert_in_buf(t_param *param, t_bindkeys *bind, char tmp2[]);
int			find_same_begin(t_vector *mylist);
int			find_longest(t_vector *mylist);
void			complete_word(t_param *param, t_bindkeys *bind);
int			find_start_of_word(t_bindkeys *bind, char tmp[]);
int			its_a_file(t_param *param, t_bindkeys *bind, t_complete *cp);
int			find_completion_type(t_param *param, t_bindkeys *bind,
					     t_complete *cp);
void			aff_completion_possibilities(t_param *param, t_vector *mylist);
void			free_completion_tab(t_vector *target);
int			create_files_tab(t_param *param, t_vector *filehist,
					 char *begin);
void			several_completion(t_param *param, t_bindkeys *bind,
					   t_complete *complete);
void			go_complete(t_param *param, t_bindkeys *bind,
				    t_complete *complete);
void			read_this_folder(t_vector *target, DIR *dir, char *begin);
void			read_tild(t_param *param, char *begin);
void			read_this_path(t_vector *target, DIR *dir, char *path);
void			read_local_cmd(t_vector *target, DIR *dir);

/* ========================= [ Background ] ====================== */
void			find_background_char(t_param *param);
void			exec_background(t_param *param, char *cmd);
void			fork_background(t_param *param);
void			exit_state(t_param *param);
void			bg_stack(t_param *param, int pid, char *cmd);
void			bg_unstack(t_param *param);
void			disp_term_info(int status, int pid, char *cmd);

#endif
