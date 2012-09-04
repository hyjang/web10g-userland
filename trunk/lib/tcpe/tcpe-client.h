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
#ifndef TCPE_CLIENT_H
#define TCPE_CLIENT_H

struct tcpe_error* tcpe_client_init(struct tcpe_client**);
void               tcpe_client_destroy(struct tcpe_client**);
struct tcpe_error* tcpe_client_get_sock(struct mnl_socket**, const tcpe_client*);
struct tcpe_error* tcpe_client_get_fam_id(int*, const tcpe_client*);
struct tcpe_error* tcpe_client_set_mask(struct tcpe_client*, struct tcpe_mask*);

#endif /* TCPE_CLIENT_H */
