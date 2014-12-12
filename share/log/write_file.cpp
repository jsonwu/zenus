#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>

#include "write_file.h"

write_file::write_file(string path)
	: fp_(NULL),
	file_fd_(0),
	path_(path)
{ }

write_file::~write_file()
{  }

int write_file::open(const string &name)
{
	this->write_size_ = 0;

	if (access(this->path_.c_str(), F_OK) != 0)
	{
		if (mkdir(this->path_.c_str(), 0777) != 0)
			return -1;
	}

	char f[1024] = {0};
	string file = this->path_ + "/" + name;
	int max_number = 4096;
	int number = 0;
	while(number < max_number)
	{
		number++;
		if (access(file.c_str(), F_OK) != 0)
			break;
		bzero(f, 1024);
		snprintf(f, 1023, "%s/%s.%d", this->path_.c_str(), name.c_str(), number);
		file = f;
	}

	/*
	this->file_fd_ = ::open(file.c_str(), O_RDWR|O_CREAT, 0777);
	if (this->file_fd_ < 0)
		return -1;
	*/
	this->fp_ = fopen(file.c_str(), "w");
	if (this->fp_ == NULL)
		return -1;
	return 0;
}

int write_file::write(const string &msg)
{
	return this->write(msg.c_str());
}

int write_file::write(const char *msg)
{
	int len = strlen(msg);
	/*
	if (::write(this->file_fd_, msg, len) < 0)
		return -1;
	*/
	if (fwrite((void *)msg, len, 1, this->fp_) != 1)
		return -1;
	//cout << "last write:" << msg << endl;
	this->write_size_ += len; 
	return 0;
}

int write_file::flush()
{
	fflush(this->fp_);
	return 0;
}

int write_file::close()
{
	this->flush();
	int ret = ::close(this->file_fd_);
	cout << "close ret " << ret << endl;
	return 0;
}
