#ifndef DELETE_FUNCTOR_H_
#define DELETE_FUNCTOR_H_

// function_class for use for_each to delete stl_con

class delete_con_functor
{
public:
	//for key-value map
	template<typename key, typename value>
	void operator()(const std::pair<key, value> &ptr)
	{
		delete ptr.second;
	}

	//for vector list queue
	template<typename T>
	void  operator()(T &t)
	{
		delete t;
	}
};

#endif
