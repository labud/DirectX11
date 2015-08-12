#include<iostream>
#include<string.h>
#include<vector>

using namespace std;

const int maxN = 10000;

char str[maxN];


int main(){
	//string str;
	char** buf  = new char*[10];
	const char *d = " "; 
	char* p;
	while (cin.getline(str, maxN)){
		p = strtok_s(str, d, buf);
		bool flag = true;
		while (p){
			//change(t)
			if (flag){
				p[0] = p[0] - 'a' + 'A';
				flag = false;
			}
			else{

			}
			if (p[0] != ',')
				printf(" ");
			printf("%s", p);
			p = strtok_s(NULL, d, buf);
		}
		printf("\n");
	}
	return 0;
}