#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "log.h"
#include "kafka_manage.h"

static void dr_msg_cb(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage,
		void *opaque) {
	if (rkmessage->err){
		LOG_ERROR("%% Message delivery failed: %s", rd_kafka_err2str(rkmessage->err));
	}else{
		LOG_INFO( "%% Message delivered (%zd bytes, partition %"PRId32")", rkmessage->len, rkmessage->partition);
	}
	/* The rkmessage is destroyed automatically by librdkafka */
}

int kafka_init(kafka_handle *handle) {

	handle->conf = rd_kafka_conf_new();

	if (rd_kafka_conf_set(handle->conf, "bootstrap.servers", handle->brokers,
			handle->errstr, sizeof(handle->errstr)) != RD_KAFKA_CONF_OK) {
		LOG_ERROR("%s\n", handle->errstr);
		return ERROR;
	}
	// 注册回调函数，消息成功或失败都会执行dr_msg_cb
	rd_kafka_conf_set_dr_msg_cb(handle->conf, dr_msg_cb);

	// 创建生产者
	handle->rk = rd_kafka_new(RD_KAFKA_PRODUCER, handle->conf, handle->errstr,
			sizeof(handle->errstr));
	if (!handle->rk) {
		LOG_ERROR( "%% Failed to create new producer: %s\n",
				handle->errstr);
		return ERROR;
	}

	// 绑定topic
	handle->rkt = rd_kafka_topic_new(handle->rk, handle->topic, NULL);
	if (!handle->rkt) {
		LOG_ERROR("%% Failed to create topic object: %s\n",
				rd_kafka_err2str(rd_kafka_last_error()));
		rd_kafka_destroy(handle->rk);
		return ERROR;
	}
	return SUCCESS;
}

void kafka_produce(kafka_handle *handle, char msg[1024]) {
	size_t len = strlen(msg);
	if (msg[len - 1] == '\n') /* Remove newline */
		msg[--len] = '\0';
	if (len == 0) {
		/* Empty line: only serve delivery reports */
		rd_kafka_poll(handle->rk, 0/*non-blocking */);
	}
	retry: if (rd_kafka_produce(
	/* Topic object */
	handle->rkt,
	/* Use builtin partitioner to select partition*/
	RD_KAFKA_PARTITION_UA,
	/* Make a copy of the payload. */
	RD_KAFKA_MSG_F_COPY,
	/* Message payload (value) and length */
	msg, len,
	/* Optional key and its length */
	NULL, 0,
	/* Message opaque, provided in
	 * delivery report callback as
	 * msg_opaque. */
	NULL) == -1) {
		/**
		 * Failed to *enqueue* message for producing.
		 */
		fprintf(stderr, "%% Failed to produce to topic %s: %s\n",
				rd_kafka_topic_name(handle->rkt),
				rd_kafka_err2str(rd_kafka_last_error()));

		/* Poll to handle delivery reports */
		if (rd_kafka_last_error() == RD_KAFKA_RESP_ERR__QUEUE_FULL) {
			/*
			 * 如果队列已满，等待消息发射，并且重试
			 * 队列长度限制在配置文件里的配置项：
			 * queue.buffering.max.messages */
			rd_kafka_poll(handle->rk, 1000/*block for max 1000ms*/);
			goto retry;
		}
	} else {
		//fprintf(stderr, "%% Enqueued message (%zd bytes) for topic %s\n", len, rd_kafka_topic_name(handle->rkt));
	}
	rd_kafka_poll(handle->rk, 0/*non-blocking*/);
}

void kafka_destroy(kafka_handle *handle) {
	LOG_INFO("%s","Flushing final messages..");
	rd_kafka_flush(handle->rk, 10 * 1000 /* 最多等待10秒*/);

	// 销毁topic
	rd_kafka_topic_destroy(handle->rkt);

	// 销毁producer
	rd_kafka_destroy(handle->rk);

}
