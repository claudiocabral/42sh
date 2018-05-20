#include <ft_printf.h>
#include <token.h>
#include <tree.h>
#include <array.h>
#include <parser.h>

t_tree	*parse_check_errors(t_tree *tree, t_array *tokens, t_token *current)
{
	if (current->type != TOKEN_END || !tree)
	{
		if (tree)
		{
			ft_dprintf(2, "tree is good though\n");
			tree_free(tree, &noop);
			tree = 0;
		}
		while (!current->begin && current != tokens->begin)
			--current;
		ft_dprintf(2, "parse error near ");
		write(2, current->begin, current->size);
		ft_dprintf(2, "\n");
	}
	array_free(tokens, &noop);
	return (tree);
}
