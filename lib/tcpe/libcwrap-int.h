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
#ifndef TCPE_LIBCWRAP_INT_H
#define TCPE_LIBCWRAP_INT_H

tcpe_error* Access(const char* _pathname, int _mode);
tcpe_error* Asprintf(int* _ret, char** _strp, const char* _fmt, ...);
tcpe_error* Calloc(void** _ptr, size_t nmemb, size_t size);
void          Closedir(DIR** _dir);
void          Fclose(FILE** _fp);
tcpe_error* Fgets(char* _s, int _size, FILE* _fp);
tcpe_error* Fopen(FILE** _fp, const char* _path, const char* _mode);
tcpe_error* Fprintf(int* _ret, FILE* _fp, const char* _fmt, ...);
tcpe_error* Fputc(int _c, FILE* _fp);
tcpe_error* Fread(size_t* _ret, void* _ptr, size_t _size, size_t _nmemb, FILE* _fp);
void          Free(void** _ptr);
tcpe_error* Fscanf(int* _ret, FILE* _stream, const char* _fmt, ...);
tcpe_error* Fseek(FILE* _fp, long _offset, int _whence);
tcpe_error* Fwrite(size_t* _ret, const void* _ptr, size_t _size, size_t _nmemb, FILE* _fp);
tcpe_error* Getpeername(int _s, struct sockaddr* _name, socklen_t* _namelen);
tcpe_error* Getsockname(int _s, struct sockaddr* _name, socklen_t* _namelen);
tcpe_error* Inet_ntop(int _af, const void* _src, char* _dst, size_t _cnt);
tcpe_error* Inet_pton(int _af, const char* _str, void* _dst);
tcpe_error* Malloc(void** _ptr, size_t _size);
tcpe_error* Opendir(DIR** _dir, const char* _name);
tcpe_error* Remove(const char* _pathname);
tcpe_error* Snprintf(int* _ret, char* _str, size_t _siz, const char* _fmt, ...);
tcpe_error* Sprintf(int* _ret, char* _str, const char* _fmt, ...);
tcpe_error* Sscanf(int* _ret, const char* _str, const char* _fmt, ...);
tcpe_error* Strdup(char** _ret, const char* _s);
tcpe_error* Strndup(char** _ret, const char* _s, size_t _n);
tcpe_error* Strtol(long int* _ret, const char* _nptr, char** _endptr, int _base);
tcpe_error* Strtoul(unsigned long int* _ret, const char* _nptr, char** _endptr, int _base);
tcpe_error* Strtoull(unsigned long long int* _ret, const char* _nptr, char** _endptr, int _base);
tcpe_error* Vasprintf(int* _ret, char** _strp, const char* _fmt, va_list _ap);
tcpe_error* Vfprintf(int* _ret, FILE* _fp, const char* _fmt, va_list _ap);
tcpe_error* Vfscanf(int* _ret, FILE* _stream, const char* _fmt, va_list _ap);
tcpe_error* Vsnprintf(int* _ret, char* _str, size_t _siz, const char* _fmt, va_list _ap);
tcpe_error* Vsprintf(int* _ret, char* _str, const char* _fmt, va_list _ap);
tcpe_error* Vsscanf(int* _ret, const char* _str, const char* _fmt, va_list _ap);

#endif /* TCPE_LIBCWRAP_INT_H */
