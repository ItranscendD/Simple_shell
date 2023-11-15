#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0.
 */
int main(void)
{
	char *command;
	size_t len = 0;
	ssize_t read;

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		read = getline(&command, &len, stdin);

		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(command);
			exit(EXIT_SUCCESS);
		}

		if (_strcmp(command, "exit\n") == 0)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}

		execute_command(command);
	}

	return (0);
}

/**
 * execute_command - Execute a command
 * @command: The command to execute
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	command[_strlen(command) - 1] = '\0'; /* Remove trailing newline */

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		/* Child process */
		if (execve(command, NULL, NULL) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
	}
}
