#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Map.h"
class Utilities {
	//This class contains static utility functions
public:
  
	//check whether a territory exists in a vector
	static bool find_Territory(const vector<Territory*> &territories, Territory* t);
	static bool find_Order_Name(const vector<string>& names, string s);
	static bool find_Bool(const vector<bool>& bools, bool b);






};
