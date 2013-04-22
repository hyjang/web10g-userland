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

static const char* argv0 = NULL;

void usage(void)
{
	printf("Usage: record_write cid\n");
}

int main(int argc, char **argv)
{

	estats_error* err = NULL;
	struct estats_nl_client* cl = NULL;
	estats_val_data* data = NULL;
	estats_record* record = NULL;
	estats_val val;
	char* str;
	int cid, i, j; 
	int opt, option;

	argv0 = argv[0];

	if (argc < 2) {
                usage();
                exit(EXIT_FAILURE);
        }	

	cid = atoi(argv[1]);
	
	Chk(estats_nl_client_init(&cl));
	Chk(estats_val_data_new(&data));
	Chk(estats_record_open(&record, "./test-record", "w"));

	Chk(estats_read_vars(data, cid, cl));

	    printf("Timestamp sec: %u, usec: %u\n", data->tv.sec, data->tv.usec);

	for (i = 0; i < data->length; i++) {
            Chk(estats_val_as_string(&str, &data->val[i], estats_var_array[i].valtype));

            printf("%s:  %s\n", estats_var_array[i].name, str);
        }
	Chk(estats_record_write_data(record, data));

 Cleanup:
	estats_val_data_free(&data);
	estats_nl_client_destroy(&cl);
	Chk(estats_record_close(&record));

	if (err != NULL) {
		PRINT_AND_FREE(err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
