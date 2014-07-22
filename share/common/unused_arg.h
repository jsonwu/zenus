#ifndef UNUSED_ARG_H_
#define UNUSED_ARG_H_

//防止未使用的参数或者变量在编译时警告
#define UNUSED_ARG(arg)   {  if (&arg) ; }

#endif
