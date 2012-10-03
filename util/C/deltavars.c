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
        printf("deltavars cid [-m mask]\n");
        printf("\n  Repeatedly list deltas of values for connection specified\n");
        printf("  by cid (which can be obtained with \"listconns\"),\n");
	printf("  with optional mask given as a 5-tuple of hex\n");
        printf("  values, e.g.\n");
        printf("\n");
        printf("  deltavars cid -m f,f,f,f,f\n");
        printf("\n");
        printf("  returns the first 4 entries of each of the MIB tables.\n");
	printf("  (Perf, Path, Stack, App, Tune; cf. RFC 4898)\n");
        printf("\n");
        printf("  deltavars cid -m 0,0,0,,0\n");
        printf("\n");
        printf("  returns only the MIB App table, etc.\n");
        printf("\n  The mask limits the time the kernel holds a lock on\n");
	printf("  the socket of interest.\n");
	printf("\n");
}

int main(int argc, char **argv)
{

	tcpe_error* err = NULL;
	tcpe_client* cl = NULL;
	tcpe_data* data = NULL;
	tcpe_data* data_new = NULL;
	tcpe_data* data_prev = NULL;
	int cid, i, j; 
	int opt, option;

	char *strmask = NULL;
        const char delim = ',';
	uint64_t tmpmask;

	struct tcpe_mask mask;

	mask.masks[0] = DEFAULT_PERF_MASK;
        mask.masks[1] = DEFAULT_PATH_MASK;
        mask.masks[2] = DEFAULT_STACK_MASK;
        mask.masks[3] = DEFAULT_APP_MASK;
        mask.masks[4] = DEFAULT_TUNE_MASK;

        for (i = 0; i < MAX_TABLE; i++) {
                mask.if_mask[i] = 0;
        }

	if (argc < 2) {
                usage();
                exit(EXIT_FAILURE);
        }	

        while ((opt = getopt(argc, argv, "hm:")) != -1) {
                switch (opt) {
		case 'h':
			usage();
			exit(EXIT_SUCCESS);
			break;
                case 'm':
                        strmask = strdup(optarg);

                        for (j = 0; j < 5; j++) {
                                char *strtmp;
                                strtmp = strsep(&strmask, &delim);
                                if (strtmp && strlen(strtmp)) {
                                char *str;
                                str = (str = strchr(strtmp, 'x')) ? str+1 : strtmp;
                                if (sscanf(str, "%"PRIx64, &tmpmask) == 1) {
                                        mask.masks[j] = tmpmask & mask.masks[j];
                                        mask.if_mask[j] = 1;
                                }
                                }
                        }
                        option = opt;

                        break;
                default:
                        exit(EXIT_FAILURE);
                        break;
                }
        }
        if ((option == 'm') && (optind+1 > argc)) {
                printf("Too few non-option args\n");
                exit(EXIT_FAILURE);
        }

	cid = atoi(argv[optind]);


	Chk(tcpe_client_init(&cl));
	Chk(tcpe_client_set_mask(cl, &mask));
	Chk(tcpe_data_new(&data));
	Chk(tcpe_data_new(&data_new));
	Chk(tcpe_data_new(&data_prev));


	while (1) {
	
	SWAP(data_new, data_prev);

	Chk(tcpe_read_vars(data_new, cid, cl));

	Chk(tcpe_data_delta(data, data_new, data_prev));

	for (j = 0; j < ARRAYSIZE(data->val); j++) {

		if (j == 0)
			printf("\n\n Perf Table\n\n");
		if (j == PERF_INDEX_MAX)
			printf("\n\n Path Table\n\n");
		if (j == PERF_INDEX_MAX+PATH_INDEX_MAX)
			printf("\n\n Stack Table\n\n");
		if (j == PERF_INDEX_MAX+PATH_INDEX_MAX+STACK_INDEX_MAX)
			printf("\n\n App Table\n\n");
		if (j == PERF_INDEX_MAX+PATH_INDEX_MAX+STACK_INDEX_MAX+APP_INDEX_MAX)
			printf("\n\n Tune Table\n\n");


		if (data->val[j].mask) continue;

		switch(tcpe_var_array[j].type) {
			case TCPE_UNSIGNED64:
				printf("%s=%"PRIu64"\n", tcpe_var_array[j].name, data->val[j].uv64);
                		break;
                        case TCPE_UNSIGNED32:
				printf("%s=%"PRIu32"\n", tcpe_var_array[j].name, data->val[j].uv32);
				break;
                        case TCPE_SIGNED32:
				printf("%s=%"PRId32"\n", tcpe_var_array[j].name, data->val[j].sv32);
                        	break;
                        case TCPE_UNSIGNED16:
				printf("%s=%"PRIu16"\n", tcpe_var_array[j].name, data->val[j].uv16);
                        	break;
                        case TCPE_UNSIGNED8:
				printf("%s=%"PRIu8"\n", tcpe_var_array[j].name, data->val[j].uv8);
                        	break;
                        default:
                                break;
                }
	}

	sleep(1);
	printf("\n\n");
	}

 Cleanup:

	tcpe_data_free(&data);
	tcpe_data_free(&data_new);
	tcpe_data_free(&data_prev);
	tcpe_client_destroy(&cl);


	if (err != NULL) {
		PRINT_AND_FREE(err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
