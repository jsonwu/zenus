#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>

using namespace std;
typedef enum
{
	LOG_LVL_DEBUG,
	LOG_LVL_INFO,
	LOG_LVL_WARN,
	LOG_LVL_ERROR
}level_value;

class level
{
public:
	level(level_value value, string name)
		:value_(value),
		lvl_name_(name)
	{ }
	level()
	{ }

	static level& level_debug()
	{
		static level lvl_debug(LOG_LVL_DEBUG, "debug");
		return lvl_debug;
	}

	static level& level_info()
	{
		static level lvl_info(LOG_LVL_INFO, "info");
		return lvl_info;
	}

	static level& level_warn()
	{
		static level lvl_warn(LOG_LVL_WARN, "warn");
		return lvl_warn;
	}

	static level& level_error()
	{
		static level lvl_error(LOG_LVL_ERROR, "error");
		return lvl_error;
	}

	level_value get_value()
	{ return this->value_; }

	string& get_name()
	{  return this->lvl_name_; }

private:
	level_value value_;
	string lvl_name_;
};

#endif
