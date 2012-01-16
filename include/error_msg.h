/*
** error_msg.h for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Mon May  5 10:08:37 2008 arnaud sellier
** Last update Fri May  9 10:50:35 2008 jocelyn de-la-rosa
*/

/* Erreurs Msg */
#define WORD_TOO_LONG   "Word too long.\n"
#define UNKNOW_VAR      "Variable not found.\n"
#define CANNOT_INIT     "Can't initialized mysh.\n"
#define CANNOT_FORK     "Can't execute the program.\n"
#define CMD_NOT_FOUND   ": Command not found.\n"

/* Redirect Errors */
#define BAD_R           "Invalid right redirection.\n"
#define BAD_L           "Invalid left redirection.\n"
#define BAD_P           "Invalid null command.\n"
#define AMB_R           "Ambigous output redirect.\n"
#define AMB_L           "Ambigous input redirect.\n"
#define MISS_NAME       "Missing name for redirect.\n"
#define LL_OVERFLOW     "Line overflow.\n"

/* Erreurs files */
#define	NO_EXIST_FILE	"No such file or directory.\n"
#define	NO_PERMISSION	"Permission denied.\n"
