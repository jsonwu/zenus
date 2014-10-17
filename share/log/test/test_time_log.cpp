#include <stdio.h>
#include <stdarg.h>
#include <iostream>

#include "logger.h"
#include "write_file.h"
#include "level_filter.h"
#include "pattern_layout.h"
#include "time_cycle_log.h"

class test_log
{
public:
	static int init(string path);
	static void log(level_value lvl, const char *format, ...);
	static level& get_lvl(const int lvl);
public:
	static bool enable_;
	static logger *logger_;
};


bool test_log::enable_ = true;
logger* test_log::logger_ = NULL;

int test_log::init(string path)
{
	if (test_log::logger_ == NULL)
	{
		test_log::logger_ = new time_cycle_log("test_log_%F", LOG_MIN);
	}
	write_file *p = new write_file(path);
	test_log::logger_->set_writer(p);
	test_log::logger_->set_filter(new level_filter(LOG_LVL_ERROR));
	test_log::logger_->set_layout(new pattern_layout("test_log::%t %l %m"));
	test_log::logger_->start();
}

void  test_log::log(level_value log_lvl, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	char buff[1024] = {0};
	vsnprintf(buff, 1023, format, ap);
	va_end(ap);

	cout << buff << endl;

	level  item_lvl;
	switch (log_lvl)
	{
	case LOG_LVL_ERROR:
		item_lvl = level::level_error();
		break;
	case LOG_LVL_WARN:
		item_lvl = level::level_warn();
		break;
	case LOG_LVL_INFO:
		item_lvl = level::level_info();
		break;
	case LOG_LVL_DEBUG:
		item_lvl = level::level_debug();
		break;
	default:
		break;
	}

	logitem item(level::level_error(), buff);	
	test_log::logger_->log(item);
}


int main()
{
	if (test_log::init("./log") < 0)
		return -1;
	sleep(10);
	int a = 0;
	test_log::log(LOG_LVL_ERROR, "hello world %s %d", "ssss", 112233);
	sleep(30);
	test_log::log(LOG_LVL_ERROR, "hello world %s %d", "ssss", 112233);
	sleep(30);
	test_log::log(LOG_LVL_ERROR, "hello world %s %d", "ssss", 112233);
	sleep(30);
	test_log::log(LOG_LVL_ERROR, "hello world %s %d", "ssss", 112233);
	sleep(30);
	test_log::logger_->close();
}
