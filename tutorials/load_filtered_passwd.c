/* load_filtered_passwd(): converts the /etc/passwd file into
** a multi-column list format, skipping the password field.
*/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/List.h>

/* reset_field(): used to reset the field context
** when a newline is encountered in the input
*/
XmIncludeStatus reset_field ( XtPointer          *in_out,
                              XtPointer          text_end,
                              XmTextType         text_type,
                              XmStringTag        locale_tag,
                              XmParseMapping     parse_mapping,
                              int                pattern_length,
                              XmString           *str_include,
                              XtPointer          call_data)
{
    /* client data is a pointer to the field counter */
    int *field_counter = (int *) call_data;

    /* A newline encountered.
    **
    ** Trivial: we reset the field counter for this line
    ** and terminate the parse sequence 
    */

    *field_counter = 0;

    return XmTERMINATE;
}

/* filter_field(): throws away the second (password) field
** and maps colon characters to tab components.
*/
XmIncludeStatus filter_field ( XtPointer          *in_out,
                               XtPointer          text_end,
                               XmTextType         text_type,
                               XmStringTag        locale_tag,
                               XmParseMapping     parse_mapping,
                               int                pattern_length,
                               XmString           *str_include,
                               XtPointer          call_data)
{
    /* client data is a pointer to the field counter */
    int *field_counter = (int *) call_data;
    char *cptr = (char *) *in_out;

    /* Skip this colon */
    cptr += pattern_length;

    /* If this is the first colon
    ** then skip the input until after the second.
    ** Otherwise, we return a TAB component
    */

    if (*field_counter == 0) {
        /* Skip over the next colon */
        while (*cptr != `:') cptr++;
            cptr++;
    }

    *str_include = XmStringComponentCreate (XmSTRING_COMPONENT_TAB,
                                            0, NULL);

    *in_out = (XtPointer) cptr;
    *field_counter = *field_counter + 1;

    return XmINSERT;
}

XmString *load_filtered_passwd (Widget list, char *file, int *count)
{
    XmParseMapping     map[2];
    FILE               *fptr;
    char               buffer[256];
    Arg                args[8];
    char               *cptr;
    XmString           *xms_array = (XmString *) 0;
    int                xms_count = 0;
    /* Used as client data to the XmParseProc routines */
    int                field_count = 0;
    int                n;

    *count = 0;

    if ((fptr = fopen (file, "r")) == (FILE *) 0) {
        return NULL;
    }

    /* Set up an XmParseProc to handle colons */
    n = 0;
    XtSetArg (args[n], XmNpattern, ":");                  n++;
    XtSetArg (args[n], XmNpatternType, XmCHARSET_TEXT);   n++;
    XtSetArg (args[n], XmNincludeStatus, XmINVOKE);       n++;
    XtSetArg (args[n], XmNinvokeParseProc, filter_field); n++;
    map[0] = XmParseMappingCreate (args, n);

    /* Set up an XmParseProc to handle newlines */
    n = 0;
    XtSetArg (args[n], XmNpattern, "\n");                n++;
    XtSetArg (args[n], XmNpatternType, XmCHARSET_TEXT);  n++;
    XtSetArg (args[n], XmNincludeStatus, XmINVOKE);      n++;
    XtSetArg (args[n], XmNinvokeParseProc, reset_field); n++;
    map[1] = XmParseMappingCreate (args, n);

    while ((cptr = fgets (buffer, 255, fptr)) != (char *) 0) {
        xms_array = (XmString *) XtRealloc ((char *) xms_array,
                            (xms_count + 1) * sizeof (XmString));

        xms_array[xms_count] = XmStringParseText (cptr, 
                                NULL, NULL, XmCHARSET_TEXT,
                                map, 2, &field_count);

        xms_count++;
    }

    (void) fclose (fptr);

    XmParseMappingFree (map[0]);
    XmParseMappingFree (map[1]);

    *count = xms_count;

    return xms_array;
}
