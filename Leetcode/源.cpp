#include<iostream>
#include<vector>
#include<string>
#include<strstream>
#include<algorithm>
using namespace std;

class Solution {
	friend bool cmp(int a, int b);
public:
	string largestNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end(), cmp);

		strstream ss;
		ss.clear();
		for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it){
			ss << *it;
		}

		string s;
		ss >> s;

		int head0 = 0;
		while (head0 < s.size() && s[head0] == '0')
			++head0;
		if (head0 == s.size())
			s = "0";
		else
			s = s.substr(head0, -1);
		return s;
	}
};

string s1, s2;
strstream ss;
bool cmp(int a, int b){
	ss.clear();
	ss << a << b;
	s1.clear();
	ss >> s1;

	ss.clear();
	ss << b << a;
	s2.clear();
	ss >> s2;

	return s1 > s2;
}

int main(){
	int d, n;
	Solution S;
	vector<int> v{ 0, 0};

	cout << S.largestNumber(v) << endl;
	system("pause");
	return 0;
}