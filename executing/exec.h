#ifndef exec_H
# define MINISHELL_H
// this struct you will push to me

typedef struct s_mini
{
    char *cmd; // command "ls"
    char **arg; // argument of command "-la"
    int nbr_arg; // number of command "2"
    int infile; 
    int outfile;
    struct t_mini *next;
    struct t_mini *prev;
}t_mini;
//this struct of enverment
typedef struct s_envp
{
    char *env; //line of enverment "PATH=/usr/local/bin"
	char *variable; // variable of enverment "PATH"
	char *value; //value "/usr/local/bin"
	t_envp *next;
	t_envp *prev;
} t_envp;
// this my struct
typedef struct s_exec
{
	t_mini *list;
	t_envp *env;
}t_exec;

#endif