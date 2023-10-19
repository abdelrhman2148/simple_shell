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

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 128
#define TOKEN_DELIMITER " \t\r\n\a"

extern char **environment;

/**
 * struct shell_data -
 * @arguments:
 * @input_str:
 * @parsed_args:
 * @exit_status:
 * @command_counter:
 * @environment_vars:
 * @process_id:
 */
typedef struct shell_data
{
	char **arguments;
	char *input_str;
	char **parsed_args;
	int exit_status;
	int command_counter;
	char **environment_vars;
	char *process_id;
} shell_data;

/**
 * struct separator_list_t
 * @separator: ; | &
 * @next:
 * Description:
 */
typedef struct separator_list_t
{
	char separator;
	struct separator_list_t *next;
} separator_list;

/**
 * struct line_list_t -
 * @line:
 * @next:
 * Description:
 */
typedef struct line_list_t
{
	char *line;
	struct line_list_t *next;
} line_list;

/**
 * struct replacement_variable_t -
 * @variable_length:
 * @value:
 * @value_length:
 * @next:
 * Description:
 */
typedef struct replacement_variable_t
{
	int variable_length;
	char *value;
	int value_length;
	struct replacement_variable_t *next;
} replacement_variable;

/**
 * struct builtin_command_t -
 * @name:
 * @function_pointer:
 */
typedef struct builtin_command_t
{
	char *name;
	int (*function_pointer)(shell_data *data);
} builtin_command;



separator_list *add_separator_node_end(separator_list **head, char separator);
void free_separator_list(separator_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);



replacement_variable *add_replacement_variable_node(replacement_variable **head, int var_length, char *var, int val_length);
void free_replacement_variable_list(replacement_variable **head);


char *_string_concat(char *destination, const char *source);
char *_string_copy(char *destination, char *source);
int _string_compare(char *str1, char *str2);
char *_string_character(char *str, char character);
int _string_span(char *str, char *accept);


void _memory_copy(void *new_pointer, const void *pointer, unsigned int size);
void *_realloc_memory(void *pointer, unsigned int old_size, unsigned int new_size);
char **_realloc_double_pointer(char **pointer, unsigned int old_size, unsigned int new_size);


char *_string_duplicate(const char *str);
int _string_length(const char *str);
int compare_characters(char str[], const char *delimiter);
char *_string_tokenize(char str[], const char *delimiter);
int _is_digit(const char *str);


void reverse_string(char *str);


int repeated_character(char *input, int index);
int error_separator_operator(char *input, int index, char last);
int first_character(char *input, int *index);
void print_syntax_error(shell_data *data, char *input, int index, int is_boolean);
int check_syntax_error(shell_data *data, char *input);



char *remove_comments(char *input);
void shell_loop(shell_data *data);



char *read_input(int *is_end_of_file);



char *swap_characters(char *input, int is_boolean);
void add_nodes(separator_list **separator_list, line_list **line_list, char *input);
void proceed_next(separator_list **separator_list, line_list **line_list, shell_data *data);
int separate_commands(shell_data *data, char *input);
char **split_input_line(char *input);


void validate_environment(replacement_variable **head, char *input, shell_data *data);
int validate_variables(replacement_variable **head, char *input, char *start, shell_data *data);
char *replace_input(replacement_variable **head, char *input, char *new_input, int new_length);
char *replace_variable(char *input, shell_data *data);


void fetch_line(char **line_pointer, size_t *size, char *buffer, size_t index);
ssize_t get_input_line(char **line_pointer, size_t *size, FILE *stream);


int execute_line(shell_data *data);


int is_current_directory(char *path, int *index);
char *find_command(char *command, char **environment_vars);
int is_executable_command(shell_data *data);
int check_command_error(char *directory, shell_data *data);
int execute_command(shell_data *data);


char *get_environment_variable(const char *name, char **environment_vars);
int set_environment_variable(char *name, char *value, shell_data *data);
int unset_environment_variable(shell_data *data);


void change_directory_dot(shell_data *data);
void change_directory_to(shell_data *data);
void change_directory_previous(shell_data *data);
void change_directory_to_home(shell_data *data);


int execute_cd_command(shell_data *data);


int (*get_builtin_command(char *command))(shell_data *data);


int exit_shell_program(shell_data *data);


int get_length(int number);
char *auxiliary_itoa(int number);
int _atoi(char *str);


char *concatenate_cd(shell_data *, char *, char *, char *);
char *get_cd_error(shell_data *data);
char *get_not_found_error(shell_data *data);
char *get_exit_shell_error(shell_data *data);


char *get_alias_error(char **arguments);
char *get_environment_error(shell_data *data);
char *get_syntax_error(char **arguments);
char *get_permission_error(char **arguments);
char *get_path_error(shell_data *data);


int get_error(shell_data *data, int evaluation);


void handle_sigint(int signal);


void help_environment();
void help_set_environment();
void help_unset_environment();
void help_general_info();
void help_exit_command();

void help();
void help_alias();
void help_cd();


int get_help_info(shell_data *data);

#endif
