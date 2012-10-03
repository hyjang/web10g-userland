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
tcpe_data_new(struct tcpe_data** data)
{
	tcpe_error* err = NULL;

	ErrIf(data == NULL, TCPE_ERR_INVAL);
	*data = NULL;

	Chk(Malloc((void**) data, sizeof(tcpe_data)));
	memset((void*) *data, 0, sizeof(tcpe_data));

 Cleanup:
 	return err;
}

struct tcpe_error*
tcpe_data_free(struct tcpe_data** data)
{
	if (data == NULL || *data == NULL)
		return;

	free(*data);
	*data = NULL;
}

struct tcpe_error* tcpe_data_delta(struct tcpe_data* data, const struct tcpe_data* data2, const struct tcpe_data* data1)
{
	tcpe_error* err = NULL;
	int i;

	ErrIf(data == NULL || data2 == NULL || data1 == NULL, TCPE_ERR_INVAL);

	for (i = 0; i < ARRAYSIZE(data->val); i++) {

		if (data2->val[i].mask || data1->val[i].mask) {
			data->val[i].mask = 1;
			continue;
		}
		switch(tcpe_var_array[i].type) {
		case TCPE_UNSIGNED64:
			data->val[i].uv64 =
				data2->val[i].uv64 - data1->val[i].uv64;
			break;
		case TCPE_UNSIGNED32:
			data->val[i].uv32 =
				data2->val[i].uv32 - data1->val[i].uv32;
			break;
		case TCPE_SIGNED32:
			data->val[i].sv32 =
				data2->val[i].sv32 - data1->val[i].sv32;
			break;
		case TCPE_UNSIGNED16:
			data->val[i].uv16 =
				data2->val[i].uv16 - data1->val[i].uv16;
			break;
		case TCPE_UNSIGNED8:
			data->val[i].uv8 =
				data2->val[i].uv8 - data1->val[i].uv8;
			break;
		default:
			break;
		}
	}

 Cleanup:
 	return err;
}
