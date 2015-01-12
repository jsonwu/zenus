#include <iostream>
#include <stdlib.h>

#include "digital.h"
#include "bytebuff_pool.h"



using namespace std;
int main(int argc, char *argv[])
{
	//for test buff	

	bytebuff *test_buff = bytebuff_pool::instance()->acquire(2);
	cout << "buff size " << test_buff->size() << endl;
	test_buff->write_short(2);
	test_buff->write_int(4);
	cout << test_buff->size() << endl;

	short a = 0;
	test_buff->look_short(a);
	cout << a << endl;
	test_buff->read_short(a);
	cout << a << endl;

	int b = 0;
	test_buff->look_int(b);
	cout << b << endl;
	test_buff->read_int(b);
	cout << b << endl;





	/*
	//for test buff_pool
	int num = atoi(argv[1]);
	cout << "num : " << num << endl;
	list<bytebuff *> buff_list;
	long all_size = 0;
	for (int i = 0; i < num; ++i)
	{
		bytebuff *buff = bytebuff_pool::instance()->acquire(i);
		if (buff == NULL)
		{
			cout << "acquire num : " << i << "error" << endl;
			continue;
		}
		//cout << num_2n(i) << endl;;
		all_size += buff->size();
		//cout << all_size << endl;
		buff_list.push_back(buff);
	}

	cout << "acquire ok" << endl;
	list<bytebuff *>::iterator iter = buff_list.begin();
	for (; iter!= buff_list.end(); ++iter)
	{
		bytebuff_pool::instance()->release(*iter);
	}
	cout << "release ok"<< endl;
	bytebuff_pool::instance()->print();

	buff_list.clear();
	for (int i = 0; i < num; ++i)
	{
		bytebuff *buff = bytebuff_pool::instance()->acquire(i);
		if (buff == NULL)
		{
			cout << "acquire num : " << i << "error" << endl;
			continue;
		}
		//cout << num_2n(i) << endl;;
		all_size += buff->size();
		//cout << all_size << endl;
		buff_list.push_back(buff);
	}
	bytebuff_pool::instance()->print();
	iter = buff_list.begin();
	for (; iter!= buff_list.end(); ++iter)
	{
		bytebuff_pool::instance()->release(*iter);
	}
	bytebuff_pool::instance()->print();

	*/

	return 0;
}
