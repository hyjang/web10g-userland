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
#ifndef TCPE_ERROR_H
#define TCPE_ERROR_H

tcpe_error*   tcpe_error_new(const TCPE_ERROR _errnum,
                             const char* _extra,
                             const char* _file,
                             const int _line,
                             const char* _function);
void          tcpe_error_free(tcpe_error** _err);
void          tcpe_error_print(FILE* _fp,
                                 const tcpe_error* _err);
TCPE_ERROR    tcpe_error_get_number(const tcpe_error* _err);
const char*   tcpe_error_get_message(const tcpe_error* _err);
const char*   tcpe_error_get_extra(const tcpe_error* _err);
const char*   tcpe_error_get_file(const tcpe_error* _err);
int           tcpe_error_get_line(const tcpe_error* _err);
const char*   tcpe_error_get_function(const tcpe_error* _err);

#endif /* TCPE_ERROR_H */
