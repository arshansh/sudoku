
//EMAIL:as12413@imperial.ac.uk
//CID=00826335
//EMAIL:as12413@imperial.ac.uk
//CID=00826335

#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>

using namespace std;

//heuristic backtracking algorithm

struct pos_zero{int position;int zero;};// declaring a structure of position and zero(number of empty cells in the row,column,sub grid of that position)

bool check_num(int position,int value,int a[9][9]);	//this function checks if "value" can be written in the "position" or not

void first_filled(const vector<pos_zero> &v,int i,int a[9][9]);	//this function does the backtracking algorithm

int number_zero(int position,int a[9][9]);//this function finds the number of empty cells in row,column and subgrid of the input position

void sort_v(vector<pos_zero> &v);// this function uses bubble sort to sort the positions from minimum number of empty cells around the position ta maximum

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

	vector<pos_zero> v;//vector of struct to store the position and its number of empty cells around it
	for(int j=0;j<81;j++){	//doing this for all cells in the sudoku
		int temp;
		temp=number_zero(j,a);
		pos_zero temp1;
		temp1.position=j;
		temp1.zero=temp;
		v.push_back(temp1);//store the data in vector
}


sort_v(v);//sort the positions and their number of empty cells from minimum to maximum

//the purpose of sorting is that we want to start backtracking from the position with minimum number of empty cell around it
//doing this makes backtracking more efficient(since there is a more chance of having the value right at first place when most the numbers around it have been filled)

first_filled(v,0,a);	//calling the backtracking function to start from position 0 in the vector

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

void first_filled(const vector<pos_zero> &v,int i,int a[9][9]){

	//this function recursively calls itself



int col=(v[i].position)%9;		//we need to change the position to "row" and "column" to use it in the array.
int row=(v[i].position)/9;

if(i==81){		//as soon as we reach position 81(we have 80 positions in the sudoku since we started from zero),we print the 2d array and return
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
        if(check_num(v[i].position,k,a)){	//checking numbers from 1 to 9
            a[col][row]=k;	//if can_be_written is true write that value in that position
            first_filled(v,i+1,a);	//move to the next position
        }
    }
    a[col][row]=0;	//if no value can be assigned in that position,write zero there and come out of the function(move to the previous call)
}
else{	//if the position is not zero move to the next position
	first_filled(v,i+1,a);
	}
}



int number_zero(int position,int a[9][9]){

	int col=position%9;		//we need to change the position to "row" and "column" to use it in the array.
	int row=position/9;

	int count=0;

	for(int j=0;j<9;j++){		//counting the  number of empty cells in the row(we do not want to check the position it self)
		if(a[col][j]==0 && j!=row){
			count++;	//count
		}
	}

	for(int i=0;i<9;i++){		//counting the number of empty cells in the colums(we do not want to check the position it self)
		if(a[i][row]==0 && i!=col){
			count++;
		}
	}

	for(int j=((row)/3)*3;j<(((row)/3)*3)+3;j++){	//counting the number of empty cells in the sub grid,the desired position can be achieved by dividing the row and column by 3 and times it by 3
		for(int i=((col)/3)*3;i<(((col)/3)*3)+3;i++){
			if(a[i][j]==0 && i!=col && j!=row){		//we do not want check the position it self that why we have i!=col and j!=row
				count++;
			}
		}
	}
	return count;	//returning count

}

void sort_v(vector<pos_zero> &v){//sorting the vector of struct using bubble sort

	for(int j=0;j<v.size()-1;j++){
		for(int i=0;i<v.size()-1;i++){

			if(v[i].zero>v[i+1].zero){

				pos_zero temp;

				temp.position=v[i+1].position;
				temp.zero=v[i+1].zero;

				v[i+1].position=v[i].position;
				v[i+1].zero=v[i].zero;

				v[i].position=temp.position;
				v[i].zero=temp.zero;
			}
		}
	}

}
