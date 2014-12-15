#ifndef SESSION_MGR_H_
#define SESSION_MGR_H_

class session_mgr : public singleton<session_mgr>
{
public:
	session_mgr()
		: curr_id_(0)
	{  }
	int alloc()
	{ return this->curr_id_++; }

private:
	int curr_id_;
};

#endif
