/*
 * Copyright (c) 2013 The Board of Trustees of the University of Illinois,
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
#ifndef ESTATS_TYPES_INT_H
#define ESTATS_TYPES_INT_H

struct estats_nl_client {
        struct mnl_socket *mnl_sock;
        int fam_id;
	struct estats_mask mask;
};

struct estats_error {
        ESTATS_ERROR num;
        const char* msg;
        char* xtra;
        const char* file;
        int line;
        const char* function;
};

#endif /* ESTATS_TYPES_INT_H */
