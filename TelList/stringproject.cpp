#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define ERROR 0;  //错误状态标识
#define valid 1;  //正确返回状态标识


int  AddCount = 0;   //标记数组最后一个元素的位置
char g_szBuffe[0x5000] = { 0 }; //主数据 存储数据
char shadow_szBuffe[30] = { 0 }; //影子数组  记录主数组变化

void ShowData();  //声明函数



//菜单函数  整合功能显示
void show()
{
	system("cls");
	printf("-----------------------------\n");
	printf("-------字符串系统------------\n");
	printf("1.增加  2.删除    3.修改-----\n");
	printf("4.查找  5.统计    6.显示资源-\n");
	printf("7.碎片整理        8.退出-----\n");
	printf("请选择需要的功能\n");
}

//字符串增加函数
int  Add()
{
	int  i = 0;
	int  Data_Index = 0;
	//存放数据的下标
	char SaveMark[2] = { "*" };
	//再每一个元素后面插入标识分割
	//存储数据后插入的标志
	char SaveData[30] = { 0 };
	//接受键入数据的
	Data_Index = AddCount;
	//每次函数执行前读取数组最后一个元素位置
	while (1)
	{
		printf("请输入要存入的字符串\n");

		scanf("%s", SaveData);
		if (strlen(SaveData) > 30)
		{
			printf("过长！请限制在30以内\n");
			break;
		}
		
		strcat(SaveData, SaveMark);
		
		if (strlen(SaveData) > (sizeof(g_szBuffe) - strlen(SaveData)))
		{
			printf("空间不足,存入失败\n");
			break;
		}

		for (i = 0; i < strlen(SaveData); i++)
		{
		    g_szBuffe[Data_Index] = SaveData[i];
			shadow_szBuffe[Data_Index] = SaveData[i];
			Data_Index++;
		}		
		printf("存入成功");
		AddCount = Data_Index;
		system("pause");
		return 0;
	}
	return 0;
}


void Next(char* target, int* next) {
	int i = 1;
	next[1] = 0;
	int j = 0;
	while (i < strlen(target)) {
		if (j == 0 || target[i - 1] == target[j - 1]) {
			i++;
			j++;
			if (target[i - 1] != target[j - 1]) {
				next[i] = j;
			}
			else {
				next[i] = next[j];
			}
		}
		else {
			j = next[j];
		}
	}
}

//KMP法求元素匹配
int KMP(char* origin, char* target)
{
	int i = 0; 
	int j = 0;

	int next[30];
	int Orlen = strlen(origin);  //被寻数组的长度
	int Talen = strlen(target);  //被寻数据的长度
	Next(target, next);

	while (i < Orlen)
	{

		if (origin[i] == target[j]&&j<Talen)  //如果当前数组的I等于被寻数据的I而且还没完全读取完，则继续读取
		{
			i++;
			j++;
		}
		if (j >=Talen)  //当J大于等候长度后，则读取完成而标识完全符合 ，返回1，表示找到了
		{
			printf("找到\n");
			return  valid;
		}
		else if (origin[i] != target[j]) //如果不等于
		{
			if (j == 0)  //而且被寻数据处于第一位  则匹配后面有没有合适的
			{
				j = 0;
				i++;
			}
			else
			{
				j = next[j - 1];   // 头位不符合  继而匹配后续的
			}
		}
	}
	if (i > Orlen && j >Talen) //头以及后续数据都不符合 ，返回0  表示找不到
	{
		system("pause");
	}
	return ERROR;
}

//搜索函数
int Find()
{
	int i = 0;
	int j = 0;
	int Data_Index = 0;
	char SaveDateTemp[] = { 0 };
	//接受返回值
	char SaveDate[30] = { 0 };
	//输入数组
	char DataFind[30] = { 0 };
	//存放标志位之前的数组

	printf("请输入你要查找的数据\n");

	scanf("%s", SaveDate);

	/*遍历大数组来寻找数据*/
	for ( i = 0; i < strlen(g_szBuffe); i++)
	{
		if (g_szBuffe[i] == '*')
		{
			if (KMP(DataFind, SaveDate))
			{
				system("pause");
				return 0; //找到直接返回
			}
		}
		else
		{
			DataFind[Data_Index] = g_szBuffe[i];  //由于*是每个元素的分割，所以一直给待寻数组赋值 每加满一个字符串
			Data_Index++;                        //则放入KMP对比
		}
	}
	printf("未能找到数据\n");
	system("pause");
	return 0;
}


//删除函数
int Del()
{
	int i = 0;
	int j = 0;
	int y = 0;
	int k = 0;
	int Data_Index = 0;
	int count = 0;
	int save = 0;
	int MarkCount = 0;
	int flag = 0;
	char SaveDate[30] = { 0 };
	char SaveIndex[30] = { 0 };//存放下标
	char DataDel[30] = { 0 };//存放删除目标的下标
	char DataFind[30] = { 0 };

	ShowData();

	printf("请输入要删除的数据\n");

	scanf("%s", SaveDate);

	for (i = 0; i < strlen(g_szBuffe); i++) //先寻找目标
	{
		if (g_szBuffe[i] == '*')
		{
			MarkCount++;
			if (KMP(DataFind, SaveDate))
			{
				save = i;  //标记找到目标的尾部
				system("pause");
				break;
			}
		}
		else
		{
			DataFind[Data_Index] = g_szBuffe[i];
			Data_Index++;
		}
	}
	
	//存储尾部

	count = save;

	if (MarkCount == 1)  //头元素直接后续元素推进头元素的长度
	{
		for ( i = 0; i < strlen(g_szBuffe); i++)
		{
			g_szBuffe[i] = g_szBuffe[i +( strlen(SaveDate)+1)];
			printf("成功删除目标\n");
			system("pause");
			return 0;
		}
	}
	else//非头元素
	{
		for (i = 0; i < strlen(g_szBuffe); i++)
		{
			if (flag == 0)  //标记是否开始推进
			{
				if (i == count)     //当遍历到达了目标元素尾部
				{
					flag=1;  //标记1
				}
			}
			if (flag == 1)    
			{
				for (i = 0; i < strlen(g_szBuffe); i++)
				{
					if (g_szBuffe[i] == '*')
					{

						if (i == count)   //遍历找到*号而等于目标尾部
						{	
							for (k = 0; k < strlen(g_szBuffe); k++)  //后续元素依次推进目标元素长度 把目标覆盖掉
							{
								g_szBuffe[Data_Index+1] = g_szBuffe[i+1];
								Data_Index++;
								i++;
							}
							AddCount = k;   //标记主数组最后一个元素位置
							printf("成功删除目标\n");
							system("pause");
							return 0;
						}
						else
						{
							Data_Index = i;
							continue;
						}
					}
				}
			}
		}
	}
	
	printf("无法删除目标\n");
	system("pause");
	return 0;
}

//修改函数
int modification()
{
	int i = 0;
	int j = 0;
	int d = 0;
	int k = 0;
	int ii = 0;
	int Data_Index = 0;
	int count = 0;
	int MarkCount = 0;
	int SizeCount = 0;
	int save = 0;
	int saveend = 0;
	int size = 0;
	char DataFind[30] = {0};
	char SaveIndex[30] = { 0 };
	char Datamod[30] = { 0 };
	char SaveMark[2] = { "*" };
	char SaveData[30] = { 0 };
	char ADDData[30] = { 0 };
	ShowData();
	printf("请输入要修改的目标\n");
	scanf("%s", &SaveData);
	
	for (i = 0; i < strlen(g_szBuffe); i++)
	{
		if (g_szBuffe[i] == '*')
		{
			MarkCount = Data_Index;
			if (KMP(DataFind,SaveData))
			{
				save = i;
				system("pause");
				break;
			}
		}
		else
		{
			DataFind[Data_Index] = g_szBuffe[i];
			Data_Index++;
		}
	}
	
	//同理删除元素 ，先寻后修，不同的是由于是修改，所以记录的是目标元素的头以及尾部
	count = (i-strlen(SaveData));
	saveend = i+1;
	system("pause");
	printf("修改为:\n");
	scanf("%s",Datamod);
	strcat(Datamod, SaveMark);

	//判断是否超出原数据长度
	if (strlen(Datamod)-1 > strlen(SaveData))
	{
		printf("超出原范围，进行后续移动操作\n");
		size = strlen(Datamod) - strlen(SaveData);

		for (int i = 0; i < strlen(g_szBuffe); i++)
		{
			if (i == count)
			{
				for (int o = saveend; o < strlen(g_szBuffe); o++)
				{
					if (g_szBuffe[o] == '*')
					{
						SizeCount = (o - saveend);
						for (ii = saveend; d <SizeCount-1; ii++)
						{
							g_szBuffe[ii+size] = g_szBuffe[ii];
							d++;
						}
						 g_szBuffe[ii + size]='*';
						printf("原值移动完成\n");  //超出后，计算超出长度，把目标数据的尾部其他数据往后移动超出长度
						break;                     //移动完成后则跳出
					} 
				}

				for ( k = i; j < strlen(Datamod); k++)   //移动好其他数据后 覆盖即可
				{
					g_szBuffe[k] = Datamod[j];
					j++;
				}
				AddCount = strlen(g_szBuffe);
				printf("修改成功!\n");
				system("pause");
				return 0;
			}
		}
	}

	for (int i = 0; i < strlen(g_szBuffe); i++)   //不超出长度的直接覆盖上即可
	{
		if (i == count)
		{
			for (int t = i; j<strlen(Datamod); t++)
			{	
				g_szBuffe[t] = Datamod[j];
				j++;
			}
			printf("修改成功!\n");
			system("pause");
			return 0;
		}
	}
	printf("修改不成功!\n");
	system("pause");
	return 0;
}


//统计函数 ，统计数据中大小写字母的次数
void statistics()
{
	double StrCount = 0;
	double ACount=0, BCount=0, CCount=0, DCount=0, ECount=0, FCount=0, GCount=0, HCount=0, ICount=0, JCount=0, KCount=0, LCount=0, NCount=0, MCount=0, OCount=0, PCount=0, QCount=0, RCount=0;
	double SCount=0, TCount=0, UCount=0, VCount=0, WCount=0, XCount=0, YCount=0, ZCount=0;
	printf("去除标志符*后字符串总数为:\n");
	for (int i = 0; i < strlen(g_szBuffe); i++)
	{
		if (g_szBuffe[i] != '*')
		{
			StrCount++;
		}
	}
	printf("%d\n", (int)StrCount);

	for (int i = 0; i < StrCount; i++) //不分大小写，遍历元素 匹配26字母 每有一次则加一
	{
		if (g_szBuffe[i] == 'A' || g_szBuffe[i] == 'a')
		{
			ACount++;
		}
		else if(g_szBuffe[i] == 'B' || g_szBuffe[i] == 'b')
		{
			BCount++;
		}
		else if (g_szBuffe[i] == 'C' || g_szBuffe[i] == 'c')
		{
			CCount++;
		}
		else if (g_szBuffe[i] == 'D' || g_szBuffe[i] == 'd')
		{
			DCount++;
		}
		else if (g_szBuffe[i] == 'E' || g_szBuffe[i] == 'e')
		{
			ECount++;
		}
		else if (g_szBuffe[i] == 'F' || g_szBuffe[i] == 'f')
		{
			FCount++;
		}
		else if (g_szBuffe[i] == 'G' || g_szBuffe[i] == 'g')
		{
			GCount++;
		}
		else if (g_szBuffe[i] == 'H' || g_szBuffe[i] == 'h')
		{
			HCount++;
		}
		else if (g_szBuffe[i] == 'I' || g_szBuffe[i] == 'i')
		{
			ICount++;
		}
		else if (g_szBuffe[i] == 'J' || g_szBuffe[i] == 'j')
		{
			JCount++;
		}
		else if (g_szBuffe[i] == 'K' || g_szBuffe[i] == 'k')
		{
			KCount++;
		}
		else if (g_szBuffe[i] == 'L' || g_szBuffe[i] == 'l')
		{
			LCount++;
		}
		else if (g_szBuffe[i] == 'N' || g_szBuffe[i] == 'n')
		{
			NCount++;
		}
		else if (g_szBuffe[i] == 'M' || g_szBuffe[i] == 'm')
		{
			MCount++;
		}
		else if (g_szBuffe[i] == 'O' || g_szBuffe[i] == 'o')
		{
			OCount++;
		}
		else if (g_szBuffe[i] == 'P' || g_szBuffe[i] == 'p')
		{
			PCount++;
		}
		else if (g_szBuffe[i] == 'Q' || g_szBuffe[i] == 'q')
		{
			QCount++;
		}
		else if (g_szBuffe[i] == 'R' || g_szBuffe[i] == 'r')
		{
			RCount++;
		}
		else if (g_szBuffe[i] == 'S' || g_szBuffe[i] == 's')
		{
			SCount++;
		}
		else if (g_szBuffe[i] == 'T' || g_szBuffe[i] == 't')
		{
			TCount++;
		}
		else if (g_szBuffe[i] == 'U' || g_szBuffe[i] == 'u')
		{
			UCount++;
		}
		else if (g_szBuffe[i] == 'V' || g_szBuffe[i] == 'v')
		{
			VCount++;
		}
		else if (g_szBuffe[i] == 'W' || g_szBuffe[i] == 'w')
		{
			WCount++;
		}
		else if (g_szBuffe[i] == 'X' || g_szBuffe[i] == 'x')
		{
			XCount++;
		}
		else if (g_szBuffe[i] == 'Y' || g_szBuffe[i] == 'y')
		{
			YCount++;
		}
		else if (g_szBuffe[i] == 'Z' || g_szBuffe[i] == 'z')
		{
			ZCount++;
		}

	}

	//计算占比  字母次数/总元素（不包括分隔符号*）
	printf("字母A（不分大小写）出现量为%d,占比为%0.2lf\n",(int)ACount,(ACount / StrCount) * 100);
	printf("字母B（不分大小写）出现量为%d,占比为%0.2f\n", (int)BCount, (BCount / StrCount) * 100);
	printf("字母C（不分大小写）出现量为%d,占比为%0.2f\n", (int)CCount, (CCount / StrCount) * 100);
	printf("字母D（不分大小写）出现量为%d,占比为%0.2f\n", (int)DCount, (DCount / StrCount) * 100);
	printf("字母E（不分大小写）出现量为%d,占比为%0.2f\n", (int)ECount, (ECount / StrCount) * 100);
	printf("字母F（不分大小写）出现量为%d,占比为%0.2f\n", (int)FCount, (FCount / StrCount) * 100);
	printf("字母G（不分大小写）出现量为%d,占比为%0.2f\n", (int)GCount, (GCount / StrCount) * 100);
	printf("字母H（不分大小写）出现量为%d,占比为%0.2f\n", (int)HCount, (HCount / StrCount) * 100);
	printf("字母I（不分大小写）出现量为%d,占比为%0.2f\n", (int)ICount, (ICount / StrCount) * 100);
	printf("字母J（不分大小写）出现量为%d,占比为%0.2f\n", (int)JCount, (JCount / StrCount) * 100);
	printf("字母K（不分大小写）出现量为%d,占比为%0.2f%\n", (int)KCount, (KCount / StrCount) * 100);
	printf("字母L（不分大小写）出现量为%d,占比为%0.2f\n", (int)LCount, (LCount / StrCount) * 100);
	printf("字母N（不分大小写）出现量为%d,占比为%0.2f\n", (int)NCount, (NCount / StrCount) * 100);
	printf("字母M（不分大小写）出现量为%d,占比为%0.2f\n", (int)MCount, (MCount / StrCount) * 100);
	printf("字母O（不分大小写）出现量为%d,占比为%0.2f\n", (int)OCount, (OCount / StrCount) * 100);
	printf("字母P（不分大小写）出现量为%d,占比为%0.2f\n", (int)PCount, (PCount / StrCount) * 100);
	printf("字母Q（不分大小写）出现量为%d,占比为%0.2f\n", (int)QCount, (QCount / StrCount) * 100);
	printf("字母R（不分大小写）出现量为%d,占比为%0.2f\n", (int)RCount, (RCount / StrCount) * 100);
	printf("字母S（不分大小写）出现量为%d,占比为%0.2f\n", (int)SCount, (SCount / StrCount) * 100);
	printf("字母T（不分大小写）出现量为%d,占比为%0.2f\n", (int)TCount, (TCount / StrCount) * 100);
	printf("字母U（不分大小写）出现量为%d,占比为%0.2f\n", (int)UCount, (UCount / StrCount) * 100);
	printf("字母V（不分大小写）出现量为%d,占比为%0.2f\n", (int)VCount, (VCount / StrCount) * 100);
	printf("字母W（不分大小写）出现量为%d,占比为%0.2f\n", (int)WCount, (WCount / StrCount) * 100);
	printf("字母X（不分大小写）出现量为%d,占比为%0.2f\n", (int)XCount, (XCount / StrCount) * 100);
	printf("字母Y（不分大小写）出现量为%d,占比为%0.2f\n", (int)YCount, (YCount / StrCount) * 100);
	printf("字母Z（不分大小写）出现量为%d,占比为%0.2f\n", (int)ZCount, (ZCount / StrCount) * 100);
	system("pause");
}

//资源显示：对影子数组进行操作，没使用的标记F 使用了标记U
int distribution()
{
	int d = 0;

	for (d = 0; d < strlen(shadow_szBuffe); d++)
	{
		if (shadow_szBuffe[d] == -5)
		{
			printf("F");
		}
		else 
		{
			printf("U");
		}
	}
	system("pause");
	return 0;
}

//清理函数，更新影子数组与主数组的状态
int clear()
{
	int i = 0;
	for ( i = 0; i < strlen(g_szBuffe); i++)
	{
		shadow_szBuffe[i] = g_szBuffe[i];
	}
	for (int k = i; k <5000- strlen(g_szBuffe); k++) //主数组没使用的分配标志
	{
		shadow_szBuffe[k] = -5;
	}
	printf("空间整理完毕\n");
	system("pause");
	return 0;
}

//显示函数 ，显示主数组内所有数据
void ShowData()  
{
	int i=0;
	int y=0;
	int Flag = 1;
	int IndexCout = 1;
	printf("数据情况如下:\n");
	for (i = 0; i < strlen(g_szBuffe); i++)
	{
		if (g_szBuffe[i] != '*')
		{
			if (Flag) 
			{	
				Flag = 0;  //分割作用
			}
			printf("%c", g_szBuffe[i]);
		}
		else
		{
			IndexCout++;
			printf("\r\n"); //打空格和换行
			Flag = 1;
		}
	}
	printf("\r\n");
	system("pause");
}


//初始化影子数组
void shadow() 
{
	for(int i = 0; i < 5000; i++)
	{
		shadow_szBuffe[i] = -5;
	}
}


//关键字搜索模式
int KeyFind()
{
	int j = 0;
	char FinData[30] = { 0 };
	char ShadowAry[0x5000] = { 0 };
	printf("请输入你要查询数据的关键字\n");
	scanf("%s", FinData);

	for (int i = 0; i <strlen(g_szBuffe); i++)   //遍历主数组输出所有符合关键字的数据
	{
		if (g_szBuffe[i] != '*')   //没找到分割符号前把元素都存入一个影子数组
		{
			ShadowAry[j]=g_szBuffe[i];
			j++;
		}
		else if (g_szBuffe[i] == '*')  //找到了
		{
			if (KMP(ShadowAry, FinData )!=0)  //KMP匹配是否带有关键字
			{
				printf("%s\r\n", ShadowAry);   //带有关键字则打印
				j = 0;
				for (int k = 0;k < 30;k++)
				{
					ShadowAry[k] = ' ';  //打印完成后清空数组 方便下一次打印
				}
			}
		}
	}
	
	system("pause");
	return  0;
}

//主函数
int main()
{
	int Input = 0;
	show(); //显示菜单
	shadow(); //初始化影子数组
	scanf("%d", &Input); //选择功能

	while (1) 
	{
		
		switch (Input)
		{
		case 1:
			Add();
			break;
		case 2:
			Del();
			break;
		case 3:
			modification();
			break;
		case 4:
			printf("1.按内容搜索   2.模糊搜索\n");
			scanf("%d", &Input);
			if (Input == 1)
			{
				Find();
			}
			else if(Input==2)
			{
				KeyFind();
			}
			break;
		case 5:
			statistics();
			break;
		case 6:
			distribution();
			break;
		case 7:
			clear();
			break;
		case 8:
			exit(0);
			break;
		default:
			break;
		}
		system("cls");
		show();
		scanf("%d", &Input);

	}
}