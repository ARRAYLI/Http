.PHONY:all
all:select_cgi insert_cgi

WORK_PATH=$(shell pwd)
CC=g++
CLFAGS=-Wall -g
LDFLAGS=-lmysqlclient

#  $@: 代表目标文件
#  $^: 代表所有依赖
#  $<: 代表第一个依赖

select_cgi:select_cgi.o sql.o
	@$(CC) $^ -o $@  $(CFLAGS) $(LDFLAGS)
	@echo "[linking] [$^] to [$@] ... done" 
insert_cgi:insert_cgi.o sql.o
	@$(CC) $^ -o $@  $(CFLAGS) $(LDFLAGS)
	@echo "[linking] [$^] to [$@] ... done" 
%.o:%.cpp
	@$(CC) -c $< $(CFLAGS) $(LDFLAGS)
	@echo "[linking] [$^] to [$@] ... done" 

.PHONY:clean

clean:
	@rm -rf *.o select_cgi insert_cgi
