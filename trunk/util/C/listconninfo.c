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
	struct estats_list* head;
	struct estats_list* pos;
	struct estats_connection_tuple_ascii tuple_ascii;

	Chk(estats_nl_client_init(&cl));
	Chk(estats_connection_list_new(&clist));

	printf("%-8s %-12s %-8s %-8s %-8s %-20s %-8s %-20s %-8s\n", "CID", "cmdline", "PID", "UID", "INO", "LocalAddr", "LocalPort", "RemAddr", "RemPort");
	printf("-------- ------------ -------- -------- -------- -------------------- -------- -------------------- --------\n");
	printf("\n");

	Chk(estats_list_conns(clist, NULL, cl));

	Chk(estats_connection_list_add_info(clist));

	head = &clist->connection_info_head;

	ESTATS_LIST_FOREACH(pos, head) {
	    estats_connection_info* ct = ESTATS_LIST_ENTRY(pos, estats_connection_info, list);
	    Chk(estats_connection_tuple_as_strings(&tuple_ascii, &ct->tuple)); 

	    printf("%-8d %-12s %-8u %-8u %-8u %-20s %-8s %-20s %-8s\n", ct->cid, ct->cmdline, ct->pid, ct->uid, ct->ino, tuple_ascii.local_addr, tuple_ascii.local_port, tuple_ascii.rem_addr, tuple_ascii.rem_port);
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
