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

static struct estats_error*
_estats_get_ino_list(struct estats_connection_list* connection_list)
{
	estats_error* err = NULL;
	struct estats_list* head = &(connection_list->connection_info_head);
	FILE* file = NULL;
	FILE* file6 = NULL;
	char buf[256];
	int scan;
	struct in6_addr in6;

	ErrIf(connection_list == NULL, ESTATS_ERR_INVAL);

	file = fopen("/proc/net/tcp", "r");
	file6 = fopen("/proc/net/tcp6", "r");

	if (file) {
		estats_connection_info* conninfo;

		while (fgets(buf, sizeof(buf), file) != NULL) {

			Chk(estats_connection_info_new(&conninfo));

			if ((scan = sscanf(buf,
				"%*u: %x:%hx %x:%hx %x %*x:%*x %*x:%*x %*x %u %*u %lu",
				(uint32_t *) &(conninfo->tuple.local_addr),
				(uint16_t *) &(conninfo->tuple.local_port),
				(uint32_t *) &(conninfo->tuple.rem_addr),
				(uint16_t *) &(conninfo->tuple.rem_port),
				(int *) &(conninfo->state),
				(uid_t *) &(conninfo->uid),
				(ino_t *) &(conninfo->ino)
				)) == 7) {

				conninfo->addrtype = ESTATS_ADDRTYPE_IPV4;
				_estats_list_add_tail(&conninfo->list, head);
			} else {
				estats_connection_info_free(&conninfo);
			}
		}
		fclose(file);
	}
	
    	if (file6) { 
		estats_connection_info* conninfo;
		char local_addr[INET6_ADDRSTRLEN];
		char rem_addr[INET6_ADDRSTRLEN];

		while (fgets(buf, sizeof(buf), file6) != NULL) {

			Chk(_estats_conninfo_new_entry(&conninfo));

			if ((scan = sscanf(buf,
				"%*u: %64[0-9A-Fa-f]:%hx %64[0-9A-Fa-f]:%hx %x %*x:%*x %*x:%*x %*x %u %*u %u", 
				(char *) &local_addr,
				(uint16_t *) &(conninfo->tuple.local_port),
				(char *) &rem_addr,
				(uint16_t *) &(conninfo->tuple.rem_port),
				(int *) &(conninfo->state),
				(uid_t *) &(conninfo->uid),
				(pid_t *) &(conninfo->ino)
				)) == 7) {
				
				sscanf(local_addr, "%8x%8x%8x%8x", &in6.s6_addr32[0], &in6.s6_addr32[1], &in6.s6_addr32[2], &in6.s6_addr32[3]); 

                		memcpy(&(conninfo->tuple.local_addr), &in6.s6_addr, 16);

				sscanf(rem_addr, "%8x%8x%8x%8x", &in6.s6_addr32[0], &in6.s6_addr32[1], &in6.s6_addr32[2], &in6.s6_addr32[3]);

                		memcpy(&(conninfo->tuple.rem_addr), &in6.s6_addr, 16);

				conninfo->addrtype = ESTATS_ADDRTYPE_IPV6;
				_estats_list_add_tail(&conninfo->list, head);
			} else {
				estats_connection_info_free(&conninfo);
	    		}
       		}
		fclose(file6);
	} 

 Cleanup:
 	return err;
}


