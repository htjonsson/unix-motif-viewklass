/*****************************************************************
    ViewKlass - C++ framework library for Motif

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Copyright (C) 2001 John Lemcke
    jostle@users.sourceforge.net
*****************************************************************/

static const char* rcsid
#ifdef __GNUC__
__attribute__ ((unused))
#endif
	= "$Id: testVkNameList.cc,v 1.8 2009/03/21 11:44:34 jostle Exp $";

#include <Vk/VkApp.h>
#include <Vk/VkWindow.h>
#include <Vk/VkCheckBox.h>
#include <Vk/VkNameList.h>

#include <iostream>

using namespace std;

extern Widget theList;

void
printNameList(VkNameList& nl) 
{
	if (&nl == 0) {
		cout << "(null list)" << endl << endl;
		return;
	}

	for (int i = 0; i < nl.size(); ++i) {
		const char* s = nl.getString(i);
		cout << s << ", ";
		delete [] s;
	}
	cout << endl << endl;
}

void
testVkNameList(Widget, XtPointer, XtPointer)
{
	// Possibly do something different each time the test is run.
	static int testCount = 0;

	const char* s1 = "s1";
	const char* s2 = "s2";
	const char* s3 = "s3";
	const char* s4 = "s4";
	const char* s5 = "s5";

	VkNameList nl;
	cout << "add(s1); add(s2); add(s3); add(s4); add(s5);" << endl;
	cout << "s1, s2, s3, s4, s5" << endl;
	nl.add(s1);
	nl.add(s2);
	nl.add(s3);
	nl.add(s4);
	nl.add(s5);
	printNameList(nl);

	cout << "VkNameList nl2(nl)" << endl;
	cout << "s1, s2, s3, s4, s5" << endl;
	VkNameList nl2(nl);
	printNameList(nl2);

	cout << "VkNameList nl3(\"c1\")" << endl;
	cout << "c1" << endl;
	VkNameList nl3("c1");
	printNameList(nl3);

	cout << "add(s2); add(s3); add(s3); add(s4);" << endl;
	cout << "s1, s2, s3, s4, s5, s2, s3, s3, s4" << endl;
	nl.add(s2);
	nl.add(s3);
	nl.add(s3);
	nl.add(s4);
	printNameList(nl);

	cout << "remove(s3);" << endl;
	cout << "s1, s2, s4, s5, s2, s4" << endl;
	nl.remove(s3);
	printNameList(nl);

	cout << "add(nl3); add(nl2);" << endl;
	cout << "s1, s2, s4, s5, s2, s4, c1, s1, s2, s3, s4, s5" << endl;
	nl.add(nl3);
	nl.add(nl2);
	printNameList(nl);

	cout << "VkNameList nl4 = nl;" << endl;
	cout << "s1, s2, s4, s5, s2, s4, c1, s1, s2, s3, s4, s5" << endl;
	VkNameList nl4 = nl;
	printNameList(nl4);

	cout << "nl != nl3" << endl;
	if (nl == nl3) {
		cout << "nl == nl3" << endl << endl;
	} else {
		cout << "nl != nl3" << endl << endl;
	}

	cout << "nl == nl4" << endl;
	if (nl == nl4) {
		cout << "nl == nl4" << endl << endl;
	} else {
		cout << "nl != nl4" << endl << endl;
	}

	cout << "exists(\"c1\")" << endl;
	if (nl.exists("c1")) {
		cout << "exists(\"c1\")" << endl << endl;
	} else {
		cout << "NOT exists(\"c1\")" << endl << endl;
	}

	cout << "NOT exists(\"c2\")" << endl;
	if (nl.exists("c2")) {
		cout << "exists(\"c2\")" << endl << endl;
	} else {
		cout << "NOT exists(\"c2\")" << endl << endl;
	}

	cout << "nl4.removeDuplicates();" << endl;
	cout << "c1, s1, s2, s3, s4, s5" << endl;
	nl4.removeDuplicates();
	printNameList(nl4);
	
	cout << "nl.reverse();" << endl;
	cout << "s5, s4, s3, s2, s1, c1, s4, s2, s5, s4, s2, s1" << endl;
	nl.reverse();
	printNameList(nl);

	cout << "char** fred = (char**)(nl4);" << endl;
	char** fred = (char**)(nl4);
	for (int i = 0; i < nl4.size(); ++i) {
		cout << fred[i] << ", ";
	}
	cout << endl;
	delete [] fred;
	printNameList(nl4);

	cout << "char* common = nl.mostCommonString();" << endl;
	const char* common = nl.mostCommonString();
	cout << "common = " << common << endl << endl;
	delete [] common;
	common = 0;

	cout << "VkNameList* nlp = nl.getSubStrings(\"c\");" << endl;
	VkNameList* nlp = nl.getSubStrings("c");
	cout << "c1" << endl;
	printNameList(*nlp);
	delete nlp;
	nlp = 0;

	cout << "VkNameList* nlp = nl.getSubStrings(\"s\");" << endl;
	nlp = nl.getSubStrings("s");
	cout << "s5, s4, s3, s2, s1, s4, s2, s5, s4, s2, s1" << endl;
	printNameList(*nlp);
	delete nlp;
	nlp = 0;

	cout << "VkNameList* nlp = nl.completeName(\"s\", comp, num);" << endl;
	char* comp;
	int num;
	nlp = nl.completeName("s", comp, num);
	cout << "s1, s2, s3, s4, s5" << endl;
	printNameList(*nlp);
	delete nlp;
	delete [] comp;
	nlp = 0;

	VkNameList nl5("abcyhey");
	nl5.add("abcnuygkh");
	nl5.add("abcyfdxser");
	cout << "nl5.completeName(\"ab\", comp, num);" << endl;
	nlp = nl5.completeName("ab", comp, num);
	cout << ":abc: 3" << endl;
	cout << ":" << comp << ": " << num << endl;
	cout << "abcnuygkh, abcyfdxser, abcyhey" << endl;
	printNameList(*nlp);
	delete nlp;
	delete [] comp;
	nlp = 0;

	cout << "nl5.completeName(\"xy\", comp, num);" << endl;
	nlp = nl5.completeName("xy", comp, num);
	cout << ":(null): 0" << endl;
	cout << ":" << long(comp) << ": " << num << endl;
	cout << "(null list)" << endl;
	printNameList(*nlp);
	delete nlp;
	delete [] comp;
	nlp = 0;

	if (testCount == 0) {
		XmStringTable st = nl.getXmStringTable();
		XtVaSetValues(theList, 
					  XmNitemCount, nl.size(),
					  XmNitems, st,
					  NULL);
		VkNameList::freeXmStringTable(st);
	}

	if (testCount == 1) {
		XmStringTable st = nl5.getXmStringTable();
		XtVaSetValues(theList, 
					  XmNitemCount, nl5.size(),
					  XmNitems, st,
					  NULL);
		VkNameList::freeXmStringTable(st);
	}

	if (testCount == 2) {
		XmStringTable st = nl4.getXmStringTable();
		XtVaSetValues(theList, 
					  XmNitemCount, nl4.size(),
					  XmNitems, st,
					  NULL);
		VkNameList::freeXmStringTable(st);
	}

	cout << "List size (12) " << nl.size() << endl;

	testCount++;
	testCount %= 3;
}

