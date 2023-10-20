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
//1
int check_interactive_mode(info_t *info);

int is_delimiter(char c, char *delim);

int is_alpha(int c);

int string_to_integer(char *s);
//1.

int error_atoi(char *);
void print_error(ShellInfoT *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int exit_shell(info_t *info);
int _exit_shell(ShellInfoT *);

int change_directory(info_t *info);
int _change_directory(ShellInfoT *);
int help_shell(info_t *info);
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


//


int display_history(info_t *info);
int unset_alias_command(info_t *info, char *alias_str);
int set_alias_command(info_t *info, char *alias_str);
int print_single_alias(list_t *alias_node);
int alias_command(info_t *info);
int display_environment(info_t *info);
char *get_environment_variable(info_t *info, const char *name);
int set_environment_variable(info_t *info);
int unset_environment_variable(info_t *info);
int populate_environment_list(info_t *info);
void print_error_message(char *str);
int write_stderr(char c);
int write_to_fd(char c, int fd);
int print_to_fd(char *str, int fd);
int convert_string_to_integer(char *s);
void print_error_message(info_t *info, char *error_string);
int print_decimal(int input, int fd);
char *convert_integer_to_string(long int num, int base, int flags);
void remove_first_comment(char *buf);
char *copy_string(char *destination, char *source, int max_characters);
char *concatenate_strings(char *first, char *second, int max_characters);
char *find_character(char *string, char character);
char **retrieve_environment(info_t *info);
int remove_environment_variable(info_t *info, char *variable);
int set_environment_variable(info_t *info, char *variable, char *value);
void initialize_info(info_t *info);
void populate_info(info_t *info, char **argv);
void release_info(info_t *info, int freeAll);
ssize_t buffer_input(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buffer(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
int main(int ac, char **av);
int bfree(void **ptr);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
void error(char *msg);
int str_length(char *str);
int str_compare(char *str1, char *str2);
char *string_starts_with(const char *haystack, const char *needle);
char *string_concatenate(char *destination, char *source);
char *string_copy(char *destination, char *source);
char *string_duplicate(const char *str);
void string_print(char *str);
int character_print(char c);
char **split_string(char *input_string, char *delimiter_string);
char **split_string_v2(char *input_string, char delimiter);
int is_chain_delimiter(info_t *info, char *buf, size_t *p);
void check_command_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_aliases(info_t *info);
int replace_variables(info_t *info);
int replace_string(char **old, char *new);




#endif
