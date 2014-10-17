#ifndef TIME_CYCLE_LOG_H_
#define TIME_CYCLE_LOG_H_

#include "logger.h"
#include "lrunnable.h"
#include "lthread.h"

enum
{
	LOG_MIN,
	LOG_HONOUR,
	LOG_DAY,
	LOG_MONTH,
	LOG_YEAR,
	LOG_NOT_NEW
};

class time_cycle_log : public logger, public lrunnable
{
public:
	time_cycle_log(const char *file_name, int time_splite_type);
	~time_cycle_log();

	virtual int start();
	virtual int run();
private:
	bool if_log_new_file();
private:
	int splite_type_;
	int last_splite_value_;
	lthread  lthread_;
};

#endif
