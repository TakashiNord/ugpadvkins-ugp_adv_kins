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
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include <uf_exit.h>
#include <uf_ui.h>
#include <uf.h>
#include <uf_mom.h>

#include "advkins1.h"  // #include "uf_mom_add_ufun_tclexts.h"

#include <uf_vec.h>
#include <uf_mtx.h>

/****************************************************************************/

int dword_1000C460 = 1; // переменная взаимосвязана с MOM_map_to_rotated_csys

typedef struct MOM_oper_setup_data_s
{
  double mtx[9];
  double origin[3];
  double translate[3];
  double tool_z_offset;
  int    kin_track_center_of_ball;
  double tool_corner1_radius;
} MOM_oper_setup_data_t, *MOM_oper_setup_data_p_t;


//----- () --------------------------------------------------------
int SET_rotd_mcs_matrix (UF_MOM_id_t mom_id,MOM_oper_setup_data_p_t oper_setup_data,double trans_method[6])
{
  double mt[3][9];
  double mtx[9]={1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0};
  double rotation_axis[3]  ;
  int i , j ;
  double ang ;
  double GRADTORAD = asin(1.0) * 0.01111111111111111;

  for ( i = 0, j = 0; i < 6; i = i + 2)
  {
    if ( trans_method[i] == 1 ) {
      ang = GRADTORAD * trans_method[i + 1] * (-1.0);
      UF_MTX3_x_vec(mtx, rotation_axis);
    } else if ( trans_method[i] == 2 ) {
    	      ang = GRADTORAD * trans_method[i + 1] * (-1.0);
            UF_MTX3_y_vec(mtx, rotation_axis);
      } else if ( trans_method[i] == 3 ) {
    	        ang = GRADTORAD * trans_method[i + 1] * (-1.0);
              UF_MTX3_z_vec(mtx, rotation_axis);
      } else { continue ; }
    UF_MTX3_rotate_about_axis(rotation_axis, ang, mt[j]);
    j++ ;
  }

  if ( j > 0 )
  {
    for(i=j-1;i>=0;i--)
    {
      UF_MTX3_multiply(mtx, mt[i], mtx); // mtx_product[9] = mtx1[9] X mtx2[9]
    }
  }

  oper_setup_data->mtx[0] = mtx[0];
  oper_setup_data->mtx[1] = mtx[1];
  oper_setup_data->mtx[2] = mtx[2];
  oper_setup_data->mtx[3] = mtx[3];
  oper_setup_data->mtx[4] = mtx[4];
  oper_setup_data->mtx[5] = mtx[5];
  oper_setup_data->mtx[6] = mtx[6];
  oper_setup_data->mtx[7] = mtx[7];
  oper_setup_data->mtx[8] = mtx[8];

  dword_1000C460 = 0;

  return 0;
}

//----- () --------------------------------------------------------
int SET_rotd_operation_data (UF_MOM_id_t mom_id,MOM_oper_setup_data_p_t oper_setup_data)
{
  int error ;
  int i ;
  char *v[]={
  "mom_origin_x",
  "mom_origin_y",
  "mom_origin_z",
  "mom_translate_x",
  "mom_translate_y",
  "mom_translate_z",
  "mom_tool_z_offset",
  "mom_kin_track_center_of_ball",
  "mom_tool_corner1_radius",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error = UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "0.0";
          oper_setup_data->origin[0] = strtod(Str, NULL);
          break;
        case 1:
          if ( !Str ) Str = "0.0";
          oper_setup_data->origin[1] = strtod(Str, NULL);
          break;
        case 2:
          if ( !Str ) Str = "0.0";
          oper_setup_data->origin[2] = strtod(Str, NULL);
          break;
        case 3:
          if ( !Str ) Str = "0.0";
          oper_setup_data->translate[0] = strtod(Str, NULL);
          break;
        case 4:
          if ( !Str ) Str = "0.0";
          oper_setup_data->translate[1] = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "0.0";
          oper_setup_data->translate[2] = strtod(Str, NULL);
          break;
        case 6:
          if ( !Str ) Str = "0.0";
          oper_setup_data->tool_z_offset = strtod(Str, NULL);
          break;
        case 7:
          if ( !Str ) Str = "0";
          oper_setup_data->kin_track_center_of_ball = (int)strtod(Str, NULL);
          break;
        case 8:
          if ( !Str ) Str = "0.0";
          oper_setup_data->tool_corner1_radius = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  //memcpy(oper_setup_data->mtx,   oper_setup_data->mtx, 144);
  return error;
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

  /* Adding MOM_rotate_mach_csys TCL extension */
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_rotate_mach_csys", mom_rotate_mach_csys)); //

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

//
// MOM_rotate_mach_csys AAXIS n BAXIS m CAXIS k
//----- () --------------------------------------------------------
/*-----------------------------------------------------------------------
 * Function Name: mom_rotate_mach_csys
 *
 -----------------------------------------------------------------------*/
extern int mom_rotate_mach_csys
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
)
{

  MOM_oper_setup_data_p_t oper_setup_data;
  UF_MOM_id_t   mom_id = ( UF_MOM_id_t ) client_data ;
  double trans_method[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;
  int error, i ;

 /* Obtain Rotate MCSYS Matrix */
 /* Obtain Translate data */
 /* Obtain Origin data */
 /* Obtain tool_z_offset from mom object */
 /* Obtain kinematic for tool tracking */
 /* Store the obtained operation data in a structure */

  oper_setup_data = ( MOM_oper_setup_data_t * ) malloc
                        ( sizeof ( MOM_oper_setup_data_t ) ) ;

  if ( argc > 7 || argc == 1 )
  {
    /* Raise error, take default action, return  as this function must noy
       have more than 6 argumnets or just one argument */

    printf( " Incorrect number of arguments\n" );
    printf( " Number of arguments should be between 1 and 6\n ");
    return 999 ;
  }

  if ( (argc - (( int ) ( argc/2 )) * 2) == 0 )
  {
    /* Raise an error as invalid number of arguments as the function
       must have odd number of arguments */

    printf( " Insufficient number of arguments, There should be atleast 2 arguments\n ");

    return 999 ;
  }

  for ( i = 1; i < argc; i = i + 2 )
  {
    if ( strcmp ( argv[i], "AAXIS" ) == 0 ) trans_method[i - 1] = 1 ;
    else if ( strcmp ( argv[i], "BAXIS" ) == 0 ) trans_method[i - 1] = 2 ;
    else if ( strcmp ( argv[i], "CAXIS" ) == 0 ) trans_method[i - 1] = 3 ;
    trans_method[i] = strtod ( argv[i+1] , NULL ) ;
  }

//
  error = SET_rotd_mcs_matrix ( mom_id, oper_setup_data, trans_method ) ;
  if( error ) { printf(" SET_rotd_mcs_matrix failed in mom_rotate_mach_csys \n ");
                return error ; }

//
  error = SET_rotd_operation_data ( mom_id, oper_setup_data ) ;
  if( error ) { printf(" SET_rotd_operation_data failed in mom_rotate_mach_csys \n ");
                return error ; }

/*  FREE ( oper_setup_data ) ; */

  return error ;

}/* mom_rotate_mach_csys */
