BIN=httpd
cc=gcc
SRC=main.c http.c threadpool.c
OBJ=$(SRC:.c=.o)
LDFLAGS=-pthread
CGI_PATH=sql wwwroot/cgi-bin 

.PHONY:all
all:$(CGI_BIN) $(BIN) cgi

cgi:
	@for i in `echo $(CGI_PATH)`;\
	 do\
	 	cd $$i;\
		make;\
		cd -;\
	done

# 链接 
$(BIN):$(OBJ)
	@$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
	@echo "[linking] [$^] to [$@] ... done"

# 编译
%.o:%.c
	@$(CC) -c $< $(CFLAGS) $(LDFLAGS)
	@echo "[comiling] [$^] to [$@] ... done"
.PHONY:clean

clean:
	@rm -rf $(OBJ) $(BIN) output
	@for i in `echo $(CGI_PATH)`;\
		do \
		 	cd $$i;\
			make clean;\
			cd -;\
		done
	@echo "clean project ... done"

.PHONY:output

output:
	@mkdir -p ./output/wwwroot/cgi-bin
	@cp -rf conf 							output
	@cp -rf wwwroot/*.html  				output/wwwroot
	@cp -rf sql/select_cgi 					output/wwwroot/cgi-bin
	@cp -rf sql/insert_cgi  				output/wwwroot/cgi-bin
	@cp -rf httpd 							output
	@cp -rf wwwroot/cgi-bin/math_cgi 		output/wwwroot/cgi-bin
	@cp -rf plugin/ctl_server.sh 			output
	@echo "output project ... done"


