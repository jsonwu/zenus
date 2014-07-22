
if [ $# == 0 ];then
	echo "please enter help"
fi

if [ "$1" == "start" ]; then
	for ((i=1; i<$2; i++))
	do
		echo $i
		./a.out &
	done
fi

if [ "$1" == "stop" ]; then
	ps -ef | grep ./a.out | grep -v "grep" | awk '{print $2}'  | xargs kill -9 
fi
