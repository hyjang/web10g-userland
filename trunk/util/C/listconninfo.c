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
#include "scripts.h"

void connection_callback(struct estats_connection_tuple* ct)
{
	char rem_addr_str[46];
	char local_addr_str[46];

	if ((ct->local_addr[16]) == ESTATS_ADDRTYPE_IPV4) {
		inet_ntop(AF_INET, &(ct->rem_addr[0]), &rem_addr_str[0], 40);
		inet_ntop(AF_INET, &(ct->local_addr[0]), &local_addr_str[0], 40);
	}
	else if ((ct->local_addr[16]) == ESTATS_ADDRTYPE_IPV6) {
		inet_ntop(AF_INET6, &(ct->rem_addr[0]), &rem_addr_str[0], 40);
		inet_ntop(AF_INET6, &(ct->local_addr[0]), &local_addr_str[0], 40);
	}
	else printf("Unknown INET address type\n");

	printf("%-8d %-20s %-8d %-20s %-8d\n", ct->cid, local_addr_str, ct->local_port, rem_addr_str, ct->rem_port);
}

int main(int argc, char **argv)
{

	struct estats_error* err = NULL;
	struct estats_nl_client* cl = NULL;
	struct estats_connection_list* clist = NULL;
	struct estats_list* head;
	struct estats_list* pos;

	Chk(estats_nl_client_init(&cl));
	Chk(estats_connection_list_new(&clist));

	printf("%-8s %-20s %-8s %-20s %-8s\n", "CID", "LocalAddr", "LocalPort", "RemAddr", "RemPort");
	printf("-------- -------------------- -------- -------------------- --------\n");
	printf("\n");

	Chk(estats_list_conns(clist, NULL, cl));

	Chk(estats_connection_list_add_info(clist));

	head = &clist->connection_info_head;

	ESTATS_LIST_FOREACH(pos, head) {
	    estats_connection_info* ci = ESTATS_LIST_ENTRY(pos, estats_connection_info, list);
	    printf("CID: %d, CMD: %s\n", ci->cid, ci->cmdline);
	}

 Cleanup:
	estats_connection_list_free(&clist);
	estats_nl_client_destroy(&cl);

	if (err != NULL) {
		PRINT_AND_FREE(err);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
