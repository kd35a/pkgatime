#include <alpm.h>
#include <alpm_list.h>
#include <stdio.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include "main.h"
#include "slist.h"

pkgatime_t* get_pkg_stat(alpm_pkg_t *pkg)
{
	alpm_filelist_t*	filelist;
	alpm_file_t		file;
	struct stat		buf;
	int			i;
	char			filename[PATH_MAX];
	pkgatime_t*		pkgatime;

	pkgatime = malloc(sizeof(pkgatime_t));
	pkgatime->time = 0; // Not optimal, but... working?
	pkgatime->pkgname = alpm_pkg_get_name(pkg);

	filelist = alpm_pkg_get_files(pkg);

	if (filelist->count == 0) {
		free(pkgatime);
		return NULL;
	}
	for(i = 0; i < filelist->count; i++) {
		file = filelist->files[i];
		sprintf(filename, "/%s", file.name);

		stat(filename, &buf);
		if (!S_ISREG(buf.st_mode)) {
			continue;
		}

		if (pkgatime->time < buf.st_atime) {
			pkgatime->time = buf.st_atime;
			strncpy(pkgatime->filename, filename, PATH_MAX - 1);
		}
	}

	return pkgatime;
}

int main(void)
{
	alpm_handle_t		*handle;
	alpm_db_t		*db;
	alpm_list_t		*pkglist;
	alpm_pkg_t		*pkg;
	enum _alpm_errno_t	err;
	pkgatime_t*		pkgatime;
	slist_t*		l = NULL;
	slist_t*		p;
	int			i;

	handle = alpm_initialize("/", "/var/lib/pacman", &err);
	db = alpm_get_localdb(handle);

	pkglist = alpm_db_get_pkgcache(db);
	printf("%zu\n", alpm_list_count(pkglist));

	for (; pkglist; pkglist = alpm_list_next(pkglist)) {
		pkg = pkglist->data;
		pkgatime = get_pkg_stat(pkg);
		if (pkgatime == NULL) {
			continue;
		}
		slist_insert(&l, pkgatime->time, pkgatime);
	}

	p = l;
	for (i = 0; i < 20; i++) {
		print_pkg(p->data);
		p = p->succ;
	}

	p = l;
	for (i = 0; i < slist_length(l); i++) {
		pkgatime = p->data;
		free(pkgatime);
		p = p->succ;
	}

	free_slist(&l);

	alpm_release(handle);

	return 0;
}

void print_pkg(pkgatime_t* pkgatime)
{
	/*printf("%s\n%ld\t%s\n",
		pkgatime->pkgname,
		pkgatime->time,
		ctime(&pkgatime->time));*/
	printf("%32s\t%s",
		pkgatime->pkgname,
		ctime(&pkgatime->time));
}
