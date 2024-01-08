#include "cmd_gen.h"
#include "bdc/core/config.h"
#include "muggle/c/muggle_c.h"

typedef struct cmd_gen_args {
	const char *name;
	const char *config;
	const char *path;
} cmd_gen_args_t;

static const char *s_cmd_gen_str_usage =
	"bdc gen [OPTIONS]\n"
	"OPTIONS:\n"
	"    -n, --name      specify data name that need generate meta info\n"
	"    -c, --config    specify the configuration file path\n"
	"    -p, --path      specify path\n";

static int parse_args_cmd_gen(int argc, char **argv, cmd_gen_args_t *args)
{
	memset(args, 0, sizeof(*args));

	int c;
	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
			{ "help", no_argument, NULL, 'h' },
			{ "name", required_argument, NULL, 'n' },
			{ "config", required_argument, NULL, 'c' },
			{ "path", required_argument, NULL, 'p' },
			{ NULL, 0, NULL, 0 }
		};

		c = getopt_long(argc, argv, "hn:c:p:", long_options, &option_index);
		if (c == -1) {
			break;
		}

		switch (c) {
		case 'h': {
			fprintf(stdout, "%s\n", s_cmd_gen_str_usage);
			exit(EXIT_SUCCESS);
		} break;
		case 'n': {
			args->name = optarg;
		} break;
		case 'c': {
			args->config = optarg;
		} break;
		case 'p': {
			args->path = optarg;
		} break;
		}
	}

	if (args->path != NULL) {
	}

	return 0;
}

int bdc_cli_run_cmd_gen(int argc, char **argv)
{
	cmd_gen_args_t args;
	if (parse_args_cmd_gen(argc, argv, &args) != 0) {
		fprintf(stderr, "failed parse args for command: gen\n");
		return -1;
	}

	// priority: path > name
	if (args.path != NULL) {
		// TODO:
	} else {
		if (args.name == NULL) {
			args.name = "default";
		}

		// TODO:
	}

	return 0;
}
