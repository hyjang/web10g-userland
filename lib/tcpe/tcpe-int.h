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
#ifndef TCPE_INT_H
#define TCPE_INT_H

/* System headers (use config.h's results to determine whether or not to
   include them) */
#include "config.h"
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <tcpe/types.h>
#include <tcpe/types-int.h>

/* tcpe public headers */
#include <tcpe/error.h>
#include <tcpe/tcpe-client.h>
#include <tcpe/tcpe-data.h>
#include <tcpe/tcpe-genl.h>
#include <tcpe/tcpe.h>
#include <tcpe/tcpe-nl.h>

/* tcpe internal headers */
#include <tcpe/debug-int.h>
#include <tcpe/error-int.h>
#include <tcpe/libcwrap-int.h>
#include <tcpe/list-int.h>
#include <tcpe/resolve-int.h>

#endif /* TCPE_INT_H */
