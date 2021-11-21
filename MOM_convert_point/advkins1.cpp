//////////////////////////////////////////////////////////////////////////////
//
//  advkins.cpp
//
//  Description:
//      Contains Unigraphics entry points for the application.
//
//////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_DEPRECATE 1

//  Include files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <uf_exit.h>
#include <uf_ui.h>
#include <uf.h>
#include <uf_obj.h>
#include <uf_attr.h>
#include <uf_mom.h>

#include "advkins1.h"  // #include "uf_mom_add_ufun_tclexts.h"

#include <uf_vec.h>
#include <uf_mtx.h>

/****************************************************************************/

#define UF_CALL(X) (report( __FILE__, __LINE__, #X, (X)))

static int report( char *file, int line, char *call, int irc)
{
  if (irc)
  {
     char    messg[133];
     printf("%s, line %d:  %s\n", file, line, call);
     (UF_get_fail_message(irc, messg)) ?
       printf("    returned a %d\n", irc) :
       printf("    returned error %d:  %s\n", irc, messg);
  }
  return(irc);
}

UF_MOM_id_t   MomId ; //


//----------------------------------------------------------------------------
//  Activation Methods
//----------------------------------------------------------------------------

//  Explicit Activation
//      This entry point is used to activate the application explicitly, as in
//      "File->Execute UG/Open->User Function..."
extern "C" DllExport void ufusr( char *parm, int *returnCode, int rlen )
{
  int result;
  char Dest[132];
  UF_MOM_id_t mom ;
  void *interp = NULL ;

  UF_MISC_set_program_name("<!<UGPKIN>!>");
  if ( UF_initialize() )
  {
    sprintf(Dest, "ERROR!: Advanced Kinematics Module Unavailable");
    printf("ERROR : Ugpost Advanced Kinematics license not found \n");
    uc1601(Dest, TRUE);
    result = UF_terminate();
  }
  else
  {
    UF_MISC_set_program_name("Kinematics");
    UF_MOM_ask_interp_from_param(parm, &interp);
    UF_MOM_ask_mom(parm, &mom);

  /* Adding MOM_convert_point TCL extension */
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_convert_point", mom_convert_point)); //

    MomId = mom; //
    result = 0;
  }
  *returnCode = result;
}

//----------------------------------------------------------------------------
//  Utilities
//----------------------------------------------------------------------------

// Unload Handler
//     This function specifies when to unload your application from Unigraphics.
//     If your application registers a callback (from a MenuScript item or a
//     User Defined Object for example), this function MUST return
//     "UF_UNLOAD_UG_TERMINATE".
extern "C" int ufusr_ask_unload( void )
{
     /* unload immediately after application exits*/
     //return ( UF_UNLOAD_IMMEDIATELY );

     /*via the unload selection dialog... */
     return ( UF_UNLOAD_SEL_DIALOG );
     /*when UG terminates...              */
     //return ( UF_UNLOAD_UG_TERMINATE );
}

//----- () --------------------------------------------------------
/*-----------------------------------------------------------------------
 * Function Name: mom_convert_point
 *
 -----------------------------------------------------------------------*/
extern int mom_convert_point
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                          argv[0] - The TCL extension */
)
{
  MOM_input_point_p_t   input_point ;
  double pcoord[6], mcoord[5], alt_mcoord[5];
  UF_MOM_id_t   mom_id = ( UF_MOM_id_t ) client_data ;

/* Set the data for the point and tool axis */
 /* Allocate memory to input_point_data structure */
  input_point = ( MOM_input_point_t * ) malloc
                        ( sizeof ( MOM_input_point_t ) );
  SET_input_point ( mom_id , input_point ) ;

/* Kevins routine called here to convert point */
  memcpy(pcoord,   input_point->mcs_goto, sizeof(double)*3);
  memcpy(pcoord+3, input_point->tool_axis, sizeof(double)*3);
  MOM_POST_dh_ext_convert_point((double *)input_point, mcoord, alt_mcoord);
/*   error =  KEVINS_CONVERT_POINT_FUNCTION
                  ( input_point_data , output_point_data ) ; */

  sub_10007760(a1, (int)&v2); //SET_operation_data (UF_MOM_id_t mom_id ,MOM_operdata_t operdata )
  sub_10002860((int)&v2);
  sub_10007980(a1, (int)&v3); //SET_input_point (UF_MOM_id_t mom_id,MOM_input_point_t input_gotos )
  sub_10005470(&v3, (int)&v4, (int)&v9);
/* Update the mom_pos values with values returned by Kevins Function */
  UF_MOM_set_double ( mom_id , "pos_x" , mcoord[0] ) ;
  UF_MOM_set_double ( mom_id , "pos_y" , mcoord[1] ) ;
  UF_MOM_set_double ( mom_id , "pos_z" , mcoord[2] ) ;
  UF_MOM_set_double ( mom_id , "pos_a1" , mcoord[3] ) ;
  UF_MOM_set_double ( mom_id , "pos_a2" , mcoord[4] ) ;

  UF_MOM_set_double ( mom_id , "alt_pos_x" , alt_mcoord[0] ) ;
  UF_MOM_set_double ( mom_id , "alt_pos_y" , alt_mcoord[1] ) ;
  UF_MOM_set_double ( mom_id , "alt_pos_z" , alt_mcoord[2] ) ;
  UF_MOM_set_double ( mom_id , "alt_pos_a1" , alt_mcoord[3] ) ;
  UF_MOM_set_double ( mom_id , "alt_pos_a2" , alt_mcoord[4] ) ;
  return 0;
} /* mom_convert_point */

