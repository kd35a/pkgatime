#ifndef slist_h
#define slist_h

#include <time.h>

typedef struct slist_t slist_t;

struct slist_t {
	slist_t*	succ;
	time_t		time;
	void*		data;
};

slist_t* new_slist(time_t, void*);
void	free_slist(slist_t**);
void	slist_insert(slist_t**, time_t, void*);
size_t slist_length(slist_t*);

#endif
