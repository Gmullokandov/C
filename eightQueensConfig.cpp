#include <iostream>
#include <cmath>
using namespace std;
void print(int q[], int count){
	cout << "Solution " << ++count << endl;
	cout << "Configuration: ";
       	for (int i=0; i<8; i++)
        	cout << q[i] << ' ';
        cout << endl;
        
}
int main(){
	//set board
	int col = 0, q[8], count = -1;
	q[0] = 0;

	while(true){
        	++col;
        	if(col == 8){
           		++count;
           		print(q,count);
           		col--;
        	}
        else
        	q[col] = -1;
        	for( ; ; ){
                	q[col]++;
               		if(q[col] == 8){
                   		--col;
                   		if(col == -1)
                        		return 0;
                   		else
                        		continue;
                	}
                bool nextRow = false;
                for(int i = 0; i < col; ++i){
                	if(q[col]==q[i] || col - i == abs(q[col] - q[i])){
                        	nextRow = true;
                        	break;
                   	}
                }
                if(nextRow)
                	continue;
                break;
           	}
	}
return 0;
}
