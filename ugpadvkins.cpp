//////////////////////////////////////////////////////////////////////////////
//
//  ugpadvkins.cpp = uf_mom_add_ufun_tclexts.c
//  O:\\ugnx40\\ip21\\src\\ugpadvkins\\no\\ind\\uf_mom_add_ufun_tclexts.c
//  Z:\\v18projs\\batch\\project\\phase14\\ugp_adv_kins\\uf_mom_add_ufun_tclexts.c
//
//  Description:
//      Contains Unigraphics entry points for the application.
//
//////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_DEPRECATE 1

//  Include files
#include <stdio.h>

#include <math.h>

#include <uf_exit.h>
#include <uf_ui.h>

#include <stdlib.h>
#include <uf.h>
#include <uf_obj.h>
#include <uf_attr.h>
#include <uf_mom.h>

#include "ugpadvkins.h"  // #include "uf_mom_add_ufun_tclexts.h"
#include "mom_post_dh.h"

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

UF_MOM_id_t   MomId ; // dword_1000C028


//----------------------------------------------------------------------------
//  Activation Methods
//----------------------------------------------------------------------------

//  Explicit Activation
//      This entry point is used to activate the application explicitly, as in
//      "File->Execute UG/Open->User Function..."
extern "C" DllExport void ufusr( char *parm, int *returnCode, int rlen )
{
  int result; // eax@2
  char Dest[132]; // [sp+4h] [bp-8Ch]@2
  UF_MOM_id_t mom ;
  void *interp = NULL ;

  UF_MISC_set_program_name("<!<UGPKIN>!>");
  if ( UF_initialize() )
  {
    sprintf(&Dest, "ERROR!: Advanced Kinematics Module Unavailable");
    printf("ERROR : Ugpost Advanced Kinematics license not found \n");
    uc1601(&Dest, TRUE);
    result = UF_terminate();
  }
  else
  {
    UF_MISC_set_program_name("Kinematics");
    UF_MOM_ask_interp_from_param(parm, &interp);
    UF_MOM_ask_mom(parm, &mom);

  /*--------------------------------------------------------------------
   * Now extend the TCL interpreter with the following functions
   * The following TCL exetensions will be added
   *  - MOM_load_kinematics
   *  - MOM_convert_point
   *  - MOM_get_tool_attribute <name of the attribute>
   *  - MOM_rotate_mach_csys AAXIS n BAXIS m CAXIS k
   *  - MOM_map_to_rotated_csys
   *  - MOM_exit_kinematics_module
  ---------------------------------------------------------------------*/

  /* Adding MOM_load_kinematics TCL extension */
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_load_kinematics", mom_load_kinematics)); // sub_10001350
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_convert_point", mom_convert_point)); // sub_10001B10
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_get_tool_attribute", mom_get_tool_attribute )); // sub_10001C10
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_rotate_mach_csys", mom_rotate_mach_csys)); // sub_100010C0
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_map_to_rotated_csys", mom_map_to_rotated_csys)); // sub_10001270
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_exit_kinematics_module", mom_exit_kinematics_module)); // mom_exit_kinematics_module

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


//----- (10001350) --------------------------------------------------------
/*-----------------------------------------------------------------------
 * Function Name: mom_load_kinematics
 *
 -----------------------------------------------------------------------*/
extern int mom_load_kinematics
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
)
{
  MOM_kin_p_t kinematics ;
  MOM_machine_kins_p_t machine ;
  MOM_output_kins_p_t output ;
  MOM_arc_kins_p_t arcs ;
  MOM_feed_kins_p_t feeds ;
  MOM_4th_axis_kins_p_t axis_4th ;
  MOM_5th_axis_kins_p_t axis_5th ;
  MOM_head_kins_p_t head ;
  MOM_holder_kins_p_t holder ;
  MOM_time_kins_p_t time ;
  MOM_operdata_p_t operdata ;

  UF_MOM_id_t   mom_id = ( UF_MOM_id_t ) client_data ;
  int error ;

/* Set the data for all kinematics */

  /* Allocate memory to machine structure */

  machine = ( MOM_machine_kins_t * ) malloc
                        ( sizeof ( MOM_machine_kins_t ) );
  SET_machine_kinematics ( mom_id , machine ) ; //  sub_10006E70


  /* Allocate memory to output structure */

  output = ( MOM_output_kins_t * ) malloc
                        ( sizeof ( MOM_output_kins_t ) );
  SET_output_kinematics ( mom_id , output ) ; // sub_10005C20


  /* Allocate memory to arc structure */

  arcs = ( MOM_arc_kins_t * ) malloc
                        ( sizeof ( MOM_arc_kins_t ) );
  SET_arc_kinematics ( mom_id , arcs ) ; // sub_10005DD0


  /* Allocate memory to feeds structure */

  feeds = ( MOM_feed_kins_t * ) malloc
                        ( sizeof ( MOM_feed_kins_t ) );
  SET_feed_kinematics ( mom_id , feeds ) ; // sub_10005F10


  /* Allocate memory to axis_4th structure */

  axis_4th = ( MOM_4th_axis_kins_t * ) malloc
                        ( sizeof ( MOM_4th_axis_kins_t ) );
  SET_4th_axis_kinematics ( mom_id , axis_4th ) ; // sub_100060E0


  /* Allocate memory to axis_5th structure */

  axis_5th = ( MOM_5th_axis_kins_t * ) malloc
                        ( sizeof ( MOM_5th_axis_kins_t ) );
  SET_5th_axis_kinematics ( mom_id , axis_5th ) ; // sub_10006420


  /* Allocate memory to head structure */

  head = ( MOM_head_kins_t * ) malloc
                        ( sizeof ( MOM_head_kins_t ) );
  SET_head_kinematics ( mom_id , head ) ; // sub_10006760


  /* Allocate memory to holder structure */

  holder = ( MOM_holder_kins_t * ) malloc
                        ( sizeof ( MOM_holder_kins_t ) );
  SET_holder_kinematics ( mom_id , holder ) ; // sub_10006960


  /* Allocate memory to time structure */

  time = ( MOM_time_kins_t * ) malloc
                        ( sizeof ( MOM_time_kins_t ) );
  SET_time_kinematics ( mom_id , time ) ; // sub_10006870


/* Allocate memory to the main kinematics structure */

  kinematics = (MOM_kin_t *)malloc(sizeof(MOM_kin_t));

  if (kinematics == NULL)
  {
     error = 1;
     return error;
  }

/* Update the main kinematics structure */

  kinematics->machine = machine ;
  kinematics->output = output ;
  kinematics->arcs = arcs ;
  kinematics->feeds = feeds ;
  kinematics->axis_4th = axis_4th ;
  kinematics->axis_5th = axis_5th ;
  kinematics->head = head ;
  kinematics->holder = holder ;
  kinematics->time = time ;


/* Set operdata data */

  /* Allocate memory to operdata structure */

  operdata = ( MOM_operdata_t * ) malloc ( sizeof ( MOM_operdata_t ) ) ;
  SET_msys_data ( mom_id , operdata ) ; // sub_10007240
  SET_mtsys_data ( mom_id , operdata ) ; // sub_100074C0
  SET_operation_data ( mom_id , operdata ) ; // sub_10007760


/* Kevins routine called here to initialize */
 {
     double mcsys[12], mtcsys[12], tool_axis[3];
     double primary_machine_center[3], secondary_machine_center[3], tool_machine_center[3];
     int i;
     MOM_POST_dh_kinematics_t dh_data, *data_p = &dh_data;


     /* compute primary machine center */
     for (i = 0; i <3; i++)
     {
         /* setoff[0..2]: offset from msys to center of 4th.
          * resultant primary_machine_center is also the origin of
          * machine tool csys.
          * Stan said: primary_machine_center[i] = mcsys[i],
          * Gupta said following: */
         primary_machine_center[i] =
             operdata->msys_origin[i] + axis_4th->kin_4th_axis_center_offset[i]; /* setoff */

         /* rotvec[0..2]: from center of 4th to cetner of 5th */
         secondary_machine_center[i] = primary_machine_center[i] +
             axis_5th->kin_5th_axis_center_offset[i]; /* kinematic_data->rotvec[i];*/

         /* compute initial location of tool, from center of 4th to
            mom_kin_4th_to_tracking_point */
         tool_machine_center[i] = primary_machine_center[i] +
             machine->kin_4th_to_tracking_point[i];
     }

     /* add MTCSYS (machine tool csys). for post teammates claim that
      *  MCSYS is the same with MTCSYS. is this really true? */
     memcpy(mcsys, operdata->msys_origin, sizeof(double)*3);
     memcpy(mcsys+3, operdata->msys_x_axis, sizeof(double)*3);
     memcpy(mcsys+6, operdata->msys_y_axis, sizeof(double)*3);
     memcpy(mcsys+9, operdata->msys_z_axis, sizeof(double)*3);
     memcpy(mtcsys, operdata->mtsys_origin, sizeof(double)*3);
     memcpy(mtcsys+3, operdata->mtsys_x_axis, sizeof(double)*3);
     memcpy(mtcsys+6, operdata->mtsys_y_axis, sizeof(double)*3);
     memcpy(mtcsys+9, operdata->mtsys_z_axis, sizeof(double)*3);

     /* for tool axis, use:holder_orientation, use POSZ as default */
     if( strstr( holder->kin_holder1_orientation, "POSX" ) != NULL)
         memcpy(tool_axis, operdata->msys_x_axis, sizeof(double)*3);
     else if( strstr( holder->kin_holder1_orientation, "POSY" ) != NULL)
         memcpy(tool_axis, operdata->msys_y_axis, sizeof(double)*3);
     else if( strstr( holder->kin_holder1_orientation, "POSZ" ) != NULL)
         memcpy(tool_axis, operdata->msys_z_axis, sizeof(double)*3);
     else if( strstr( holder->kin_holder1_orientation, "NEGX" ) != NULL)
         for (i = 0; i < 3; i++)  tool_axis[i] = -operdata->msys_x_axis[i];
     else if( strstr( holder->kin_holder1_orientation, "NEGY" ) != NULL)
         for (i = 0; i < 3; i++)  tool_axis[i] = -operdata->msys_y_axis[i];
     else if( strstr( holder->kin_holder1_orientation, "NEGZ" ) != NULL)
         for (i = 0; i < 3; i++)  tool_axis[i] = -operdata->msys_z_axis[i];
     else
         memcpy(tool_axis, operdata->msys_z_axis, sizeof(double)*3); /* no holder, along z of msys */

     if(strstr( machine->kin_machine_type, "5_axis_dual_table") != NULL)
         data_p->mom_kin_machine_type = is_5_axis_dual_table;
     else if (strstr( machine->kin_machine_type, "5_axis_dual_head") != NULL)
         data_p->mom_kin_machine_type = is_5_axis_dual_head;
     else if (strstr( machine->kin_machine_type, "5_axis_head_table") != NULL)
         data_p->mom_kin_machine_type = is_5_axis_head_table;

     /* assign tolerance */
     data_p->resl = machine->kin_machine_resolution;
     memcpy(data_p->mom_translate, operdata->translate, sizeof(double)*3);
     memcpy(data_p->mom_origin, operdata->origin, sizeof(double)*3); /* dynamic_vars->mom_origin; */
     memcpy(data_p->setoff, axis_4th->kin_4th_axis_center_offset, sizeof(double)*3); /* kinematic_data->setoff; */
     data_p->track_ball = atoi(machine->kin_track_center_of_ball) == 1 ? true: false; /*  kinematic_data->track_ball */
     data_p->ball_center = operdata->tool_corner1_radius; /* dynamic_vars->ball_center; */

     /* rotary limits */
     data_p->primary_min_limit = kinematics->axis_4th->kin_4th_axis_min_limit;
     data_p->primary_max_limit = kinematics->axis_4th->kin_4th_axis_max_limit;
     data_p->secondary_min_limit = kinematics->axis_5th->kin_5th_axis_min_limit;
     data_p->secondary_max_limit  = kinematics->axis_5th->kin_5th_axis_max_limit;

     /* tool length offset */
     data_p->tool_z_offset = operdata->tool_z_offset;

     /* setup initial configuration */
     // sub_10004420
     MOM_POST_dh_setup_vector_conversion(
         mtcsys, mcsys, primary_machine_center, axis_4th->kin_4th_axis_vector,
         secondary_machine_center, axis_5th->kin_5th_axis_vector,
         tool_machine_center, tool_axis, data_p);
 }

/*
  free(v2);
  free((void *)v1);
  if ( v16 )
    free(v16);
  if ( v153 )
    free(v153);
  if ( v155 )
    free(v155);
  free((void *)v162);
  free((void *)v158);
  if ( v154 )
    free(v154);
  if ( v163 )
    free(v163);
  if ( v156 )
    free(v156);*/


  return 0 ;
}

//----- (10001B10) --------------------------------------------------------
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
}


//----- (10001C10) --------------------------------------------------------
/*-----------------------------------------------------------------------
 * Function Name: mom_get_tool_attribute
 *
 -----------------------------------------------------------------------*/
static int mom_get_tool_attribute
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
)
{
  int             error ;
  const char      *mom_value ;
  char            error_message[512] ;
  char            tool_name[MAX_LINE_SIZE+1] ;
  char            curr_tool_name[UF_OBJ_NAME_LEN+1] ;
  char            attribute_title[UF_ATTR_MAX_TITLE_LEN+1] ;
  char            attribute_value[UF_ATTR_MAX_STRING_LEN+1];
  char            tcl_variable[MAX_LINE_SIZE+1] ;
  char            default_attribute_value[MAX_LINE_SIZE+1] ;
  tag_t           tool_object_tag = NULL_TAG ;
  UF_ATTR_value_t value ;
  UF_MOM_id_t     mom_id = ( UF_MOM_id_t ) client_data ;

  strcpy ( default_attribute_value , "   " ) ;
  strcpy ( tcl_variable , "tool_attribute_text" ) ;
  strcpy ( tool_name , "tool_name" ) ;

  if ( argc != 2)
  {
/*
     UF_MOM_set_string ( mom_id , "tool_attribute",
                         "Failed. Wrong number of arguments" ) ;
*/
     strcpy ( error_message , "Invalid number of arguments" ) ;
     printf ( " ERROR : %s \n " , error_message ) ;
     return (1) ;
  }

  /* Get the tool name for which the attribute is required */

  error = UF_MOM_ask_string ( mom_id ,
                              tool_name ,
                              &mom_value ) ;
  if ( error )
  {
     strcpy ( error_message , "No Tool Name obtained from UGPost" ) ;
     printf ( " ERROR : %s \n " , error_message ) ;
     return (1) ;
  }

  strcpy ( curr_tool_name , mom_value ) ;

  /* Get the tool tag for the tool defined in mom_tool_name by UGPost */

  strcpy( attribute_title , argv[1] ) ;

  error = UF_OBJ_cycle_by_name (
                                  curr_tool_name,
                                  &tool_object_tag
                               ) ;
  if ( error )
  {
      printf ( " UF_OBJ_cycle_by_name could not get the tool_object_tag \n" );
      return (1) ;
  }

  /* Read the tool attribute string for the tool */

  if (tool_object_tag != 0)
  {
    value.value.string = attribute_value;
    error = UF_ATTR_read_value (
                                 tool_object_tag,
                                 attribute_title,
                                 UF_ATTR_string,
                                 &value
                               ) ;

    if ( error )
    {
        printf ( " UF_ATTR_read_value could not return tool string \n" );
        return (1) ;
    }

    /* Set the default value if reading of the arributre fails */

    if ( value.type != UF_ATTR_string )
    {
       strcpy ( attribute_value , default_attribute_value ) ;
    }
  }
  else
  {
    strcpy ( attribute_value , default_attribute_value ) ;
  }

  /* Return the the tool attribute string to tcl and set in the tcl variable
     mom_tool_attribute_text */

  UF_MOM_set_string (
                      mom_id ,
                      tcl_variable,
                      attribute_value
                    ) ;
  return ( 0 ) ;
}

//
// MOM_rotate_mach_csys AAXIS n BAXIS m CAXIS k
//----- (100010C0) --------------------------------------------------------
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

//sub_10007ED0
  error = SET_rotd_mcs_matrix ( mom_id, oper_setup_data, trans_method ) ;
  if( error ) { printf(" SET_rotd_mcs_matrix failed in mom_rotate_mach_csys \n ");
                return error ; }

//sub_10007B00
  error = SET_rotd_operation_data ( mom_id, oper_setup_data ) ;
  if( error ) { printf(" SET_rotd_operation_data failed in mom_rotate_mach_csys \n ");
                return error ; }

/*  FREE ( oper_setup_data ) ; */

  return error ;

}/* mom_rotate_mach_csys */

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
 //sub_10007980                       
 error = SET_input_point ( mom_id, input_gotos ) ;
 if ( error ) {printf(" SET_input_point failed in mom_map_to_rotated_csys\n ");
               return error; }

 /* Process the input gotos for translation and origin */
 processed_gotos = ( MOM_input_point_t *) malloc
                        ( sizeof ( MOM_input_point_t ) ) ;
 //sub_10007E30                       
 error = mom_process_input_gotos ( input_gotos , processed_gotos ) ;
 if ( error ) {printf(" mom_process_input_gotos failed in mom_map_to_rotated_csys\n ");
               return error; }

 /* Transfer processed gotos to rotated mcsys */
 rotd_gotos = ( MOM_input_point_t *) malloc
                        ( sizeof ( MOM_input_point_t ) ) ;
 //sub_10007D30
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


//----- (10001350) --------------------------------------------------------
extern int mom_exit_kinematics_module
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
)
{
  UF_terminate();
  return 0 ;
}
