#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<ctime>
#include<random>
#include<unordered_map>
#include"idiom_4.h"
static long long i = 0;
using namespace std;
vector<Idiom> Idiom_vector;
vector<int> thestack;//找最长成语用到
vector<int> themax;//找最长成语用到
unordered_map<string, vector<int>> line;
clock_t startTime, endTime;
void set_file();
void hash_in();
int isword(string );
void f_theword();
void f_longest();
void f_easy();
void f_worst();
void f_best();
void use_back();
bool not_cout(string);
int output(string);
bool checklost(int);
void  recurrence(int stacksize);
int main()
{
	set_file();
	hash_in();
	cout << line.size();
	cout << "请选择   退出:q   查询:t   最长:l   随机:e   恶意:w   友善:b"
		<< endl << "你的选择是:  ";
	cout << Idiom_vector.size();
	while (1)//初始界面,一级程序执行界面.
	{
		char x;
		cin >> x;
		
		switch (x)
		{
		case 't':
			f_theword();
			break;
		case 'l':
			f_longest();
			break;
		case 'e':
			f_easy();
			break;
		case 'w':
			f_worst();
			break;
		case 'b':
			f_best();
			break;
		case 'q':
			exit(0);
		default:
			cout << "请做出正确的选择:   ";
			continue;
		}
		cout << endl << "请选择   退出:q   查询:t   最长:l   随机:e   恶意:w   友善:b"
			<< endl << "你的选择是:  ";
	}

}
void set_file()
{
	ifstream thefile("A:\\desktop\\idiom.txt");
	//读取文件,要改为绝对路径,且不能有中文
	if (!thefile)
	{
		cout << "没有找到文件" << endl;
		return;
	}
	string line, word, theline, explain;
	istringstream record;
	int theid = 0;
	for (int a = 0; a < 25000; a++)
	{
		getline(thefile, line);
		record.clear();
		record.str(line);
		record >> theline;
		if (theline[0] == 'x')
		{
			word = theline.substr(1, theline.find('y') - 1);
			explain = theline.substr(theline.find('y') + 1);
			Idiom a(theid++, word, explain);
			Idiom_vector.push_back(a);
		}
	}
	/*while (getline(thefile, line))
	{

		record.clear();
		record.str(line);
		record >> theline;
		if (theline[0] == 'x')
		{
			word = theline.substr(1, theline.find('y') - 1);
			explain = theline.substr(theline.find('y') + 1);
			Idiom a(theid++, word, explain);
			Idiom_vector.push_back(a);
		}
	}*/
}

void hash_in()
{
	
	startTime = clock();
	for (auto& a : Idiom_vector)
	{
		line[a.get_firstword()].push_back(a.get_id());
	}
	endTime = clock();//计时结束
	cout << "初始化用的总时间是: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

}


void f_theword()
{
	cout << "请输入你想要查询的成语:   ";
	while (true)
	{
		string x;
		cin >> x;
		cout << endl;
		if (x == "q")
		{
			return
				;
		}
		for (auto a : Idiom_vector)
		{
			if (a.get_word() == x)
			{				
				cout << "意思是:" << endl << a.get_explain() << endl << endl<<a.get_id();			
				break;

				
			}
		}
		cout << "请再次输入成语:  ";
	}
}

void f_easy() 
{
	srand(time(0));
	string a = "";
	int m_id =10;
	int u_id;
	string m;
	while ((line[Idiom_vector[m_id].get_lastword()].size()) <25)
	{
		m_id = rand() % Idiom_vector.size();
		//cout << Idiom_vector[m_id].get_word()<<endl
		//<< line[Idiom_vector[m_id].get_lastword()].size()<<endl<<endl;
		
		//测试代码是否生成了可以接龙数量大于25的成语
	}
	Idiom_vector[m_id].worduse();
	cout << "我的回合:   " << Idiom_vector[m_id].get_word()<<endl;
	cout << "你的回合:   ";
	while (true)
	{
		
		while (true)
		{
			cin >> a;
			
			cout << endl;
			if (a=="q")//a是q的话直接退出
			{
				cout << "你输了.";
				use_back();
				system("pause");
				return;
			}
			u_id = isword(a);
			if (u_id==-1)//isword fuction if a is a idiom
			{
				cout << "你输入的不是成语,请重新输入:   ";
				continue;
			}
			if (Idiom_vector[u_id].if_use())//a对应的成语被用过的话
			{
				cout << "你输入的成语已经使用过,请重新输入:   ";
				continue;
			}
			if (Idiom_vector[u_id].get_firstword() != Idiom_vector[m_id].get_lastword())
			{
				cout << "你输入的成语不符合游戏规则,请重新输入:   ";
				continue;
			}
			break;
		}	
		Idiom_vector[u_id].worduse();
		m= Idiom_vector[u_id].get_lastword();
		if (not_cout(m)) // 不可以输出成语:输
		{
			cout << "你赢了."<<endl;
			use_back();
			system("pause");
			return;
		}
		else
		{
			m_id=output(m);
			Idiom_vector[m_id].worduse();
			cout << "我的回合:   " << Idiom_vector[m_id].get_word()<<endl;
			string m = Idiom_vector[m_id].get_lastword();
			if (not_cout(m))
			{
				cout << "你输了."<<endl;
				use_back();
				system("pause");
				return;
			}
		
		}
		cout << "你的回合:   ";
	}
}
int output(string a)
{

	int x;
	while (true)
	{
		x = rand() % line[a].size();
		if (!Idiom_vector[line[a][x]].if_use())
		{
			return line[a][x];
		}
	}

}
bool not_cout(string a)
{
	if (line[a].empty()) return 1;
	for (auto x : line[a])
	{
		if (!Idiom_vector[x].if_use()) return 0;
	}
	return 1;
}

void use_back()//将所有成语的使用情况返回为未使用.
{
	for (auto& a : Idiom_vector)
	{
		a.wordunuse();
	}
}


int isword(string a)//判断是否是一个成语
{
	for (auto t : Idiom_vector)
	{
		if (a == t.get_word())
		{
			return t.get_id();
		}
	}
	return -1;
}
void f_longest()
{
	
	for (auto& a : Idiom_vector)
	{
		
		//cout << "压入编号" << a.get_id() << endl;
		//cout << a.get_id() << endl;
		thestack.push_back(a.get_id());
		a.worduse();		
		recurrence(a.get_id());
		
	}
	

	cout << themax.size() << endl;
	cout << "最长的成语接龙有" <<themax.size()<< "个"<<endl;
	for (auto a :themax)
	{
		
		cout << Idiom_vector[a].get_word() << endl;
	}
}
void  recurrence(int theid)
{	
	i++;

		if (not_cout(Idiom_vector[theid].get_lastword()))
		{
			if (thestack.size() > themax.size())
			{
				
				cout << "现在已经数到" << thestack.size() << "个了" << endl;
				cout << i << endl;
				themax = thestack;
				if (thestack.size() >4411)
				{
					int x = 0;
					ofstream out("A:\\desktop\\1.txt");
					for (auto a : themax)
					{
						out << Idiom_vector[a].get_word() <<endl;
					}
					
					system("pause");
				}
			}
			thestack.pop_back();
			//cout << "弹出编号" << theid << "  栈数量为:  " << thestack.size() <<endl;
			Idiom_vector[theid].wordunuse();
			return;
		}
		for (int a : line[Idiom_vector[theid].get_lastword()])
		{
			if (!Idiom_vector[a].if_use())
			{
				thestack.push_back(a);
			//cout << "压入编号" << theid << "  栈数量为:  " << thestack.size() <<endl;
				Idiom_vector[a].worduse();
				recurrence(a);
			}
		}
		Idiom_vector[theid].wordunuse();
		thestack.pop_back();
		//cout << "弹出编号" << theid <<"  栈数量为:  "<<thestack.size()<< endl;
		return;

}



void f_worst()
{}
void f_best() {}
