#ifndef LOGGER_H_
#define LOGGER_H_
#include <string.h>
#include <stdlib.h>
#include "log4c.h"
#include "log4c/category.h"

log4c_category_t* logger;

#define LOG_ERROR(msg, args...) \
    { \
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
    char new_fmt[2048];\
	const char *head_fmt = "[FILE:%s, LINE:%d, FUNCTION:%s] ";\
	sprintf(new_fmt, head_fmt , __FILE__ , __LINE__ , __FUNCTION__);\
	strcat(new_fmt, msg);\
    log4c_category_log_locinfo(logger, &locinfo, LOG4C_PRIORITY_ERROR, new_fmt, ##args); \
    }

#define LOG_WARN(msg, args...) \
    { \
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
    char new_fmt[2048];\
	const char *head_fmt = "[FILE:%s, LINE:%d, FUNCTION:%s] ";\
	sprintf(new_fmt, head_fmt , __FILE__ , __LINE__ , __FUNCTION__);\
	strcat(new_fmt, msg);\
    log4c_category_log_locinfo(logger, &locinfo, LOG4C_PRIORITY_WARN, new_fmt, ##args); \
    }

#define LOG_INFO(msg, args...) \
    { \
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL); \
    char new_fmt[2048];\
	const char *head_fmt = "[FILE:%s, LINE:%d, FUNCTION:%s] ";\
	sprintf(new_fmt, head_fmt , __FILE__ , __LINE__ , __FUNCTION__);\
	strcat(new_fmt, msg);\
    log4c_category_log_locinfo(logger, &locinfo, LOG4C_PRIORITY_INFO, new_fmt, ##args); \
    }

#define LOG_DEBUG(msg, args...) \
    { \
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL); \
    char new_fmt[2048];\
	const char *head_fmt = "[FILE:%s, LINE:%d, FUNCTION:%s] ";\
	sprintf(new_fmt, head_fmt , __FILE__ , __LINE__ , __FUNCTION__);\
	strcat(new_fmt, msg);\
    log4c_category_log_locinfo(logger, &locinfo, LOG4C_PRIORITY_DEBUG, new_fmt, ##args); \
    }

#define LOG_TRACE(msg, args...) \
    { \
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER(NULL);\
    char new_fmt[2048];\
	const char *head_fmt = "[FILE:%s, LINE:%d, FUNCTION:%s] ";\
	sprintf(new_fmt, head_fmt , __FILE__ , __LINE__ , __FUNCTION__);\
	strcat(new_fmt, msg);\
    log4c_category_log_locinfo(logger, &locinfo, LOG4C_PRIORITY_TRACE, new_fmt, ##args); \
    }

#endif
