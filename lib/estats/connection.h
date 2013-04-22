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
#ifndef ESTATS_CONNECTION_H
#define ESTATS_CONNECTION_H

struct	estats_error* estats_connection_list_new( struct estats_connection_list** );

void	estats_connection_list_free( struct estats_connection_list** );

struct	estats_error* estats_connection_info_new( struct estats_connection_info** );

void	estats_connection_info_free( struct estats_connection_info** );

struct estats_error* estats_connection_tuple_copy(
			struct estats_connection_tuple*,
                        const struct estats_connection_tuple*);

struct	estats_error* estats_connection_tuple_as_strings(
				struct estats_connection_tuple_ascii*,
				struct estats_connection_tuple* );

struct estats_error* estats_connection_list_add_info(struct estats_connection_list*);

estats_error* estats_connection_info_get_cid(int* /*cid*/, const estats_connection_info*);

estats_error* estats_connection_info_get_pid(int* /*pid*/, const estats_connection_info*);

estats_error* estats_connection_info_get_uid(int* /*uid*/, const estats_connection_info*);

estats_error* estats_connection_info_get_cmdline(char** /*str*/, const estats_connection_info*);

estats_error* estats_connection_info_get_tuple(struct estats_connection_tuple*, const estats_connection_info*);

#endif /* ESTATS_CONNECTION_H */
