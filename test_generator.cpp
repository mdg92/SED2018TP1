#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
	srand (time(NULL));	
	for(int i = 0; i<50; i++){
		int wgc = stoi(argv[1]);
		if(stoi(argv[1]) == 5) wgc = rand()%5;
		cout << i*365+1 << ":00:00:00 swcg [" << wgc << "]"<< endl;
		if(stoi(argv[2]) && 85 <= rand()% 100 ){
			int which = rand()%3;
			string event;
			if(which == 0) event = "[0.75, 1, 1]";
                        if(which == 1) event = "[1, 1.25, 1]";
                        if(which == 2) event = "[1, 1, 1.25]";
		cout << i*365+rand()%364+1 << ":00:00:00 ext " << event << endl;
		}
		cout << endl;
	}
}
