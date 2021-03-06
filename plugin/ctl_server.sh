#!/bin/bash

ROOT_PATH=$(pwd)

LIB=$ROOT_PATH/mysql_lib/lib
BIN=$ROOT_PATH/httpd
CONF=$ROOT_PATH/conf/server.conf


proc=$(basename $0)
id=""

# $0     这个程序的名字
# #n     这个程序的名字第 n 个参数，n=1.9
# $*     这个程序的所有参数，此选项参数可超过 9 个
# $#     这个程序的参数个数
# $$     这个程序的 PID（脚本运行的当前进程 ID 好）
# $!     执行上一个背景指令的 PID （后台运行的最后一个进程的进程 ID 号）
# $?     执行上一个指令的返回值（显示最后命令的退出状态。 0 表示错误，其他任何值表明有错误 ）
# $-     显示 shell 使用的当前选项，与 set 命令功能相同
# $@     与 $* 类似，但是可以当参数使用

function usage()
{
	printf "Usage: %s [start(-s) | stop(-t) | restart(-rt) | status(-ss) | daemon(-d)]\n" "$proc"
}

function server_status()
{
	server_bin=$(basename $BIN)
	id=$(pidof $server_bin)
	if [ ! -z "$id" ];then
		return 0
	else
		return 1
	fi
}

function server_start()
{
	if ! server_status; then
		ip=$(awk -F: '/^IP/{print $NF}' $CONF)
		port=$(awk -F: '/^PORT/{print $NF}' $CONF)
		if [ "X$1" = "Xd" ]; then
			$BIN $ip $port d
		else
			$BIN $ip $port
		fi
		if [ $? -eq 0 ] ;then
		    echo "Start ... done"
		else
		    echo "Start ... faild"
		fi
	else
		echo "server is already running: $id, please stop first!"
	fi
}


function server_stop()
{
	if server_status; then
		kill -9 $id
		echo "Stop ... done"
	else
		echo "server is not running: $id, please start first!"
	fi
}

function server_restart()
{
	if server_status; then
		server_stop
	fi
	server_start
}


function service_status()
{
	if server_status; then
		echo "running"
	else
		echo "not running"
	fi
}

if [ $# -eq 0 ]; then
	usage
	exit 1
fi


case $1 in
	start | -s )
		server_start
		;;
	stop | -t )
		server_stop
		;;
	restart | -rt )
		server_restart
		;;
	status | -ss )
		service_status
		;;
	daemon | -d )
		server_start d
		;;
	* )
		usage;
		exit 1
		;;
esac

