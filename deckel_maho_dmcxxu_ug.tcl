
#=============================================================
proc PB_start_of_program { } {
#=============================================================

   if [llength [info commands PB_CMD_kin_start_of_program] ] {
      PB_CMD_kin_start_of_program
   }

   PB_CMD_init_kinematics
   PB_CMD_nurbs_initialize
   MOM_set_seq_off
   MOM_do_template start_of_program_1
   MOM_do_template blank_form_1
   MOM_do_template blank_form_2
}


#=============================================================
proc PB_CMD_before_motion { } {
#=============================================================
global mom_cutcom_status cutter_comp

if {![info exist mom_cutcom_status]} {
    set cutter_comp "R0"
} elseif {$mom_cutcom_status == "OFF"} {
    set cutter_comp "R0"
} elseif {$mom_cutcom_status == "LEFT"} {
    set cutter_comp "RL"
} elseif {$mom_cutcom_status == "OFF"} {
    set cutter_comp "RR"
}

PB_CMD_dmu_before_motion
}


#=============================================================
proc PB_CMD_init_kinematics { } {
#=============================================================
# Disable new IKS for dual-head mill
 
global mom_kin_iks_usage
global mom_kin_machine_type
global mom_sys_ugpadvkins_used
 
if { $mom_sys_ugpadvkins_used == 0 } {
   if [string match "5_axis_dual_head" $mom_kin_machine_type] {
      if { $mom_kin_iks_usage == 1 } {
         PB_CMD_revert_dual_head_kin_vars
         set mom_kin_iks_usage 0
      }
   }
   set mom_sys_ugpadvkins_used 1
}
 
 
#-------------------------------------------------------------------------------
#
# This procedure will convert a standard five axis head table machine into a
# DECKEL MAHO DMC Head Table 5 Axis machine.  You will need to place this custom
# command in the Start of Program event marker.  You will also need to add the
# following line to the MOM_before_motion custom command (without the "#").

# PB_CMD_dmu_before_motion

# Additionally, if you need the conversational codes, make a new post and set the
# controller to the "Heidenhain Conversational".  This will set you up with all
# of the formats.
#
# Note that this post will do all of the mapping in the head.  If your control
# does the transformation of the tool lengths, then you will need to set your 
# tool length offsets to zero.

# You will need to purchase the Advanced Kinematic License for this post to work.

#
# Primary Axis - B Axis 
#    This is the Head with the rotary Axis inclined at approximately 45 degrees
#    to the Z or Y axis of MCS
#
# Secondary Axis - C Axis
#    This is the Table of the machine 
#
# Setting of Kinematic Variables defining the machine tool
#
  global mom_kin_machine_resolution
  global mom_kin_machine_type
  global mom_kin_4th_axis_plane
  global mom_kin_4th_axis_vector
  global mom_kin_4th_axis_angles
  global mom_kin_4th_axis_min_incr 
  global mom_kin_4th_axis_min_limit 
  global mom_kin_4th_axis_max_limit 
  global mom_kin_4th_axis_direction 
  global mom_kin_4th_axis_rotation 
  global mom_kin_4th_axis_zero 
  global mom_kin_4th_axis_center_offset 
  global mom_kin_pivot_gauge_offset 
#  global mom_kin_4th_to_tracking_point
  global mom_kin_gauge_to_pivot

  global mom_kin_5th_axis_plane 
  global mom_kin_5th_axis_vector 
  global mom_kin_5th_axis_angles 
  global mom_kin_5th_axis_min_incr 
  global mom_kin_5th_axis_min_limit 
  global mom_kin_5th_axis_max_limit 
  global mom_kin_5th_axis_direction 
  global mom_kin_5th_axis_rotation 
  global mom_kin_5th_axis_inclination_to_4th 
  global mom_kin_5th_axis_zero 
  global mom_kin_5th_axis_center_offset

  global mom_kin_linearization_tol 
  global mom_kin_linearization_flag 
  global mom_kin_independent_head 
  global mom_kin_nurbs_output_type 
  global mom_kin_output_unit 

  global mom_kin_4th_axis_center_offset_x
  global mom_kin_4th_axis_center_offset_y
  global mom_kin_4th_axis_center_offset_z
  global mom_kin_4th_axis_angles_a1
  global mom_kin_4th_axis_angles_a2
  global mom_kin_4th_axis_vector_i
  global mom_kin_4th_axis_vector_j
  global mom_kin_4th_axis_vector_k
  global mom_kin_track_center_of_ball
  global mom_kin_read_ahead_next_motion
  
  global leader_4th leader_5th
  global tcl_platform

  global first_move_after_MCSROT MCSROT_flag 
  global is_MCSROT_matrix_set first_motion_flag          

  set first_move_after_MCSROT    0
  set MCSROT_flag                0
  set is_MCSROT_matrix_set       0
  set first_motion_flag          0

  if {$tcl_platform(os) == "HP-UX"} {
      set plat "hpp"
      set suffix "sl"
  } elseif {$tcl_platform(os) == "windows" ||  $tcl_platform(os) == "Windows NT"} {
      set plat "wnt"
      set suffix "dll"
  } else {
      set plat "sun"
      set suffix "so"
  }

  set uf_library "ugpadvkins.$suffix"

  set mom_kin_read_ahead_next_motion             TRUE
  set mom_kin_machine_resolution                 0.000001
  set mom_kin_machine_type                       5_axis_head_table
  set mom_kin_track_center_of_ball               FALSE

  set mom_kin_4th_axis_plane                     NONE
  set mom_kin_4th_axis_vector(0)                 0.0
  set mom_kin_4th_axis_vector(1)                 1.0
  set mom_kin_4th_axis_vector(2)                 1.0
#  set mom_kin_4th_axis_angles(0)                0.0
#  set mom_kin_4th_axis_angles(1)                0.0
  set mom_kin_4th_axis_min_incr                  0.001
  set mom_kin_4th_axis_min_limit                 0.0
  set mom_kin_4th_axis_max_limit                 180.0
  set mom_kin_4th_axis_direction                 MAGNITUDE_DETERMINES_DIRECTION
#  set mom_kin_4th_axis_direction                 SIGN_DETERMINES_DIRECTION
  set mom_kin_4th_axis_rotation                  standard
  set mom_kin_4th_axis_zero                      0
  set mom_kin_4th_axis_center_offset(0)          0.0
  set mom_kin_4th_axis_center_offset(1)          0.0
  set mom_kin_4th_axis_center_offset(2)          0.0

  set mom_kin_pivot_gauge_offset                 0.0
  set mom_kin_gauge_to_pivot(0)                  0.0
  set mom_kin_gauge_to_pivot(1)                  99.663
  set mom_kin_gauge_to_pivot(2)                  99.663

#  set mom_kin_4th_to_tracking_point(0)           -0.023
#  set mom_kin_4th_to_tracking_point(1)           99.983
#  set mom_kin_4th_to_tracking_point(2)           99.990

  set mom_kin_5th_axis_plane                     NONE
  set mom_kin_5th_axis_vector(0)                 0.0000
  set mom_kin_5th_axis_vector(1)                 0.0000
  set mom_kin_5th_axis_vector(2)                 1.0000
#  set mom_kin_5th_axis_angles(0)                 0.0000
#  set mom_kin_5th_axis_angles(1)                 0.0000
  set mom_kin_5th_axis_min_incr                  0.001
  set mom_kin_5th_axis_min_limit                -9999.999
  set mom_kin_5th_axis_max_limit                 9999.999
  set mom_kin_5th_axis_direction                 MAGNITUDE_DETERMINES_DIRECTION
#  set mom_kin_5th_axis_direction                 SIGN_DETERMINES_DIRECTION
  set mom_kin_5th_axis_rotation                  standard
  set mom_kin_5th_axis_zero                      0
  set mom_kin_5th_axis_center_offset(0)          0.0
  set mom_kin_5th_axis_center_offset(1)          0.0
  set mom_kin_5th_axis_center_offset(2)          0.0

  set mom_kin_linearization_tol                  0.001
  set mom_kin_linearization_flag                 TRUE
  set mom_kin_independent_head                   NONE


# The globals below are to enable ufunc to read the kinematics
# value of center_offset_x/y/z is the same with  above 
# mom_kin_4th_axis_center_offset(i), tcl/ufun can not read array


  global mom_kin_5th_axis_center_offset_x
  global mom_kin_5th_axis_center_offset_y
  global mom_kin_5th_axis_center_offset_z
  global mom_kin_5th_axis_angles_a1
  global mom_kin_5th_axis_angles_a2
  global mom_kin_5th_axis_vector_i
  global mom_kin_5th_axis_vector_j
  global mom_kin_5th_axis_vector_k
  global mom_kin_gauge_to_pivot_x
  global mom_kin_gauge_to_pivot_y
  global mom_kin_gauge_to_pivot_z
  
  set mom_kin_4th_axis_center_offset_x $mom_kin_4th_axis_center_offset(0)
  set mom_kin_4th_axis_center_offset_y $mom_kin_4th_axis_center_offset(1) 
  set mom_kin_4th_axis_center_offset_z $mom_kin_4th_axis_center_offset(2)

  set mom_kin_5th_axis_center_offset_x $mom_kin_5th_axis_center_offset(0)
  set mom_kin_5th_axis_center_offset_y $mom_kin_5th_axis_center_offset(1) 
  set mom_kin_5th_axis_center_offset_z $mom_kin_5th_axis_center_offset(2)

  set mom_kin_4th_axis_vector_i $mom_kin_4th_axis_vector(0)
  set mom_kin_4th_axis_vector_j $mom_kin_4th_axis_vector(1)
  set mom_kin_4th_axis_vector_k $mom_kin_4th_axis_vector(2)

  set mom_kin_5th_axis_vector_i $mom_kin_5th_axis_vector(0)
  set mom_kin_5th_axis_vector_j $mom_kin_5th_axis_vector(1)
  set mom_kin_5th_axis_vector_k $mom_kin_5th_axis_vector(2)

  set mom_kin_gauge_to_pivot_x $mom_kin_gauge_to_pivot(0)
  set mom_kin_gauge_to_pivot_y $mom_kin_gauge_to_pivot(1)
  set mom_kin_gauge_to_pivot_z $mom_kin_gauge_to_pivot(2)

  switch $mom_kin_4th_axis_plane {
    "XY" -
    "YX"
         {
           set mom_kin_4th_axis_vector_i                  0.0
           set mom_kin_4th_axis_vector_j                  0.0
           set mom_kin_4th_axis_vector_k                  1.0
         }
    "YZ" -
    "ZY"
         {
           set mom_kin_4th_axis_vector_i                  1.0
           set mom_kin_4th_axis_vector_j                  0.0
           set mom_kin_4th_axis_vector_k                  0.0
         }
    "ZX" -
    "XZ"
         {
           set mom_kin_4th_axis_vector_i                  0.0
           set mom_kin_4th_axis_vector_j                  1.0
           set mom_kin_4th_axis_vector_k                  0.0
         }
  default
         {
           if {[info exists mom_kin_4th_axis_vector]} {
               set mom_kin_4th_axis_vector_i $mom_kin_4th_axis_vector(0)
               set mom_kin_4th_axis_vector_j $mom_kin_4th_axis_vector(1)
               set mom_kin_4th_axis_vector_k $mom_kin_4th_axis_vector(2)
           } elseif {[info exists mom_kin_4th_axis_angles]} {
               set mom_kin_4th_axis_angles_a1 $mom_kin_4th_axis_angles(0)
               set mom_kin_4th_axis_angles_a2 $mom_kin_4th_axis_angles(1)
           } else {
               set mom_kin_4th_axis_vector_i                  0.0
               set mom_kin_4th_axis_vector_j                  0.0
               set mom_kin_4th_axis_vector_k                  0.0
               set mom_kin_4th_axis_angles_a1                 0.0
               set mom_kin_4th_axis_angles_a2                 0.0
               MOM_output_to_listing_device  "ERROR: Machine's 4th axis Kinematics are INCONSISTANT"
           }
         }
  }

  switch $mom_kin_5th_axis_plane {
    "XY" -
    "YX"
         {
           set mom_kin_5th_axis_vector_i                  0.0
           set mom_kin_5th_axis_vector_j                  0.0
           set mom_kin_5th_axis_vector_k                  1.0
         }
    "YZ" -
    "ZY"
         {
           set mom_kin_5th_axis_vector_i                  1.0
           set mom_kin_5th_axis_vector_j                  0.0
           set mom_kin_5th_axis_vector_k                  0.0
         }
    "ZX" -
    "XZ"
         {
           set mom_kin_5th_axis_vector_i                  0.0
           set mom_kin_5th_axis_vector_j                  1.0
           set mom_kin_5th_axis_vector_k                  0.0
         }
  default
         {
           if {[info exists mom_kin_5th_axis_vector]} {
               set mom_kin_5th_axis_vector_i $mom_kin_5th_axis_vector(0)
               set mom_kin_5th_axis_vector_j $mom_kin_5th_axis_vector(1)
               set mom_kin_5th_axis_vector_k $mom_kin_5th_axis_vector(2)
           } elseif {[info exists mom_kin_5th_axis_angles]} {
               set mom_kin_5th_axis_angles_a1 $mom_kin_5th_axis_angles(0)
               set mom_kin_5th_axis_angles_a2 $mom_kin_5th_axis_angles(1)
           } else {
               set mom_kin_5th_axis_vector_i                  0.0
               set mom_kin_5th_axis_vector_j                  0.0
               set mom_kin_5th_axis_vector_k                  0.0
               set mom_kin_5th_axis_angles_a1                 0.0
               set mom_kin_5th_axis_angles_a2                 0.0
               MOM_output_to_listing_device  "ERROR: Machine's 5th axis Kinematics are INCONSISTANT"
           }
         }
  }

  MOM_run_user_function [MOM_ask_env_var UGII_CAM_AUXILIARY_DIR]$uf_library ufusr
 # MOM_run_user_function $uf_library ufusr
  MOM_load_kinematics
}

#=============================================================
proc PB_CMD_dmu_before_motion { } {
#=============================================================
#-------------------------------------------------------------------------------

  global mom_mcs_goto
  global mom_tool_axis
  global mom_alt_pos
  global mom_pos
  global mom_out_angle_pos
  global mom_motion_type
  global mom_motion_event
  global mom_nxt_motion_event

  FEEDRATE_SET
  SET_MCS_MATRIX

  if {$mom_motion_event == "circular_move"} {
      CONVERT_ARC_DATA
  }

  if {$mom_motion_type != "CYCLE"} {
      CONVERT_POINT mom_mcs_goto  mom_tool_axis  mom_pos  mom_alt_pos  mom_out_angle_pos
  } else {
      CONVERT_CYCLES_DATA
  }
}


#-------------------------------------------------------------------------------
proc SET_MCS_MATRIX {  } {
#-------------------------------------------------------------------------------

  global mom_operation_type
  global mom_motion_type
  global mom_tool_axis
  global mom_prev_tool_axis

  global is_MCSROT_matrix_set
  global MCSROT_flag
  global trans_axis 
  global trans_angle
  global first_motion_flag
  global first_move_after_MCSROT

# Check if the MCSROT is programmed, return if not

  if {$MCSROT_flag == 0} { return }

# Check if the initial_move or first_move have been triggered, if not return

  if {$first_motion_flag == 0} { return }

# Check if the operation type is compatible for MCS rotation

  if {$mom_operation_type == "VAR_CONTOUR"} {
      MOM_output_to_listing_device  "ERROR: ***** INVALID OPERATION TYPE FOR MCS ROTATION *****"
      MOM_output_to_listing_device  "OPERATION - $mom_path_name"
      MOM_output_to_listing_device  "MESSAGE: Variable Axis Contouring type of operations are invalid"
      MOM_output_to_listing_device  "         when in Coordinate System Rotation mode"
      return
  }

# Check if the rotation matrix has been set up, if yes do not do anything.

  if {$is_MCSROT_matrix_set == 0} {
      SET_MCS_ROTATION_ANGLES
      set deg2rad [expr asin(1.0)/90.0]
      MOM_rotate_mach_csys $trans_axis(0) $trans_angle(0)  $trans_axis(1) $trans_angle(1)  $trans_axis(2) $trans_angle(2)]
      set first_move_after_MCSROT 1
      MOM_suppress always K
      set is_MCSROT_matrix_set 1
      OUTPUT_MCS_ROTATION
  }
}



#-------------------------------------------------------------------------------
proc SET_MCS_ROTATION_ANGLES {  } {
#-------------------------------------------------------------------------------

  global mom_record_fields
  global mom_field_count
  global mom_tool_axis
  global mom_origin
  global mom_translate

  global mom_translate_x mom_translate_y mom_translate_z
  global mom_origin_x mom_origin_y mom_origin_z
  global MCSROT_flag
  global first_move_after_MCSROT
  global trans_axis 
  global trans_angle

  set MCSROT_flag 1

  switch $mom_record_fields(1) {
  "AUTO"
    {
      set I $mom_tool_axis(0)
      set J $mom_tool_axis(1)
      set K $mom_tool_axis(2)
      set rad2deg [expr 90.0/asin(1.0)]
      set reslt_JK [expr sqrt(pow($J,2)+pow($K,2))]

      set trans_axis(0) "AAXIS"
      set trans_axis(1) "BAXIS"
      set trans_axis(2) "0"
      set trans_angle(0) [expr -1.0*atan2($J,$K)*$rad2deg]
      set trans_angle(1) [expr atan2($I,$reslt_JK)*$rad2deg]
      set trans_angle(2) 0.0
    }
  default
    { 
      if {$mom_field_count > 7 ||  $mom_field_count == 1 ||  [expr fmod($mom_field_count,2)] == 0.0 } {
          MOM_output_to_listing_device  "ERROR: Invalid number of arguments for MCSROT"
          MOM_output_to_listing_device  "ACTION: Aborting Coordinate System Rotation"
          set MCSROT_flag 0
          return
      }

      set j 0
      for {set i 1} {$i < 7} {incr i 2} {
           if {[info exists mom_record_fields($i)]} {
               set trans_axis($j) $mom_record_fields($i)
           } else { set trans_axis($j) 0 }
 
           set k [expr $i+1]
           if {[info exists mom_record_fields($k)]} {
               set trans_angle($j) $mom_record_fields($k)
           } else { set trans_angle($j) 0 }
           incr j
      }
    }
  }

# Prepare the variables for the UFunc library to access mom variables
# The code below is to facilitate the USER FUNCTION extension to read mom vars

  if {[info exists mom_origin]} {
      set mom_origin_x $mom_origin(0)
      set mom_origin_y $mom_origin(1)
      set mom_origin_z $mom_origin(2)
  }

  if {[info exists mom_translate]} {
      set mom_translate_x $mom_translate(0)
      set mom_translate_y $mom_translate(1)
      set mom_translate_z $mom_translate(2)
  }
}

#-------------------------------------------------------------------------------
proc OUTPUT_MCS_ROTATION {  } {
#-------------------------------------------------------------------------------

  global MCSROT_axis_A 
  global MCSROT_axis_B 
  global MCSROT_axis_C
  global is_MCSROT_matrix_set
  global trans_axis trans_angle

  if {$is_MCSROT_matrix_set} {
      for {set i 0} {$i < 3} {incr i} {
        switch $trans_axis($i) {
          "AAXIS" {set MCSROT_axis_A $trans_angle($i)}
          "BAXIS" {set MCSROT_axis_B $trans_angle($i)}
          "CAXIS" {set MCSROT_axis_C $trans_angle($i)}
        }
      }
      MOM_do_template rotate_mcs
  }
#
# The following blocks and addresses must be added to the def file
#

# ADDRESS A5  {
#              FORMAT Coordinate
#              ZERO_FORMAT zero_coord
#              FORCE  always
#              LEADER "A5="
#            }
# ADDRESS B5  {
#              FORMAT Coordinate
#              ZERO_FORMAT zero_coord
#              FORCE  always
#              LEADER "B5="
#            }
# ADDRESS C5  {
#              FORMAT Coordinate
#              ZERO_FORMAT zero_coord
#              FORCE  always
#              LEADER "C5="
#            }
#BLOCK_TEMPLATE rotate_mcs {
#      G[$mom_sys_mcs_rotation_code]
#      L1[1]
#      A5[$MCSROT_axis_A]\opt
#      B5[$MCSROT_axis_B]\opt
#      C5[$MCSROT_axis_C]\opt
#      }
}

proc CONVERT_ARC_DATA {  } {
global mom_arc_center
  global mom_prev_mcs_goto
  global mom_tool_axis
  global mom_pos_arc_center
  global mom_prev_pos
  global mom_prev_alt_pos

# Set the dummy variables

  set dummy_out_angle_pos(0) 0.0
  set dummy_out_angle_pos(1) 0.0
  set dummy_alt_pos(0) 0.0
  set dummy_alt_pos(1) 0.0
  set dummy_alt_pos(2) 0.0
  set dummy_alt_pos(3) 0.0
  set dummy_alt_pos(4) 0.0

# Convert arc center point

  CONVERT_POINT mom_arc_center  mom_tool_axis  mom_pos_arc_center  dummy_alt_pos  dummy_out_angle_pos

# Convert previous mcs goto point

  CONVERT_POINT mom_prev_mcs_goto  mom_tool_axis  mom_prev_pos  mom_prev_alt_pos  dummy_out_angle_pos
}

#-------------------------------------------------------------------------------
proc CONVERT_POINT { mcs_goto tool_axis pos alt_pos out_angle_pos } {
#-------------------------------------------------------------------------------

    upvar $mcs_goto mom_mcs_goto
    upvar $tool_axis mom_tool_axis
    upvar $pos mom_pos
    upvar $alt_pos mom_alt_pos
    upvar $out_angle_pos mom_out_angle_pos

    global mom_pos_x mom_pos_y mom_pos_z
    global mom_pos_a1 mom_pos_a2
    global mom_mcs_goto_x mom_mcs_goto_y mom_mcs_goto_z
    global mom_tool_axis_i mom_tool_axis_j mom_tool_axis_k
    global mom_alt_pos_x mom_alt_pos_y mom_alt_pos_z
    global mom_alt_pos_a1 mom_alt_pos_a2
    global mom_kin_5th_axis_min_limit
    global mom_kin_5th_axis_max_limit
    global first_move_after_MCSROT
    global MCSROT_flag

    global c_value
    global theta_value
    global prev_c_value
    global prev_theta_value

    set mom_mcs_goto_x $mom_mcs_goto(0)
    set mom_mcs_goto_y $mom_mcs_goto(1)
    set mom_mcs_goto_z $mom_mcs_goto(2)

    set mom_tool_axis_i $mom_tool_axis(0)
    set mom_tool_axis_j $mom_tool_axis(1)
    set mom_tool_axis_k $mom_tool_axis(2)

# Call to userfuntion routine to convert point

    if {$first_move_after_MCSROT == 1 && $MCSROT_flag == 1} {
        MOM_map_to_rotated_csys
    } else {
        MOM_convert_point
    }

#SWS
    while {$mom_pos_a1 < 0.0} {set mom_pos_a1 [expr $mom_pos_a1+360.0]}
    while {$mom_pos_a1 >= 360.0} {set mom_pos_a1 [expr $mom_pos_a1-360.0]}
    while {$mom_pos_a2 < 0.0} {set mom_pos_a2 [expr $mom_pos_a2+360.0]}
    while {$mom_pos_a2 >= 360.0} {set mom_pos_a2 [expr $mom_pos_a2-360.0]}
    while {$mom_alt_pos_a1 < 0.0} {set mom_alt_pos_a1 [expr $mom_alt_pos_a1+360.0]}
    while {$mom_alt_pos_a1 >= 360.0} {set mom_alt_pos_a1 [expr $mom_alt_pos_a1-360.0]}
    while {$mom_alt_pos_a2 < 0.0} {set mom_alt_pos_a2 [expr $mom_alt_pos_a2+360.0]}
    while {$mom_alt_pos_a2 >= 360.0} {set mom_alt_pos_a2 [expr $mom_alt_pos_a2-360.0]}
#SWS

# say "[format %.3f $mom_tool_axis_i] [format %.3f $mom_tool_axis_j] [format %.3f $mom_tool_axis_k]"
# Storing the converted point back in mom_pos variables
# Check if the 5th axis is out of limit for DMUxxV case for Neil Carter

    set rot_5th_axis [format "%-.7f" $mom_pos_a2]

    if {[EQ_is_lt $rot_5th_axis $mom_kin_5th_axis_min_limit] ||  [EQ_is_gt $rot_5th_axis $mom_kin_5th_axis_max_limit] } {

        set mom_pos(0) $mom_alt_pos_x
        set mom_pos(1) $mom_alt_pos_y
        set mom_pos(2) $mom_alt_pos_z
        set mom_pos(3) $mom_alt_pos_a1
        set mom_pos(4) $mom_alt_pos_a2

        set mom_alt_pos(0) $mom_pos_x
        set mom_alt_pos(1) $mom_pos_y
        set mom_alt_pos(2) $mom_pos_z
        set mom_alt_pos(3) $mom_pos_a1
        set mom_alt_pos(4) $mom_pos_a2
        
        set theta_value $mom_alt_pos_a2

        if {[info exist prev_theta_value]} {
          set c_value [SET_ROTARY_ANGLE $theta_value]
        } else {
          set c_value $theta_value
        }

        set mom_out_angle_pos(0) $mom_alt_pos_a1
        set mom_out_angle_pos(1) $c_value

        set prev_theta_value $theta_value    ;# was set prev_theta_value $c_value (whb)
        set prev_c_value $c_value            ;# was set prev_c_value $mc_value (whb)

    } else {
    
        set mom_pos(0) $mom_pos_x
        set mom_pos(1) $mom_pos_y
        set mom_pos(2) $mom_pos_z
        set mom_pos(3) $mom_pos_a1
        set mom_pos(4) $mom_pos_a2

        set mom_alt_pos(0) $mom_alt_pos_x
        set mom_alt_pos(1) $mom_alt_pos_y
        set mom_alt_pos(2) $mom_alt_pos_z
        set mom_alt_pos(3) $mom_alt_pos_a1
        set mom_alt_pos(4) $mom_alt_pos_a2

        set theta_value $mom_pos_a2

        if {[info exist prev_theta_value]} {
          set c_value [SET_ROTARY_ANGLE $theta_value]
        } else {
          set c_value $theta_value
        }

        set mom_out_angle_pos(0) $mom_pos_a1
        set mom_out_angle_pos(1) $c_value

        set prev_theta_value $theta_value
        set prev_c_value $c_value
    }
}


#-------------------------------------------------------------------------------
proc SET_MCS_ROTATION_ANGLES {  } {
#-------------------------------------------------------------------------------

  global mom_record_fields
  global mom_field_count
  global mom_tool_axis
  global mom_origin
  global mom_translate

  global mom_translate_x mom_translate_y mom_translate_z
  global mom_origin_x mom_origin_y mom_origin_z
  global MCSROT_flag
  global first_move_after_MCSROT
  global trans_axis 
  global trans_angle

  set MCSROT_flag 1

  switch $mom_record_fields(1) {
  "AUTO"
    {
      set I $mom_tool_axis(0)
      set J $mom_tool_axis(1)
      set K $mom_tool_axis(2)
      set rad2deg [expr 90.0/asin(1.0)]
      set reslt_JK [expr sqrt(pow($J,2)+pow($K,2))]

      set trans_axis(0) "AAXIS"
      set trans_axis(1) "BAXIS"
      set trans_axis(2) "0"
      set trans_angle(0) [expr -1.0*atan2($J,$K)*$rad2deg]
      set trans_angle(1) [expr atan2($I,$reslt_JK)*$rad2deg]
      set trans_angle(2) 0.0
    }
  default
    { 
      if {$mom_field_count > 7 ||  $mom_field_count == 1 ||  [expr fmod($mom_field_count,2)] == 0.0 } {
          MOM_output_to_listing_device  "ERROR: Invalid number of arguments for MCSROT"
          MOM_output_to_listing_device  "ACTION: Aborting Coordinate System Rotation"
          set MCSROT_flag 0
          return
      }

      set j 0
      for {set i 1} {$i < 7} {incr i 2} {
           if {[info exists mom_record_fields($i)]} {
               set trans_axis($j) $mom_record_fields($i)
           } else { set trans_axis($j) 0 }
 
           set k [expr $i+1]
           if {[info exists mom_record_fields($k)]} {
               set trans_angle($j) $mom_record_fields($k)
           } else { set trans_angle($j) 0 }
           incr j
      }
    }
  }

# Prepare the variables for the UFunc library to access mom variables
# The code below is to facilitate the USER FUNCTION extension to read mom vars

  if {[info exists mom_origin]} {
      set mom_origin_x $mom_origin(0)
      set mom_origin_y $mom_origin(1)
      set mom_origin_z $mom_origin(2)
  }

  if {[info exists mom_translate]} {
      set mom_translate_x $mom_translate(0)
      set mom_translate_y $mom_translate(1)
      set mom_translate_z $mom_translate(2)
  }
}

#-------------------------------------------------------------------------------
proc CONVERT_CYCLES_DATA {  } {
#-------------------------------------------------------------------------------

    global mom_mcs_goto
    global mom_tool_axis
    global mom_out_angle_pos
    global mom_cycle_rapid_to
    global mom_cycle_retract_to
    global mom_cycle_feed_to
    global mom_pos
    global mom_cycle_rapid_to_pos
    global mom_cycle_retract_to_pos
    global mom_cycle_feed_to_pos

# Set up the dummy variables

  set dummy_alt_pos(0) 0.0
  set dummy_alt_pos(1) 0.0
  set dummy_alt_pos(2) 0.0
  set dummy_alt_pos(3) 0.0
  set dummy_alt_pos(4) 0.0

# Converting the mom_mcs_goto point

    CONVERT_POINT mom_mcs_goto  mom_tool_axis  mom_pos  mom_alt_pos  mom_out_angle_pos

# Converting the RTRCTO point

  # Compute the retract to point
  # retract_to_point = mcs_goto + tool_axis_vector * retract_to_value

  set retract_to_point(0) [expr $mom_mcs_goto(0) +  $mom_cycle_retract_to * $mom_tool_axis(0)]
  set retract_to_point(1) [expr $mom_mcs_goto(1) +  $mom_cycle_retract_to * $mom_tool_axis(1)]
  set retract_to_point(2) [expr $mom_mcs_goto(2) +  $mom_cycle_retract_to * $mom_tool_axis(2)]
  CONVERT_POINT retract_to_point  mom_tool_axis  mom_cycle_retract_to_pos  dummy_alt_pos  mom_out_angle_pos
    
# Converting the RAPTO point    

  # Compute the rapid to point
  # rapid_to_point = mcs_goto + tool_axis_vector * rapid_to_value

  set rapid_to_point(0) [expr $mom_mcs_goto(0) +  $mom_cycle_rapid_to * $mom_tool_axis(0)]
  set rapid_to_point(1) [expr $mom_mcs_goto(1) +  $mom_cycle_rapid_to * $mom_tool_axis(1)]
  set rapid_to_point(2) [expr $mom_mcs_goto(2) +  $mom_cycle_rapid_to * $mom_tool_axis(2)]
  CONVERT_POINT rapid_to_point  mom_tool_axis  mom_cycle_rapid_to_pos  dummy_alt_pos  mom_out_angle_pos
    
# Converting the FEDTO point    

  # Compute the feed to point
  # feed_to_point = mcs_goto + tool_axis_vector * feed_to_value

  set feed_to_point(0) [expr $mom_mcs_goto(0) +  $mom_cycle_feed_to * $mom_tool_axis(0)]
  set feed_to_point(1) [expr $mom_mcs_goto(1) +  $mom_cycle_feed_to * $mom_tool_axis(1)]
  set feed_to_point(2) [expr $mom_mcs_goto(2) +  $mom_cycle_feed_to * $mom_tool_axis(2)]
  CONVERT_POINT feed_to_point  mom_tool_axis  mom_cycle_feed_to_pos  dummy_alt_pos  mom_out_angle_pos
}

