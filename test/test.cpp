// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef void   *UF_MOM_id_t;

int UF_MOM_ask_string
( 
   UF_MOM_id_t          mom_id,    /* <I> - see above */
   char                *var_name,  /* <I> - see above */
   const char         **var_val    /* <OF> - see above */
){ return 0 ; }

void UF_MTX3_rotate_about_axis(
const double rotation_axis[3] ,/* <I>
                               Vector of the rotation axis
                               */
double rotation_angle ,/* <I>
                       Angle of the rotation (in radians)
                       */
double mtx[9]  /* <O>
               Rotation Matrix
               */
)
{ ; }
void UF_MTX3_multiply(
const double mtx1[9] ,/* <I>
                      Matrix #1
                      */
const double mtx2[9] ,/* <I>
                      Matrix #2
                      */
double mtx_product[9]  /* <O>
                       Matrix product
                       mtx_product = mtx1 X mtx2
                       */
){ ; }

void UF_MTX3_x_vec(
const double mtx[9] ,/* <I>
                     3x3 Matrix whose X-direction is required
                     */
double x_vec[3]  /* <O>
                 X-direction vector of the matrix
                 */
){ ; }
void UF_MTX3_y_vec(
const double mtx[9] ,/* <I>
                     Matrix whose Y-direction is required
                     */
double y_vec[3]  /* <O>
                 Y-direction vector of the matrix
                 */
){ ; }
void UF_MTX3_z_vec(
const double mtx[9] ,/* <I>
                     Matrix whose Z-direction is required
                     */
double z_vec[3]  /* <O>
                 Z-direction vector of the matrix
                 */
){ ; }

int dword_1000C460 = 0;

typedef struct MOM_oper_setup_data_s
{
  double mtx[9];
  double origin[3];
  double translate[3];
  double tool_z_offset;
  int    kin_track_center_of_ball;
  double tool_corner1_radius;
} MOM_oper_setup_data_t, *MOM_oper_setup_data_p_t;


//----- (10007ED0) --------------------------------------------------------
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

//----- (10007B00) --------------------------------------------------------
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
  const char *Str=&S[0]; // [sp+34h] [bp-4h]@6

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


int main(int argc, char* argv[])
{
  MOM_oper_setup_data_p_t oper_setup_data;

  oper_setup_data = ( MOM_oper_setup_data_t * ) malloc
                        ( sizeof ( MOM_oper_setup_data_t ) ) ;

  UF_MOM_id_t mom_id=NULL;
  double trans_method[6]={0,0,0,0,0,0};
	
  SET_rotd_operation_data(mom_id,oper_setup_data) ;
  
  SET_rotd_mcs_matrix (mom_id,oper_setup_data,trans_method) ;

  printf("\n-------\n");
  printf("\noper_setup_data->mom_origin_x=%f",oper_setup_data->origin[0]);
  printf("\noper_setup_data->mom_kin_track_center_of_ball=%d",oper_setup_data->kin_track_center_of_ball);
  printf("\n-------\n");

  free(oper_setup_data);

	return 0;
}

