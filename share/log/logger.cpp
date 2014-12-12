#include <stdarg.h>
#include <stdio.h>
#include <iostream>

#include "logger.h"
#include "thread_mutex_guard.h"

#define MAX_LOG_BUFF_SIZE 4096
#define MAX_LOG_FILENAME_SIZE 512

logger::logger(string filename_pattern)
	:filename_pattern_(filename_pattern)
{  }

logger::~logger()
{
	if (this->writer_ != NULL)
	{
		delete this->writer_;
		this->writer_ = NULL;
	}
	if (this->filter_ != NULL)
	{
		delete this->filter_;
		this->filter_ = NULL;
	}
	if (this->layout_ != NULL)
	{
		delete this->layout_;
		this->layout_ = NULL;
	}
}

void logger::close()
{
	this->writer_->close();
}

int logger::open()
{
	string file_name;
	this->logfile_name(file_name);

	thread_mutex_guard<thread_mutex_lock> lock(this->mutex_lock_);
	return this->writer_->open(file_name);
}

int logger::log(char *formate, ...)
{
	if (this->writer_ == NULL)
		return -1;

	va_list args;
	va_start(args, formate);
	char buff[MAX_LOG_BUFF_SIZE] = {0};
	vsnprintf(buff, MAX_LOG_BUFF_SIZE-1, formate, args);
	va_end(args);
	
	thread_mutex_guard<thread_mutex_lock> lock(this->mutex_lock_);
	int result = this->writer_->write(buff);
	return result;
}

int logger::log(logitem &item)
{
	if (this->filter_ != NULL)
	{
		if (!this->filter_->pass(item))
			return -1;
	}

	string write_msg;
	if (this->layout_ != NULL)
	{
		this->layout_->render(item, write_msg);
	}else
	{
		write_msg = item.msg();
	}

	thread_mutex_guard<thread_mutex_lock> lock(this->mutex_lock_);
	this->writer_->write(write_msg);

	return 0;
}

void logger::set_layout(layout *l)
{
	if (this->layout_ != NULL)
		delete this->layout_;

	this->layout_ = l;
}

void logger::set_filter(filter *f)
{
	if (this->filter_ != NULL)
		delete this->filter_;

	this->filter_ = f;
}

void logger::set_writer(writer *w)
{
	if (this->writer_ != NULL)
		delete this->writer_;

	this->writer_ = w;
}

void logger::logfile_name(string &file_name)
{
	char buff[MAX_LOG_FILENAME_SIZE] = {0};
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(buff, MAX_LOG_FILENAME_SIZE-1, this->filename_pattern_.c_str(), t);
	file_name = buff; 
}
