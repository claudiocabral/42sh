# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_rules.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccabral <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/24 13:19:14 by ccabral           #+#    #+#              #
#    Updated: 2018/03/20 14:35:52 by ccabral          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: $(LIBFT_CLEAN) $(LIBFT_FCLEAN)

$(LIBFT):	$(LIBFT_OBJS) \
			$(LIBFT_SLICE_OBJS) \
			$(LIBFT_ARRAY_OBJS) \
			$(LIBFT_TREE_OBJS) \
			$(LIBFT_BTREE_OBJS) \
			$(LIBFT_RING_BUFFER_OBJS) \
			$(LIBFT_HASH_TABLE_OBJS) \
			$(LIBFT_STRING_OBJS) \
			Makefile
	@ar rcs $@ $^

#$(LIBFT_ARRAY_OBJS)/%.o: $(LIBFT_INCLUDES)/array.h
#$(LIBFT_SLICE_OBJS)/%.o: $(LIBFT_INCLUDES)/slice.h
#$(LIBFT_TREE_OBJS)/%.o: $(LIBFT_INCLUDES)/tree.h
#$(LIBFT_BTREE_OBJS)/%.o: $(LIBFT_INCLUDES)/ft_btree.h
#$(LIBFT_STRING_OBJS)/%.o: $(LIBFT_INCLUDES)/ft_string.h
#$(LIBFT_RING_BUFFER_OBJS)/%.o: $(LIBFT_INCLUDES)/ring_buffer.h
#$(LIBFT_HASH_TABLE_OBJS)/%.o: $(LIBFT_INCLUDES)/hash_table.h

$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_PATH)/srcs/%.c $(LIBFT_INCLUDES)/libft.h
	@[[ -d $(dir $@ ) ]] || mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) -I$(LIBFT_INCLUDES)

$(LIBFT_CLEAN):
ifeq ($(shell [ -e $(LIBFT_OBJ_DIR) ] && echo 1 || echo 0),1)
	rm -rf $(LIBFT_OBJ_DIR)
endif

$(LIBFT_FCLEAN): $(LIBFT_CLEAN)
ifeq ($(shell [ -e $(LIBFT) ] && echo 1 || echo 0),1)
	rm -rf $(LIBFT)
endif
