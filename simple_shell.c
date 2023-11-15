#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 100

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("simple_shell> ");
}

/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		display_prompt();

		/* Read user input */
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			/* Handle end of file (Ctrl+D) */
			printf("\n");
			break;
		}

		/* Remove the newline character at the end */
		input[strcspn(input, "\n")] = 0;

		/* Fork a child process */
		pid_t pid = fork();

		if (pid == -1)
		{
			/* Forking error */
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			/* Execute the command using execve */
			if (execlp(input, input, (char *)NULL) == -1)
			{
				/* Print an error message if the command is not found */
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process */
			/* Wait for the child process to finish */
			int status;
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
