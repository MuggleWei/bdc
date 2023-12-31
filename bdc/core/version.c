#include "version.h"
#include "muggle/c/muggle_c.h"

static char s_compile_dt_buf[32];
static void init_compile_datetime_once()
{
	memset((void *)s_compile_dt_buf, 0, sizeof(s_compile_dt_buf));
	const char *compile_time = bdc_compile_datetime();

	// year
	s_compile_dt_buf[0] = compile_time[7];
	s_compile_dt_buf[1] = compile_time[8];
	s_compile_dt_buf[2] = compile_time[9];
	s_compile_dt_buf[3] = compile_time[10];
	s_compile_dt_buf[4] = '-';

	// First month letter, Oct Nov Dec = '1' otherwise '0'
	s_compile_dt_buf[5] = (compile_time[0] == 'O' || compile_time[0] == 'N' ||
						   compile_time[0] == 'D') ?
							  '1' :
							  '0';
	// Second month letter
	s_compile_dt_buf[6] =
		(compile_time[0] == 'J') ? ( (compile_time[1] == 'a') ? '1' : // Jan, Jun or Jul
				((compile_time[2] == 'n') ? '6' : '7') ) :
		(compile_time[0] == 'F') ? '2' : // Feb 
		(compile_time[0] == 'M') ? (compile_time[2] == 'r') ? '3' : '5' : // Mar or May
		(compile_time[0] == 'A') ? (compile_time[1] == 'p') ? '4' : '8' : // Apr or Aug
		(compile_time[0] == 'S') ? '9' : // Sep
		(compile_time[0] == 'O') ? '0' : // Oct
		(compile_time[0] == 'N') ? '1' : // Nov
		(compile_time[0] == 'D') ? '2' : // Dec
		0;
	s_compile_dt_buf[7] = '-';

	// First day letter, replace space with digit
	s_compile_dt_buf[8] = compile_time[4] == ' ' ? '0' : compile_time[4];
	// Second day letter
	s_compile_dt_buf[9] = compile_time[5];
	s_compile_dt_buf[10] = 'T';

	memcpy(&s_compile_dt_buf[11], &compile_time[12], 8);
}

const char *bdc_version()
{
	return BDC_VERSION;
}

const char *bdc_compile_datetime()
{
	return __DATE__ " " __TIME__;
}

static muggle_once_flag s_flag = MUGGLE_ONCE_FLAG_INIT;
const char *bdc_compile_datetime_iso8601()
{
	muggle_call_once(&s_flag, init_compile_datetime_once);
	return s_compile_dt_buf;
}
