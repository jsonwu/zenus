#include <iostream>
#include <stdio.h>
#include "pattern_layout.h"

pattern_layout::pattern_layout(const char *name)
	:pattern_(name)
{  }

void pattern_layout::render(logitem &item, string &out)
{
	cout << "laytout :" << item.msg() << endl; 
	cout << "laytout :" << this->pattern_ << endl; 
	string::const_iterator it = this->pattern_.begin();
	while(it != this->pattern_.end())
	{
		if (*it != '%')
		{
			out.append(1, *it);
			it++;
		}else
		{
			it++;
			if(it == this->pattern_.end())
			{
				out.append(1, *it);
			}else
			{
				string s;
				bool result = this->pattern_msg(item, *it, s);
				if(!result)
				{
					out.append(1, '%');
					out.append(1, *it);
				}else
				{
					out.append(s);
				}
				it++;
			}
		}
	}
	cout << "laytout :" << out << endl; 
}


bool pattern_layout::pattern_msg(logitem &item, char c, string &out)
{
	bool result = true;
	switch(c)
	{
		case 'm':
			out = item.msg();
			break;
		case 'l':
			out = item.lvl_name();
			break;
		case 't':
			out = item.strtime();
			break;
		case 'T':
			{
				char buff[32] = {0};
				snprintf(buff, 31, "%d", item.time());
				result = buff;
				break;
			}
		default:
			result = false;
			break;
	}
	return result;
}
