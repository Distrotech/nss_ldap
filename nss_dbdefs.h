/*
   Donated by HP to enable Winbindd to build on HPUX 11.x.
   Copyright (C) Jeremy Allison 2002.
 
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
 
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
 
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA  02111-1307, USA.
*/

#ifndef _NSS_DBDEFS_H
#define _NSS_DBDEFS_H

#include <errno.h>
#include <netdb.h>
#include <limits.h>
 
#ifndef NSS_INCLUDE_UNSAFE
#define NSS_INCLUDE_UNSAFE      1       /* Build old, MT-unsafe interfaces, */
#endif  /* NSS_INCLUDE_UNSAFE */
 
enum nss_netgr_argn {
	NSS_NETGR_MACHINE,
	NSS_NETGR_USER,
	NSS_NETGR_DOMAIN,
	NSS_NETGR_N
};
 
enum nss_netgr_status {
	NSS_NETGR_FOUND,
	NSS_NETGR_NO,
	NSS_NETGR_NOMEM
};

struct nss_setnetgrent_args {
	const char *netgroup;
	nss_backend_t *iterator;
};

struct nss_getnetgrent_args {
	char *buffer;
	int buflen;
	enum nss_netgr_status status;
	char *retp[NSS_NETGR_N];
};
 
typedef unsigned nss_innetgr_argc;
typedef char **nss_innetgr_argv;
 
struct nss_innetgr_1arg {
	nss_innetgr_argc argc;
	nss_innetgr_argv argv;
};

struct nss_innetgr_args {
	struct nss_innetgr_1arg arg[NSS_NETGR_N];
	struct nss_innetgr_1arg groups;
	enum nss_netgr_status status;
};
 
typedef struct {
	void *result;	/* "result" parameter to getXbyY_r() */
	char *buffer;	/* "buffer"     "	     "      */
	int buflen;	/* "buflen"     "	     "      */
} nss_XbyY_buf_t;
 
extern nss_XbyY_buf_t *_nss_XbyY_buf_alloc(int struct_size, int buffer_size);
extern void _nss_XbyY_buf_free(nss_XbyY_buf_t *);
 
union nss_XbyY_key {
	uid_t uid;
	gid_t gid;
	const char *name;
	int number;
	struct {
		long net; /* int on Solaris */
		int type;
	} netaddr;
	struct {
		const char *addr;
		int len;
		int type;
	} hostaddr;
	struct {
		union {
			const char *name;
			int port;
		} serv;
		const char *proto;
	} serv;
	void *ether;
	/* Solaris has private key args here */
};
 
typedef struct nss_XbyY_args {
	nss_XbyY_buf_t buf;
	int stayopen;
	/*
	 * Support for setXXXent(stayopen)
	 * Used only in hosts, protocols,
	 * networks, rpc, and services.
	 */
	int (*str2ent)(const char *instr, int instr_len, void *ent, char *buffer, int buflen);
	union nss_XbyY_key key;
 
	void *returnval;
	int erange;
#undef h_errno
	int h_errno;
	nss_status_t status;
} nss_XbyY_args_t;

struct nss_groupsbymem {
	const char *username;
	gid_t *gid_array;
	int maxgids;
	int force_slow_way;
	int (*str2ent)(const char *instr, int instr_len, void *ent, char *buffer, int buflen);
	nss_status_t (*process_cstr)(const char *instr, int instr_len, struct nss_groupsbymem *);
	int numgids;
};
 
#endif /* _NSS_DBDEFS_H */

