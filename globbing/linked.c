/*
 * file: linked.c
 * author: iomonad
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "globbing.h"
#include "linked.h"

/*
 * Allocate new node
 */
t_glob*
newnode(const char *raw, Flavor flavor)
{
	t_glob *node;

	if (raw == NULL || raw[0] == 0x0) {
		return (NULL);
	}
	if ((node = (t_glob*)malloc(sizeof(t_glob))) == NULL) {
		return (NULL);
	}
	node->raw = strdup(raw);
	node->token = flavor;
	node->next = NULL;
	return (node);
}

/*
 * Append new node
 */
void
append(t_glob** head, t_glob *node)
{
	t_glob* iterator;

	if (node == NULL) {
		return ;
	}
	if (head == NULL || *head == NULL) {
		*head = node;
	} else {
		iterator = *head;
		while (iterator->next != NULL) {
			iterator = iterator->next;
		}
		iterator->next = node;
	}
}
