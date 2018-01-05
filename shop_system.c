#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAXCODE 20
//商品数量
 
void boundar(); 
int boundar_choice();
void info_init(); 
void info_change();
void info_dele();
void info_search();
void info_flush();
void OutputAll();
void info_output(int i);
int info_search_model(char name_search[]);
void info_insert();
 
struct info{
	int code;
	char name[30];
	int amount;
	float price;
}infor[MAXCODE]={0};

int main(void)
{
	printf("                          超市商品管理系统v0.9\n");
	boundar();
	boundar_choice();
	return 0;
}

void boundar()//界面 
{
	printf("        *********************************************************\n\
        *********************************************************\n\
	**                                                     **\n\
	**        按 键                       功 能            **\n\
	**                                                     **\n\
	**          1                      录入商品信息        **\n\
	**                                                     **\n\
	**          2                      修改商品信息        **\n\
	**                                                     **\n\
	**          3                      删除商品信息        **\n\
	**                                                     **\n\
	**          4                      查找商品信息        **\n\
	**                                                     **\n\
	**          5                      插入商品信息        **\n\
	**                                                     **\n\
	**          6                       保存并退出         **\n\
	**                            (退出需输入两次以确认）  **\n\
	*********************************************************\n\
	*********************************************************\n\n\n");
}

int boundar_choice()//功能选择 
{
	int choice,flag=0;

	do{
		printf("\n        请输入你要使用的功能：");
		scanf(" %d",&choice);
		switch (choice){
			case 1:info_init();break;
			case 2:info_change();break;
			case 3:info_dele();break;
			case 4:info_search();break;
			case 5:info_insert();break;
			case 6:info_flush();break;
			default:;break;
		}
	}while (choice!=6);
}

void info_init()//读入信息，大功能一 
{
	FILE *fp;
	int i=0,*j=0;
	struct info *p_infor; 
	
	fp=fopen("message.txt","r");
	if (fp==NULL){
		printf("        文件不存在或无法打开\n");
		exit(EXIT_FAILURE);
	}
	
	p_infor=infor;
	do{
		fscanf(fp,"%d %d %f %s",&p_infor->code,
				&p_infor->amount,&p_infor->price,&p_infor->name);
		p_infor++;
		*j++;
	}while (!feof(fp));
	
	fclose(fp);
}

void info_flush()//输出到文件，保存并退出，大功能六 
{
	FILE *fp;
	int i=0;
	fp=fopen("message.txt","w");
	if(fp==NULL){
		printf("        文件不存在或无法打开\n");
		exit(EXIT_FAILURE);
	}else{
		for(i=0;i<MAXCODE&&infor[i].code!=0;i++){
			if (infor[i].code==-1)
				continue;
			fprintf(fp,"%d %d %.2f %s\n",infor[i].code,infor[i].amount,infor[i].price,infor[i].name);
		}
	}
	fclose(fp);
}

void OutputAll()//输出全部（未在程序中实装 ） 
{
	int i;
	for(i=0;i<MAXCODE&&infor[i].code!=0;i++){
		printf("%d %d %.2f %s\n",infor[i].code,infor[i].amount,infor[i].price,infor[i].name);
	}
}

void info_output(int i)//输出单个（未在程序中实装 ） 
{
	printf("%d %d %.2f %s\n",infor[i].code,infor[i].amount,infor[i].price,infor[i].name);
}

void info_change()//修改条目内容,大功能二
{
	char name_search[30];
	int i;
	
	i=info_search_model(name_search);
	printf("        请输入更新后的数量和价格：");
	scanf("%d %f",&infor[i].amount,&infor[i].price);
	printf("        已修改,将返回到功能选择界面\n");
}

void info_dele()//删除条目，大功能三 ，将编号设为-1，便于之后插入时位置的检测和最后的输出 
{
	char name_search[30];
	int i,a;
	
	i=info_search_model(name_search);
	infor[i].code = -1; 
	printf("        已删除\n"); 
}

void info_search()//内容搜索，大功能四 
{
	char name_search[30];
	int i,a,flag=0;
	
	printf("        请输入要查找的商品名称：");
 	scanf("%s",name_search);
 	for (i=0;i<MAXCODE&&infor[i].code!=0;i++){
		if (infor[i].code==-1)
 			continue;
		if (strcmp(name_search,infor[i].name)==0){
			printf("        已找到\n        名称 数量 价格\n");
			printf("         %s  %d  %.2f\n",infor[i].name,infor[i].amount,infor[i].price);
			flag=1;
			break;
		}
 	}
	if (flag==0){
		printf("        未找到，返回选择界面请输入0,重新查找请输入1：");
			scanf(" %d",&a);
		if (a==1)
			info_search();
		else
			boundar_choice();
	}
}

int info_search_model(char name_search[])//用于各功能的搜索模块 
{
	int i,a,flag=0;
	
	printf("        请输入要查找的商品名称：");
 	scanf("%s",name_search);
 	for (i=0;i<MAXCODE&&infor[i].code!=0;i++){
		if (infor[i].code==-1)
 			continue;
		if (strcmp(name_search,infor[i].name)==0){
			printf("        已找到\n        名称 数量 价格\n");
			printf("         %s  %d  %.2f\n",infor[i].name,infor[i].amount,infor[i].price);
			flag=1;
			break;
		}
 	}
	if (flag==0){
		printf("        未找到，返回选择界面请输入0,重新查找请输入1：");
			scanf(" %d",&a);
		if (a==1)
			info_search();
		else
			boundar_choice();
	}
 	return i;
}

void info_insert()//信息的插入，大功能五 
{
	int i,flag=0;
	
	for (i=0;i<MAXCODE;i++){
		if (infor[i].code==0||infor[i].code==-1){
			flag=1;
			break;
		}
	}
	if (flag==1){
		for (i=0;i<MAXCODE;i++){
			if (infor[i].code==0||infor[i].code==-1){
				infor[i].code=i;
				printf("        请输入你要增加的商品的名称:");
				scanf(" %s",&infor[i].name);
				printf("\n        请输入你要增加的商品的数量:");
				scanf(" %d",&infor[i].amount);
				printf("\n        请输入你要增加的商品的价格:");
				scanf(" %f",&infor[i].price);
				printf("        增加成功\n"); 
				break;
			}
		}
	}else
		printf("        商品库已满\n");
} 
