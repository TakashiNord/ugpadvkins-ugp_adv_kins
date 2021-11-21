/*****************************************************************************
**
** advkins.h
**
** Description:
**    advkins header file.
**
*****************************************************************************/
// static void PrintErrorMessage( int errorCode );
#ifndef _TCL_EXTMOM
#define _TCL_EXTMOM

/****************************************************************************/

#define _ANSI_ARGS_(x)	x

typedef struct Tcl_Interp {
    char *result;		/* If the last command returned a string
				 * result, this points to it. */
    void (*freeProc) _ANSI_ARGS_((char *blockPtr));
				/* Zero means the string result is
				 * statically allocated. TCL_DYNAMIC means
				 * it was allocated with ckalloc and should
				 * be freed with ckfree. Other values give
				 * the address of procedure to invoke to
				 * free the result. Tcl_Eval must free it
				 * before executing next command. */
    int errorLine;              /* When TCL_ERROR is returned, this gives
                                 * the line number within the command where
                                 * the error occurred (1 if first line). */
} Tcl_Interp;

/*
 * When a TCL command returns, the string pointer interp->result points to
 * a string containing return information from the command.  In addition,
 * the command procedure returns an integer value, which is one of the
 * following:
 *
 * TCL_OK		Command completed normally;  interp->result contains
 *			the command's result.
 * TCL_ERROR		The command couldn't be completed successfully;
 *			interp->result describes what went wrong.
 * TCL_RETURN		The command requests that the current procedure
 *			return;  interp->result contains the procedure's
 *			return value.
 * TCL_BREAK		The command requests that the innermost loop
 *			be exited;  interp->result is meaningless.
 * TCL_CONTINUE		Go on to the next iteration of the current loop;
 *			interp->result is meaningless.
 */

#define TCL_OK		0
#define TCL_ERROR	1
#define TCL_RETURN	2
#define TCL_BREAK	3
#define TCL_CONTINUE	4

/****************************************************************************/

/*
 * Exported Tcl procedures:
 */
 
static int mom_load_kinematics
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
);

#endif /* _TCL_EXTMOM */
 
