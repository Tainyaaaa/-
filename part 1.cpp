#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <cassert>
#include <vector>
using namespace std;
/*
begin	BEGIN	1
end		END		2
if		IF		3
then		THEN		4
else		ELSE		5
while	WHILE	6
do		DO		7
标识符	IDN		8
十进制1	DEC		9
<		LT		10
<=		LE		11
;		SEMI	12
<>		NEQ		13
>		GT		14
>=		GE		15
=		EQ		16
+		ADD		17
-		SUB		18
*		MUL		19
/		DIV		20
(       SLP		21
)		SRP		22
八进制	OCT		23 
十六进制HEX		24 
非法八	ILOCT	25
非法16	ILHEX	26 
*/


const char* table1[] = { " ","begin","end","if","then","else","while","do" };
const char* table2[] = { " ","BEGIN","END","IF","THEN","ELSE","WHILE","DO","IDN","DEC","LT","LE","SEMI","NEQ","GT","GE","EQ","ADD","SUB","MUL","DIV","SLP","SRP","OCT","HEX" ,"ILOCT","ILHEX"};
char TOKEN[30];
int lookup(char a[])
{
	int i;
	for (i = 1; i <= 7; i++)
	{
		if (strcmp(a, table1[i]) == 0)return i;
	}
	if (i == 8)return 0;
}
void out(int a, const char b[])
{
	ofstream fout("result.txt", fstream::app);
	char temp = '-';
	if (a == 8 || a == 9||(a>=23&&a<=26))//标识符
	{
		fout  << table2[a] ;
		for(int j=0;j<10-strlen(table2[a]);j++) fout<<" ";
		fout<< b << endl;
	}
	else
	{
		fout << table2[a] ;
		for(int j=0;j<10-strlen(table2[a]);j++) fout<<" ";
		fout<< temp <<endl;
	}

	fout.close();
}

void report_error(void)//返回错误
{
	ofstream fout("result.txt", fstream::app);
	fout << "输入不合规范！";
	fout.close();
	//exit(0);
}
void scanner_example(FILE* fp)//识别输入单词串，遇到#结束
{
	char ch;
	int i, c, flag = 0;;
	//ch = fgetc(fp);
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == ' ')ch = fgetc(fp);
		if (ch == '\n')ch = fgetc(fp);
		if (ch == '#')break;
		if (isalpha(ch))
		{
			TOKEN[0] = ch; ch = fgetc(fp); i = 1;
			while (isalnum(ch))//检查所传的字符是否是字母和数字
			{
				TOKEN[i] = ch; i++;
				ch = fgetc(fp);
			}
			TOKEN[i] = '\0';
			fseek(fp, -1, 1); //从文件当前位置后退一个字符
			c = lookup(TOKEN);//查找在第二个表中的位置，如果是关键字返回下标，标识符返回0
			if (c == 0) out(8, TOKEN);//识别标识符
			else out(c, TOKEN);//识别关键字
		}
		else if (isdigit(ch))//判断字符是否为数字字符
		{
			TOKEN[0] = ch; ch = fgetc(fp); i = 1;
			if(TOKEN[0]=='0')
			{
				i++;
				//ch = fgetc(fp);
				int flag=0;
				if(!isdigit(ch)&&(ch!='x'&&ch!='X'))
				{
					TOKEN[i] = '\0';
					fseek(fp, -1, 1);
					out(9, TOKEN);
				}
				else if(ch=='x'||ch=='X')
				{
					i=0;
					ch = fgetc(fp);
					while (isdigit(ch)||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z') )
					{
						if((ch>='g'&&ch<='z')||(ch>='G'&&ch<='Z'))
							flag=1;
						TOKEN[i] = ch; i++;
						ch = fgetc(fp);
					}
				TOKEN[i] = '\0';
				fseek(fp, -1, 1);
				if(flag==0)
				out(24, TOKEN);
				else out(26,TOKEN);
				}
				else
				{
					i=0;
					//ch = fgetc(fp);
					while (isdigit(ch) )
					{
						if(ch=='8'||ch=='9')
						flag=1;
						TOKEN[i] = ch; i++;
						ch = fgetc(fp);
					}
				TOKEN[i] = '\0';
				fseek(fp, -1, 1);
				if(flag==0)
				out(23, TOKEN);
				else out(25,TOKEN);
				}
			} 
			else
			{
			
				while (isdigit(ch) )
				{
					TOKEN[i] = ch; i++;
					ch = fgetc(fp);
				}
				TOKEN[i] = '\0';
				fseek(fp, -1, 1);
				out(9, TOKEN);
			}
		}
		else
			switch (ch)
			{
			case '<': ch = fgetc(fp);
				if (ch == '=')out(11, TOKEN);//<=
				else if (ch == '>') out(13, TOKEN);//<>
				else
				{
					fseek(fp, -1, 1);
					out(10, TOKEN);//<
				}
				break;
			case '=': 
				out(16, TOKEN);//=
				break;
			case ';':
				out(12,TOKEN);//;
				break; 
			case '>': ch = fgetc(fp);
				if (ch == '=')out(15, TOKEN);//>=
				else
				{
					fseek(fp, -1, 1);
					out(14, TOKEN);//>
				}
				break;
			case '+':out(17, TOKEN); break;
			case '-':out(18, TOKEN); break;
			case '*':out(19, TOKEN); break;
			case '/':out(20, TOKEN); break;
			case '(':out(21,TOKEN); break;
			case ')':out(22,TOKEN); break;
			default: report_error(); break;
			}

	}
	return;
}

int main()
{
	FILE* fp1;
	FILE* fp2;
	fp2 =fopen("result.txt", "w");
	fclose(fp2);
	fp1 = fopen("test.txt", "r");
	if (!fp1)
	{
		printf("打开文件失败！");
	}
	scanner_example(fp1);
	
	cout << "表达式为：" << endl;
	ifstream myfile1("test.txt", ios::in);
	string temp;
	if (!myfile1.is_open())
	{
		cout << "未成功打开文件" << endl;
	}
	while (getline(myfile1, temp))
	{
		cout << temp<<endl;
	}
	myfile1.close();

	cout << "词法分析结果为：" << endl;
	ifstream myfile2("result.txt", ios::in);
	if (!myfile2.is_open())
	{
		cout << "未成功打开文件" << endl;
	}
	while (getline(myfile2, temp))
	{
		cout << temp << endl;
	}
	myfile2.close();

	fclose(fp1);
	fclose(fp2);
	return 0;
}

