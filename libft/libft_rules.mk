# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_rules.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccabral <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/24 13:19:14 by ccabral           #+#    #+#              #
#    Updated: 2017/12/08 15:46:27 by claudioca        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: $(LIBFT_CLEAN) $(LIBFT_FCLEAN)

$(LIBFT):	$(LIBFT_OBJS) \
			$(LIBFT_TREE_OBJS) \
			$(LIBFT_BTREE_OBJS) \
			$(LIBFT_ARRAY_OBJS) \
			$(LIBFT_RING_BUFFER_OBJS) \
			$(LIBFT_STRING_OBJS) \
			Makefile
	@ar rcs $@ $^

$(LIBFT_BTREE_OBJS)/%.o: $(LIBFT_INCLUDES)/ft_btree.h
$(LIBFT_ARRAY_OBJS)/%.o: $(LIBFT_INCLUDES)/array.h
$(LIBFT_STRING_OBJS)/%.o: $(LIBFT_INCLUDES)/ft_string.h
$(LIBFT_RING_BUFFER_OBJS)/%.o: $(LIBFT_INCLUDES)/ring_buffer.h

$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_PATH)srcs/%.c $(LIBFT_INCLUDES)/libft.h
	@[[ -d $(dir $@ ) ]] || mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) -I$(LIBFT_INCLUDES)

$(LIBFT_CLEAN):
	rm -rf $(LIBFT_OBJ_DIR)

$(LIBFT_FCLEAN): $(LIBFT_CLEAN)
	rm -rf $(LIBFT)
