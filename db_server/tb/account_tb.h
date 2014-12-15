#ifndef ACCOUNT_TB_H_
#define ACCOUNT_TB_H_

#include <string>
#include "table_obj.h"

class account_tb : public table_obj
{
public:
	virtual int insert(db_date *date);
	virtual int get_info(db_date *date);

private:
	static std::string table_name_;
};

#endif
