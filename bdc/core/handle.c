#include "handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bdc/core/version.h"

static const char *s_str_usage =
	"Usage: %s COMMAND [OPTIONS]\n"
	"\n"
	"Commands:\n"
	"    gen      generate DBC meta files\n"
	"    check    check datas\n"
	"    compare  compare two source's DBC meta files\n"
	"    connect  connect to server\n";

int bdc_cli_run(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, s_str_usage, argv[0]);
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		fprintf(stdout, s_str_usage, argv[0]);
		exit(EXIT_SUCCESS);
	}

	if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
		fprintf(
			stdout,
			"bdc (backup-data-checker)\nVersion: %s\nCompile Datetime: %s\n",
			bdc_version(), bdc_compile_datetime_iso8601());
		exit(EXIT_SUCCESS);
	}

	// TODO:

	return 0;
}
