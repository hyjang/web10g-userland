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

void connection_callback(struct tcpe_connection_tuple* ct)
{
	char rem_addr_str[46];
	char local_addr_str[46];

	if ((ct->local_addr[16]) == TCPE_ADDRTYPE_IPV4) {
		inet_ntop(AF_INET, &(ct->rem_addr[0]), &rem_addr_str[0], 40);
		inet_ntop(AF_INET, &(ct->local_addr[0]), &local_addr_str[0], 40);
	}
	else if ((ct->local_addr[16]) == TCPE_ADDRTYPE_IPV6) {
		inet_ntop(AF_INET6, &(ct->rem_addr[0]), &rem_addr_str[0], 40);
		inet_ntop(AF_INET6, &(ct->local_addr[0]), &local_addr_str[0], 40);
	}
	else printf("Unknown INET address type\n");

	printf("%-8d %-20s %-8d %-20s %-8d\n", ct->cid, local_addr_str, ct->local_port, rem_addr_str, ct->rem_port);
}

int main(int argc, char **argv)
{

	struct tcpe_error* err = NULL;
	struct tcpe_client* cl = NULL;

	Chk(tcpe_client_init(&cl));


	printf("%-8s %-20s %-8s %-20s %-8s\n", "CID", "LocalAddr", "LocalPort", "RemAddr", "RemPort");
	printf("-------- -------------------- -------- -------------------- --------\n");
	printf("\n");


	Chk(tcpe_list_conns(cl, connection_callback));

 Cleanup:
	tcpe_client_destroy(&cl);

	if (err != NULL) {
		PRINT_AND_FREE(err);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
