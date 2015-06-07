#pragma once

#include "util\Data.h"

void TestDataClass(std::ostream& log) {

	Data d;
	d.Insert("IntTest", "234");
	d.Insert("DoubleTest", "1.0000000000000002");
	d.Insert("StrTest", "A String!");

	d.Insert("TrueTest", "true");
	d.Insert("TrueTest1", "True");
	d.Insert("TrueTest2", "T");
	d.Insert("TrueTest3", "1");
	d.Insert("TrueTest4", "t");
	d.Insert("FalseTest", "itdontmaterwhatIputhere");

	// Int testing
	int i;
	bool succ = d.Int("IntTest", i);

	if (succ != true) {
		log << "IntTest failed to get\n";
	} else if (i != 234) {
		log << "IntTest failed to convert to the correct value; expected 234, got " << i << "\n";
	}

	// Double Testing
	double dd;
	succ = d.Double("DoubleTest", dd);

	if (succ != true) {
		log << "DoubleTest failed to get\n";
	} else if (dd != 1.0000000000000002) {
		log << "DoubleTest failed to convert to the correct value; expected 1.0000000000000002, got " << dd << "\n";
	}

	// String Testing
	std::string s;
	succ = d.String("StrTest", s);

	if (succ != true) {
		log << "StrTest failed to get\n";
	} else if (s != "A String!") {
		log << "StrTest failed to get to the correct value; expected 'A String!', got " << s << "\n";
	}

	// Override Testing
	succ = d.Insert("StrTest", "Should Fail", true);

	if (succ != false) {
		log << "Returned true when it should have failed to override 'StrTest'";
	}

	std::string s2;
	succ = d.Insert("StrTest", "Shouldn't Fail");

	if (succ == false) {
		log << "Returned false when it should have been able to override 'StrTest'";
	} else if (!d.String("StrTest", s2)) {
		log << "failed to get the correct value for StrTest when overwritten";
	} else if (s2 != "Shouldn't Fail") {
		log << "StrTest should have been overwritten to 'Shouldn't Fail' but was really: " << s2 << "\n";
	}


	// Flag testing
	d.Insert("TrueTest", "true");
	d.Insert("TrueTest1", "True");
	d.Insert("TrueTest2", "T");
	d.Insert("TrueTest3", "1");
	d.Insert("TrueTest4", "t");
	d.Insert("FalseTest", "itdontmaterwhatIputhere");

	if (!d.Flag("TrueTest")) {
		log << "Failed to correctly parse 'true' as true\n";
	}

	if (!d.Flag("TrueTest1")) {
		log << "Failed to correctly parse 'True' as true\n";
	}

	if (!d.Flag("TrueTest2")) {
		log << "Failed to correctly parse 'T' as true\n";
	}

	if (!d.Flag("TrueTest3")) {
		log << "Failed to correctly parse '1' as true\n";
	}

	if (!d.Flag("TrueTest4")) {
		log << "Failed to correctly parse 't' as true\n";
	}

	if (d.Flag("False")) {
		log << "Failed to correctly parse 'itdontmaterwhatIputhere' as false\n";
	}

	if (d.Flag("ThisFlagIsntPresent")) {
		log << "Failed to return false when requesting a flag that isn't present\n";
	}

	// int list testing
	d.Insert("IntList", "100, 200, 300,  \t400  , \n500");
	std::vector<int> int_list;

	succ = d.IntList("IntList", int_list);
	if (succ != true) {
		log << "Failed to convert the IntList";
	} else if (int_list.size() != 5) {
		log << "int_list Size is not what expected (5): " << int_list.size() << "\n";
	} else if (int_list[0] != 100) {
		log << "Value on int_list[0] is not what expected (100): " << int_list[0] << "\n";
	} else if (int_list[4] != 500) {
		log << "Value on int_list[4] is not what expected (500): " << int_list[4] << "\n";
	}
	succ = d.IntList("IntList", int_list);
	if (succ != true) {
		log << "Failed to convert and append the int list";
	} else if (int_list.size() != 10) {
		log << "int_list Size after appending is not what expected (10): " << int_list.size() << "\n";
	} else if (int_list[2] != 300) {
		log << "Value on int_list[2] is not what expected (300): " << int_list[3] << "\n";
	} else if (int_list[6] != 200) {
		log << "Value on int_list[6] is not what expected (200): " << int_list[6] << "\n";
	}

	d.Insert("IntList", "100, 200, HAHA,  \t400  , \n500");
	int_list.clear();

	succ = d.IntList("IntList", int_list);
	if (succ != false) {
		log << "Expected IntList to fail parsing but succeeded";
	} else if (int_list.size() != 2) {
		log << "int_list Size is not what expected (2): " << int_list.size() << "\n";
	} else if (int_list[0] != 100) {
		log << "Value on int_list[0] is not what expected (100): " << int_list[0] << "\n";
	}


}