// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct MOM_feed_kins_s
{
  int i1;
  int i2;
} MOM_feed_kins_t, *MOM_feed_kins_p_t;

int p(MOM_feed_kins_p_t ff) ;

int main(int argc, char* argv[])
{
  MOM_feed_kins_p_t feeds ;
	
  printf("Hello World!\n");

  feeds = ( MOM_feed_kins_t * ) malloc ( sizeof ( MOM_feed_kins_t ) );
  p(feeds) ;

  printf("\n-------\n");
  printf("\nfeeds->i1=%d",feeds->i1);
  printf("\nfeeds->i2=%d",feeds->i2);
  printf("\n-------\n");

  free(feeds);

	return 0;
}

int p(MOM_feed_kins_p_t ff)
{
  int i ;
  char *v[]={
  "mom_kin_min_fpm",
  "mom_kin_max_fpm",
  "END"
  };

  i=0;
  while (v[i]!="END") {
	  printf("\n %s",v[i]+4);
	  switch(i){
	    case 0: ff->i1=0; break;
		case 1: ff->i2=99; break;
		case 2: ff->i1=-9999; break;
	  }
	  i++;

  }
  return 0;
}
