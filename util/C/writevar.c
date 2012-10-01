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

void usage(void)
{
        printf("\n\n");
        printf("writevar cid var-name value\n");
	printf("\n Write a value to one of the four writable MIB vars\n");
	printf(" Currently supported: LimRwin, LimCwnd\n");
}

int main(int argc, char **argv)
{

	tcpe_error* err = NULL;
	struct tcpe_client* cl = NULL;
	tcpe_data* data = NULL;
	int cid, i, j; 
	int opt, option;
	char varname[24];
	char *endptr, *str;
	uintmax_t val;

	if (argc < 4) {
                usage();
                exit(EXIT_FAILURE);
        }	

        while ((opt = getopt(argc, argv, "h")) != -1) {
                switch (opt) {
		case 'h':
                        usage();
                        exit(EXIT_SUCCESS);
                        break;
                default:
                        exit(EXIT_FAILURE);
                        break;
                }
        }

	cid = atoi(argv[1]);
	strncpy(varname, argv[2], 24);

	str = argv[3];
	val = strtoumax(str, &endptr, 10);

	Chk(tcpe_client_init(&cl));

	Chk(tcpe_write_var(varname, (uint32_t)val, cid, cl));

 Cleanup:
	tcpe_client_destroy(&cl);

	if (err != NULL) {
		PRINT_AND_FREE(err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
