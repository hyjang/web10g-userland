#ifndef _TCP_ESTATS_NL_H_
#define _TCP_ESTATS_NL_H_

enum nl_estats_msg_types {
	TCPE_CMD_INIT,
        TCPE_CMD_LIST_CONNS,
        TCPE_CMD_READ_ALL,
        TCPE_CMD_READ_VARS,
        TCPE_CMD_WRITE_VAR,
        NLE_MSG_MAX
};

enum nl_estats_attr {
        NLE_ATTR_UNSPEC,
	NLE_ATTR_NUM_TABLES,
	NLE_ATTR_NUM_VARS,
        NLE_ATTR_PERF_VARS,
        NLE_ATTR_PATH_VARS,
        NLE_ATTR_STACK_VARS,
        NLE_ATTR_APP_VARS,
        NLE_ATTR_TUNE_VARS,
        NLE_ATTR_EXTRAS_VARS,
        NLE_ATTR_PERF_VALS,
        NLE_ATTR_PATH_VALS,
        NLE_ATTR_STACK_VALS,
        NLE_ATTR_APP_VALS,
        NLE_ATTR_TUNE_VALS,
        NLE_ATTR_EXTRAS_VALS,
        NLE_ATTR_MASK,
        NLE_ATTR_4TUPLE,
	NLE_ATTR_WRITE,
	NLE_ATTR_TIME,
        __NLE_ATTR_MAX
};
#define NLE_ATTR_MAX (__NLE_ATTR_MAX - 1)

enum neattr_vars {
        NEA_UNSPEC_VAR,
        NEA_VAR_NAME,
        NEA_VAR_TYPE,
        __NEA_VAR_MAX
};
#define NEA_VAR_MAX (__NEA_VAR_MAX - 1)

enum neattr_4tuple {
        NEA_UNSPEC_TUPLE,
        NEA_REM_ADDR,
        NEA_REM_PORT,
        NEA_LOCAL_ADDR,
        NEA_LOCAL_PORT,
	NEA_ADDR_TYPE,
        NEA_CID,
        __NEA_4TUPLE_MAX
};
#define NEA_4TUPLE_MAX (__NEA_4TUPLE_MAX - 1)

enum neattr_mask {
        NEA_UNSPEC_MASK,
        NEA_PERF_MASK,
        NEA_PATH_MASK,
        NEA_STACK_MASK,
        NEA_APP_MASK,
        NEA_TUNE_MASK,
	NEA_EXTRAS_MASK,
        __NEA_MASK_MAX
};
#define NEA_MASK_MAX (__NEA_MASK_MAX - 1)

enum neattr_write {
	NEA_UNSPEC_WRITE,
	NEA_WRITE_VAR,
	NEA_WRITE_VAL,
	__NEA_WRITE_MAX
};
#define NEA_WRITE_MAX (__NEA_WRITE_MAX - 1)

enum neattr_time {
	NEA_UNSPEC_TIME,
	NEA_TIME_SEC,
	NEA_TIME_USEC,
	__NEA_TIME_MAX
};
#define NEA_TIME_MAX (__NEA_TIME_MAX - 1)

#endif /* _TCP_ESTATS_NL_H_ */