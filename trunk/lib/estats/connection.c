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
#include <estats/estats-int.h>

struct estats_error*
estats_connection_list_new(struct estats_connection_list** connection_list)
{
	estats_error* err = NULL;

	ErrIf(connection_list == NULL, ESTATS_ERR_INVAL);
	*connection_list = NULL;

	Chk(Malloc((void**) connection_list, sizeof(estats_connection_list)));
	memset((void*) *connection_list, 0, sizeof(estats_connection_list));
	_estats_list_init(&((*connection_list)->connection_head));
	_estats_list_init(&((*connection_list)->connection_info_head));

 Cleanup:
 	return err;
}

void
estats_connection_list_free(struct estats_connection_list** connection_list)
{
	struct estats_list* conn_pos;
	struct estats_list* tmp;

	if (connection_list == NULL || *connection_list == NULL)
		return;

	ESTATS_LIST_FOREACH_SAFE(conn_pos, tmp, &((*connection_list)->connection_head)) {
        	estats_connection* curr_conn = ESTATS_LIST_ENTRY(conn_pos, estats_connection, list);
        	_estats_list_del(conn_pos);
        	free(curr_conn);
	}

	ESTATS_LIST_FOREACH_SAFE(conn_pos, tmp, &((*connection_list)->connection_info_head)) {
        	estats_connection_info* curr_conn = ESTATS_LIST_ENTRY(conn_pos, estats_connection_info, list);
        	_estats_list_del(conn_pos);
        	free(curr_conn);
	}

	free(*connection_list);
	*connection_list = NULL;
}

struct estats_error*
estats_connection_info_new(struct estats_connection_info** connection_info)
{
	estats_error* err = NULL;

	ErrIf(connection_info == NULL, ESTATS_ERR_INVAL);

	*connection_info = NULL;
	
	Chk(Malloc((void**) connection_info, sizeof(estats_connection_info)));
	memset((void*) *connection_info, 0, sizeof(estats_connection_info));

 Cleanup:
 	return err;
}

void
estats_connection_info_free(struct estats_connection_info** connection_info)
{
	if (connection_info == NULL || *connection_info == NULL)
		return;

	free(*connection_info);
	*connection_info = NULL;
}

struct estats_error*
estats_connection_tuple_compare(int* res,
                               const struct estats_connection_tuple *s1,
                               const struct estats_connection_tuple *s2)
{
    estats_error* err = NULL;

    ErrIf(s1 == NULL || s2 == NULL, ESTATS_ERR_INVAL);

    *res = 1;

    if ( (s1->rem_port == s2->rem_port) &&
         strcmp((char *)(s1->rem_addr), (char *)(s2->rem_addr)) == 0 &&
         (s1->local_port == s2->local_port) &&
         strcmp((char *)(s1->local_addr), (char *)(s2->local_addr)) == 0 ) {

        *res = 0;
    }

Cleanup:
    return err;
}

struct estats_error*
estats_connection_tuple_copy(struct estats_connection_tuple *s1,
			const struct estats_connection_tuple *s2)
{
	estats_error* err = NULL;
	int i;

	ErrIf(s1 == NULL || s2 == NULL, ESTATS_ERR_INVAL);

	for (i = 0; i < 17; i++) {
		s1->rem_addr[i] = s2->rem_addr[i];
		s1->local_addr[i] = s2->local_addr[i];
	}
	s1->rem_port = s2->rem_port;
	s1->local_port = s2->local_port;
	s1->cid = s2->cid;

Cleanup:
    return err;
}

struct estats_error*
estats_connection_tuple_as_strings(struct estats_connection_tuple_ascii* tuple_ascii, struct estats_connection_tuple* tuple)
{
	estats_error* err = NULL;

	Chk(Sprintf(NULL, tuple_ascii->rem_port, "%u", tuple->rem_port));
	Chk(Sprintf(NULL, tuple_ascii->local_port, "%u", tuple->local_port));
	Chk(Sprintf(NULL, tuple_ascii->cid, "%d", tuple->cid));

	if (tuple->rem_addr[16] == ESTATS_ADDRTYPE_IPV4)
        	Chk(Inet_ntop(AF_INET, (void*) (tuple->rem_addr), tuple_ascii->rem_addr, INET_ADDRSTRLEN));
	else if (tuple->rem_addr[16] == ESTATS_ADDRTYPE_IPV6)
        	Chk(Inet_ntop(AF_INET6, (void*) (tuple->rem_addr), tuple_ascii->rem_addr, INET6_ADDRSTRLEN));
	else Err(ESTATS_ERR_UNKNOWN);

	if (tuple->local_addr[16] == ESTATS_ADDRTYPE_IPV4)
        	Chk(Inet_ntop(AF_INET, (void*) (tuple->local_addr), tuple_ascii->local_addr, INET_ADDRSTRLEN));
	else if (tuple->rem_addr[16] == ESTATS_ADDRTYPE_IPV6)
        	Chk(Inet_ntop(AF_INET6, (void*) (tuple->local_addr), tuple_ascii->local_addr, INET6_ADDRSTRLEN));
	else Err(ESTATS_ERR_UNKNOWN);

 Cleanup:
    return err;
}

estats_error*
estats_connection_info_get_cid(int* cid, const estats_connection_info* connection_info)
{
    estats_error* err = NULL;

    ErrIf(cid == NULL || connection_info == NULL, ESTATS_ERR_INVAL);
    *cid = connection_info->cid;

Cleanup:
    return err;
}
	
estats_error*
estats_connection_info_get_pid(int* pid, const estats_connection_info* connection_info)
{
    estats_error* err = NULL;

    ErrIf(pid == NULL || connection_info == NULL, ESTATS_ERR_INVAL);
    *pid = connection_info->pid;

Cleanup:
    return err;
}
	
estats_error*
estats_connection_info_get_uid(int* uid, const estats_connection_info* connection_info)
{
    estats_error* err = NULL;

    ErrIf(uid == NULL || connection_info == NULL, ESTATS_ERR_INVAL);
    *uid = connection_info->uid;

Cleanup:
    return err;
}

estats_error*
estats_connection_info_get_cmdline(char** str, const estats_connection_info* connection_info)
{
    estats_error* err = NULL;

    ErrIf(connection_info == NULL, ESTATS_ERR_INVAL);
    Chk(Strdup(str, connection_info->cmdline));

Cleanup:
    return err;
}

estats_error*
estats_connection_info_get_tuple(struct estats_connection_tuple* tuple, const estats_connection_info* connection_info)
{
    estats_error* err = NULL;

    ErrIf(tuple == NULL || connection_info == NULL, ESTATS_ERR_INVAL);

    *tuple = connection_info->tuple;

Cleanup:
    return err;
}

static struct estats_error* _estats_get_tcp_list(struct estats_list*, const struct estats_connection_list*);
static struct estats_error* _estats_get_ino_list(struct estats_list*);
static struct estats_error* _estats_get_pid_list(struct estats_list*);

struct estats_error*
estats_connection_list_add_info(struct estats_connection_list* connection_list)
{
	estats_error* err = NULL;
	struct estats_list* head;
	struct estats_list tcp_head;
	struct estats_list ino_head;
	struct estats_list pid_head;
	struct estats_list* tcp_pos;
	struct estats_list* ino_pos;
	struct estats_list* pid_pos;
	struct estats_list* tmp;
	estats_connection_info* conninfo;
	int dif;
	int tcp_entry, fd_entry;

	ErrIf(connection_list == NULL, ESTATS_ERR_INVAL);

	head = &connection_list->connection_info_head;

	Chk(_estats_get_tcp_list(&tcp_head, connection_list));
	Chk(_estats_get_ino_list(&ino_head));
	Chk(_estats_get_pid_list(&pid_head));

    ESTATS_LIST_FOREACH(tcp_pos, &tcp_head) {

	estats_connection_info* tcp_ent = ESTATS_LIST_ENTRY(tcp_pos, estats_connection_info, list);
	tcp_entry = 0;
 
        ESTATS_LIST_FOREACH(ino_pos, &ino_head) {

            estats_connection_info* ino_ent = ESTATS_LIST_ENTRY(ino_pos, estats_connection_info, list);
	    
	    Chk(estats_connection_tuple_compare(&dif, &ino_ent->tuple, &tcp_ent->tuple));

	    if (!dif) {
	       	tcp_entry = 1;
	       	fd_entry = 0;

		ESTATS_LIST_FOREACH(pid_pos, &pid_head) {

                    estats_connection_info* pid_ent = ESTATS_LIST_ENTRY(pid_pos, estats_connection_info, list);

		    if(pid_ent->ino == ino_ent->ino) { //then create entry 
			fd_entry = 1;

                        Chk(estats_connection_info_new(&conninfo));

			conninfo->pid = pid_ent->pid; 

                        strncpy(conninfo->cmdline, pid_ent->cmdline, sizeof(pid_ent->cmdline));
                        conninfo->uid = ino_ent->uid;
		       	conninfo->state = ino_ent->state;

			conninfo->cid = tcp_ent->cid;

			conninfo->addrtype = tcp_ent->addrtype; 

                        conninfo->tuple = tcp_ent->tuple;
			
			conninfo->ino = ino_ent->ino;

                        _estats_list_add_tail(&(conninfo->list), head);
		    }
	       	}
	       	if(!fd_entry) { // add entry w/out cmdline 

                        Chk(estats_connection_info_new(&conninfo));

			conninfo->pid = 0;
			conninfo->uid = ino_ent->uid;
		       	conninfo->state = ino_ent->state;

			conninfo->cid = tcp_ent->cid;
			conninfo->addrtype = tcp_ent->addrtype; 

                        conninfo->tuple = tcp_ent->tuple;
                        
                        strncpy(conninfo->cmdline, "\0", 1);
                        
                        _estats_list_add_tail(&(conninfo->list), head);
	       	}
	    }
	}
	if(!tcp_entry) { // then connection has vanished; add residual cid info

            Chk(estats_connection_info_new(&conninfo));

	    conninfo->cid = tcp_ent->cid; 
	    conninfo->addrtype = tcp_ent->addrtype; 

            conninfo->tuple = tcp_ent->tuple;

            strncpy(conninfo->cmdline, "\0", 1);

            _estats_list_add_tail(&(conninfo->list), head);
       	}
    }

Cleanup:
    
    ESTATS_LIST_FOREACH_SAFE(tcp_pos, tmp, &tcp_head) {
        estats_connection_info* tcp_ent = ESTATS_LIST_ENTRY(tcp_pos, estats_connection_info, list);
        _estats_list_del(tcp_pos);
        free(tcp_ent);
    }
    ESTATS_LIST_FOREACH_SAFE(ino_pos, tmp, &ino_head) {
        estats_connection_info* ino_ent = ESTATS_LIST_ENTRY(ino_pos, estats_connection_info, list);
        _estats_list_del(ino_pos);
        free(ino_ent);
    }
    ESTATS_LIST_FOREACH_SAFE(pid_pos, tmp, &pid_head) {
        estats_connection_info* pid_ent = ESTATS_LIST_ENTRY(pid_pos, estats_connection_info, list);
        _estats_list_del(pid_pos);
        free(pid_ent);
    }

    return err;
}

static struct estats_error*
_estats_get_tcp_list(struct estats_list* head, const estats_connection_list* connection_list)
{
	estats_error* err = NULL;
	const struct estats_list* connection_head;
	struct estats_list* pos;
	int i;

	ErrIf(head == NULL || connection_list == NULL, ESTATS_ERR_INVAL);
	_estats_list_init(head);
	
	connection_head = &connection_list->connection_head;

	ESTATS_LIST_FOREACH(pos, connection_head) {
		estats_connection* ent = ESTATS_LIST_ENTRY(pos, estats_connection, list);
		estats_connection_info* conninfo;
		Chk(estats_connection_info_new(&conninfo));

		conninfo->cid = ent->cid;
		for (i = 0; i < 17; i++)
			conninfo->tuple.rem_addr[i] = ent->rem_addr[i];
		for (i = 0; i < 17; i++)
			conninfo->tuple.local_addr[i] = ent->local_addr[i];
		conninfo->tuple.rem_port = ent->rem_port;
		conninfo->tuple.local_port = ent->local_port;
		conninfo->addrtype = ent->local_addr[16];

		_estats_list_add_tail(&conninfo->list, head);
	}

 Cleanup:
 	return err;
}

static struct estats_error*
_estats_get_ino_list(struct estats_list* head)
{
	estats_error* err = NULL;
	FILE* file = NULL;
	FILE* file6 = NULL;
	char buf[256];
	int scan;
	struct in6_addr in6;

	ErrIf(head == NULL, ESTATS_ERR_INVAL);
	_estats_list_init(head);

	file = fopen("/proc/net/tcp", "r");
	file6 = fopen("/proc/net/tcp6", "r");

	if (file) {
		estats_connection_info* conninfo;

		while (fgets(buf, sizeof(buf), file) != NULL) {

			Chk(estats_connection_info_new(&conninfo));

			if ((scan = sscanf(buf,
				"%*u: %x:%hx %x:%hx %x %*x:%*x %*x:%*x %*x %u %*u %lu",
				(uint32_t *) &(conninfo->tuple.local_addr),
				(uint16_t *) &(conninfo->tuple.local_port),
				(uint32_t *) &(conninfo->tuple.rem_addr),
				(uint16_t *) &(conninfo->tuple.rem_port),
				(int *) &(conninfo->state),
				(uid_t *) &(conninfo->uid),
				(ino_t *) &(conninfo->ino)
				)) == 7) {

				conninfo->addrtype = ESTATS_ADDRTYPE_IPV4;
				_estats_list_add_tail(&conninfo->list, head);
			} else {
				estats_connection_info_free(&conninfo);
			}
		}
		fclose(file);
	}
	
    	if (file6) { 
		estats_connection_info* conninfo;
		char local_addr[INET6_ADDRSTRLEN];
		char rem_addr[INET6_ADDRSTRLEN];

		while (fgets(buf, sizeof(buf), file6) != NULL) {

			Chk(estats_connection_info_new(&conninfo));

			if ((scan = sscanf(buf,
				"%*u: %64[0-9A-Fa-f]:%hx %64[0-9A-Fa-f]:%hx %x %*x:%*x %*x:%*x %*x %u %*u %u", 
				(char *) &local_addr,
				(uint16_t *) &(conninfo->tuple.local_port),
				(char *) &rem_addr,
				(uint16_t *) &(conninfo->tuple.rem_port),
				(int *) &(conninfo->state),
				(uid_t *) &(conninfo->uid),
				(pid_t *) &(conninfo->ino)
				)) == 7) {
				
				sscanf(local_addr, "%8x%8x%8x%8x", &in6.s6_addr32[0], &in6.s6_addr32[1], &in6.s6_addr32[2], &in6.s6_addr32[3]); 

                		memcpy(&(conninfo->tuple.local_addr), &in6.s6_addr, 16);

				sscanf(rem_addr, "%8x%8x%8x%8x", &in6.s6_addr32[0], &in6.s6_addr32[1], &in6.s6_addr32[2], &in6.s6_addr32[3]);

                		memcpy(&(conninfo->tuple.rem_addr), &in6.s6_addr, 16);

				conninfo->addrtype = ESTATS_ADDRTYPE_IPV6;
				_estats_list_add_tail(&conninfo->list, head);
			} else {
				estats_connection_info_free(&conninfo);
	    		}
       		}
		fclose(file6);
	} 

 Cleanup:
 	return err;
}

static struct estats_error*
_estats_get_pid_list(struct estats_list* head)
{
	estats_error* err = NULL;
	estats_connection_info* conninfo;
	DIR *dir, *fddir;
	struct dirent *direntp, *fddirentp;
	pid_t pid;
	char path[PATH_MAX];
	char buf[256];
	struct stat st;
	int stno;
	FILE* file;

	ErrIf(head == NULL, ESTATS_ERR_INVAL);
	_estats_list_init(head);

	Chk(Opendir(&dir, "/proc"));

	while ((direntp = readdir(dir)) != NULL) {
		if ((pid = atoi(direntp->d_name)) != 0) {

			sprintf(path, "%s/%d/%s/", "/proc", pid, "fd"); 

			if ((fddir = opendir(path)) != NULL) { //else lacks permissions 
	     
			while ((fddirentp = readdir(fddir)) != NULL) { 

		    	strcpy(buf, path);
		    	strcat(buf, fddirentp->d_name); 
		    	stno = stat(buf, &st); 

		    	if (S_ISSOCK(st.st_mode)) { // add new list entry

			sprintf(buf, "/proc/%d/status", pid);

			if ((file = fopen(buf, "r")) == NULL)
				continue;

			if (fgets(buf, sizeof(buf), file) == NULL)
			    	goto FileCleanup; 
       	
	                Chk(estats_connection_info_new(&conninfo));

			if (sscanf(buf, "Name: %16s\n", conninfo->cmdline) != 1) {
			    estats_connection_info_free(&conninfo);
			    goto FileCleanup;
		       	}

			conninfo->ino = st.st_ino;
		       	conninfo->pid = pid;
                        _estats_list_add_tail(&conninfo->list, head);

 FileCleanup:
			fclose(file); 
		    	}
	       		}
	       		closedir(fddir);
	    		}
       		}
    	}
    	closedir(dir);

 Cleanup:
    return err;
}



