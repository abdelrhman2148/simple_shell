#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;
/**
 * struct DataShell - A structure to hold data for a shell
 *
 * @av: An array of strings, typically command and arguments
 * @input: A string representing user input
 * @args: An array of strings representing command arguments
 * @status: An integer representing the status of the shell
 * @counter: An integer for tracking purposes
 * @environment: An array of strings representing the environment variables
 * @pid: A string representing the process ID
*/
typedef struct DataShell
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **environment;
	char *pid;
} data_shell;
/**
 * struct SeparatorList - A structure to manage separators
 *
 * @separator: A character representing a separator
 * @next: A pointer to the next separator in the list
*/
typedef struct SeparatorList
{
	char separator;
	struct SeparatorList *next;
} sep_list;
/**
 * struct LineList - A structure to manage lines
 *
 * @line: A string representing a line of text
 * @next: A pointer to the next line in the list
*/
typedef struct LineList
{
	char *line;
	struct LineList *next;
} line_list;
/**
 * struct ReplaceVarList - A structure to manage variable replacement
 *
 * @len_var: An integer representing the length of the variable
 * @val: A string representing the value to replace the variable
 * @len_val: An integer representing the length of the value
 * @next: A pointer to the next item in the replacement list
*/
typedef struct ReplaceVarList
{
	int len_var;
	char *val;
	int len_val;
	struct ReplaceVarList *next;
} r_var;
/**
 * struct Builtin - A structure to define shell built-in commands
 *
 * @name: A string representing the name of the built-in command
 * @func: A function pointer to the function handling the command
*/
typedef struct Builtin
{
	char *name;
	int (*func)(data_shell *datash);
} builtin_t;

sep_list *add_separator_node_end(sep_list **head, char separator);
void free_separator_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);
r_var *add_replace_var_node(r_var **head, int len_var, char *var, int len_val);
void free_replace_var_list(r_var **head);

char *_string_concat(char *dest, const char *src);
char *_string_copy(char *dest, char *src);
int _string_compare(char *s1, char *s2);
char *_string_character(char *s, char c);
int _string_span(char *s, char *accept);
void _memory_copy(void *new_ptr, const void *ptr, unsigned int size);
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocate_double_pointer(char **ptr, unsigned int old_size,
		unsigned int new_size);
char *_string_duplicate(const char *s);
int _string_length(const char *s);
int compare_characters(char str[], const char *delim);
char *_string_tokenize(char str[], const char *delim);
int is_digit(const char *s);
void reverse_string(char *s);

int repeated_character(char *input, int i);
int error_separator_operator(char *input, int i, char last);
int first_character(char *input, int *i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);

char *remove_comments(char *input);
void shell_loop(data_shell *datash);

char *read_line(int *i_eof);

char *swap_characters(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

void check_environment(r_var **h, char *in, data_shell *data);
int check_variables(r_var **h, char *in, char *st, data_shell *data);
char *replace_input(r_var **head, char *input, char *new_input, int nlen);
char *replace_variable(char *input, data_shell *datash);

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

int execute_line(data_shell *datash);

int is_current_directory(char *path, int *i);
char *find_executable(char *cmd, char **environment);
int check_command_error(char *dir, data_shell *datash);
int execute_command(data_shell *datash);

char *_get_environment(const char *name, char **environment);
int print_environment(data_shell *datash);
void set_environment_variable(char *name, char *value, data_shell *datash);
int set_environment(data_shell *datash);
int unset_environment(data_shell *datash);

void change_directory_dot(data_shell *datash);
void change_directory(data_shell *datash);
void change_directory_previous(data_shell *datash);
void change_directory_home(data_shell *datash);

int execute_shell(data_shell *datash);

int (*get_builtin_function(char *cmd))(data_shell *datash);

int exit_the_shell(data_shell *datash);

char *string_concat_cd(data_shell *datash, char *dest, char *dir, char *file);
char *error_getting_cd(data_shell *datash);
char *error_not_found_cd(data_shell *datash);
char *error_exit_shell(data_shell *datash);

char *error_getting_alias(char **args);
char *error_printing_environment(data_shell *datash);
char *error_syntax_error(char **args);
char *error_permission_denied(char **args);
char *error_command_not_found(data_shell *datash);

int handle_error(data_shell *datash, int eval);

void handle_sigint(int sig);

void show_help_environment(void);
void show_help_set_environment(void);
void show_help_unset_environment(void);
void show_help_general(void);
void show_help_exit(void);

void show_help(void);
void show_help_alias(void);
void show_help_change_directory(void);

int show_help_message(data_shell *datash);

#endif
