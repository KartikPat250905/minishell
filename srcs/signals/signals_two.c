# include "minishell.h"

void here_doc_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("here doc sig");
		g_exit_status = 130;
		exit(130);
	}
}
