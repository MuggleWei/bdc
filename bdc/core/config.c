#include "config.h"
#include "muggle/c/muggle_c.h"
#include "bdc/core/utils.h"
#include <stdlib.h>

static const char *bdc_get_root_dir(char *buf, size_t bufsize)
{
	char bin_path[MUGGLE_MAX_PATH];
	char bin_dir[MUGGLE_MAX_PATH];

	if (muggle_os_process_path(bin_path, sizeof(bin_path)) != 0) {
		return NULL;
	}

	if (muggle_path_dirname(bin_path, bin_dir, sizeof(bin_dir)) != 0) {
		return NULL;
	}

	if (muggle_path_dirname(bin_dir, buf, bufsize) != 0) {
		return NULL;
	}

	return buf;
}

static char s_default_config_path[MUGGLE_MAX_PATH];
static void bdc_init_default_config_path()
{
	// ${USER_HOME}/.local/bdc/config.xml
	const char *path_home_local_cfg = NULL;

	// ${USER_HOME}/.bdc/config.xml
	const char *path_home_cfg = NULL;

	// ${BDC_BIN_PATH}/../etc/config.xml
	const char *path_bdc_etc_cfg = NULL;

	char homedir[128];
	char home_local_cfg[256];
	char home_cfg[256];
	if (bdc_homedir(homedir, sizeof(homedir))) {
		if (muggle_path_join(homedir, ".local/bdc/config.xml", home_local_cfg,
							 sizeof(home_local_cfg)) == 0) {
			path_home_local_cfg = home_local_cfg;
		}

		if (muggle_path_join(homedir, ".bdc/config.xml", home_cfg,
							 sizeof(home_cfg)) == 0) {
			path_home_cfg = home_cfg;
		}
	}

	char root_dir[MUGGLE_MAX_PATH];
	char bdc_etc_cfg[MUGGLE_MAX_PATH];
	if (bdc_get_root_dir(root_dir, sizeof(root_dir))) {
		if (muggle_path_join(root_dir, "etc/config.xml", bdc_etc_cfg,
							 sizeof(bdc_etc_cfg)) == 0) {
			path_bdc_etc_cfg = bdc_etc_cfg;
		}
	}

	memset(s_default_config_path, 0, sizeof(s_default_config_path));

	if (muggle_path_exists(path_home_local_cfg)) {
		strncpy(s_default_config_path, path_home_local_cfg,
				sizeof(s_default_config_path) - 1);
		return;
	}

	if (muggle_path_exists(path_home_cfg)) {
		strncpy(s_default_config_path, path_home_cfg,
				sizeof(s_default_config_path) - 1);
		return;
	}

	if (muggle_path_exists(path_bdc_etc_cfg)) {
		strncpy(s_default_config_path, path_bdc_etc_cfg,
				sizeof(s_default_config_path) - 1);
		return;
	}
}

static muggle_once_flag s_flag = MUGGLE_ONCE_FLAG_INIT;
const char *bdc_default_config_path()
{
	muggle_call_once(&s_flag, bdc_init_default_config_path);
	if (s_default_config_path[0] != '\0') {
		return s_default_config_path;
	}
	return NULL;
}
