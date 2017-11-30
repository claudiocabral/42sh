# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_rules.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccabral <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/24 13:19:14 by ccabral           #+#    #+#              #
#    Updated: 2017/11/22 12:31:02 by claudioca        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: $(LIBFT_CLEAN) $(LIBFT_FCLEAN)

$(LIBFT): $(LIBFT_OBJS) $(LIBFT_BTREE_OBJS) Makefile
	ar rcs $@ $^

$(LIBFT_BTREE_OBJS)/%.o: $(LIBFT_INCLUDES)/ft_btree.h

$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_PATH)srcs/%.c $(LIBFT_INCLUDES)/libft.h
	@mkdir -p $(LIBFT_OBJ_DIR)/btree
	$(CC) -c $< -o $@ $(CFLAGS) -I$(LIBFT_INCLUDES)

$(LIBFT_CLEAN):
	rm -rf $(LIBFT_OBJ_DIR)

$(LIBFT_FCLEAN): $(LIBFT_CLEAN)
	rm -rf $(LIBFT)
