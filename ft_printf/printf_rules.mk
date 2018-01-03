.PHONY: $(PRINTF_FCLEAN) $(PRINTF_CLEAN)

$(PRINTF): $(PRINTF_OBJS)
	ar rcs $(PRINTF) $(PRINTF_OBJS)

$(PRINTF_OBJS_DIR)/%.o: $(PRINTF_PATH)/srcs/%.c
	@mkdir -p $(PRINTF_OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(PRINTF_DEPFLAGS) -I$(PRINTF_INCLUDES)
	$(PRINTF_POSTCOMPILE)

$(PRINTF_DEPDIR)/%.dep: ;
.PRECIOUS: $(PRINTF_DEPDIR)/%.dep

$(PRINTF_FCLEAN): $(PRINTF_CLEAN)
ifeq ($(shell [ -e $(PRINTF) ] && echo 1 || echo 0),1)
	rm -rf $(PRINTF)
endif
ifeq ($(shell [ -e $(PRINTF_DEPDIR) ] && echo 1 || echo 0),1)
	rm -rf $(PRINTF_DEPDIR)
endif

$(PRINTF_CLEAN):
ifeq ($(shell [ -e $(PRINTF_OBJS_DIR) ] && echo 1 || echo 0),1)
	rm -rf $(PRINTF_OBJS_DIR)
endif
