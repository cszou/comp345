#include "Utilities.h"
using namespace std;


 bool Utilities::find_Territory(const vector<Territory*>& territories, Territory* t) {

	bool result = false;
	if (find(territories.begin(), territories.end(), t) != territories.end()) {
		result = true;
	}

	return result;

}

 bool Utilities::find_Order_Name(const vector<string>& names, string s) {

	 bool result = false;
	 if (find(names.begin(), names.end(), s) != names.end()) {
		 result = true;
	 }

	 return result;

 }

  bool Utilities::find_Bool(const vector<bool>& bools, bool b) {
	  bool result = false;
	  if (find(bools.begin(), bools.end(), b) != bools.end()) {
		  result = true;
	  }

	  return result;

 }
