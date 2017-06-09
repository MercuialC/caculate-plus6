#include<iostream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>
#include"caculate.h"
using namespace std;



	unordered_map< char, unordered_map < char, char > > Priorities;
	
	string infilepath, outfilepath;

	//______________________________________________________________


	Randomvalue* RandomSimpleFactory::creatrandom(const char & x)//工厂模式函数实现
	{
		if (x == 'o')
			return new RandomOperation();
		else if (x == 'n')
			return new RandomNumber();
	}

	//____________________________________________________________
	Filestream F;
	//Randomvalue R;
	
	void InitPriorities()//优先级代码
	{
		Priorities['+']['-'] = '>';
		Priorities['+']['+'] = '>';
		Priorities['+']['*'] = '<';
		Priorities['+']['/'] = '<';
		Priorities['+']['('] = '<';
		Priorities['+'][')'] = '>';

		Priorities['-']['-'] = '>';
		Priorities['-']['+'] = '>';
		Priorities['-']['*'] = '<';
		Priorities['-']['/'] = '<';
		Priorities['-']['('] = '<';
		Priorities['-'][')'] = '>';

		Priorities['*']['-'] = '>';
		Priorities['*']['+'] = '>';
		Priorities['*']['*'] = '>';
		Priorities['*']['/'] = '>';
		Priorities['*']['('] = '<';
		Priorities['*'][')'] = '>';

		Priorities['/']['-'] = '>';
		Priorities['/']['+'] = '>';
		Priorities['/']['*'] = '>';
		Priorities['/']['/'] = '>';
		Priorities['/']['('] = '<';
		Priorities['/'][')'] = '>';

		Priorities['(']['+'] = '<';
		Priorities['(']['-'] = '<';
		Priorities['(']['*'] = '<';
		Priorities['(']['/'] = '<';
		Priorities['(']['('] = '<';
		Priorities['('][')'] = '=';
	}

/*	Filestream::Filestream(string _infilepath, string _outfilepath)
	{
		_InFilePath = _infilepath;
		_OutFilePath = _outfilepath;
		_ifs.open(_InFilePath.c_str(), ios::in);
		_ofs.open(_OutFilePath.c_str(), ios::out|ios::ate);
	}*/
	void Mutual::init()//初始化
	{
		answer = 0;
		correctNum = 0;
	}
	Randomvalue::Randomvalue()
	{
		for (int i = 1; i <= 10; i++)
		{
			num.push_back(i);
		}
		sign.push_back('+');
		sign.push_back('-');
		sign.push_back('*');
		sign.push_back('/');
	}

	void Mutual::scan(float f)//该函数用于与用户交互，获取输入数据
	{
		float myans;
		answer = f;
		cin >> myans;
		F.writeFile(out_file_name,myans);
		if (myans == answer)
		{
			cout << "正确" << endl << endl;
			F.writeFile(out_file_name,"正确\n\n");
			//myfile << "正确\n\n";
			correctNum++;
		}
		else
		{
			cout << "错误,";
			F.writeFile(out_file_name,"错误,");
			//myfile << "错误,";
			DisPlayAnswer();
			cout << endl;
		}
	}

	void Mutual::DisPlayAnswer()
	{
		cout << "答案是:" << answer << endl;
		F.writeFile(out_file_name,"答案是:");
		F.writeFile(out_file_name,answer);
		F.writeFile(out_file_name,"\n");
		//myfile << "答案是:" << answer << "\n";
	}

	void Mutual::print()//将统计结果输出给用户
	{
		cout << "共作对" << correctNum << "题" << endl << endl;
		F.writeFile(out_file_name,"共作对");
		F.writeFile(out_file_name,correctNum);
		F.writeFile(out_file_name,"题\n\n");
		//myfile << "共作对" << correctNum << "题\n\n";
	}

	//生成算式部分----------------------------------------------------------------------
	int RandomNumber::randomNumber()//用于随机生成数字
	{
		return num[rand() % num.size()];
	}
	char RandomOperation::randomOperation()//用于随机生成运算符
	{
		return sign[rand() % sign.size()];
	}

	Randomvalue *r1 = RandomSimpleFactory::creatrandom('n');
	Randomvalue* r2 = RandomSimpleFactory::creatrandom('o');

	template<typename T>//模板
	string CreatExpresstion::Tostring(T i)
	{
		stringstream ss;
		string s;
		ss << i;
		ss >> s;
		return s;
	}

	void CreatExpresstion::generateExpression()//用于生成运算式
	{
		expression = Tostring(r1->randomNumber()) + Tostring(r2->randomOperation()) + Tostring(r1->randomNumber());
		int len = rand() % 5 + 2;
		for (int i = 0; i < len; i++)//add '(' and ')'
		{
			int rdnum = rand() % 10 + 1;
			if (rdnum<2)//10% 加左边 加括号
			{
				expression = Tostring(r1->randomNumber()) + Tostring(r2->randomOperation()) + "(" + Tostring(expression) + ")";
			}
			else if (rdnum>8)//10% 加右边 加括号
			{
				expression = "(" + Tostring(expression) + ")" + Tostring(r2->randomOperation()) + Tostring(r1->randomNumber());
			}
			else if (rdnum<4)//20% 加左边 不加括号
			{
				expression = Tostring(r1->randomNumber()) + Tostring(r2->randomOperation()) + Tostring(expression);
			}
			else if (rdnum>6)//20% 加右边 不加括号
			{
				expression = Tostring(expression) + Tostring(r2->randomOperation()) + Tostring(r1->randomNumber());
			}
			//30% 不加
		}
		cout << expression << " = ";//输出算式
		F.writeFile(out_file_name,expression);//写入文件中
		F.writeFile(out_file_name," = ");
		//myfile << expression << " = ";
		answer = calculateResult();
	}
	//----------------------------------------------------------------------------------

	//算式计算部分----------------------------------------------------------------------
	float CreatExpresstion::calculateResult()
	{
		vector<float> Operands;
		vector<char> Operators;
		float OperandTemp = 0;
		char LastOperator = 0;

		for (int i = 0; i < expression.size(); i++)
		{
			char ch = expression[i];
			if ('0' <= ch && ch <= '9')
			{
				OperandTemp = OperandTemp * 10 + ch - '0';
			}
			else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
			{
				if (ch != '(' && LastOperator != ')')
				{
					Operands.push_back(OperandTemp);
					OperandTemp = 0;
				}
				char Opt2 = ch;
				for (; Operators.size() > 0;)
				{
					char Opt1 = Operators.back();
					char CompareRet = Priorities[Opt1][Opt2];
					if (CompareRet == '>')
					{
						float Operand2 = Operands.back();
						Operands.pop_back();
						float Operand1 = Operands.back();
						Operands.pop_back();
						Operators.pop_back();
						float Ret = caculate(Operand1, Operand2, Opt1);
						Operands.push_back(Ret);
					}
					else if (CompareRet == '<')
					{
						break;
					}
					else if (CompareRet == '=')
					{
						Operators.pop_back();
						break;
					}
				}
				if (Opt2 != ')')
				{
					Operators.push_back(Opt2);
				}
				LastOperator = Opt2;
			}
		}
		if (LastOperator != ')')
		{
			Operands.push_back(OperandTemp);
		}
		for (; Operators.size() > 0;)
		{
			float Operand2 = Operands.back();
			Operands.pop_back();
			float Operand1 = Operands.back();
			Operands.pop_back();
			char Opt = Operators.back();
			Operators.pop_back();
			float Ret = caculate(Operand1, Operand2, Opt);
			Operands.push_back(Ret);
		}
		return (float)((int)(Operands.back() * 100)) / 100;
	}

	float CreatExpresstion::caculate(float Operand1, float Operand2, char Operator)
	{
		if (Operator == '+') return Operand1 + Operand2;
		if (Operator == '-') return Operand1 - Operand2;
		if (Operator == '*') return Operand1 * Operand2;
		if (Operator == '/') return Operand1 / Operand2;
	}
	//----------------------------------------------------------------------------------


	int Filestream::readFile(string _infilepath)
	{
		_ifs.open(_infilepath);
		int n = 0;
		_ifs >> n;
		_ifs.close();
		return n;
	}

	template <typename T>
	void Filestream::writeFile(string _outfilepath,T t)
	{
		_ofs.open(_outfilepath,ios::out|ios::app);
		_ofs << t;
		_ofs.close();
	}
