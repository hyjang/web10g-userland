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

void usage(void)
{
	;
}

int main(int argc, char **argv)
{

	estats_error* err = NULL;
	struct estats_nl_client* cl = NULL;
	estats_data* data = NULL;
	estats_record* record = NULL;
	estats_val val;
	char* str;
	int cid, i, j; 
	int opt, option;

	if (argc < 2) {
                usage();
                exit(EXIT_FAILURE);
        }	

	cid = atoi(argv[1]);
	
	Chk(estats_nl_client_init(&cl));
	Chk(estats_data_new(&data));
	Chk(estats_record_open(&record, "./test-record", "w"));

	Chk(estats_read_vars(data, cid, cl));

	for (i = 0; i < data->length; i++) {
            Chk(estats_val_as_string(&str, &data->val[i], estats_var_array[i].valtype));

            printf("%s:  %s\n", estats_var_array[i].name, str);
        }
	Chk(estats_record_write_data(record, data));

	printf("length: %lu\n", data->length);

 Cleanup:
	estats_data_free(&data);
	estats_nl_client_destroy(&cl);
	Chk(estats_record_close(&record));

	if (err != NULL) {
		PRINT_AND_FREE(err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
