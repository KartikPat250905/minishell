# include "parsing.h"

bool	is_type_token(int value)
{
	return (value == END || value == RED_FO || value == RED_TO
			|| value == PIPE || value == ERROR || value == WORD
			|| value == DLESS || value == DGREAT);
}

bool	is_non_terminal(int value)
{
	return (value == ACCEPT || value == PIPE_SEQ || value == SIMPLE_CMD
			|| value == CMD_NAME || value == CMD_WORD || value == CMD_PRE
			|| value == CMD_SUFFIX || value == IO_REDIRECT || value == IO_FILE
			|| value == FILENAME || value == IO_HERE || value == HERE_END);
}

bool	is_state(int value)
{
	return (value >= 0 && value <= 30);
}