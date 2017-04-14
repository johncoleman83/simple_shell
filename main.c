#include "header.h"

/**
 * buildarginv - function to build a struct of the arguments inventory
 * Return: pointer to arguments inventory struct
 */
arg_inventory_t *buildarginv(void)
{
	arg_inventory_t *arginv;

	arginv = safe_malloc(sizeof(arg_inventory_t));
	arginv->input_commands = safe_malloc(BUFSIZE * sizeof(char));
	arginv->envlist = env_list();
	arginv->history = history_list(arginv);
	arginv->buflimit = BUFSIZE;
	arginv->st_mode = _filemode(STDIN_FILENO);
	arginv->exit = 0;

	if (arginv->envlist == NULL)
	{
		perror("No Memory");
		write(STDOUT_FILENO, "insufficient memory", 19);
	}

	return (arginv);
}

void sig_handler(int sig)
{
	(void) sig;
	_puts("");
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - custom shell
 * Return: 0
 */
int main(void)
{
	arg_inventory_t *arginv;

	arginv = buildarginv();
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sig_handler);
	while (!arginv->exit)
	{
		if (arginv->st_mode)
			write(STDOUT_FILENO, "$ ", 2);
		_getline(&arginv->input_commands, &arginv->buflimit);
		add_node_history(&arginv->history, arginv->input_commands);

		tokenize(&arginv->tokens, arginv->input_commands);

		if(arginv->tokens.tokensN>0)
		{
			if (parse(&arginv->parser, &arginv->tokens))
			{
				delete_parser(&arginv->parser);
				delete_tokens(&arginv->tokens);
				continue;
			}

			init_pipeline(&arginv->pipeline, arginv->parser.tree);
			worker_execute(arginv);
			delete_pipeline(&arginv->pipeline);
			delete_parser(&arginv->parser);
		}

		mem_reset(arginv->input_commands, BUFSIZE);

		delete_tokens(&arginv->tokens);
	}
	freeall(arginv);

	return (0);
}
