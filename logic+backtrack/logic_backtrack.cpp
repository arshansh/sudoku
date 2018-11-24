//NAME:ARSHAN SHAFIEI
//EMAIL:as12413@imperial.ac.uk
//CID=00826335

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>


using namespace std;

void first_filled(int position,int a[9][9]);

bool check_num1(int x,int y,int value,int a[9][9]);	//this function checks if "value" can be written in position x,y in the 2d array or not

bool check_num(int position,int value,int a[9][9]);

int main(){

	int a[9][9];	//a 2d array to put the numbers in the sudoku in
	int count_free=0;	//count free is the number of free cells in my sudoku
	bool write_value=1;	//a boolean to check the sudoku can be solved or not (details bellow)

	ifstream infile;
	string filename;	//the user has to type the name of the input file
	cin>>filename;
	infile.open(filename.c_str()); //open the file

	if(!infile.is_open()){	//if the file is empty print this
		cout<<"the file is empty"<<endl;
		exit(EXIT_FAILURE);
	}

for(int j=0;j<9;j++){
	for(int i=0;i<9;i++){
		infile>>a[i][j];	//put the data in the file in a 2d array a[i][j].Hence a[0][0] will be my first position and a[1][0] will be my second position ..

		if(a[i][j]==0){	//if the position is zero,increment  count_free by 1 to keep record of the number of free positions
			count_free++;
		}
	}
}
infile.close();


while((count_free!=0)&&(write_value==1)){	//while there are  still empty cells in my sudoku and a value has been assigend to a cell(sudoku can be solved),I want to go through the sudoku again

	write_value=0;	//initialize write_value by zero(sudoku can not be solved)


	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){	//checking all the cells in the sudoku

			if(a[i][j]!=0){	//find an empty cell
				continue;
			}
			//we want to write the value in that empty cell,only if there is only one possibility(one number) that can be written there.
			//therefore we use a temp variable and initialize it with zero
			int temp=0;
			for(int k=1;k<10;k++){
				if(check_num1(i,j,k,a)==1){	//checking if numbers 1 to 9 can be assigned to that cell
					if(temp==0){	//temp is zero for the first time,so we equal it to k.but the next time a possible value is found temp is not zero so we come out of the for loop and move to the next empty cell
						temp=k;
					}
					else{
						temp=0;
						break;	//come out of the loop
					}
				}
			}

			if(temp!=0){	//if only one value can be assigned to that cell(temp is zero) after cheking all the numbers,we write that number in that cell and decrease the number if empty cells by one
				a[i][j]=temp;
				write_value=1;	//as soon as we write a value in a cell,this might lead us writing another value in another cell in the sudoku..so have to go to the sudoku again from the beginning.
								//by changing this boolean to 1 we go through the while loop again(start again from the beginning)
				count_free--;
			}
		}
	}
}
	//after all the free spaces have been filled count_free=0 and the sudoku is solved(we come out of the while loop)

//sometimes the sudoku can not be solved so far,then we can use backtracking to solve the rest of the sudoku
if(write_value==0){

	first_filled(0,a);
	return 0;
}

	for(int j=0;j<9;j++){
		for(int i=0;i<9;i++){	//printing the sudoku
			cout<<a[i][j]<<"  ";
		}
		cout<<endl;
		}

	return 0;
}




bool check_num1(int x,int y,int value,int a[9][9]){	//check function to see if that "value" can be written in the  x and y position

	bool can_be_written=1;



for(int j=0;j<9;j++){	//checking if the same number exists in the row(we do not want to check the position it self)
	if(a[x][j]==value && j!=y){
		can_be_written=0;	//if the value exits we have can_be_written as zero
	}
}

for(int i=0;i<9;i++){	//checking if the same number exists in the column(we do not want to check the position it self)
	if(a[i][y]==value&& i!=x){
		can_be_written=0;
	}
}

for(int j=((y)/3)*3;j<(((y)/3)*3)+3;j++){	//checking if the same number exists in the sub grid,the desired position can be achieved by dividing the row and column by 3 and times it by 3
	for(int i=((x)/3)*3;i<(((x)/3)*3)+3;i++){
		if(a[i][j]==value && i!=x && j!=y){	//we do not want check the position it self that why we have i!=col and j!=row
			can_be_written=0;
		}
	}
}
return can_be_written;		//returning can_be_written(0 or 1)

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



