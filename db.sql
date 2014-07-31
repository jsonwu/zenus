
drop table if exists account_info;
create table account_info(
	accout      varchar(63) not null primary key,    #帐号
	password    varchar(16) not null,                #密码 
	regist_time int not nULL default 0,              #注册时间
	in_time     int not null default 0,              #最近一次登录时间
	out_time    int not null default 0               #最近一次登出时间
)engine=InnoDB;

