#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>

#include "kafka_manage.h"
#include "ctail.h"
#include "log.h"

#define FILE_LINE_LENGTH 1024

long offset = 0;
static int ifrun = 1;             // 程序退出标识

long file_length(char *file);


static void stop(int sig) {
	ifrun = 0;
	LOG_INFO("%s", "程序结束！");
}

void set_signal(){
	signal(SIGINT, stop);
	signal(SIGKILL, stop);
	signal(SIGSTOP, stop);
	signal(SIGTERM, stop);
}


long file_length(char *file) {
	long len;
	FILE *fp = fopen(file, "r");
	if (!fp) {
		LOG_ERROR("cant open file, file: %s\n", file);
		return -2;
	}
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fclose(fp);
	return len;
}

int ctail(char *path, int position, kafka_handle *handle, void (*callback)()) {

	if (position == 0) {
		offset = 0;
	} else if (position == -1) {
		offset = file_length(path);
	} else {
		return -1;
	}
	if (!path){
		return -1;
	}
	set_signal();
	while (1) {
		LOG_INFO("offset : %d", offset);
		if (ifrun == 0) {
			break;
		}
		// 如果读取长度超过文件长度，则重置offset为当前文本新的长度
		if (offset > file_length(path)) {
			offset = file_length(path);
		}
		FILE *fp = fopen(path, "r");
		if (!fp) {
			LOG_ERROR("cant open file, file: %s\n", path);
			return -2;
		}

		fseek(fp, offset, SEEK_SET);
		char text[FILE_LINE_LENGTH];
		char *result;
		uint32_t len;
		while (!feof(fp)) {
			memset(text, 0x0, FILE_LINE_LENGTH);
			result = fgets(text, FILE_LINE_LENGTH, fp);

			if (result){
				len = strlen(text);
				if (len == 0 || text[len - 1] != '\n')
					continue;
				text[len - 1] = 0;
				offset += len;
				callback(handle, text);
			} else {
				LOG_INFO("result: %s", result);
			}
			if (ifrun == 0) {
				break;
			}
		}

		fclose(fp);
		sleep(1);
	}
	return 0;
}
