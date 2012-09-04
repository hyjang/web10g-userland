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

/*
 * Array of error code -> string mappings, in the style of sys_errlist.
 * Must be kept in sync with the defined errors in tcpe.h.
 */

static const char* const _tcpe_sys_errlist[] = {
        "Success",                      /* TCPE_ERR_SUCCESS */
        "Message un-acked",             /* TCPE_ERR_ACK */
        "No returned data",             /* TCPE_ERR_RET_DATA */
        "Invalid argument",             /* TCPE_ERR_INVAL */
        "Out of memory",                /* TCPE_ERR_NOMEM */
        "Entry not found",              /* TCPE_ERR_NOENT */
        "Socket operation failed",      /* TCPE_ERR_NOLINK */
        NULL, /* from strerror */       /* TCPE_ERR_LIBC */
	"End of file",                  /* ESTATS_ERR_EOF */
        "Checksum error",               /* TCPE_ERR_CHKSUM */
	"Error while converting value from string", /* ESTATS_ERR_STRING_CONVERSION */
	"Error thrown from genetlink library", /* TCPE_ERR_GENL */
        "Error not in error table",     /* TCPE_ERR_UNKNOWN */
};

/*
 * Number of tcpe errors, in the style of sys_nerr.
 */
static int _tcpe_sys_nerr = ARRAYSIZE(_tcpe_sys_errlist);

static struct tcpe_error _UnknownError = {
    TCPE_ERR_UNKNOWN, /* num */
    "Error not found in error table", /* msg */
    NULL,               /* xtra */
    __FILE__,           /* file */
    __LINE__,           /* line */
    NULL,               /* function */
};

static struct tcpe_error _OOMError = {
    TCPE_ERR_NOMEM,   /* num */
    "Out of memory",    /* msg */
    NULL,               /* xtra */
    __FILE__,           /* file */
    __LINE__,           /* line */
    NULL,               /* function */
};


tcpe_error*
tcpe_error_new(const TCPE_ERROR errnum,
                 const char* xtra,
                 const char* file,
                 const int line,
                 const char* function)
{
    tcpe_error* err;

    if (errnum < 0 || errnum >= _tcpe_sys_nerr)
        return &_UnknownError;

    if ((err = malloc(sizeof(tcpe_error))) == NULL)
        return &_OOMError;

    if (xtra != NULL) {
        if ((err->xtra = strdup(xtra)) == NULL) {
            free(err);
            return &_OOMError;
        }
    } else {
        err->xtra = NULL;
    }
    
    err->num = errnum;
    if (errnum == TCPE_ERR_LIBC)
        err->msg = strerror(errno);
    else
        err->msg = _tcpe_sys_errlist[errnum];
    err->file = file;
    err->line = line;
    err->function = function;
 
    return err;
}


void
tcpe_error_free(tcpe_error** err)
{
    if (err == NULL || *err == NULL)
        return;
    if (*err == &_UnknownError || *err == &_OOMError)
        return;
    
    free((*err)->xtra);
    free(*err);
    *err = NULL;
}


void
tcpe_error_print(FILE* fp,
                   const tcpe_error* err)
{
    if (err == NULL)
	return;

    if (err->xtra != NULL)
        fprintf(fp, "%s: ", err->xtra);
    if (err->msg != NULL)
        fprintf(fp, "%s", err->msg);
    if (err->file != NULL)
        fprintf(fp, " at %s", err->file);
    if (err->line != -1)
        fprintf(fp, ":%d", err->line);
    if (err->function != NULL)
        fprintf(fp, " in function %s", err->function);
    fprintf(fp, "\n");
}


TCPE_ERROR
tcpe_error_get_number(const tcpe_error* err)
{
    return err->num;
}


const char*
tcpe_error_get_message(const tcpe_error* err)
{
    return err->msg;
}


const char*
tcpe_error_get_extra(const tcpe_error* err)
{
    return err->xtra;
}


const char*
tcpe_error_get_file(const tcpe_error* err)
{
    return err->file;
}


int
tcpe_error_get_line(const tcpe_error* err)
{
    return err->line;
}


const char*
tcpe_error_get_function(const tcpe_error* err)
{
    return err->function;
}
