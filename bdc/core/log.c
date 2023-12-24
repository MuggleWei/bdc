#include "log.h"
#include "muggle/c/muggle_c.h"

static int bdc_log_console_fmt(const muggle_log_msg_t *msg, char *buf,
							   size_t bufsize)
{
	const char *payload = "(null)";
	if (msg->payload) {
		payload = msg->payload;
	}
	return (int)snprintf(buf, bufsize, "%s\n", payload);
}

static int bdc_log_file_fmt(const muggle_log_msg_t *msg, char *buf,
							size_t bufsize)
{
	const char *level = muggle_log_level_to_str(msg->level);

	char filename[MUGGLE_MAX_PATH];
	muggle_path_basename(msg->src_loc.file, filename, sizeof(filename));

	struct tm t;
	gmtime_r(&msg->ts.tv_sec, &t);

	const char *payload = "";
	if (msg->payload) {
		payload = msg->payload;
	}

	return (
		int)snprintf(buf, bufsize,
					 "%s|%d-%02d-%02dT%02d:%02d:%02d.%03d|%s:%u|%s|%llu - %s\n",
					 level, (int)t.tm_year + 1900, (int)t.tm_mon + 1,
					 (int)t.tm_mday, (int)t.tm_hour, (int)t.tm_min,
					 (int)t.tm_sec, (int)msg->ts.tv_nsec / 1000000, filename,
					 (unsigned int)msg->src_loc.line, msg->src_loc.func,
					 (unsigned long long)msg->tid, payload);
}

int bdc_log_init(int level_console, int level_file, const char *log_path,
				 int use_rotate)
{
	static muggle_log_fmt_t console_formatter = { MUGGLE_LOG_FMT_ALL,
												  bdc_log_console_fmt };
	static muggle_log_fmt_t file_formatter = { MUGGLE_LOG_FMT_ALL,
											   bdc_log_file_fmt };

	muggle_logger_t *logger = muggle_logger_default();

	// console handler
	if (level_console >= 0) {
		static muggle_log_console_handler_t console_handler;
		muggle_log_console_handler_init(&console_handler, 1);
		muggle_log_handler_set_level((muggle_log_handler_t *)&console_handler,
									 level_console);
		muggle_log_handler_set_fmt((muggle_log_handler_t *)&console_handler,
								   &console_formatter);
		logger->add_handler(logger, (muggle_log_handler_t *)&console_handler);
	}

	if (level_file > 0) {
		if (use_rotate) {
			static muggle_log_file_time_rot_handler_t file_time_rot_handler;
			muggle_log_file_time_rot_handler_init(
				&file_time_rot_handler, log_path,
				MUGGLE_LOG_TIME_ROTATE_UNIT_DAY, 1, false);
			muggle_log_handler_set_level(
				(muggle_log_handler_t *)&file_time_rot_handler, level_file);
			muggle_log_handler_set_fmt(
				(muggle_log_handler_t *)&file_time_rot_handler,
				&file_formatter);
			logger->add_handler(logger,
								(muggle_log_handler_t *)&file_time_rot_handler);
		} else {
			static muggle_log_file_handler_t file_handler;
			muggle_log_file_handler_init(&file_handler, log_path, "wb");
			muggle_log_handler_set_level((muggle_log_handler_t *)&file_handler,
										 level_file);
			muggle_log_handler_set_fmt((muggle_log_handler_t *)&file_handler,
									   &file_formatter);
			logger->add_handler(logger, (muggle_log_handler_t *)&file_handler);
		}
	}

	return 0;
}
