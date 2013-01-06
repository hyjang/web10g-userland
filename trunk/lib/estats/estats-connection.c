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
#include <estats/estats-int.h>

struct estats_error*
estats_connection_list_new(struct estats_connection_list** connection_list)
{
	estats_error* err = NULL;

	ErrIf(connection_list == NULL, ESTATS_ERR_INVAL);
	*connection_list = NULL;

	Chk(Malloc((void**) connection_list, sizeof(estats_connection_list)));
	memset((void*) *connection_list, 0, sizeof(estats_connection_list));
	_estats_list_init(&((*connection_list)->connection_head));
	_estats_list_init(&((*connection_list)->connection_info_head));

 Cleanup:
 	return err;
}

void
estats_connection_list_free(struct estats_connection_list** connection_list)
{
	struct estats_list* conn_pos;
	struct estats_list* tmp;

	if (connection_list == NULL || *connection_list == NULL)
		return;

	ESTATS_LIST_FOREACH_SAFE(conn_pos, tmp, &((*connection_list)->connection_head)) {
        	estats_connection* curr_conn = ESTATS_LIST_ENTRY(conn_pos, estats_connection, list);
        	_estats_list_del(conn_pos);
        	free(curr_conn);
	}

	ESTATS_LIST_FOREACH_SAFE(conn_pos, tmp, &((*connection_list)->connection_info_head)) {
        	estats_connection* curr_conn = ESTATS_LIST_ENTRY(conn_pos, estats_connection, list);
        	_estats_list_del(conn_pos);
        	free(curr_conn);
	}

	free(*connection_list);
	*connection_list = NULL;
}

struct estats_error*
estats_connection_info_new(struct estats_connection_info** connection_info)
{
	estats_error* err = NULL;

	ErrIf(connection_info == NULL, ESTATS_ERR_INVAL);

	*connection_info = NULL;
	
	Chk(Malloc((void**) connection_info, sizeof(estats_connection_info)));
	memset((void*) connection_info, 0, sizeof(estats_connection_info));

 Cleanup:
 	return err;
}

void
estats_connection_info_free(struct estats_connection_info** connection_info)
{
	if (connection_info == NULL || *connection_info == NULL)
		return;

	free(*connection_info);
	*connection_info = NULL;
}
	
struct estats_error*
estats_connection_list_add_info(struct estats_connection_list* connection_list)
{
	estats_error* err = NULL;

 Cleanup:
 	return err;
}
