#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define ERROR 0;  //����״̬��ʶ
#define valid 1;  //��ȷ����״̬��ʶ


int  AddCount = 0;   //����������һ��Ԫ�ص�λ��
char g_szBuffe[0x5000] = { 0 }; //������ �洢����
char shadow_szBuffe[30] = { 0 }; //Ӱ������  ��¼������仯

void ShowData();  //��������



//�˵�����  ���Ϲ�����ʾ
void show()
{
	system("cls");
	printf("-----------------------------\n");
	printf("-------�ַ���ϵͳ------------\n");
	printf("1.����  2.ɾ��    3.�޸�-----\n");
	printf("4.����  5.ͳ��    6.��ʾ��Դ-\n");
	printf("7.��Ƭ����        8.�˳�-----\n");
	printf("��ѡ����Ҫ�Ĺ���\n");
}

//�ַ������Ӻ���
int  Add()
{
	int  i = 0;
	int  Data_Index = 0;
	//������ݵ��±�
	char SaveMark[2] = { "*" };
	//��ÿһ��Ԫ�غ�������ʶ�ָ�
	//�洢���ݺ����ı�־
	char SaveData[30] = { 0 };
	//���ܼ������ݵ�
	Data_Index = AddCount;
	//ÿ�κ���ִ��ǰ��ȡ�������һ��Ԫ��λ��
	while (1)
	{
		printf("������Ҫ������ַ���\n");

		scanf("%s", SaveData);
		if (strlen(SaveData) > 30)
		{
			printf("��������������30����\n");
			break;
		}
		
		strcat(SaveData, SaveMark);
		
		if (strlen(SaveData) > (sizeof(g_szBuffe) - strlen(SaveData)))
		{
			printf("�ռ䲻��,����ʧ��\n");
			break;
		}

		for (i = 0; i < strlen(SaveData); i++)
		{
		    g_szBuffe[Data_Index] = SaveData[i];
			shadow_szBuffe[Data_Index] = SaveData[i];
			Data_Index++;
		}		
		printf("����ɹ�");
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

//KMP����Ԫ��ƥ��
int KMP(char* origin, char* target)
{
	int i = 0; 
	int j = 0;

	int next[30];
	int Orlen = strlen(origin);  //��Ѱ����ĳ���
	int Talen = strlen(target);  //��Ѱ���ݵĳ���
	Next(target, next);

	while (i < Orlen)
	{

		if (origin[i] == target[j]&&j<Talen)  //�����ǰ�����I���ڱ�Ѱ���ݵ�I���һ�û��ȫ��ȡ�꣬�������ȡ
		{
			i++;
			j++;
		}
		if (j >=Talen)  //��J���ڵȺ򳤶Ⱥ����ȡ��ɶ���ʶ��ȫ���� ������1����ʾ�ҵ���
		{
			printf("�ҵ�\n");
			return  valid;
		}
		else if (origin[i] != target[j]) //���������
		{
			if (j == 0)  //���ұ�Ѱ���ݴ��ڵ�һλ  ��ƥ�������û�к��ʵ�
			{
				j = 0;
				i++;
			}
			else
			{
				j = next[j - 1];   // ͷλ������  �̶�ƥ�������
			}
		}
	}
	if (i > Orlen && j >Talen) //ͷ�Լ��������ݶ������� ������0  ��ʾ�Ҳ���
	{
		system("pause");
	}
	return ERROR;
}

//��������
int Find()
{
	int i = 0;
	int j = 0;
	int Data_Index = 0;
	char SaveDateTemp[] = { 0 };
	//���ܷ���ֵ
	char SaveDate[30] = { 0 };
	//��������
	char DataFind[30] = { 0 };
	//��ű�־λ֮ǰ������

	printf("��������Ҫ���ҵ�����\n");

	scanf("%s", SaveDate);

	/*������������Ѱ������*/
	for ( i = 0; i < strlen(g_szBuffe); i++)
	{
		if (g_szBuffe[i] == '*')
		{
			if (KMP(DataFind, SaveDate))
			{
				system("pause");
				return 0; //�ҵ�ֱ�ӷ���
			}
		}
		else
		{
			DataFind[Data_Index] = g_szBuffe[i];  //����*��ÿ��Ԫ�صķָ����һֱ����Ѱ���鸳ֵ ÿ����һ���ַ���
			Data_Index++;                        //�����KMP�Ա�
		}
	}
	printf("δ���ҵ�����\n");
	system("pause");
	return 0;
}


//ɾ������
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
	char SaveIndex[30] = { 0 };//����±�
	char DataDel[30] = { 0 };//���ɾ��Ŀ����±�
	char DataFind[30] = { 0 };

	ShowData();

	printf("������Ҫɾ��������\n");

	scanf("%s", SaveDate);

	for (i = 0; i < strlen(g_szBuffe); i++) //��Ѱ��Ŀ��
	{
		if (g_szBuffe[i] == '*')
		{
			MarkCount++;
			if (KMP(DataFind, SaveDate))
			{
				save = i;  //����ҵ�Ŀ���β��
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
	
	//�洢β��

	count = save;

	if (MarkCount == 1)  //ͷԪ��ֱ�Ӻ���Ԫ���ƽ�ͷԪ�صĳ���
	{
		for ( i = 0; i < strlen(g_szBuffe); i++)
		{
			g_szBuffe[i] = g_szBuffe[i +( strlen(SaveDate)+1)];
			printf("�ɹ�ɾ��Ŀ��\n");
			system("pause");
			return 0;
		}
	}
	else//��ͷԪ��
	{
		for (i = 0; i < strlen(g_szBuffe); i++)
		{
			if (flag == 0)  //����Ƿ�ʼ�ƽ�
			{
				if (i == count)     //������������Ŀ��Ԫ��β��
				{
					flag=1;  //���1
				}
			}
			if (flag == 1)    
			{
				for (i = 0; i < strlen(g_szBuffe); i++)
				{
					if (g_szBuffe[i] == '*')
					{

						if (i == count)   //�����ҵ�*�Ŷ�����Ŀ��β��
						{	
							for (k = 0; k < strlen(g_szBuffe); k++)  //����Ԫ�������ƽ�Ŀ��Ԫ�س��� ��Ŀ�긲�ǵ�
							{
								g_szBuffe[Data_Index+1] = g_szBuffe[i+1];
								Data_Index++;
								i++;
							}
							AddCount = k;   //������������һ��Ԫ��λ��
							printf("�ɹ�ɾ��Ŀ��\n");
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
	
	printf("�޷�ɾ��Ŀ��\n");
	system("pause");
	return 0;
}

//�޸ĺ���
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
	printf("������Ҫ�޸ĵ�Ŀ��\n");
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
	
	//ͬ��ɾ��Ԫ�� ����Ѱ���ޣ���ͬ�����������޸ģ����Լ�¼����Ŀ��Ԫ�ص�ͷ�Լ�β��
	count = (i-strlen(SaveData));
	saveend = i+1;
	system("pause");
	printf("�޸�Ϊ:\n");
	scanf("%s",Datamod);
	strcat(Datamod, SaveMark);

	//�ж��Ƿ񳬳�ԭ���ݳ���
	if (strlen(Datamod)-1 > strlen(SaveData))
	{
		printf("����ԭ��Χ�����к����ƶ�����\n");
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
						printf("ԭֵ�ƶ����\n");  //�����󣬼��㳬�����ȣ���Ŀ�����ݵ�β���������������ƶ���������
						break;                     //�ƶ���ɺ�������
					} 
				}

				for ( k = i; j < strlen(Datamod); k++)   //�ƶ����������ݺ� ���Ǽ���
				{
					g_szBuffe[k] = Datamod[j];
					j++;
				}
				AddCount = strlen(g_szBuffe);
				printf("�޸ĳɹ�!\n");
				system("pause");
				return 0;
			}
		}
	}

	for (int i = 0; i < strlen(g_szBuffe); i++)   //���������ȵ�ֱ�Ӹ����ϼ���
	{
		if (i == count)
		{
			for (int t = i; j<strlen(Datamod); t++)
			{	
				g_szBuffe[t] = Datamod[j];
				j++;
			}
			printf("�޸ĳɹ�!\n");
			system("pause");
			return 0;
		}
	}
	printf("�޸Ĳ��ɹ�!\n");
	system("pause");
	return 0;
}


//ͳ�ƺ��� ��ͳ�������д�Сд��ĸ�Ĵ���
void statistics()
{
	double StrCount = 0;
	double ACount=0, BCount=0, CCount=0, DCount=0, ECount=0, FCount=0, GCount=0, HCount=0, ICount=0, JCount=0, KCount=0, LCount=0, NCount=0, MCount=0, OCount=0, PCount=0, QCount=0, RCount=0;
	double SCount=0, TCount=0, UCount=0, VCount=0, WCount=0, XCount=0, YCount=0, ZCount=0;
	printf("ȥ����־��*���ַ�������Ϊ:\n");
	for (int i = 0; i < strlen(g_szBuffe); i++)
	{
		if (g_szBuffe[i] != '*')
		{
			StrCount++;
		}
	}
	printf("%d\n", (int)StrCount);

	for (int i = 0; i < StrCount; i++) //���ִ�Сд������Ԫ�� ƥ��26��ĸ ÿ��һ�����һ
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

	//����ռ��  ��ĸ����/��Ԫ�أ��������ָ�����*��
	printf("��ĸA�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2lf\n",(int)ACount,(ACount / StrCount) * 100);
	printf("��ĸB�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)BCount, (BCount / StrCount) * 100);
	printf("��ĸC�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)CCount, (CCount / StrCount) * 100);
	printf("��ĸD�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)DCount, (DCount / StrCount) * 100);
	printf("��ĸE�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)ECount, (ECount / StrCount) * 100);
	printf("��ĸF�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)FCount, (FCount / StrCount) * 100);
	printf("��ĸG�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)GCount, (GCount / StrCount) * 100);
	printf("��ĸH�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)HCount, (HCount / StrCount) * 100);
	printf("��ĸI�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)ICount, (ICount / StrCount) * 100);
	printf("��ĸJ�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)JCount, (JCount / StrCount) * 100);
	printf("��ĸK�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f%\n", (int)KCount, (KCount / StrCount) * 100);
	printf("��ĸL�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)LCount, (LCount / StrCount) * 100);
	printf("��ĸN�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)NCount, (NCount / StrCount) * 100);
	printf("��ĸM�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)MCount, (MCount / StrCount) * 100);
	printf("��ĸO�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)OCount, (OCount / StrCount) * 100);
	printf("��ĸP�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)PCount, (PCount / StrCount) * 100);
	printf("��ĸQ�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)QCount, (QCount / StrCount) * 100);
	printf("��ĸR�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)RCount, (RCount / StrCount) * 100);
	printf("��ĸS�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)SCount, (SCount / StrCount) * 100);
	printf("��ĸT�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)TCount, (TCount / StrCount) * 100);
	printf("��ĸU�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)UCount, (UCount / StrCount) * 100);
	printf("��ĸV�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)VCount, (VCount / StrCount) * 100);
	printf("��ĸW�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)WCount, (WCount / StrCount) * 100);
	printf("��ĸX�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)XCount, (XCount / StrCount) * 100);
	printf("��ĸY�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)YCount, (YCount / StrCount) * 100);
	printf("��ĸZ�����ִ�Сд��������Ϊ%d,ռ��Ϊ%0.2f\n", (int)ZCount, (ZCount / StrCount) * 100);
	system("pause");
}

//��Դ��ʾ����Ӱ��������в�����ûʹ�õı��F ʹ���˱��U
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

//������������Ӱ���������������״̬
int clear()
{
	int i = 0;
	for ( i = 0; i < strlen(g_szBuffe); i++)
	{
		shadow_szBuffe[i] = g_szBuffe[i];
	}
	for (int k = i; k <5000- strlen(g_szBuffe); k++) //������ûʹ�õķ����־
	{
		shadow_szBuffe[k] = -5;
	}
	printf("�ռ��������\n");
	system("pause");
	return 0;
}

//��ʾ���� ����ʾ����������������
void ShowData()  
{
	int i=0;
	int y=0;
	int Flag = 1;
	int IndexCout = 1;
	printf("�����������:\n");
	for (i = 0; i < strlen(g_szBuffe); i++)
	{
		if (g_szBuffe[i] != '*')
		{
			if (Flag) 
			{	
				Flag = 0;  //�ָ�����
			}
			printf("%c", g_szBuffe[i]);
		}
		else
		{
			IndexCout++;
			printf("\r\n"); //��ո�ͻ���
			Flag = 1;
		}
	}
	printf("\r\n");
	system("pause");
}


//��ʼ��Ӱ������
void shadow() 
{
	for(int i = 0; i < 5000; i++)
	{
		shadow_szBuffe[i] = -5;
	}
}


//�ؼ�������ģʽ
int KeyFind()
{
	int j = 0;
	char FinData[30] = { 0 };
	char ShadowAry[0x5000] = { 0 };
	printf("��������Ҫ��ѯ���ݵĹؼ���\n");
	scanf("%s", FinData);

	for (int i = 0; i <strlen(g_szBuffe); i++)   //����������������з��Ϲؼ��ֵ�����
	{
		if (g_szBuffe[i] != '*')   //û�ҵ��ָ����ǰ��Ԫ�ض�����һ��Ӱ������
		{
			ShadowAry[j]=g_szBuffe[i];
			j++;
		}
		else if (g_szBuffe[i] == '*')  //�ҵ���
		{
			if (KMP(ShadowAry, FinData )!=0)  //KMPƥ���Ƿ���йؼ���
			{
				printf("%s\r\n", ShadowAry);   //���йؼ������ӡ
				j = 0;
				for (int k = 0;k < 30;k++)
				{
					ShadowAry[k] = ' ';  //��ӡ��ɺ�������� ������һ�δ�ӡ
				}
			}
		}
	}
	
	system("pause");
	return  0;
}

//������
int main()
{
	int Input = 0;
	show(); //��ʾ�˵�
	shadow(); //��ʼ��Ӱ������
	scanf("%d", &Input); //ѡ����

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
			printf("1.����������   2.ģ������\n");
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