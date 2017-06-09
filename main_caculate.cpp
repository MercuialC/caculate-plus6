#include <iostream>
#include <ctime>
#include"caculate.h"
using namespace std;
#include "File.h"

int main(int argc, char **argv)
{
	string infilepath, outfilepath;
	if (argc == 3)//判断主函数参数个数（避免直接打开报错）
	{
		infilepath = argv[1];
		outfilepath = argv[2];
	}
	else cin >> infilepath >> outfilepath;//从命令行中输入路径和输出路径

	srand(time(0));
	InitPriorities();
	//Mutual m(infilepath, outfilepath);
	Mutual m(outfilepath);
	Filestream f;
	f.clearfile(outfilepath);
	//Randomvalue r;
	CreatExpresstion c(outfilepath);
	m.init();
	f.writeFile(outfilepath,"计算结果如有小数请保留2位,只舍不入");//写入文件
	f.writeFile(outfilepath,"请输入题目数目\n");
	f.writeFile(outfilepath,"------------------------------------------------\n");
	int proNum = f.readFile(infilepath);//读入文件
	f.writeFile(outfilepath,proNum);
	f.writeFile(outfilepath, "\n");
	cout << "计算结果如有小数请保留2位,只舍不入" << endl;
	cout << "请输入题目数目:";
	cout << proNum << endl;
	cout << "------------------------------------------------" << endl;

	for (int i = 1; i <= proNum; i++)
	{
		c.generateExpression();//生成运算式
		m.scan(c.calculateResult());//与用户交互输入数据
	}
	m.print();//将统计结果输出给用户

	return 0;
}

