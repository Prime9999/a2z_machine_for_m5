
/* $Id: getopt.c,v 1.1.1.1 2000/05/10 14:21:34 jholder Exp $   
 * --------------------------------------------------------------------
 * see doc/License.txt for License Information   
 * --------------------------------------------------------------------
 * 
 * File name: $Id: getopt.c,v 1.1.1.1 2000/05/10 14:21:34 jholder Exp $  
 *   
 * Description:    
 *    
 * Modification history:      
 * $Log: getopt.c,v $
 * Revision 1.1.1.1  2000/05/10 14:21:34  jholder
 *
 * imported
 *
 *
 * --------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>

#define ERR(s, c) \
    if (zd_opterr) {\
        char errbuf[2];\
        errbuf[0] = (char) c; errbuf[1] = '\n';\
        (void) fwrite (argv[0], strlen (argv[0]), 1, stderr);\
        (void) fwrite (s, strlen (s), 1, stderr);\
        (void) fwrite (errbuf, 2, 1, stderr);\
    }

int zd_opterr = 1;
int zd_optind = 1;
int zd_optopt;
const char *zd_optarg;

int getopt( int argc, char *argv[], const char *opts )
{
   static int sp = 1;
   int c;
   char *cp;

   if ( sp == 1 )
      if ( zd_optind >= argc || argv[zd_optind][0] != '-' || argv[zd_optind][1] == '\0' )
         return ( EOF );
      else if ( strcmp( argv[zd_optind], "--" ) == 0 )
      {
         zd_optind++;
         return ( EOF );
      }
   zd_optopt = c = argv[zd_optind][sp];
   if ( c == ':' || ( cp = strchr( opts, c ) ) == NULL )
   {
      ERR( ": illegal option -- ", c );
      if ( argv[zd_optind][++sp] == '\0' )
      {
         zd_optind++;
         sp = 1;
      }
      return ( '?' );
   }
   if ( *++cp == ':' )
   {
      if ( argv[zd_optind][sp + 1] != '\0' )
         zd_optarg = &argv[zd_optind++][sp + 1];
      else if ( ++zd_optind >= argc )
      {
         ERR( ": option requires an argument -- ", c );
         sp = 1;
         return ( '?' );
      }
      else
         zd_optarg = argv[zd_optind++];
      sp = 1;
   }
   else
   {
      if ( argv[zd_optind][++sp] == '\0' )
      {
         sp = 1;
         zd_optind++;
      }
      zd_optarg = NULL;
   }

   return ( c );

}                               /* getopt */
