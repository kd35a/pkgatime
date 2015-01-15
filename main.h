#ifndef main_h
#define main_h

#include <time.h>

typedef struct _pkgatime_t {
	time_t		time;
	const char*	pkgname;
	char		filename[PATH_MAX];
} pkgatime_t;

void print_pkg(pkgatime_t*);

#endif
