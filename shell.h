#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>

#include "help.h"/*for message help and prompt*/

/**
 * struct program_data- data of program
 * @prog_name: name of program
 * @input: pointer to the nput read for _getline
 * @cmd_name: pointer to command input by user
 * @exec_count: number of executed commands
 * @token: pointer to array of tokenized inputs
 * @env: a copy of environment
 * @fd: file descriptor
 * @alias_list: array of pointers with aliases
 */
typedef struct program_data
{
	char *prog_name;
	char *input;
	char *cmd_name;
	char **token;
	char **env;
	char **alias_list;
	int exec_count;
	int fd;
} info;

/**
 * struct builtins- for the builtins
 * @builtin: name of builtin function or system call
 * @func: pointer to function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*func)(info *data);
} builtins;


/*=== shell.c ===*/
void initialize_data(info *data, int argc, char *argv[], char **env);
void inf_prompt(char *prompt, info *data);
void ctrl_c_handler(int opr UNUSED);

/*=== _getline.c ===*/
int _getline(info *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/*=== expansions.c ===*/
void expand_var(info *data);
void exp_alias(info *data);
int add_buffer(char *buffer, char *str_add);

/*=== strtok_builtin.c ===*/
void tokenize(info *data);
char *_strtok(char *line, char *delim);

/*=== path_exec.c ===*/
int execute(info *data);

/*=== buitins_exec.c ===*/
int exec_list(info *data);

/*=== find_in_path.c ===*/
char **tokenize_path(info *data);
int find_program(info *data);

/*=== free_helper.c ===*/
void free_arr_ptr(char **arr);
void free_recurrent(info *data);
void free_data(info *data);

/*=== builtins.c ===*/
int builtin_exit(info *data);
int builtin_cd(info *data);
int set_work_dir(info *data, char *new_dir);
int builtin_help(info *data);
int builtin_alias(info *data);

/*=== env_builtins.c ===*/
int builtin_env(info *data);
int builtin_set_env(info *data);
int builtin_unset_env(info *data);

/*=== env_management.c ===*/
char *env_get_var(char *var, info *data);
int env_set_var(char *var, char *value, info *data);
int env_remove_key(char *key, info *data);
void print_env(info *data);

/*=== _printf.c ===*/
int _prints(char *str);
int print_err(char *str);
int print_errcode(int errcode, info *data);

/*=== _stringsh.c ===*/
int str_len(char *str);
char *str_duplicate(char *str);
int str_cmp(char *str1, char *str2, int num);
char *str_cat(char *str1, char *str2);
void str_rev(char *str);

/*=== converter_helper.c ===*/
void num_to_string(long number, char *str, int base);
int _atoi(char *str);
int count_character(char *str, char *character);

/*=== alias.c ===*/
int print_alias(info *data, char *alias_name);
char *get_alias(info *data, char *alias_name);
int set_alias(char *alias_string, info *data);
#endif/** SHELL_H**/
