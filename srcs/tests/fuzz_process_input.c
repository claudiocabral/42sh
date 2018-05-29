#include <shellma.h>
#include <stdint.h>
#include <libft.h>
#include <stdlib.h>
#include <mysh.h>
#include <array.h>

#define llvm_fuzzer_test_one_input LLVMFuzzerTestOneInput

extern char **environ;

int llvm_fuzzer_test_one_input(const uint8_t *data, size_t size)
{
	char	*str;
	int		result;

	if (!get_environment_array())
	{
		if (!ft_prepare_env(environ) || !init_path_table())
		{
			ft_dprintf(2, "42sh: failed to setup environment\n");
			return (1);
		}
	}

	ZERO_IF_FAIL(str = (char *)malloc(size + 1));
	ft_memcpy(str, data, size);
	str[size] = 0;
	result = process_input(str);
	//array_free(get_environment_array(), (t_freef) & free_wrapper);
	//free_global_paths();
	return (result);
}
