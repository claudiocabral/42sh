#include <slice.h>

int			lex_comment(t_slice input)
{
	int	pos;

	pos = input.size + 1;
	while (input.ptr[pos] && input.ptr[pos] != '\n')
		++pos;
	return (pos);
}
