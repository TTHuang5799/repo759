#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[]){
	int x = atoi(argv[1]);
	for (int i = 0; i <= x; i++){
		printf("%d ", i);
	}
	printf("\n");
	
	for (int j = x; j >= 0; j--){
		cout << j << " ";
	}
	cout << endl;
	
	return 0;
}
