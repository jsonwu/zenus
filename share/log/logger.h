#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

#include "writer.h"
#include "logitem.h"
#include "pattern_layout.h"
#include "filter.h"

using namespace std;

class logger
{
public:
	logger(string filename_pattern);
	~logger();

	virtual int start()
	{  return 0; }
	int open();
	void close();

	int log(char *formate, ...);
	int log(logitem &item);
	void set_filter(filter *f);
	void set_layout(layout *l);
	void set_writer(writer *w);

private:
	void logfile_name(string &file_name);

private:
	filter *filter_;
	layout *layout_;
	writer *writer_;
	string filename_pattern_;
};


#endif
