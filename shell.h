#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3


#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;
/**
 * struct ListNode - singly linked list node
 * @num: the number field
 * @str: a string
 * @next: points to the next node
*/
typedef struct ListNode
{
	int num;
	char *str;
	struct ListNode *next;
} ListT;
/**
 * struct ShellInfo - contains pseudo-arguments to pass into a function,
 *                   allowing a uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @environ: custom modified copy of environ from LL env
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @command_buffer: address of pointer to command_buffer, on if chaining
 * @command_buffer_type: CMD_type ||, &&, ;
 * @read_fd: the file descriptor from which to read line input
 * @histcount: the history line number count
*/
typedef struct ShellInfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	ListT *env;
	ListT *history;
	ListT *alias;
	char **environ;
	int env_changed;
	int status;
	char **command_buffer;
	int command_buffer_type;
	int read_fd;
	int histcount;

} ShellInfoT;

#define SHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}
/**
 * struct BuiltinCommand - contains a built-in string and related function
 * @type: the built-in command flag
 * @func: the function
 */
typedef struct BuiltinCommand
{
	char *type;
	int (*func)(ShellInfoT *);

} BuiltinCommandT;



int hsh(ShellInfoT *, char **);
int find_builtin(ShellInfoT *);
void find_command(ShellInfoT *);
void fork_command(ShellInfoT *);

int is_command(ShellInfoT *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(ShellInfoT *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **split_string(char *, char *);
char **split_string2(char *, char);

char *_memset(char *, char, unsigned int);
void free_strings(char **);
void *_realloc(void *, unsigned int, unsigned int);

int batch_free(void **);

int interactive(ShellInfoT *);
int is_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

int error_atoi(char *);
void print_error(ShellInfoT *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int _exit_shell(ShellInfoT *);
int _change_directory(ShellInfoT *);
int _show_help(ShellInfoT *);

int _show_history(ShellInfoT *);
int _manage_alias(ShellInfoT *);

ssize_t get_input(ShellInfoT *);
int _getline(ShellInfoT *, char **, size_t *);
void sigintHandler(int);

void clear_info(ShellInfoT *);
void set_info(ShellInfoT *, char **);
void free_info(ShellInfoT *, int);

char *_get_environment(ShellInfoT *, const char *);
int _show_environment(ShellInfoT *);
int _set_environment(ShellInfoT *);
int _unset_environment(ShellInfoT *);
int populate_environment_list(ShellInfoT *);

char **get_environment(ShellInfoT *);
int _unset_environment(ShellInfoT *, char *);
int _set_environment(ShellInfoT *, char *, char *);

char *get_history_file(ShellInfoT *);
int write_history(ShellInfoT *);
int read_history(ShellInfoT *);
int build_history_list(ShellInfoT *, char *, int linecount);
int renumber_history(ShellInfoT *);

ListT *add_node(ListT **, const char *, int);
ListT *add_node_end(ListT **, const char *, int);
size_t print_list_str(const ListT *);
int delete_node_at_index(ListT **, unsigned int);
void free_list(ListT **);

size_t list_length(const ListT *);
char **list_to_strings(ListT *);
size_t print_list(const ListT *);
ListT *node_starts_with(ListT *, char *, char);
ssize_t get_node_index(ListT *, ListT *);

int is_chain(ShellInfoT *, char *, size_t *);
void check_chain(ShellInfoT *, char *, size_t *, size_t, size_t);
int replace_alias(ShellInfoT *);
int replace_vars(ShellInfoT *);
int replace_string(char **, char *);

#endif
