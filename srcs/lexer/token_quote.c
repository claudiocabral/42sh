int	token_quote(char c)
{
	return (c == '"' || c == '\'' || c == '`');
}

int	get_quote(int quote)
{
	static int	ret;

	if (quote != -42)
		ret = quote;
	return (ret);
}

int	skip_char(int skip)
{
	static int	ret;

	if (skip != -42)
		ret = skip;
	return (ret);
}
