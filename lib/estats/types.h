/*
 * Copyright (c) 2012 The Board of Trustees of the University of Illinois,
 *                    Carnegie Mellon University.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 */
#ifndef ESTATS_TYPES_H
#define ESTATS_TYPES_H

enum MIB_TABLE {
        PERF_TABLE,
        PATH_TABLE,
        STACK_TABLE,
        APP_TABLE,
        TUNE_TABLE,
        __MAX_TABLE
};
#define MAX_TABLE __MAX_TABLE

typedef enum ESTATS_VAL_TYPE {
        ESTATS_UNSIGNED64,
        ESTATS_UNSIGNED32,
        ESTATS_SIGNED32,
        ESTATS_UNSIGNED16,
        ESTATS_UNSIGNED8,
} ESTATS_VAL_TYPE;

typedef enum ESTATS_TYPE {
	ESTATS_TYPE_INTEGER,
	ESTATS_TYPE_INTEGER32,
	ESTATS_TYPE_INET_ADDRESS_IPV4,
	ESTATS_TYPE_COUNTER32,
	ESTATS_TYPE_GAUGE32,
	ESTATS_TYPE_UNSIGNED32,
	ESTATS_TYPE_TIME_TICKS,
	ESTATS_TYPE_COUNTER64,
	ESTATS_TYPE_INET_PORT_NUMBER,
	ESTATS_TYPE_INET_ADDRESS,
	ESTATS_TYPE_INET_ADDRESS_IPV6,
	ESTATS_TYPE_OCTET,
} ESTATS_TYPE;

typedef enum ESTATS_ERROR {
        ESTATS_ERR_SUCCESS	= 0,
        ESTATS_ERR_ACK		= 1,
        ESTATS_ERR_RET_DATA	= 2,
        ESTATS_ERR_INVAL	= 3,
        ESTATS_ERR_NOMEM	= 4,
        ESTATS_ERR_NOENT	= 5,
        ESTATS_ERR_NOLINK	= 6,
        ESTATS_ERR_LIBC		= 7,
	ESTATS_ERR_EOF		= 8,
        ESTATS_ERR_CHKSUM	= 9,
	ESTATS_ERR_STR_CONV	= 10,
	ESTATS_ERR_GENL		= 11,
	ESTATS_ERR_FILE		= 12,
	ESTATS_ERR_ACCESS	= 13,
        ESTATS_ERR_UNKNOWN	= 14,
} ESTATS_ERROR;

typedef enum ESTATS_EVENT {
        ESTATS_NEW_CONN           = 0,
} ESTATS_EVENT;

union estats_union {
	uint64_t uv64;
	uint32_t uv32;
	int32_t  sv32;
	uint16_t uv16;
	uint8_t  uv8;
};

struct estats_val {
        uint64_t masked; /* uint64_t for alignment when r/w to records */
        union {
                uint64_t uv64;
                uint32_t uv32;
                int32_t  sv32;
                uint16_t uv16;
                uint8_t  uv8;
        };
};

struct estats_var {
        char *name;
        enum ESTATS_VAL_TYPE valtype;
	enum ESTATS_TYPE type;
};

struct estats_timeval {
	uint32_t sec;
	uint32_t usec;
};

struct estats_data {
	int length;
	struct estats_val val[0];
};

struct estats_mask {
	uint64_t masks[MAX_TABLE];
	int      if_mask[MAX_TABLE];
};

typedef enum ESTATS_ADDRTYPE {
	ESTATS_ADDRTYPE_IPV4 = 1,
	ESTATS_ADDRTYPE_IPV6 = 2
} ESTATS_ADDRTYPE;

/*
 * estats_addrtype is sent in *_addr[16], below
 */

struct estats_connection_tuple {
	uint8_t   rem_addr[17];
	uint8_t   local_addr[17];
	uint16_t  rem_port;
	uint16_t  local_port;
	int       cid;
};

struct estats_connection_tuple_ascii {
	char rem_addr[INET6_ADDRSTRLEN];
	char local_addr[INET6_ADDRSTRLEN];
	char rem_port[6];
	char local_port[6];
	char cid[11];
};

struct estats_list {
        struct estats_list* next;
        struct estats_list* prev;
};

struct estats_connection {
	uint8_t   rem_addr[17];
	uint8_t   local_addr[17];
	uint16_t  rem_port;
	uint16_t  local_port;
	int       cid;
	struct estats_list  list;
};

#define ESTATS_CMDLINE_LEN_MAX 32

struct estats_connection_info {
	struct estats_connection_tuple  tuple;
	char             cmdline[ESTATS_CMDLINE_LEN_MAX];
	pid_t            pid;
	uid_t            uid;
	ino_t            ino;
	int              state;
	int		 cid;
	ESTATS_ADDRTYPE  addrtype;
	struct estats_list  list;
};

struct estats_connection_list {
	struct estats_list  connection_head;
	struct estats_list  connection_info_head;
};

typedef void (*estats_connection_func)(struct estats_connection_tuple*);

/*
struct estats_record_entry {
	struct estats_timeval tv;
	struct estats_data*   data;
};
*/

typedef enum ESTATS_RECORD_MODE {
	R_MODE,
	W_MODE
} ESTATS_RECORD_MODE;

struct estats_record {
	FILE*  fp;
	int    swap;
	int    bufsize;
	int    nvars;
	ESTATS_RECORD_MODE  mode;
};

extern int max_index[];

extern struct estats_var estats_var_array[];

typedef struct estats_connection	estats_connection;
typedef struct estats_connection_info	estats_connection_info;
typedef struct estats_connection_list	estats_connection_list;
typedef struct estats_data		estats_data;
typedef struct estats_error		estats_error;
typedef struct estats_nl_client		estats_nl_client;
typedef struct estats_record		estats_record;
typedef struct estats_val		estats_val;

static inline int single_index(int inda, int indb)
{
	int ret = indb;
	int i;

	if (inda > 0) {
		for (i = 0; i < inda; i++) {
			ret += max_index[i];
		}
	}
	return ret;
}

typedef enum ESTATS_PERF_INDEX {
	SEGSOUT                 = 0,
	DATASEGSOUT,
	DATAOCTETSOUT,
	HCDATAOCTETSOUT, 
	SEGSRETRANS,
	OCTETSRETRANS,
	SEGSIN,
	DATASEGSIN,
	DATAOCTETSIN,
	HCDATAOCTETSIN, 
	ELAPSEDSECS,
	ELAPSEDMICROSECS,
	STARTTIMESTAMP,
	CURMSS,
	PIPESIZE,
	MAXPIPESIZE,
	SMOOTHEDRTT,
	CURRTO,
	CONGSIGNALS,
	CURCWND,
	CURSSTHRESH,
	TIMEOUTS,
	CURRWINSENT,
	MAXRWINSENT,
	ZERORWINSENT,
	CURRWINRCVD,
	MAXRWINRCVD,
	ZERORWINRCVD,
	SNDLIMTRANSRWIN,
	SNDLIMTRANSCWND,
	SNDLIMTRANSSND,
	SNDLIMTIMERWIN,
	SNDLIMTIMECWND,
	SNDLIMTIMESND,
        __PERF_INDEX_MAX
} ESTATS_PERF_INDEX;
#define PERF_INDEX_MAX __PERF_INDEX_MAX

typedef enum ESTATS_PATH_INDEX {
        RETRANTHRESH,
        NONRECOVDAEPISODES,
        SUMOCTETSREORDERED,
        NONRECOVDA,
        SAMPLERTT,
        RTTVAR,
        MAXRTT,
        MINRTT,
        SUMRTT,
        HCSUMRTT,
        COUNTRTT,
        MAXRTO,
        MINRTO,
        IPTTL,
        IPTOSIN,
        IPTOSOUT,
        PRECONGSUMCWND,
        PRECONGSUMRTT,
        POSTCONGSUMRTT,
        POSTCONGCOUNTRTT,
        ECNSIGNALS,
        DUPACKEPISODES,
        RCVRTT,
        DUPACKSOUT,
        CERCVD,
        ECESENT,
        __PATH_INDEX_MAX
} ESTATS_PATH_INDEX;
#define PATH_INDEX_MAX __PATH_INDEX_MAX

typedef enum ESTATS_STACK_INDEX {
	ACTIVEOPEN,
	MSSSENT,
	MSSRCVD,
	WINSCALESENT,
	WINSCALERCVD,
	TIMESTAMPS,
	ECN,
	WILLSENDSACK,
	WILLUSESACK,
	STATE,
	NAGLE,
	MAXSSCWND,
	MAXCACWND,
	MAXSSTHRESH,
	MINSSTHRESH,
	INRECOVERY,
	DUPACKSIN,
	SPURIOUSFRDETECTED,
	SPURIOUSRTODETECTED,
	SOFTERRORS,
	SOFTERRORREASON,
	SLOWSTART,
	CONGAVOID,
	OTHERREDUCTIONS,
	CONGOVERCOUNT,
	FASTRETRAN,
	SUBSEQUENTTIMEOUTS,
	CURTIMEOUTCOUNT,
	ABRUPTTIMEOUTS,
	SACKSRCVD,
	SACKBLOCKSRCVD,
	SENDSTALL,
	DSACKDUPS,
	MAXMSS,
	MINMSS,
	SNDINITIAL,
	RECINITIAL,
	CURRETXQUEUE,
	MAXRETXQUEUE,
	CURREASMQUEUE,
	MAXREASMQUEUE,
        __STACK_INDEX_MAX
} ESTATS_STACK_INDEX;
#define STACK_INDEX_MAX __STACK_INDEX_MAX

typedef enum ESTATS_APP_INDEX {
        SNDUNA,
        SNDNXT,
        SNDMAX,
        THRUOCTETSACKED,
        HCTHRUOCTETSACKED, 
        RCVNXT,
        THRUOCTETSRECEIVED,
        HCTHRUOCTETSRECEIVED, 
        CURAPPWQUEUE,
        MAXAPPWQUEUE,
        CURAPPRQUEUE,
        MAXAPPRQUEUE,
        __APP_INDEX_MAX
} ESTATS_APP_INDEX;
#define APP_INDEX_MAX __APP_INDEX_MAX

typedef enum ESTATS_TUNE_INDEX { 
        LIMCWND,
        LIMSSTHRESH,
        LIMRWIN,
        LIMMSS,
        __TUNE_INDEX_MAX
} ESTATS_TUNE_INDEX;
#define TUNE_INDEX_MAX __TUNE_INDEX_MAX

#define TOTAL_INDEX_MAX PERF_INDEX_MAX+PATH_INDEX_MAX+STACK_INDEX_MAX+APP_INDEX_MAX+TUNE_INDEX_MAX

#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))

#endif /* ESTATS_TYPES_H */
