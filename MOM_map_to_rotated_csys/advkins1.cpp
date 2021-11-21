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

#include <uf_exit.h>
#include <uf_ui.h>
#include <uf.h>
#include <uf_obj.h>
#include <uf_mom.h>

#include "advkins1.h"  // #include "uf_mom_add_ufun_tclexts.h"

#include <uf_vec.h>
#include <uf_mtx.h>


/****************************************************************************/

int dword_1000C460 = 0 ; // переменная взаимосвязана с MOM_rotate_mach_csys
int dword_1000C450 = 0 ;

double vec_unk_1000C430[3] ;
double vec_unk_1000C3D0[3] ;
double dbl_1000C448 ;
double dbl_1000C458 ;
double dbl_1000C418[3];

typedef struct MOM_input_point_s
{
  double mcs_goto[3];
  double tool_axis[3];
} MOM_input_point_t, *MOM_input_point_p_t;


//----- () --------------------------------------------------------
int SET_input_point (UF_MOM_id_t mom_id,MOM_input_point_p_t input_gotos )
{
  int i ;
  char *v[]={
  "mom_mcs_goto_x",
  "mom_mcs_goto_y",
  "mom_mcs_goto_z",
  "mom_tool_axis_i",
  "mom_tool_axis_j",
  "mom_tool_axis_k",
  "END"
  };
  char S[128] ;
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "0.0";
          input_gotos->mcs_goto[0] = strtod(Str, NULL);
          break;
        case 1:
          if ( !Str ) Str = "0.0";
          input_gotos->mcs_goto[1] = strtod(Str, NULL);
          break;
        case 2:
          if ( !Str ) Str = "0.0";
          input_gotos->mcs_goto[2] = strtod(Str, NULL);
          break;
        case 3:
          if ( !Str ) Str = "0.0";
          input_gotos->tool_axis[0] = strtod(Str, NULL);
          break;
        case 4:
          if ( !Str ) Str = "0.0";
          input_gotos->tool_axis[1] = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "0.0";
          input_gotos->tool_axis[2] = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return 0;
}


//----- () --------------------------------------------------------
int mom_process_input_gotos(MOM_input_point_p_t input_gotos ,MOM_input_point_p_t processed_gotos )
{
  double v3[3];

  UF_VEC3_add(input_gotos->mcs_goto, vec_unk_1000C430, processed_gotos->mcs_goto); // vec_sum = vec1 + vec2
  UF_VEC3_sub(input_gotos->mcs_goto, vec_unk_1000C3D0, processed_gotos->mcs_goto); // vec_diff = vec1 - vec2
  UF_VEC3_copy(input_gotos->tool_axis, processed_gotos->tool_axis); // vec_dst = vec_src

  UF_VEC3_scale(dbl_1000C448, processed_gotos->tool_axis, v3); // scaled_vec = (scale x vec)
  UF_VEC3_add(input_gotos->mcs_goto, v3, processed_gotos->mcs_goto);
  if ( dword_1000C450 == 1 )
  {
    UF_VEC3_scale(dbl_1000C458, processed_gotos->tool_axis, v3);
    UF_VEC3_add(input_gotos->mcs_goto, v3, processed_gotos->mcs_goto);
  }
  return 0;
}


//----- () --------------------------------------------------------
int mom_transfer_gotos_rotd_mcsys(MOM_input_point_p_t processed_gotos ,MOM_input_point_p_t rotd_gotos )
{
  int is_equal ;

  if ( !dword_1000C460 )
  {
    UF_VEC3_is_equal(processed_gotos->tool_axis, dbl_1000C418, 0.00000001, &is_equal);
    if ( !is_equal )
    {
      printf("WARNING  The tool axis is not matching with the \
                      rotated MCS-Z axis. The output may be INCORRECT\n");
      uc1601(
        "WARNING  The tool axis is not matching with the * \
                            rotated MCS-Z axis. The output may be INCORRECT\n",
        TRUE);
    }
    dword_1000C460 = 1;
  }
  UF_VEC3_copy(processed_gotos->mcs_goto, v15);
  UF_VEC3_copy(processed_gotos->tool_axis, v14);
  UF_MTX3_vec_multiply(processed_gotos->mcs_goto, &v5, rotd_gotos->mcs_goto);
  UF_MTX3_vec_multiply(processed_gotos->tool_axis, &v5, rotd_gotos->tool_axis);
  return 0;
}

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

  /* Adding MOM_map_to_rotated_csys TCL extension */
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_map_to_rotated_csys", mom_map_to_rotated_csys)); //

    MomId = mom; // dword_1000C028
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

//----- (10001270) --------------------------------------------------------
/* -----------------------------------------------------------------------
 *  Function : mom_map_to_rotated_csys
 *
 * ----------------------------------------------------------------------*/
extern int mom_map_to_rotated_csys
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
)
{
  MOM_input_point_p_t     input_gotos ;
  MOM_input_point_p_t     rotd_gotos ;
  MOM_input_point_p_t     processed_gotos ;

  UF_MOM_id_t   mom_id = ( UF_MOM_id_t ) client_data ;
  int error ;

 /* Get the goto and tool axis from mom object */
 input_gotos = ( MOM_input_point_t *) malloc
                        ( sizeof ( MOM_input_point_t ) ) ;
 //                       
 error = SET_input_point ( mom_id, input_gotos ) ;
 if ( error ) {printf(" SET_input_point failed in mom_map_to_rotated_csys\n ");
               return error; }

 /* Process the input gotos for translation and origin */
 processed_gotos = ( MOM_input_point_t *) malloc
                        ( sizeof ( MOM_input_point_t ) ) ;
 //                       
 error = mom_process_input_gotos ( input_gotos , processed_gotos ) ;
 if ( error ) {printf(" mom_process_input_gotos failed in mom_map_to_rotated_csys\n ");
               return error; }

 /* Transfer processed gotos to rotated mcsys */
 rotd_gotos = ( MOM_input_point_t *) malloc
                        ( sizeof ( MOM_input_point_t ) ) ;
 //
 error = mom_transfer_gotos_rotd_mcsys ( processed_gotos , rotd_gotos ) ;
 if ( error ) {printf(" mom_transfer_gotos_rotd_mcsys failed in mom_map_to_rotated_csys\n ");
                return error;}

 /* Update the mom_pos values with values returned by Kevins Function */
  UF_MOM_set_double ( mom_id , "pos_x" , rotd_gotos->mcs_goto[0] ) ;
  UF_MOM_set_double ( mom_id , "pos_y" , rotd_gotos->mcs_goto[1] ) ;
  UF_MOM_set_double ( mom_id , "pos_z" , rotd_gotos->mcs_goto[2] ) ;

 // free ( input_gotos ) ;
 // free ( rotd_gotos ) ;
 // free ( processed_gotos );

 return error ;

} /* mom_map_to_rotated_csys */

