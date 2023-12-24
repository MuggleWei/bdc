#include "utils.h"
#include "muggle/c/muggle_c.h"

const char *bdc_homedir(char *buf, unsigned int bufsize)
{
	if (buf == NULL) {
		return NULL;
	}

#if WIN32
#else
	const char *home_dir = getenv("HOME");
	if (home_dir == NULL) {
		fprintf(stderr, "failed get home directory, failed getenv(\"HOME\")");
		return NULL;
	}

	size_t len = strlen(home_dir);
	if (len >= bufsize) {
		fprintf(stderr,
				"failed get home directory, buffer size is not enough\n");
		return NULL;
	}

	memcpy(buf, home_dir, len);
	buf[len] = '\0';
	return buf;
#endif
}
