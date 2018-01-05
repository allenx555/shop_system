#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAXCODE 20
//��Ʒ����
 
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
	printf("                          ������Ʒ����ϵͳv0.9\n");
	boundar();
	boundar_choice();
	return 0;
}

void boundar()//���� 
{
	printf("        *********************************************************\n\
        *********************************************************\n\
	**                                                     **\n\
	**        �� ��                       �� ��            **\n\
	**                                                     **\n\
	**          1                      ¼����Ʒ��Ϣ        **\n\
	**                                                     **\n\
	**          2                      �޸���Ʒ��Ϣ        **\n\
	**                                                     **\n\
	**          3                      ɾ����Ʒ��Ϣ        **\n\
	**                                                     **\n\
	**          4                      ������Ʒ��Ϣ        **\n\
	**                                                     **\n\
	**          5                      ������Ʒ��Ϣ        **\n\
	**                                                     **\n\
	**          6                       ���沢�˳�         **\n\
	**                            (�˳�������������ȷ�ϣ�  **\n\
	*********************************************************\n\
	*********************************************************\n\n\n");
}

int boundar_choice()//����ѡ�� 
{
	int choice,flag=0;

	do{
		printf("\n        ��������Ҫʹ�õĹ��ܣ�");
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

void info_init()//������Ϣ������һ 
{
	FILE *fp;
	int i=0,*j=0;
	struct info *p_infor; 
	
	fp=fopen("message.txt","r");
	if (fp==NULL){
		printf("        �ļ������ڻ��޷���\n");
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

void info_flush()//������ļ������沢�˳��������� 
{
	FILE *fp;
	int i=0;
	fp=fopen("message.txt","w");
	if(fp==NULL){
		printf("        �ļ������ڻ��޷���\n");
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

void OutputAll()//���ȫ����δ�ڳ�����ʵװ �� 
{
	int i;
	for(i=0;i<MAXCODE&&infor[i].code!=0;i++){
		printf("%d %d %.2f %s\n",infor[i].code,infor[i].amount,infor[i].price,infor[i].name);
	}
}

void info_output(int i)//���������δ�ڳ�����ʵװ �� 
{
	printf("%d %d %.2f %s\n",infor[i].code,infor[i].amount,infor[i].price,infor[i].name);
}

void info_change()//�޸���Ŀ����,���ܶ�
{
	char name_search[30];
	int i;
	
	i=info_search_model(name_search);
	printf("        ��������º�������ͼ۸�");
	scanf("%d %f",&infor[i].amount,&infor[i].price);
	printf("        ���޸�,�����ص�����ѡ�����\n");
}

void info_dele()//ɾ����Ŀ�������� ���������Ϊ-1������֮�����ʱλ�õļ���������� 
{
	char name_search[30];
	int i,a;
	
	i=info_search_model(name_search);
	infor[i].code = -1; 
	printf("        ��ɾ��\n"); 
}

void info_search()//���������������� 
{
	char name_search[30];
	int i,a,flag=0;
	
	printf("        ������Ҫ���ҵ���Ʒ���ƣ�");
 	scanf("%s",name_search);
 	for (i=0;i<MAXCODE&&infor[i].code!=0;i++){
		if (infor[i].code==-1)
 			continue;
		if (strcmp(name_search,infor[i].name)==0){
			printf("        ���ҵ�\n        ���� ���� �۸�\n");
			printf("         %s  %d  %.2f\n",infor[i].name,infor[i].amount,infor[i].price);
			flag=1;
			break;
		}
 	}
	if (flag==0){
		printf("        δ�ҵ�������ѡ�����������0,���²���������1��");
			scanf(" %d",&a);
		if (a==1)
			info_search();
		else
			boundar_choice();
	}
}

int info_search_model(char name_search[])//���ڸ����ܵ�����ģ�� 
{
	int i,a,flag=0;
	
	printf("        ������Ҫ���ҵ���Ʒ���ƣ�");
 	scanf("%s",name_search);
 	for (i=0;i<MAXCODE&&infor[i].code!=0;i++){
		if (infor[i].code==-1)
 			continue;
		if (strcmp(name_search,infor[i].name)==0){
			printf("        ���ҵ�\n        ���� ���� �۸�\n");
			printf("         %s  %d  %.2f\n",infor[i].name,infor[i].amount,infor[i].price);
			flag=1;
			break;
		}
 	}
	if (flag==0){
		printf("        δ�ҵ�������ѡ�����������0,���²���������1��");
			scanf(" %d",&a);
		if (a==1)
			info_search();
		else
			boundar_choice();
	}
 	return i;
}

void info_insert()//��Ϣ�Ĳ��룬������ 
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
				printf("        ��������Ҫ���ӵ���Ʒ������:");
				scanf(" %s",&infor[i].name);
				printf("\n        ��������Ҫ���ӵ���Ʒ������:");
				scanf(" %d",&infor[i].amount);
				printf("\n        ��������Ҫ���ӵ���Ʒ�ļ۸�:");
				scanf(" %f",&infor[i].price);
				printf("        ���ӳɹ�\n"); 
				break;
			}
		}
	}else
		printf("        ��Ʒ������\n");
} 
