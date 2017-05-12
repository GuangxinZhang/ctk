/*
 ============================================================================
 Name        : ctk.c
 Author      : guangxinzhang@outlook.com
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#include "kafka_manage.h"
#include "config.h"
#include "ctail.h"
#include "log.h"
#include "ini.h"

kafka_handle *k_handle;
config conf;

int main(int argc, char *argv[]) {

	init_config("config.ini", &conf);

	if (log4c_init()) {
		printf("log4c_init() failed");
	}

	logger = log4c_category_get("log_file");

	LOG_INFO("程序开始！文件：%s 位置：%s  kafka：%s topic：%s ", conf.path, conf.position, conf.brokers, conf.topic);

	k_handle = (kafka_handle*) malloc(sizeof(kafka_handle));
	k_handle->brokers = conf.brokers;
	k_handle->topic = conf.topic;

	if (kafka_init(k_handle)) {
		LOG_INFO("%s","kafka topic  已连接！");
	} else {
		LOG_ERROR("%s","kafka topic  连接失败！");
	}
	if (conf.path){
		// 实时读取文本数据，推送至kafka
		ctail(conf.path, atoi(conf.position), k_handle, kafka_produce);
	} else {
		LOG_ERROR("%s 文本不存在！", conf.path);
	}

	LOG_INFO("%s","销毁kafka...");
	kafka_destroy(k_handle);

	LOG_INFO("%s","退出日志...");
	if (log4c_fini()) {
		printf("log4c_fini() failed");
	}

	return 0;
}
