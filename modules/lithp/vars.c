/* lithp - vars
 *
 *      handle the variables
 *      
 *      (c)2001/2006 Scott Lawrence   yorgle@gmail.com
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <string.h>
#include "lithp.h"

le * variableFind( le * varlist, char * key )
{
	le * temp = varlist;

	if (!varlist || !key) return( NULL );

	while (temp) {
		if (!strcmp(key, temp->data))  return( temp );
		temp = temp->list_next;
	}

	return( NULL );
}

le * variableSet( le * varlist, char * key, le * value )
{
	le * temp;

	if (!key || !value)  return( varlist );

	temp = variableFind( varlist, key );
	if ( temp ) {
		leWipe( temp->branch );
		temp->branch = leDup( value );
	} else {
		temp = leNew( key );
		temp->branch = leDup( value );
		varlist = leAddHead( varlist, temp );
	}
	return( varlist );
}

le * variableSetString( le * varlist, char * key, char * value )
{
	le * temp;

	if (!key || !value)  return( varlist );

	temp = leNew(value);
	varlist = variableSet( varlist, key, temp );
	leWipe( temp );

	return( varlist );
}

le * variableGet( le * varlist, char * key )
{
	le * temp = variableFind(varlist, key);
	if (temp && temp->branch)  return( temp->branch );
	return( NULL );
}

char * variableGetString( le * varlist, char * key )
{
	le * temp = variableFind(varlist, key);
	if (    temp
             && temp->branch
             && temp->branch->data
	     && countNodes(temp->branch) == 1)
		return( strdup(temp->branch->data) );
	return( strdup("-1") );
}


void variableDump( le * varlist )
{
        le * temp = varlist;
	while (temp) {
		if (temp->branch && temp->data) {
			printf("%s \t", temp->data);
			leDumpReformat( stdout, temp->branch );
			printf("\n");
		}
		temp = temp->list_next;
	}
}
