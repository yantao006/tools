#ifndef GR_LOG_H
#define GR_LOG_H

#include "com_log.h"
#include <sstream>
#include <base/logging.h>

namespace gr {

#define CHECK_RET(n, s) { \
    if (n != 0) { \
        LOG(FATAL) << s; \
        exit(1); \
    } \
  }

#define GRLOG(level, log_id, cuid) \
    LOG(level) << "log_id[" << log_id << "], cuid[" \
               << cuid << "], "

#define GRLOG_EX_KERNEL(level, log_id, uid, cuid, baiduid) \
    GrLogStream(level) << __FILE__ << ":" << __LINE__ << "] " << "log_id[" << log_id \
    << "], uid[" << uid \
    << "], cuid[" << cuid \
    << "], baiduid[" << baiduid \
    << "], "

#define GRLOG_EX_KERNEL_CUID(level, log_id, cuid) \
    GrLogStream(level) << __FILE__ << ":" << __LINE__ << "] " << "log_id[" << log_id \
    << "], cuid[" << cuid \
    << "], "

#define GRLOG_EX(level) \
    GRLOG_EX_KERNEL(COMLOG_##level, _log_id, _uid, _cuid, _baiduid)

#define GRLOG_EX_SELF(level) \
    GRLOG_EX_KERNEL(#level, _log_id, _uid, _cuid, _baiduid)

#define GRLOG_EX_CUID(level) \
    GRLOG_EX_KERNEL_CUID(#level, _log_id, _cuid)

#define GRSAMPLELOG_EX(level, log_id, cuid) \
    GRLOG_EX_KERNEL_CUID(#level, log_id, cuid)

class GrLogStream {
public:
    GrLogStream(const std::string& level) {
        _level = comspace::getLogId(level.c_str());
    }

    GrLogStream(const char* level) {
        _level = comspace::getLogId(level);
    }

    GrLogStream(uint32_t level) : _level(level) {}

    ~GrLogStream() {
        com_writelog(_level, "%s", _ss.str().c_str());
    }

    template <typename T> inline GrLogStream& operator<<(T const& t) {
        _ss << t;
        return *this;
    }
private:
    std::stringstream _ss;  // 日志内容缓冲区
    uint32_t _level;        // 日志等级,与comlog对齐
};

}

#endif
