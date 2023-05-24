#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: 0 on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	info data_struct = {NULL};
	info *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, ctrl_c_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	inf_prompt(prompt, data);
	return (0);
}

/**
 * ctrl_c_handler - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void ctrl_c_handler(int opr UNUSED)
{
	_prints("\n");
	_prints(PROMPT_MSG);
}

/**
 * initialize_data - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 * Return: nothing
 */
void initialize_data(info *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->prog_name = argv[0];
	data->input = NULL;
	data->cmd_name = NULL;
	data->exec_count = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->fd = STDIN_FILENO;
	else
	{
		data->fd = open(argv[1], O_RDONLY);
		if (data->fd == -1)
		{
			print_err(data->prog_name);
			print_err(": 0: Can't open ");
			print_err(argv[1]);
			print_err("\n");
			exit(127);
		}
	}
	data->token = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * inf_prompt - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void inf_prompt(char *prompt, info *data)
{
	int error_code = 0, str_len = 0;

	while (++(data->exec_count))
	{
		_prints(prompt);
		error_code = str_len = _getline(data);

		if (error_code == EOF)
		{
			free_data(data);
			exit(errno); /* if EOF is the firrt Char of string, exit*/
		}
		if (str_len >= 1)
		{
			exp_alias(data);
			expand_var(data);
			tokenize(data);
			if (data->token[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					print_errcode(error_code, data);
			}
			free_recurrent(data);
		}
	}
}
