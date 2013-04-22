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
#include "scripts.h"

int main(int argc, char **argv)
{

	struct estats_error* err = NULL;
	struct estats_nl_client* cl = NULL;
	struct estats_connection_list* clist = NULL;
	struct estats_list* list_pos;
	struct estats_connection_tuple_ascii asc;

	Chk(estats_nl_client_init(&cl));
	Chk(estats_connection_list_new(&clist));

	printf("%-8s %-20s %-8s %-20s %-8s\n", "CID", "LocalAddr", "LocalPort", "RemAddr", "RemPort");
	printf("-------- -------------------- -------- -------------------- --------\n");
	printf("\n");

	Chk(estats_list_conns(clist, cl));

	ESTATS_LIST_FOREACH(list_pos, &(clist->connection_head)) {
		struct estats_connection* cp = ESTATS_LIST_ENTRY(list_pos, estats_connection, list);
		struct estats_connection_tuple* ct = (struct estats_connection_tuple*) cp;
		Chk(estats_connection_tuple_as_strings(&asc, ct));

		printf("%-8s %-20s %-8s %-20s %-8s\n", asc.cid, asc.local_addr, asc.local_port, asc.rem_addr, asc.rem_port);
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
