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
#include <string.h>
#include <math.h>

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

/*
int SET_machine_kinematics (UF_MOM_id_t mom_id ,MOM_machine_kins_p_t machine ) ;
int SET_output_kinematics (UF_MOM_id_t mom_id ,MOM_output_kins_p_t output ) ;
int SET_arc_kinematics(UF_MOM_id_t mom_id, MOM_arc_kins_p_t arcs) ;
int SET_feed_kinematics(UF_MOM_id_t mom_id, MOM_feed_kins_p_t feeds);
int SET_4th_axis_kinematics (UF_MOM_id_t mom_id ,MOM_4th_axis_kins_p_t axis_4th );
int SET_5th_axis_kinematics (UF_MOM_id_t mom_id ,MOM_5th_axis_kins_p_t axis_5th );
int SET_head_kinematics (UF_MOM_id_t mom_id ,MOM_head_kins_p_t head );
int SET_holder_kinematics (UF_MOM_id_t mom_id ,MOM_holder_kins_p_t holder );
int SET_time_kinematics (UF_MOM_id_t mom_id ,MOM_time_kins_p_t time ) ;

int SET_msys_data (UF_MOM_id_t mom_id ,MOM_operdata_p_t operdata );
int SET_mtsys_data (UF_MOM_id_t mom_id ,MOM_operdata_p_t operdata );
int SET_operation_data (UF_MOM_id_t mom_id ,MOM_operdata_p_t operdata );
*/

typedef struct MOM_machine_kins_s
{
	char   kin_machine_type[133];
	char   kin_track_center_of_ball[133];
	char   kin_wire_tilt_output_type[133];
	char   kin_clsf_generation[133];
	char   kin_coordinate_type[133];
	char   kin_linearization_flag[133];
	double kin_machine_resolution;
	double kin_tool_tracking_height;
	double kin_5th_axis_inclination_to_4th;
	double kin_linearization_tol;
	double kin_gauge_to_pivot[3];
	double kin_4th_to_tracking_point[3];
} MOM_machine_kins_t, *MOM_machine_kins_p_t;

typedef struct MOM_output_kins_s
{
  char kin_nurbs_output_type[133];
  char kin_output_unit[133];
  char kin_polar_radius_side[133];
  char kin_read_ahead_next_motion[133];
  double kin_pivot_gauge_offset;
  double kin_rapid_feed_rate;
} MOM_output_kins_t, *MOM_output_kins_p_t;

typedef struct MOM_arc_kins_s
{
  char kin_arc_output_mode[133];
  char kin_arc_valid_plane[133];
  double kin_min_arc_radius;
  double kin_max_arc_radius;
} MOM_arc_kins_t, *MOM_arc_kins_p_t;

typedef struct MOM_feed_kins_s
{
  double kin_max_fpm;
  double kin_min_fpm;
  double kin_max_fpr;
  double kin_min_fpr;
  double kin_max_frn;
  double kin_min_frn;
  double kin_max_dpm;
  double kin_min_dpm;
} MOM_feed_kins_t, *MOM_feed_kins_p_t;

typedef struct MOM_4th_axis_kins_s
{
  char kin_4th_axis_plane[132];
  char kin_4th_axis_direction[132];
  char kin_4th_axis_rotation[132];
  double kin_4th_axis_min_incr ;
  double kin_4th_axis_min_limit ;
  double kin_4th_axis_max_limit ;
  double kin_4th_axis_zero ;
  double kin_4th_axis_center_offset[3];
  double kin_4th_axis_vector[3] ;
  double kin_4th_axis_angles_a1 ;
  double kin_4th_axis_angles_a2 ;
} MOM_4th_axis_kins_t, *MOM_4th_axis_kins_p_t;

typedef struct MOM_5th_axis_kins_s
{
  char kin_5th_axis_plane[132];
  char kin_5th_axis_direction[132];
  char kin_5th_axis_rotation[132];
  double kin_5th_axis_min_incr ;
  double kin_5th_axis_min_limit ;
  double kin_5th_axis_max_limit ;
  double kin_5th_axis_zero ;
  double kin_5th_axis_center_offset[3] ;
  double kin_5th_axis_vector[3] ;
  double kin_5th_axis_angles_a1 ;
  double kin_5th_axis_angles_a2 ;
} MOM_5th_axis_kins_t, *MOM_5th_axis_kins_p_t;

typedef struct MOM_head_kins_s
{
  char kin_independent_head[132];
  double kin_ind_to_dependent_head_x;
  double kin_ind_to_dependent_head_z;
} MOM_head_kins_t, *MOM_head_kins_p_t;

typedef struct MOM_holder_kins_s
{
  char kin_holder1_orientation[132];
  char kin_holder2_orientation[132];
  char kin_holder3_orientation[132];
  char kin_holder4_orientation[132];
  char kin_holder5_orientation[132];
  char kin_holder6_orientation[132];
  double kin_holder1_offset[3];
  double kin_holder2_offset[3];
  double kin_holder3_offset[3];
  double kin_holder4_offset[3];
  double kin_holder5_offset[3];
  double kin_holder6_offset[3];
} MOM_holder_kins_t, *MOM_holder_kins_p_t;

typedef struct MOM_operdata_s
{
  double msys_origin[3];
  double msys_x_axis[3];
  double msys_y_axis[3];
  double msys_z_axis[3];

  double mtsys_origin[3];
  double mtsys_x_axis[3];
  double mtsys_y_axis[3];
  double mtsys_z_axis[3];

  double origin[3];
  double translate[3];
    char tool_type[132];
  double tool_z_offset;
  double tool_corner1_radius;
} MOM_operdata_t, *MOM_operdata_p_t;

typedef struct MOM_time_kins_s
{
  double kin_tool_change_time;
  double kin_clamp_time;
  double kin_flush_time;
} MOM_time_kins_t, *MOM_time_kins_p_t;

typedef struct MOM_kin_s
{
  MOM_machine_kins_p_t machine ;
  MOM_output_kins_p_t output ;
  MOM_arc_kins_p_t    arcs ;
  MOM_feed_kins_p_t   feeds ;
  MOM_4th_axis_kins_p_t axis_4th ;
  MOM_5th_axis_kins_p_t axis_5th ;
  MOM_head_kins_p_t   head ;
  MOM_holder_kins_p_t holder ;
  MOM_time_kins_p_t   time ;
} MOM_kin_t, *MOM_kin_p_t;


//************************************************************************

//----- (10006E70) --------------------------------------------------------
int SET_machine_kinematics(UF_MOM_id_t mom_id, MOM_machine_kins_p_t machine)
{
 int error;
 int i ;
 char *v[]={
	"mom_kin_machine_type",
	"mom_kin_track_center_of_ball",
	"mom_kin_wire_tilt_output_type",
	"mom_kin_clsf_generation",
	"mom_kin_coordinate_type",
	"mom_kin_linearization_flag",
	"mom_kin_machine_resolution",
	"mom_kin_tool_tracking_height",
	"mom_kin_5th_axis_inclination_to_4th",
	"mom_kin_linearization_tol",
	"mom_kin_gauge_to_pivot_x" ,
	"mom_kin_gauge_to_pivot_y",
	"mom_kin_gauge_to_pivot_z",
  "END" } ;
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "3_axis_mill";
          strcpy( machine->kin_machine_type , Str );
          break;
        case 1:
          if ( !Str ) Str = "T";
          strcpy( machine->kin_track_center_of_ball , Str );
          break;
        case 2:
          if ( !Str ) Str = "NONE";
          strcpy( machine->kin_wire_tilt_output_type , Str );
          break;
        case 3:
          if ( !Str ) Str = "F";
          strcpy( machine->kin_clsf_generation , Str );
          break;
        case 4:
          if ( !Str ) Str = "CARTESIAN";
          strcpy( machine->kin_coordinate_type , Str );
          break;
        case 5:
          if ( !Str ) Str = "F";
          strcpy( machine->kin_linearization_flag , Str );
          break;
        case 6:
          if ( !Str ) Str = "0.0001";
          machine->kin_machine_resolution = strtod(Str, NULL);
          break;
        case 7:
          if ( !Str ) Str = "0";
          machine->kin_tool_tracking_height = strtod(Str, NULL);
          break;
        case 8:
          if ( !Str ) Str = "90.0";
          machine->kin_5th_axis_inclination_to_4th = strtod(Str, NULL);
          break;
        case 9:
          if ( !Str ) Str = "0.0001";
          machine->kin_linearization_tol = strtod(Str, NULL);
          break;
        case 10:
          if ( !Str ) {
            error = UF_MOM_ask_string(mom_id, "kin_4th_to_tracking_point_x", &Str);
            if ( !Str || error ) Str = "0.0";
          }
          machine->kin_gauge_to_pivot[0] = strtod(Str, NULL);
          break;
        case 11:
          if ( !Str ) {
            error = UF_MOM_ask_string(mom_id, "kin_4th_to_tracking_point_y", &Str);
            if ( !Str || error ) Str = "0.0";
          }
          machine->kin_gauge_to_pivot[1] = strtod(Str, NULL);
          break;
        case 12:
          if ( !Str ) {
            error = UF_MOM_ask_string(mom_id, "kin_4th_to_tracking_point_z", &Str);
            if ( !Str || error ) Str = "0.0";
          }
          machine->kin_gauge_to_pivot[2] = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;

}

//----- (10005C20) --------------------------------------------------------
int SET_output_kinematics (UF_MOM_id_t mom_id ,MOM_output_kins_p_t output )
{
  int error ;
  int i ;
  char *v[]={
  "mom_kin_nurbs_output_type",
  "mom_kin_output_unit",
  "mom_kin_polar_radius_side",
  "mom_kin_read_ahead_next_motion",
  "mom_kin_pivot_gauge_offset",
  "mom_kin_rapid_feed_rate",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "NONE";
          strcpy( output->kin_nurbs_output_type , Str );
          break;
        case 1:
          if ( !Str ) Str = "IN";
          strcpy( output->kin_output_unit , Str );
          break;
        case 2:
          if ( !Str ) Str = "NONE";
          strcpy( output->kin_polar_radius_side , Str );
          break;
        case 3:
          if ( !Str ) Str = "F";
          strcpy( output->kin_read_ahead_next_motion , Str );
          break;
        case 4:
          if ( !Str ) Str = "0.0";
          output->kin_pivot_gauge_offset = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "400.00";
          output->kin_rapid_feed_rate = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (10005DD0) --------------------------------------------------------
int SET_arc_kinematics(UF_MOM_id_t mom_id, MOM_arc_kins_p_t arcs)
{
  int error;
  int i ;
  char *v[]={
  "mom_kin_arc_output_mode",
  "mom_kin_arc_valid_plane",
  "mom_kin_min_arc_radius",
  "mom_kin_max_arc_radius",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "FULL_CIRCLE";
          strcpy( arcs->kin_arc_output_mode , Str );
          break;
        case 1:
          if ( !Str ) Str = "XY";
          strcpy( arcs->kin_arc_valid_plane , Str );
          break;
        case 2:
          if ( !Str ) Str = "0.0001";
          arcs->kin_min_arc_radius = strtod(Str, NULL);
          break;
        case 3:
          if ( !Str ) Str = "9999.9999";
          arcs->kin_max_arc_radius = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (10005F10) --------------------------------------------------------
int SET_feed_kinematics(UF_MOM_id_t mom_id, MOM_feed_kins_p_t feeds)
{
  int error ;
  int i ;
  char *v[]={
  "mom_kin_max_fpm",
  "mom_kin_min_fpm",
  "mom_kin_max_fpr",
  "mom_kin_min_fpr",
  "mom_kin_max_frn",
  "mom_kin_min_frn",
  "mom_kin_max_dpm",
  "mom_kin_min_dpm",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "999.999";
          feeds->kin_max_fpm = strtod(Str, NULL);
          break;
        case 1:
          if ( !Str ) Str = "0.001";
          feeds->kin_min_fpm = strtod(Str, NULL);
          break;
        case 2:
          if ( !Str ) Str = "99.999";
          feeds->kin_max_fpr = strtod(Str, NULL);
          break;
        case 3:
          if ( !Str ) Str = "0.001";
          feeds->kin_min_fpr = strtod(Str, NULL);
          break;
        case 4:
          if ( !Str ) Str = "99999.999";
          feeds->kin_max_frn = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "0.001";
          feeds->kin_min_frn = strtod(Str, NULL);
          break;
        case 6:
          if ( !Str ) Str = "99.999";
          feeds->kin_max_dpm = strtod(Str, NULL);
          break;
        case 7:
          if ( !Str ) Str = "0.0";
          feeds->kin_min_dpm = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (100060E0) --------------------------------------------------------
int SET_4th_axis_kinematics (UF_MOM_id_t mom_id ,MOM_4th_axis_kins_p_t axis_4th )
{
  int error ;
  int i ;
  char *v[]={
  "mom_kin_4th_axis_plane",
  "mom_kin_4th_axis_direction",
  "mom_kin_4th_axis_rotation",
  "mom_kin_4th_axis_min_incr",
  "mom_kin_4th_axis_min_limit",
  "mom_kin_4th_axis_max_limit",
  "mom_kin_4th_axis_zero",
  "mom_kin_4th_axis_center_offset_x",
  "mom_kin_4th_axis_center_offset_y",
  "mom_kin_4th_axis_center_offset_z",
  "mom_kin_4th_axis_vector_i",
  "mom_kin_4th_axis_vector_j",
  "mom_kin_4th_axis_vector_k",
  "mom_kin_4th_axis_angles_a1",
  "mom_kin_4th_axis_angles_a2",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "YZ";
          strcpy( axis_4th->kin_4th_axis_plane , Str );
          break;
        case 1:
          if ( !Str ) Str = "MAGNITUDE_DETERMINES_DIRECTION";
          strcpy( axis_4th->kin_4th_axis_direction , Str );
          break;
        case 2:
          if ( !Str ) Str = "STANDARD";
          strcpy( axis_4th->kin_4th_axis_rotation , Str );
          break;
        case 3:
          if ( !Str ) Str = "0.001";
          axis_4th->kin_4th_axis_min_incr = strtod(Str, NULL);
          break;
        case 4:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_min_limit = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "360.000";
          axis_4th->kin_4th_axis_max_limit = strtod(Str, NULL);
          break;
        case 6:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_zero = strtod(Str, NULL);
          break;
        case 7:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_center_offset[0] = strtod(Str, NULL);
          break;
        case 8:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_center_offset[1] = strtod(Str, NULL);
          break;
        case 9:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_center_offset[2] = strtod(Str, NULL);
          break;
        case 10:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_vector[0] = strtod(Str, NULL);
          break;
        case 11:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_vector[1] = strtod(Str, NULL);
          break;
        case 12:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_vector[2] = strtod(Str, NULL);
          break;
        case 13:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_angles_a1 = strtod(Str, NULL);
          break;
        case 14:
          if ( !Str ) Str = "0.0";
          axis_4th->kin_4th_axis_angles_a2 = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (10006420) --------------------------------------------------------
int SET_5th_axis_kinematics (UF_MOM_id_t mom_id ,MOM_5th_axis_kins_p_t axis_5th )
{
  int error ;
  int i ;
  char *v[]={
  "mom_kin_5th_axis_plane",
  "mom_kin_5th_axis_direction",
  "mom_kin_5th_axis_rotation",
  "mom_kin_5th_axis_min_incr",
  "mom_kin_5th_axis_min_limit",
  "mom_kin_5th_axis_max_limit",
  "mom_kin_5th_axis_zero",
  "mom_kin_5th_axis_center_offset_x",
  "mom_kin_5th_axis_center_offset_y",
  "mom_kin_5th_axis_center_offset_z",
  "mom_kin_5th_axis_vector_i",
  "mom_kin_5th_axis_vector_j",
  "mom_kin_5th_axis_vector_k",
  "mom_kin_5th_axis_angles_a1",
  "mom_kin_5th_axis_angles_a2",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "YZ";
          strcpy( axis_5th->kin_5th_axis_plane , Str );
          break;
        case 1:
          if ( !Str ) Str = "MAGNITUDE_DETERMINES_DIRECTION";
          strcpy( axis_5th->kin_5th_axis_direction , Str );
          break;
        case 2:
          if ( !Str ) Str = "STANDARD";
          strcpy( axis_5th->kin_5th_axis_rotation , Str );
          break;
        case 3:
          if ( !Str ) Str = "0.001";
          axis_5th->kin_5th_axis_min_incr = strtod(Str, NULL);
          break;
        case 4:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_min_limit = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "360.000";
          axis_5th->kin_5th_axis_max_limit = strtod(Str, NULL);
          break;
        case 6:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_zero = strtod(Str, NULL);
          break;
        case 7:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_center_offset[0] = strtod(Str, NULL);
          break;
        case 8:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_center_offset[1] = strtod(Str, NULL);
          break;
        case 9:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_center_offset[2] = strtod(Str, NULL);
          break;
        case 10:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_vector[0] = strtod(Str, NULL);
          break;
        case 11:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_vector[1] = strtod(Str, NULL);
          break;
        case 12:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_vector[2] = strtod(Str, NULL);
          break;
        case 13:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_angles_a1 = strtod(Str, NULL);
          break;
        case 14:
          if ( !Str ) Str = "0.0";
          axis_5th->kin_5th_axis_angles_a2 = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (10006760) --------------------------------------------------------
int SET_head_kinematics (UF_MOM_id_t mom_id , MOM_head_kins_p_t head )
{
  int error ;
  int i ;
  char *v[]={
  "mom_kin_independent_head",
  "mom_kin_ind_to_dependent_head_x",
  "mom_kin_ind_to_dependent_head_z",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "FRONT";
          strcpy( head->kin_independent_head , Str );
          break;
        case 1:
          if ( !Str ) Str = "0.0";
          head->kin_ind_to_dependent_head_x = strtod(Str, NULL);
          break;
        case 2:
          if ( !Str ) Str = "0.0";
          head->kin_ind_to_dependent_head_z = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (10006960) --------------------------------------------------------
int SET_holder_kinematics (UF_MOM_id_t mom_id ,MOM_holder_kins_p_t holder )
{
  int error ;
  int i ;
  char *v[]={
  "mom_kin_holder1_orientation",
  "mom_kin_holder1_orientation",
  "mom_kin_holder2_orientation",
  "mom_kin_holder3_orientation",
  "mom_kin_holder4_orientation",
  "mom_kin_holder5_orientation",
  "mom_kin_holder6_orientation",
  "mom_kin_holder1_offset_x",
  "mom_kin_holder1_offset_y",
  "mom_kin_holder1_offset_z",
  "mom_kin_holder2_offset_x",
  "mom_kin_holder2_offset_y",
  "mom_kin_holder2_offset_z",
  "mom_kin_holder3_offset_x",
  "mom_kin_holder3_offset_y",
  "mom_kin_holder3_offset_z",
  "mom_kin_holder4_offset_x",
  "mom_kin_holder4_offset_y",
  "mom_kin_holder4_offset_z",
  "mom_kin_holder5_offset_x",
  "mom_kin_holder5_offset_y",
  "mom_kin_holder5_offset_z",
  "mom_kin_holder6_offset_x",
  "mom_kin_holder6_offset_y",
  "mom_kin_holder6_offset_z",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "POSZ";
          strcpy( holder->kin_holder1_orientation , Str );
          break;
        case 1:
          if ( !Str ) Str = "POSZ";
          strcpy( holder->kin_holder2_orientation , Str );
          break;
        case 2:
          if ( !Str ) Str = "POSZ";
          strcpy( holder->kin_holder3_orientation , Str );
          break;
        case 3:
          if ( !Str ) Str = "POSZ";
          strcpy( holder->kin_holder4_orientation , Str );
          break;
        case 4:
          if ( !Str ) Str = "POSZ";
          strcpy( holder->kin_holder5_orientation , Str );
          break;
        case 5:
          if ( !Str ) Str = "POSZ";
          strcpy( holder->kin_holder6_orientation , Str );
          break;
        case 6:
          if ( !Str ) Str = "0.0";
          holder->kin_holder1_offset[0] = strtod(Str, NULL);
          break;
        case 7:
          if ( !Str ) Str = "0.0";
          holder->kin_holder1_offset[1] = strtod(Str, NULL);
          break;
        case 8:
          if ( !Str ) Str = "0.0";
          holder->kin_holder1_offset[2] = strtod(Str, NULL);
          break;
        case 9:
          if ( !Str ) Str = "0.0";
          holder->kin_holder2_offset[0] = strtod(Str, NULL);
          break;
        case 10:
          if ( !Str ) Str = "0.0";
          holder->kin_holder2_offset[1] = strtod(Str, NULL);
          break;
        case 11:
          if ( !Str ) Str = "0.0";
          holder->kin_holder2_offset[2] = strtod(Str, NULL);
          break;
        case 12:
          if ( !Str ) Str = "0.0";
          holder->kin_holder3_offset[0] = strtod(Str, NULL);
          break;
        case 13:
          if ( !Str ) Str = "0.0";
          holder->kin_holder3_offset[1] = strtod(Str, NULL);
          break;
        case 14:
          if ( !Str ) Str = "0.0";
          holder->kin_holder3_offset[2] = strtod(Str, NULL);
          break;
        case 15:
          if ( !Str ) Str = "0.0";
          holder->kin_holder4_offset[0] = strtod(Str, NULL);
          break;
        case 16:
          if ( !Str ) Str = "0.0";
          holder->kin_holder4_offset[1] = strtod(Str, NULL);
          break;
        case 17:
          if ( !Str ) Str = "0.0";
          holder->kin_holder4_offset[2] = strtod(Str, NULL);
          break;
        case 18:
          if ( !Str ) Str = "0.0";
          holder->kin_holder5_offset[0] = strtod(Str, NULL);
          break;
        case 19:
          if ( !Str ) Str = "0.0";
          holder->kin_holder5_offset[1] = strtod(Str, NULL);
          break;
        case 20:
          if ( !Str ) Str = "0.0";
          holder->kin_holder5_offset[2] = strtod(Str, NULL);
          break;
        case 21:
          if ( !Str ) Str = "0.0";
          holder->kin_holder6_offset[0] = strtod(Str, NULL);
          break;
        case 22:
          if ( !Str ) Str = "0.0";
          holder->kin_holder6_offset[1] = strtod(Str, NULL);
          break;
        case 23:
          if ( !Str ) Str = "0.0";
          holder->kin_holder6_offset[2] = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (10007240) --------------------------------------------------------
int SET_msys_data (UF_MOM_id_t mom_id ,MOM_operdata_p_t operdata )
{
  int error ;
  int i ;
  char *v[]={
  "mom_msys_origin_x",
  "mom_msys_origin_y"
  "mom_msys_origin_z"
  "mom_msys_x_axis_i"
  "mom_msys_x_axis_j"
  "mom_msys_x_axis_k"
  "mom_msys_y_axis_i"
  "mom_msys_y_axis_j"
  "mom_msys_y_axis_k"
  "mom_msys_z_axis_i"
  "mom_msys_z_axis_j"
  "mom_msys_z_axis_k"
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "0.0";
          operdata->msys_origin[0] = strtod(Str, NULL);
          break;
        case 1:
          if ( !Str ) Str = "0.0";
          operdata->msys_origin[1] = strtod(Str, NULL);
          break;
        case 2:
          if ( !Str ) Str = "0.0";
          operdata->msys_origin[2] = strtod(Str, NULL);
          break;
        case 3:
          if ( !Str ) Str = "1.0";
          operdata->msys_x_axis[0] = strtod(Str, NULL);
          break;
        case 4:
          if ( !Str ) Str = "0.0";
          operdata->msys_x_axis[1] = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "0.0";
          operdata->msys_x_axis[2] = strtod(Str, NULL);
          break;
        case 6:
          if ( !Str ) Str = "0.0";
          operdata->msys_y_axis[0] = strtod(Str, NULL);
          break;
        case 7:
          if ( !Str ) Str = "1.0";
          operdata->msys_y_axis[1] = strtod(Str, NULL);
          break;
        case 8:
          if ( !Str ) Str = "0.0";
          operdata->msys_y_axis[2] = strtod(Str, NULL);
          break;
        case 9:
          if ( !Str ) Str = "0.0";
          operdata->msys_z_axis[0] = strtod(Str, NULL);
          break;
        case 10:
          if ( !Str ) Str = "0.0";
          operdata->msys_z_axis[1] = strtod(Str, NULL);
          break;
        case 11:
          if ( !Str ) Str = "1.0";
          operdata->msys_z_axis[2] = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (100074C0) --------------------------------------------------------
int SET_mtsys_data (UF_MOM_id_t mom_id ,MOM_operdata_p_t operdata )
{
  int error ;
  int i ;
  char *v[]={
  "mom_mtsys_origin_x",
  "mom_mtsys_origin_y"
  "mom_mtsys_origin_z"
  "mom_mtsys_x_axis_i"
  "mom_mtsys_x_axis_j"
  "mom_mtsys_x_axis_k"
  "mom_mtsys_y_axis_i"
  "mom_mtsys_y_axis_j"
  "mom_mtsys_y_axis_k"
  "mom_mtsys_z_axis_i"
  "mom_mtsys_z_axis_j"
  "mom_mtsys_z_axis_k"
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_origin[0] = strtod(Str, NULL);
          break;
        case 1:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_origin[1] = strtod(Str, NULL);
          break;
        case 2:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_origin[2] = strtod(Str, NULL);
          break;
        case 3:
          if ( !Str ) Str = "1.0";
          operdata->mtsys_x_axis[0] = strtod(Str, NULL);
          break;
        case 4:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_x_axis[1] = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_x_axis[2] = strtod(Str, NULL);
          break;
        case 6:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_y_axis[0] = strtod(Str, NULL);
          break;
        case 7:
          if ( !Str ) Str = "1.0";
          operdata->mtsys_y_axis[1] = strtod(Str, NULL);
          break;
        case 8:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_y_axis[2] = strtod(Str, NULL);
          break;
        case 9:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_z_axis[0] = strtod(Str, NULL);
          break;
        case 10:
          if ( !Str ) Str = "0.0";
          operdata->mtsys_z_axis[1] = strtod(Str, NULL);
          break;
        case 11:
          if ( !Str ) Str = "1.0";
          operdata->mtsys_z_axis[2] = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (10007760) --------------------------------------------------------
int SET_operation_data (UF_MOM_id_t mom_id ,MOM_operdata_p_t operdata )
{
  int error ;
  int i ;
  char *v[]={
  "mom_origin_x",
  "mom_origin_y"
  "mom_origin_z"
  "mom_translate_x"
  "mom_translate_y"
  "mom_translate_z"
  "mom_tool_type"
  "mom_tool_z_offset"
  "mom_tool_corner1_radius"
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "0.0";
          operdata->origin[0] = strtod(Str, NULL);
          break;
        case 1:
          if ( !Str ) Str = "0.0";
          operdata->origin[1] = strtod(Str, NULL);
          break;
        case 2:
          if ( !Str ) Str = "0.0";
          operdata->origin[2] = strtod(Str, NULL);
          break;
        case 3:
          if ( !Str ) Str = "1.0";
          operdata->translate[0] = strtod(Str, NULL);
          break;
        case 4:
          if ( !Str ) Str = "0.0";
          operdata->translate[1] = strtod(Str, NULL);
          break;
        case 5:
          if ( !Str ) Str = "0.0";
          operdata->translate[2] = strtod(Str, NULL);
          break;
        case 6:
          if ( !Str ) Str = "MILL";
          strcpy( operdata->tool_type , Str );
          break;
        case 7:
          if ( !Str ) Str = "1.0";
          operdata->tool_z_offset = strtod(Str, NULL);
          break;
        case 8:
          if ( !Str ) Str = "0.0";
          operdata->tool_corner1_radius = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

//----- (10006870) --------------------------------------------------------
int SET_time_kinematics(UF_MOM_id_t mom_id ,MOM_time_kins_p_t time)
{
  int error ;
  int i ;
  char *v[]={
  "mom_kin_tool_change_time",
  "mom_kin_clamp_time" ,
  "mom_kin_flush_time",
  "END"
  };
  char S[132];
  const char *Str=&S[0];

  i=0;
  while (v[i]!="END") {
	  error=UF_MOM_ask_string(mom_id, v[i] + 4, &Str);
	  switch(i){

        case 0:
          if ( !Str ) Str = "0.5";
          time->kin_tool_change_time = strtod(Str, NULL);
          break;
        case 1:
          if ( !Str ) Str = "0.5";
          time->kin_clamp_time = strtod(Str, NULL);
          break;
        case 2:
          if ( !Str ) Str = "3.0";
          time->kin_flush_time = strtod(Str, NULL);
          break;
        default:
          break;

 	  }
	  i++;
  }
  return error;
}

/****************************************************************************/

#define is_5_axis_dual_table 2
#define is_5_axis_dual_head 1
#define is_5_axis_head_table 0

typedef struct MOM_POST_dh_kinematics_s
{
	int mom_kin_machine_type ; // is_5_axis_dual_table is_5_axis_dual_head is_5_axis_head_table
	double resl ;
	double mom_translate[3];
	double mom_origin[3];
	double setoff[3];
	int track_ball ;
	double ball_center ;
	double primary_min_limit ;
	double primary_max_limit ;
	double secondary_min_limit ;
	double secondary_max_limit ;
	double tool_z_offset ;
} MOM_POST_dh_kinematics_t, *MOM_POST_dh_kinematics_p_t;

int MOM_POST_dh_setup_vector_conversion(
         double mtcsys[12], double mcsys[12], double primary_machine_center[3], double kin_4th_axis_vector[3],
         double secondary_machine_center[3], double kin_5th_axis_vector[3],
         double tool_machine_center[3], double tool_axis[3], MOM_POST_dh_kinematics_p_t data_p)
{
	
	
	return 0 ;
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

  /* Adding MOM_load_kinematics TCL extension */
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_load_kinematics", mom_load_kinematics)); //

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
} /* mom_load_kinematics */
