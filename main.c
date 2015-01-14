#include <alpm.h>
#include <alpm_list.h>
#include <stdio.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void print_pkg_files(alpm_pkg_t *pkg)
{
	alpm_filelist_t	*filelist;
	alpm_file_t	file;
	struct stat	buf;
	char		filename[PATH_MAX];
	int		i;

	filelist = alpm_pkg_get_files(pkg);

	for(i = 0; i < filelist->count; i++) {
		file = filelist->files[i];
		sprintf(filename, "/%s", file.name);

		stat(filename, &buf);
		if (!S_ISREG(buf.st_mode)) {
			continue;
		}

		printf("%ld\t%s\t%s\n",
			buf.st_atime,
			strtok(ctime(&buf.st_atime), "\n"),
			filename);
	}
}

int main(void)
{
	alpm_handle_t		*handle;
	alpm_db_t		*db;
	alpm_list_t		*pkglist;
	alpm_pkg_t		*pkg;
	enum _alpm_errno_t	err;
	char			*pkgfilter = "ctags";
	size_t			pkgfiltersize = sizeof(pkgfilter);

	handle = alpm_initialize("/", "/var/lib/pacman", &err);
	db = alpm_get_localdb(handle);

	pkglist = alpm_db_get_pkgcache(db);
	printf("%zu\n", alpm_list_count(pkglist));

	for (; pkglist; pkglist = alpm_list_next(pkglist)) {
		pkg = pkglist->data;
		if (strncmp(alpm_pkg_get_name(pkg), pkgfilter, pkgfiltersize) == 0) {
			print_pkg_files(pkg);
		}
	}

	alpm_release(handle);

	return 0;
}
