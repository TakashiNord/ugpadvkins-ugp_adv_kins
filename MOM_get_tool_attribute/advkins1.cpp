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

#include <stdlib.h>
#include <uf.h>
#include <uf_obj.h>
#include <uf_attr.h>
#include <uf_mom.h>

#include <uf_exit.h>
#include <uf_ui.h>


#include "advkins1.h"  // #include "uf_mom_add_ufun_tclexts.h"

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

  /* Adding MOM_get_tool_attribute TCL extension */
    UF_CALL(UF_MOM_extend_xlator(mom, "MOM_get_tool_attribute", mom_get_tool_attribute ));

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
} /* mom_get_tool_attribute */

