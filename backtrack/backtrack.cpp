/*
 * sudoku.cpp
 *
 *  Created on: Mar 29, 2014
 *      Author: sh_arsh2000
 */
//NAME:ARSHAN SHAFIEI
//EMAIL:as12413@imperial.ac.uk
//CID=00826335

#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>

using namespace std;

//backtracking algorithm

bool check_num(int position,int value,int a[9][9]);	//this function checks if "value" can be written in the "position" or not

void first_filled(int position,int a[9][9]);	//this function does the backtracking algorithm


int main(){


	int a[9][9];	//a 2d array to put the numbers in the sudoku in
	ifstream infile;

	string filename;	//the user has to type the name of the input file
	cin>>filename;

	infile.open(filename.c_str());	//open the file

	if(!infile.is_open()){		//if the file is empty print this
		cout<<"the file is empty"<<endl;
		exit(EXIT_FAILURE);
	}

	for(int j=0;j<9;j++){	//put the data in the file in a 2d array a[i][j].Hence a[0][0] will be my first position and a[1][0] will be my second position ..
		for(int i=0;i<9;i++){
			infile>>a[i][j];
		}
	}

	infile.close();


first_filled(0,a);	//calling the backtracking function to start from position zero in the 2d array

return 0;


}


bool check_num(int position,int value,int a[9][9]){  //check function to see if that "value" can be written in the "position"

	bool can_be_written=1;

	int col=position%9;		//we need to change the position to "row" and "column" to use it in the array.
	int row=position/9;

for(int j=0;j<9;j++){		//checking if the same number exists in the row(we do not want to check the position it self)
	if(a[col][j]==value && j!=row){
		can_be_written=0;	//if the value exits we have can_be_written as zero
	}
}

for(int i=0;i<9;i++){		//checking if the same number exists in the column(we do not want to check the position it self)
	if(a[i][row]==value&& i!=col){
		can_be_written=0;
	}
}

for(int j=((row)/3)*3;j<(((row)/3)*3)+3;j++){	//checking if the same number exists in the sub grid,the desired position can be achieved by dividing the row and column by 3 and times it by 3
	for(int i=((col)/3)*3;i<(((col)/3)*3)+3;i++){
		if(a[i][j]==value && i!=col && j!=row){		//we do not want check the position it self that why we have i!=col and j!=row
			can_be_written=0;
		}
	}
}
return can_be_written;	//returning can_be_written(0 or 1)

}

void first_filled(int position,int a[9][9]){

	//this function recursively calls itself

int col=position%9;		//we need to change the position to "row" and "column" to use it in the array.
int row=position/9;

if(position==81){		//as soon as we reach position 81(we have 80 positions in the sudoku since we started from zero),we print the 2d array and return
    for(int j=0;j<9;++j){
        for(int i=0;i<9;++i){
            cout<<a[i][j]<<"  ";
        }
        cout<<endl;
    }
    return;
    }


if(a[col][row]==0){	//if that position is zero,check all the numbers from 1 to 9 in that position,as soon as one value can be written there we move to the next position
    for(int k=1;k<10;k++){
        if(check_num(position,k,a)){	//checking numbers from 1 to 9
            a[col][row]=k;	//if can_be_written is true write that value in that position
            first_filled(position+1,a);	//move to the next position
        }
    }
    a[col][row]=0;	//if no value can be assigned in that position,write zero there and come out of the function(move to the previous call)
}
else{	//if the position is not zero move to the next position
	first_filled(position+1,a);
	}
}


