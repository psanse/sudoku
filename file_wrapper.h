//file_wrapper.h: interface (and implementation) of File class, simple wrapper to parse text files
//date: 22/04/16


#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

typedef unsigned int UINT;

#ifndef __FILE_WRAPPER_H_
#define __FILE_WRAPPER_H_
class File{
	fstream m_f;
public:
	enum mode_t{READ, WRITE, APPEND};
	File(const char* name, mode_t type);
	File(const char* name, const char* text , mode_t type);		
	~File(){close();}
	fstream& get_file(){return m_f;}
	void print();												//file to console
	stringstream read(int num_char=250);						//file to buffer
	stringstream read_line(int num_char=250);					//line to buffer
	void close(){m_f.close();}
};

File::File(const char* name, mode_t type){
	switch (type){
	case READ:
		m_f.open(name, fstream::in);
		if(m_f.is_open()) cout<<"File opened ok"<<endl;
		else cout<<"error: unable to open file";
		break;
	case WRITE:
		m_f.open(name, fstream::out);
		break;
	case APPEND:
		m_f.open(name, fstream::app);
		break;
	default:
		cout<<"File::undef type, filed to open"<<endl;
	};
}

File::File(const char* name, const char* text, mode_t type){
	switch (type){
	case WRITE:
		m_f.open(name, fstream::out);
		m_f<<text;
		break;
	case APPEND:
		m_f.open(name, fstream::app);
		m_f<<text;
		break;
	default:
		cout<<"File::undef type, filed to open"<<endl;
	};
}

inline
void File::print(){
	char line[250];
	while(!m_f.eof()){
		m_f.getline(line, 250, '\n');
		cout<<line;		
	}
}

inline
stringstream File::read(int num_char){
	stringstream o;
	char* line = new char[num_char+1];
	while(!m_f.eof()){
		m_f.getline(line, num_char, '\n');
		o<<line;		
	}
	delete line;
	return o;
}

inline
stringstream File::read_line(int num_char){
	stringstream o;
	char* line = new char[num_char+1];
	m_f.getline(line, num_char, '\n');
	o<<line;								
	delete line;
	return o;
}

#endif

