#ifndef CP5_ex7_27_h
#define CP5_ex7_27_h
#include<iostream>
#include<vector>
using namespace std;
class  Idiom
{
public:
	Idiom(int theid=0,string theword = " ", string  theexplain = " ") :
		id(theid),word(theword), explain(theexplain) 
	{
		firstword = word.substr(0, 2);
		lastword = word.substr(word.size()-2,2);
	}//构造函数
	string get_word() { return word; }//返回成语
	string get_explain() { return explain; }//返回注释
	string get_lastword() { return lastword; }
	string get_firstword() { return firstword; }
	void worduse() { word_use = 1; }
	void wordunuse() { word_use = 0; }
	int get_id() { return id; }
	int if_use() { return word_use; }//返回是否使用过


private:
	int id;//序号
	string  const word;//成语
	string  firstword;
	string lastword;
	string  const explain;//成语的解释
	int word_use = 0;//是否使用过


};

#endif
