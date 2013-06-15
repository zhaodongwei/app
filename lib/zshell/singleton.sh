#!/bin/sh
# 设置锁文件
done_path="./done/"
done_file="20130615"
if [ -d ${done_path} ] ; then
    :
else
    mkdir ${done_path}
fi
lock_file=${done_path}"/"${done_file}
# 每次运行前检测锁文件是否存在，以及进程是否alive
if [ -f ${lock_file} ] ; then
    kill -0 `cat ${lock_file}`
    if [ 0 -eq $? ] ; then
        echo "program is running ..."
        echo "exit now"
        exit 1
    fi
fi
 
at_exit()
{
    `rm ${lock_file}`
}
# 设置退出时执行的函数, ctrl-C 和 kill 时执行
trap "at_exit;exit 1" INT 15
# 把pid作为锁文件保存,创建了锁文件
echo $$ >${lock_file}
 
# do your work
echo "work start"
sleep 10
echo "work begin"
 
at_exit
