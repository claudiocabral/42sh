/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:14:13 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/13 17:56:46 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# define REVERSE_VIDEO "\e[7m"
# define GREEN_FG "\e[32m"
# define RESET "\e[0m"
# define BACKSPACE 127
# define DELETE "\e[3~"
# define BACKSLASH 92
# define RETURN 10
# define UP "\e[A"
# define DOWN "\e[B"
# define RIGHT "\e[C"
# define LEFT "\e[D"
# define ALT_UP "\e\e[A"
# define ALT_DOWN "\e\e[B"
# define ALT_RIGHT "\e\e[C"
# define ALT_LEFT "\e\e[D"
# define SHIFT_ALT_R "10C"
# define SHIFT_ALT_L "10D"
# define HOME "\e[H"
# define END "\e[F"
# define ECHAP 27
# define TAB 9

/*
** prompt_type define:
*/

# define STANDARD 0
# define MULTI_LINE 1
# define QUOTE 2
# define DQUOTE 3
# define HEREDOC 4

typedef struct s_sh		t_sh;

typedef	struct			s_prompt
{
	char				c;
	char				cursor;
	char				insertion;
	char				selected;
	char				prompt_len;
	char				prompt_type;
	struct s_prompt		*previous;
	struct s_prompt		*next;
	struct s_prompt		*previous_list;
	struct s_prompt		*next_list;
}						t_prompt;

typedef struct			s_histo_list
{
	char				*command;
	int					index;
	char				cursor;
	struct s_histo_list	*previous;
	struct s_histo_list	*next;
}						t_histo_list;

typedef struct			s_histo
{
	t_histo_list		*history;
	int					fd_history;
}						t_histo;

int						ft_putc(int c);
int						is_only_space(char *str);
char					is_quote_close(t_prompt *list);
char					is_skipable(char c);
char					is_operand(char c);

char					*read_input(t_sh *sh);

void					init_term(t_sh *sh);
void					reset_sh(t_sh *sh);

t_prompt				*init_list(void);
t_prompt				*create_elem(char c);
void					add_elem(t_prompt **list, t_prompt *new);
void					expand_line(t_prompt **list);

t_prompt				*get_first_list(t_prompt *list);
t_prompt				*get_last_list(t_prompt *list);
t_prompt				*get_first_elem(t_prompt *list);
t_prompt				*get_last_elem(t_prompt *list);
t_prompt				*get_last_line(t_prompt *list, int col);

void					link_elem(t_prompt *previous, t_prompt *next);
void					copy_info_elem(t_prompt *src, t_prompt *dst);
void					list_set_link(t_prompt *link_address,
							t_prompt *list, char *previous_or_next);
void					list_apply_type(t_prompt *list, char type);

char					*list_to_str(t_prompt **list);

void					display_prompt(t_prompt *list, char with_options,
							char adj_cursor);
void					print_all_list(t_prompt *list, char with_options);
void					print_list(t_prompt *list, char with_options);

t_prompt				*str_to_list(char *str);
unsigned int			list_len(t_prompt *list);
unsigned int			list_nb(t_prompt *list);
unsigned int			list_nb_return(t_prompt *list);

unsigned int			prompt_len(t_prompt *list);

void					move_left(t_prompt **list);
void					move_right(t_prompt **list);
void					move_begin(t_prompt **list);
void					move_end(t_prompt **list);
void					word_left(t_prompt **list);
void					word_right(t_prompt **list);

void					move_down(t_prompt **list);
void					move_up(t_prompt **list);

void					delete_backspace(t_prompt **list);
void					delete_delete(t_prompt **list);
void					delete_current_elem(t_prompt **list, t_prompt *to_del);

void					free_elem(t_prompt **elem);
void					free_list(t_prompt **list);

void					adjust_cursor(t_prompt *list);
int						get_height_prompt(t_prompt *list);
void					remove_cursor(t_prompt	*list);

void					history_add_command(t_histo_list **history,
									char *command);
void					history_up(t_prompt **list, t_histo_list *history);
void					history_down(t_prompt **list, t_histo_list *history);
void					history_reset_cursor(t_histo_list *history);
void					history(t_histo_list *history);

t_histo_list			*history_file_to_list(int fd);
int						open_history_file(void);
void					write_history(t_sh *sh, t_prompt **list,
							char *prompt_return);

void					copy(t_prompt **list, char input, t_sh *sh);
void					paste(t_prompt **list, t_sh *sh);
void					cut(t_prompt **list);

char					*selectedlist_to_str(t_prompt *list);
t_prompt				*selectedstr_to_list(char *str);
void					remove_selection(t_prompt *list, t_sh *sh);

void					control_d(t_prompt **list);
void					control_l(t_prompt **list);
t_prompt				**get_address_list(t_prompt **list, char address);

int						is_open_bracket(char c);
char					get_closing_bracket(char c);

int						interactive_session(void);
#endif
