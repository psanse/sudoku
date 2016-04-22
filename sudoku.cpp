//sudoku.cpp: simple sudoku 9x9 reader from text files in two formats designed as an example for students
//taking the course of Informatica Industrial y Comunicaciones, ETSIDI, UPM
//author:pss 
//date: 22/04/16

#include <iostream>
#include "file_wrapper.h"

using namespace std;

class Sudoku{
public:
	enum type_t{EMPTY=0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
private:
	static const int SUDOKU_ERROR=-1;
	static const int SUDOKU_OK=0;
	type_t ** board;
public:
	friend ostream& operator<<(ostream& o, const Sudoku& s);
	static const int SUDOKU_ROWS=9;
	Sudoku();		//empty sudoku
	~Sudoku();

	int add_number(int i, int j, type_t val);
	void reset();
	int read_compressed_format(char* filename);
	int read_standard_format(char* filename);
};

Sudoku::Sudoku(){
	board= new type_t*[SUDOKU_ROWS];
	for(int i=0; i<SUDOKU_ROWS; i++){
		board[i]= new type_t[SUDOKU_ROWS];
	}

	for(int i=0; i<SUDOKU_ROWS; i++){
		for(int j=0; j<SUDOKU_ROWS; j++){
			board[i][j]=EMPTY;
		}
	}
}

Sudoku::~Sudoku(){
	for(int i=0; i<SUDOKU_ROWS; i++){
		delete [] board[i];
	}
	delete [] board;
}

void Sudoku::reset(){
	for(int i=0; i<Sudoku::SUDOKU_ROWS; i++){
		for(int j=0; j<Sudoku::SUDOKU_ROWS; j++){
			 board[i][j]=EMPTY;

		}
	}
}

int Sudoku::add_number(int i, int j, type_t val){
	if(i>=EMPTY && i<SUDOKU_ROWS && j>=EMPTY && j<SUDOKU_ROWS){
		board[i][j]=val;
	}
	else return SUDOKU_ERROR;
return SUDOKU_OK;
}

inline 
ostream& operator<<(ostream& o, const Sudoku& s){
	for(int i=0; i<Sudoku::SUDOKU_ROWS; i++){
		for(int j=0; j<Sudoku::SUDOKU_ROWS; j++){
			o<<(int)s.board[i][j]<<" ";

		}
		o<<endl;
	}
	return o;
}

inline
int Sudoku::read_compressed_format(char* filename){
//all numbers packed together in a single line with no spaces
//between them
	int num_read=0; int row=0; int col=0;
	char num_sudo[1];
	
	File f(filename, File::READ);
	stringstream sstr=f.read(100);
	reset();
	while(true){
		sstr.read(num_sudo, 1);
		if(sstr.fail()){
			cout<<"Error when parsing the Sudoku"<<endl;
			return SUDOKU_ERROR;
		}
		add_number(row, col, (Sudoku::type_t)atoi(num_sudo));
		col++;
		if(col% Sudoku::SUDOKU_ROWS==0){
			col=0;
			row++;
		}	
		num_read++;
		if(num_read==SUDOKU_ROWS*SUDOKU_ROWS) break;
	}
return SUDOKU_OK;
}

inline
int Sudoku::read_standard_format(char* filename){
//rows in different lines with spaces between each number

	int num_read=0; int row=0; 
	stringstream sstr("");
	File f(filename, File::READ);

	reset();
	while(true){
		sstr=f.read_line();
		if(sstr.fail()){
			cout<<"Error when parsing the Sudoku"<<endl;
			return SUDOKU_ERROR;
		}

		//parse line
		int val;
		for(int col=0; col<SUDOKU_ROWS; col++){
			sstr>>val;
			add_number(row, col, (Sudoku::type_t)val);
		}

		row++;
		if(row==SUDOKU_ROWS) break;		
	}
return SUDOKU_OK;
}

//test
void main (){
	Sudoku s;
	s.read_compressed_format("EasterMonster.txt");
	cout<<s;

	s.read_standard_format("AIEscargot.txt");
	cout<<s;
}