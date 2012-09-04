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
#include <tcpe/tcpe-int.h>

struct tcpe_error*
tcpe_client_init(struct tcpe_client** cl)
{
	tcpe_error *err = NULL;
	struct mnl_socket *sock;
	int id;
	int ret;
	int i;
	
	ErrIf(cl == NULL, TCPE_ERR_INVAL);
	*cl = NULL;

	Chk(Malloc((void**) cl, sizeof(tcpe_client)));
	memset((void*) *cl, 0, sizeof(tcpe_client));
	_tcpe_list_init(&((*cl)->connection_list_head));

	sock = mnl_socket_open(NETLINK_GENERIC);
	ErrIf(sock == NULL, TCPE_ERR_NOLINK);

	ret = mnl_socket_bind(sock, 0, MNL_SOCKET_AUTOPID);
	ErrIf(ret == -1, TCPE_ERR_NOLINK);

	(*cl)->mnl_sock = sock;

	ret = resolve_genladdr("tcp_estats", *cl);
	ErrIf(ret, TCPE_ERR_NOLINK);

	(*cl)->mask.masks[0] = DEFAULT_PERF_MASK;
	(*cl)->mask.masks[1] = DEFAULT_PATH_MASK;
	(*cl)->mask.masks[2] = DEFAULT_STACK_MASK;
	(*cl)->mask.masks[3] = DEFAULT_APP_MASK;
	(*cl)->mask.masks[4] = DEFAULT_TUNE_MASK;

	for (i = 0; i < MAX_TABLE; i++) {
		(*cl)->mask.if_mask[i] = 0;
	}

 Cleanup:
        return err;
}

void
tcpe_client_destroy(struct tcpe_client** cl)
{
	struct tcpe_list* conn_pos;
	struct tcpe_list* tmp;

	if (cl == NULL || *cl == NULL)
		return;

	mnl_socket_close((*cl)->mnl_sock);

	TCPE_LIST_FOREACH_SAFE(conn_pos, tmp, &((*cl)->connection_list_head)) {
        	tcpe_connection* currConn = TCPE_LIST_ENTRY(conn_pos, tcpe_connection, list);
        	_tcpe_list_del(conn_pos);
        	free(currConn);
	}

	free(*cl);
	*cl = NULL;
}

struct tcpe_error*
tcpe_client_set_mask(struct tcpe_client* cl, struct tcpe_mask* mask)
{
	tcpe_error* err = NULL;

	ErrIf(cl == NULL || mask == NULL, TCPE_ERR_INVAL);

	cl->mask = *mask;

 Cleanup:
 	return err;
}

struct tcpe_error*
tcpe_client_get_sock(struct mnl_socket** nl, const tcpe_client* cl)
{
	tcpe_error* err = NULL;

	ErrIf(nl == NULL || cl == NULL, TCPE_ERR_INVAL);

	*nl = cl->mnl_sock;

 Cleanup:
 	return err;
}

struct tcpe_error*
tcpe_client_get_fam_id(int* id, const tcpe_client* cl)
{
	tcpe_error* err = NULL;

	ErrIf(id == NULL || cl == NULL, TCPE_ERR_INVAL);

	*id = cl->fam_id;

 Cleanup:
 	return err;
}
