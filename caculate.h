#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
void InitPriorities();

extern string infilepath, outfilepath;

class Mutual        //用户的交互类
{
public:
	Mutual(string out) :out_file_name(out){}
	//Mutual(string in, string out) :in_file_name(in), out_file_name(out){}
	void init();                //初始化
	void scan(float f);                //该函数用于与用户交互，获取输入数据
	void DisPlayAnswer();       //输出正确答案
	void print();               //将统计结果输出给用户   
private:
	float answer;
	int correctNum;
	string in_file_name;
	string out_file_name;
};
class Randomvalue       //随机生成类(基类)
{
public:
	Randomvalue();//初始化数字和符号
	virtual int randomNumber(){ return 0; }         //用于随机生成数字
	virtual char randomOperation(){ return 'a'; }     //用于随机生成运算符
protected:
	vector<char> sign;
	vector<int> num;
};
class RandomNumber :public Randomvalue//RandomNumber类继承于Randomvalue
{
public:
	RandomNumber() : Randomvalue(){}
	virtual int randomNumber();         //用于随机生成数字
//	virtual char randomOperation();     //用于随机生成运算符
};
class RandomOperation :public Randomvalue//RandomOperation类继承于Randomvalue
{
public:
	RandomOperation() :Randomvalue(){}
//	virtual int randomNumber();         //用于随机生成数字
	virtual char randomOperation();     //用于随机生成运算符
};
class CreatExpresstion      //算式类 
{
public:
	CreatExpresstion(){}
	CreatExpresstion(string out) :out_file_name(out){}
	template<typename T> string Tostring(T i);
	void generateExpression();  //用于生成运算式   
	float calculateResult();    //计算结果 
	float caculate(float Operand1, float Operand2, char Operator);
private:
	string expression;
	float answer;
	string out_file_name;
};

class Filestream        //文件读写类
{
public:
	//Filestream(string _infilepath, string _outfilepath);
	int readFile(string _infilepath);
	void clearfile(string s)
	{
		_ofs.open(s);
		_ofs.close();
	}
	template <typename T> void writeFile(string _outfilepath, T t);
private:
	 string _InFilePath;
	 string _OutFilePath;
	ifstream _ifs;
	ofstream _ofs;
};
class RandomSimpleFactory//随机类简单工厂
{
public:RandomSimpleFactory(){}
	   static Randomvalue* creatrandom(const char & x);
};
class Problem
{
public:

private:
	string str1, str2;
	Filestream F;
	//Randomvalue R;
	RandomNumber r1;
	RandomOperation r2;
	CreatExpresstion C;
	Mutual M;
};
