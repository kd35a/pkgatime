#include <time.h>
#include <stdlib.h>
#include "slist.h"

slist_t* new_slist(time_t time, void* data)
{
	slist_t*	node;

	node = malloc(sizeof(slist_t));
	node->data = data;
	node->time = time;
	node->succ = NULL;

	return node;
}

void free_slist(slist_t** head)
{
	slist_t*	tmp;

	if (*head == NULL) {
		return;
	}

	while ((tmp = (*head)->succ) != NULL) {
		(*head)->succ = tmp->succ;
		free(tmp);
	}
	free(*head);
	*head = NULL;
}


void slist_insert(slist_t** head, time_t time, void* data)
{
	slist_t*	p;
	slist_t*	prev;
	slist_t*	next;

	p = new_slist(time, data);

	if (*head == NULL) {
		*head = p;
		return;
	}

	prev = NULL;
	next = (*head);
	while (next != NULL && next->time <= time) {
		prev = next;
		next = next->succ;
	}
	if (next == NULL) {
		prev->succ = p;
	} else if (prev != NULL) {
		p->succ = prev->succ;
		prev->succ = p;
	} else {
		p->succ = (*head);
		(*head) = p;
	}
}

size_t slist_length(slist_t* head)
{
	slist_t*	p;
	size_t		count;

	if (head == NULL) {
		return 0;
	}

	count = 1;
	p = head;
	while ((p = p->succ) != NULL) {
		count++;
	}

	return count;
}
