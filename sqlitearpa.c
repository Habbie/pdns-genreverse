#include <sqlite3ext.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <strings.h>
SQLITE_EXTENSION_INIT1

static void arpaizev4Func(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const unsigned char *in = sqlite3_value_text(argv[0]);
  char *out;
  unsigned int x1,x2,x3,x4;
  
  sscanf(in, "%3u.%3u.%3u.%3u", &x1, &x2, &x3, &x4);
  
  asprintf(&out, "%d.%d.%d.%d.in-addr.arpa", x4,x3,x2,x1);
  
  sqlite3_result_text(context, out, -1, SQLITE_TRANSIENT);
  free(out);
}

static void arpaizev6Func(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const unsigned char *in = sqlite3_value_text(argv[0]);
  char out[32*2+8+1];
  char *hex="0123456789abcdef";
  struct in6_addr istruct;
  int i;

  bzero(&istruct, sizeof(istruct));

  inet_pton(AF_INET6, in, &istruct);

  for(i=0; i<16; i++)
  {
    out[4*i]=hex[istruct.s6_addr[15-i] & 15];
    out[4*i+1]='.';
    out[4*i+2]=hex[istruct.s6_addr[15-i] >> 4];
    out[4*i+3]='.';
  }
  strcpy(out+64, "ip6.arpa");

  sqlite3_result_text(context, out, -1, SQLITE_TRANSIENT);
}

/* SQLite invokes this routine once when it loads the extension.
** Create new functions, collating sequences, and virtual table
** modules here.  This is usually the only exported symbol in
** the shared library.
*/
int sqlite3_extension_init(
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pApi
){
  SQLITE_EXTENSION_INIT2(pApi)
  sqlite3_create_function(db, "arpaizev4", 1, SQLITE_ANY, 0, arpaizev4Func, 0, 0);
  sqlite3_create_function(db, "arpaizev6", 1, SQLITE_ANY, 0, arpaizev6Func, 0, 0);
  return 0;
}