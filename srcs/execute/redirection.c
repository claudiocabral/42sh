int	make_redirection(int from, int mode, t_array *children)
{
	t_tree	**it;
}

int	redirect(t_tree *tree)
{
	int		from;
	int		mode;

	mode = O_RDRW | O_CREATE;
	if ((t_token *)tree->value->tag == '<')
		from = STDIN_FILENO;
	else if ((t_token *)tree->value->tag == '>')
		from = STDOUT_FILENO;
	else if ((t_token *)tree->value->tag == '>')
	{
		from = STDOUT_FILENO;
		mode |= O_APPEND;
	}
	return (make_redirection(from, mode, tree->children));
}
