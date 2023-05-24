#include "shell.h"
/**
 * execute - executes command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: 0 if success otherwise, return -1.
 */
int execute(info *data)
{
	int retrival = 0, status;
	pid_t pidd;

	/* check for program in built ins */
	retrival = exec_list(data);
	if (retrival != -1)/* not found in built ins */
		return (retrival);

	/*check for program file system */
	retrival = find_program(data);
	if (retrival)
	{/*program not found */
		return (retrival);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(data->cmd_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			retrival = execve(data->token[0], data->token, data->env);
			if (retrival == -1) /* if error when execve*/
				perror(data->cmd_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
