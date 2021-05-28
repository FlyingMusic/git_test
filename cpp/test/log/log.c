#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdarg.h>

typedef enum LOG_LEVEL {
    LEVEL_DEBUG = 0,
    LEVEL_INFO,
    LEVEL_NOTICE,
    LEVEL_WARN,
    LEVEL_ERROR,
} LOG_LEVEL;

void log_info(LOG_LEVEL level, const char *prefix, const char *func, const char *fmt, ...);

#define LOG_D(prefix,fmt,...) log_info(LEVEL_DEBUG,prefix,__FUNCTION__,fmt,##__VA_ARGS__)
#define LOG_W(prefix,fmt,...) log_info(LEVEL_WARN,prefix,__FUNCTION__,fmt,##__VA_ARGS__)
#define LOG_E(prefix,fmt,...) log_info(LEVEL_ERROR,prefix,__FUNCTION__,fmt,##__VA_ARGS__)
#define LOG_I(prefix,fmt,...) log_info(LEVEL_INFO,prefix,__FUNCTION__,fmt,##__VA_ARGS__)
#define LOG_N(prefix,fmt,...) log_info(LEVEL_NOTICE,prefix,__FUNCTION__,fmt,##__VA_ARGS__)

void log_info(LOG_LEVEL level, const char *prefix, const char *func, const char *format,...){
	struct timeval tv;
    gettimeofday(&tv,NULL);
    uint64_t sec=tv.tv_sec;
    uint64_t min=tv.tv_sec/60;
    struct tm cur_tm;
    localtime_r((time_t*)&sec,&cur_tm);
    char cur_time[20];
    snprintf(cur_time,20,"%d-%02d-%02d %02d:%02d:%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);

    char buf[1024] = {0};
	va_list vlist;
	va_start(vlist,format);
	vsnprintf(buf, 1024, format, vlist);
	va_end(vlist);

    char *log_level = NULL;
    switch(level) {
        case LEVEL_DEBUG:
            log_level = "DEBUG"; break;
        case LEVEL_INFO:
            log_level = "INFO"; break;
        case LEVEL_NOTICE:
            log_level = "NOTE"; break;
        case LEVEL_WARN:
            log_level = "WARN"; break;
        case LEVEL_ERROR:
            log_level = "ERROR"; break;
        default:
            log_level = "UNKONW"; break;
    }

    FILE *fpA = fopen("info.log", "a");
    fprintf(fpA, "[%s] %s[%s][%s] %s", cur_time, prefix, func, log_level, buf);
    fclose(fpA);
}

int main() {
    LOG_I("a = %d\n", 10);
    LOG_I("a = %d\n", 10);
    LOG_I("a = %d\n", 10);
    LOG_I("a = %d\n", 10);
    LOG_E("a = %d\n", 10);

    return 0;
}
