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

	estats_error* err = NULL; 
	estats_data* data = NULL;
	estats_record* record = NULL;
	estats_val val;
	char* str;
	int i, j; 
	int opt, option;

	
	Chk(estats_record_open(&record, "./test-record", "r"));

	Chk(estats_record_read_data(&data, record));

	printf("Timestamp sec: %u, usec: %u\n", data->tv.sec, data->tv.usec);

	for (i = 0; i < data->length; i++) {
	    Chk(estats_val_as_string(&str, &data->val[i], estats_var_array[i].valtype));

	    printf("%s:  %s\n", estats_var_array[i].name, str);
	}

 Cleanup:
	estats_data_free(&data);
	Chk(estats_record_close(&record));

	if (err != NULL) {
		PRINT_AND_FREE(err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
