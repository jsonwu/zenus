#ifndef WRITE_FILE_H_
#define WRITE_FILE_H_

#include "writer.h"

class write_file  : public writer
{
public:
	write_file(string path);
	virtual ~write_file();

	virtual int open(const string &name);
	virtual int write(const string &msg);
	virtual int write(const char *msg);
	virtual int flush();
	virtual int close();
private:
	int file_fd_;
	string path_;
};

#endif
