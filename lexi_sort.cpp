#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

// this method involves adding weights to each string in the array and then sorting the array in numerical order based on the weights
// for example, if the array of strings is ["acb", "abc", "bca"], and the string specifying lexicographical order is "abc"
// we would determine the weights of the strings in the array based on the following formula
// (length of string specifying lexicographical order)^(length of string specifying lexicographical order - 1 - current position) * (value for character in corresponding lexicographical mapping)
// lexicographical mapping for "abc": {a:1,b;2,c:3}
// "acb" => 3^2*1 + 3^1*3 + 3^0*2 = 20
// "abc" => 3^2*1 + 3^1*2 + 3^0*3 = 18
// "bca" => 3^2*2 + 3^1*3 + 3^0*1 = 28
// the lexicographical order would be "abc","acb","bca"

// structure that associates a weight to a letter
struct mapping{
	string s;
	int val;
};

// create a mapping for string specifying lexicographical order
// if the string is "abcde", the mapping would be
// {a:1,b:2,c:3,d:4,e:5}
vector<mapping> create_map(string lex_str){
	int lex_str_len = lex_str.size();
	vector<mapping> lex_map;
	for(int i = 0; i < lex_str_len; i++){
		mapping temp;
		temp.s = lex_str[i];
		temp.val = i+1;
		lex_map.push_back(temp);
	}
	return lex_map;
}

// find total value in the lexicographical mapping for a string in the array to be sorted
int calculate_priority(vector<mapping> lex_map, int lex_str_len, string s){

	int sum = 0;
	for(int k = 0; k < s.size(); k++){

		// add more weight to characters that do not appear in mapping
		int current_weight = 0;

		string letter(1,s[k]);
		for(int i = 0; i < lex_map.size(); i++){
			if(lex_map.at(i).s.compare(letter) == 0){
				current_weight = 1;
				sum += pow(lex_str_len,lex_str_len-1-k)*lex_map.at(i).val;
				break;
			}
		}

		if(current_weight == 0){
			sum += pow(lex_str_len,lex_str_len-k)*(lex_str_len+1);
		}
	}
	return sum;
}

// helper function to sort a vector of mapping structures
bool compareByPriority(mapping a, mapping b){
	return a.val < b.val;
}

// sort the string of arrays in lexicographical order
void lexi_sort(string s_array[], int len_array, string lex_str){

	vector<mapping> lex_map = create_map(lex_str);
	vector<mapping> lex_priority;
	int lex_str_len = lex_str.size();

	for(int j = 0; j < len_array; j++){
		mapping temp;
		temp.s = s_array[j];
		temp.val = calculate_priority(lex_map, lex_str_len, s_array[j]); 	
		lex_priority.push_back(temp);
	}

	sort(lex_priority.begin(),lex_priority.end(),compareByPriority);	

	// print strings in lexicographically sorted order with the weight total
	for(int i = 0; i < lex_priority.size(); i++){
		cout << lex_priority.at(i).s << " " << lex_priority.at(i).val << endl;
	}
}

int main(){
	
	// reading input from command line
	cout << "Enter the number of strings in array:" << endl;
	int len_array;
	cin >> len_array;
	cout << "Enter " << len_array << " strings" << endl;
	string s_array[len_array];
	for(int i = 0; i < len_array; i++){
		string temp;
		cin >> temp;
		s_array[i] = temp;
	}
	cout << "Enter string specifying lexicographical order:" << endl;
	string lex_order_str;
	cin >> lex_order_str;

	// sorting array in lexicographical order
	lexi_sort(s_array, len_array, lex_order_str);

	return 0;
}

// runtime analysis

// let m represent length of string specifying lexicographical order
// let n represent the sum of the length of all the strings in the unsorted array

// Worst Case RunTime

// runtime of create_map is O(m) - linear time
// runtime of calculate_priority is O(mn) - quadratic time
// runtime of compareByPriority is O(1) - constant time
// runtime of lexi_sort is O(mn) - quadratic time
// runtime of main() is O(mn) - quadratic time
// worst case rutime is quadratic

// Best Case Runtime (if the string specifying lexicographical order is one character)

// runtime of create_map is O(1) - constant time
// runtime of calculate_priority is O(n) - linear time
// runtime of compareByPriority is O(1) - constant time
// runtime of lexi_sort is O(n) - linear time
// runtime of main() is O(n) - linear time
// best case runtime is linear

