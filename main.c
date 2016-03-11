#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXNUM 100

//����ͨѶ��Ϣ�ṹ��  ���棺����name���绰��tel�����ʹ���type������email 
struct AddBook{
	char name[15];
	unsigned int tel;
	unsigned int type;	
	char email[30];
};

//����һ��Ϊ�յ�ͨѶ¼��Ϣ��ȫ�ֱ��� 
struct AddBook nil_addbook={"",0,0,""};
//����һ�������������ͨѶ��Ϣ������ 
struct AddBook all_addbooks[MAXNUM]={{"",0,0,""}};
//count������¼��ǰͨѶ¼�б������Ϣ������ 
unsigned int count=0;
//���ʹ����Ӧ���������� 
char *typecode[]={"fellow","friend","business","ordinary"};

//���ͨѶ��Ϣ�ķ��� 
void add_addbook(char *name,unsigned int tel,unsigned int type,char *email);
//�����Ʋ���ͨѶ��Ϣ�ķ��� 
void find_addbook_by_name(struct AddBook *target,struct AddBook *result,char *name);
//�����Ͳ���ͨѶ��Ϣ�ķ��� 
void find_addbook_by_type(struct AddBook *target,struct AddBook *result,unsigned int type);
//ɾ��ͨѶ��Ϣ�ķ��� 
void delete_addbook(struct AddBook *target);
//���ļ�����ͨѶ��Ϣ�ķ��� 
void import_addbook(char *filename);
//����ͨѶ��Ϣ���ļ��ķ��� 
void export_addbook(char *filename);

int main(int argc, char const *argv[])
{
    //��whileѭ��һֱִ�� ֪�������comman����'E' �������� 
	char command=' ';
	while(1){
		printf("���������\n\t����A:����һ��ͨѶ��Ϣ��\n\t����N:�����Ʋ���ͨѶ��Ϣ��\n\t����T:�����Ͳ���ͨѶ��Ϣ��\n\t����D:ɾ��һ��ͨѶ��Ϣ��\n\t����I:��ͨѶ¼�ļ����롣\n\t����O:��ͨѶ��Ϣ�������ļ�\n\t����E:�˳�����\n");
		scanf("%c",&command);
		char name[15],email[30],filename[50];
		unsigned int tel=0,type=0,i=0;
		struct AddBook infos[MAXNUM]={{"",0,0,""}};
		system("cls");
		switch(command){
			case 'A':
				printf("����������ͨѶ��Ϣ�����ơ��绰�����ʹ��롢����(�磺���� 15761673823 0 annie@email.com):\n");
				printf("���ʹ��룺0=fellow,1=friend,2=business,3=ordinary.\n");
				scanf("%s %u %u %s",&name,&tel,&type,&email);
				//����¼�����Ϣ �½�һ��ͨѶ��Ϣ 
				add_addbook(name,tel,type,email);
				break;
			case 'N':
				printf("����������:\n");
				fflush(stdin);
				scanf("%s",&name);
				find_addbook_by_name(all_addbooks,infos,name);
				//���������ҵ���ͨѶ��Ϣ��ӡ���� 
				for(i=0;strcmp(infos[i].name,"")!=0;++i)
				  printf("ͨѶ��Ϣ��\n\t���ƣ�%s\n\t�绰��%u\n\t���ͣ�%s\n\t���ʣ�%s\n\t**********\n",infos[i].name,infos[i].tel,typecode[infos[i].type],infos[i].email);
				break;
			case 'T':
				printf("���������ʹ���(0=fellow,1=friend,2=business,3=ordinary):\n");
				scanf("%u",&type);
				find_addbook_by_type(all_addbooks,infos,type);
				//���������ҵ���ͨѶ��Ϣ��ӡ���� 
				for(i=0;strcmp(infos[i].name,"")!=0;++i)
					printf("ͨѶ��Ϣ��\n\t���ƣ�%s\n\t�绰��%u\n\t���ͣ�%s\n\t���ʣ�%s\n\t**********\n",infos[i].name,infos[i].tel,typecode[infos[i].type],infos[i].email);
				break;
			case 'D':
				printf("����������:\n");
				scanf("%s",&name);
				//�������ҵ�Ҫɾ����ͨѶ��Ϣ 
                find_addbook_by_name(all_addbooks,infos,name);
                //���ҵ���ͨѶ��Ϣɾ�� 
			    delete_addbook(infos);
				break;
			case 'I':
				printf("�������ļ���ַ��\n");
				scanf("%s",&filename);
				//����������ļ���ַ  ����ͨѶ��Ϣ 
				import_addbook(filename);
				break;
			case 'O':
				printf("�������ļ���ַ��\n");
				scanf("%s",&filename);
				//����������ļ���ַ  ����ͨѶ��Ϣ 
				export_addbook(filename);
				break;
			case 'E':
                 // ������������ΪE �������ѫ 
				return 0;
			//�����벻Ϊ�������� ���������� 
			default: printf("������Ч������������룡\n");
		}
		system("pause");
		system("cls");
		//ˢ�»����� 
		fflush(stdin);
	}
	return 0;
}

//����ͨѶ��Ϣ����ͬ�������д�����ѯ���Ƿ񸲸ǡ� ���δ����½���name,tel,type,email 
void add_addbook(char *name,unsigned int tel,unsigned int type,char *email){
	struct AddBook info_t[MAXNUM]={{"",0,0,""}},info_n[MAXNUM]={{"",0,0,""}};
	char flag='N';
	//���Ҹ����͵��Ƿ���ͨѶ��Ϣ 
	find_addbook_by_type(all_addbooks,info_t,type);
	if(strcmp(info_t[0].name,"")!=0){
        //����������ͨѶ��Ϣ  �����Ʋ��� 
		find_addbook_by_name(info_t,info_n,name);
		//��û����ֱ�����  ������ѯ������ӻ��Ǹ��� 
		if(strcmp(info_n[0].name,"")!=0){
			printf("���������д��ˣ��Ƿ񸲸�(Y/N):\n");
			fflush(stdin);
			scanf("%c",&flag);
		}
	}
	//���Ǿ��ǰ� ��ͬ�Ķ�ɾ�� ���½� 
	if(flag=='Y') delete_addbook(info_n);
	//�½�ͨѶ��Ϣ 
	struct AddBook new_add;
	strcpy(new_add.name,name);new_add.tel=tel;new_add.type=type;strcpy(new_add.email,email);
	//������  �ҵ���all_addbooks�п��Դ���½�ͨѶ��Ϣ��λ��save_num 
	int save_num=0;
	for(;strcmp(all_addbooks[save_num].name,"")!=0;++save_num);
	//���½���ͨѶ��Ϣ�ŵ�all_addbooks�� 
	all_addbooks[save_num]=new_add;
	//��count��1 
	++count;
	printf("����Ϊ��%s��ͨѶ��Ϣ��ӳɹ���\n",name);
}

//�����Ʋ���ͨѶ��Ϣ  �÷����ȴ���һ�����ҷ�Χtarget���ٴ���һ�������������result�����һ��������Ҫ��ѯ������name 
void find_addbook_by_name(struct AddBook *target,struct AddBook *result,char *name){
	unsigned int cnt=0,i=0,j=0;
  for(i=0;cnt<count;++i){
    //��target[i].name��Ϊ����cnt��1  ��cnt���ڵ�ǰ��Ϣ������ʱ��������ѯ���� 
  	if(strcmp(target[i].name,"")!=0) ++cnt;
  	//���target[i].name��name���  ������ҵ�һ��ͨѶ��Ϣ  ��������Ϣ�ŵ�result�� 
  	if(strcmp(name,target[i].name)==0){ result[j]=target[i];++j;}
  }
  printf("�����ƹ��ҵ�%d��ͨѶ��Ϣ��\n",j);
}

//�����Ͳ���ͨѶ��Ϣ  ��find_addbook_by_name���� 
void find_addbook_by_type(struct AddBook *target,struct AddBook *result,unsigned int type){
	unsigned int cnt=0,i=0,j=0;
	for(i=0;cnt<count;++i){
        //��target[i].name��Ϊ����cnt��1  ��cnt���ڵ�ǰ��Ϣ������ʱ��������ѯ����                  
		if(strcmp(target[i].name,"")!=0) ++cnt;
		//��target[i].type��type���  ������ҵ�һ��ͨѶ��Ϣ  ��������Ϣ�ŵ�result�� 
		if(type==target[i].type){result[j]=target[i];++j;}
	}
	printf("�����͹��ҵ�%d��ͨѶ��Ϣ��\n",j);
}

//ɾ��ͨѶ��Ϣ   ����һ����Ҫɾ����ͨѶ��Ϣ�ļ���  �÷��������ΰ�����ɾ��
//ɾ��  ���Ѹ�λ�õ���Ϣ����Ϊ��nil_addbook 
void delete_addbook(struct AddBook *target){
	unsigned int cnt=0;
	//ɾ����count��ֵ��1 
	for(;strcmp(target[cnt].name,"")!=0;++cnt){target[cnt]=nil_addbook;--count;}
	printf("��ɾ��%d��ͨѶ��Ϣ��\n",cnt);
}

//����ͨѶ��Ϣ  ���뵼����ļ����ļ��� 
void import_addbook(char *filename){
    //�����ļ�ָ�� 
	FILE *fp;  
	unsigned int save_num=0,tel=0,type=0,cnt=0;
	char name[15],email[30];
  //���ļ� 
  if((fp=fopen(filename,"r"))==NULL){printf("Cannot open this file.");exit(1);}    
  while(!feof(fp)){
    //���ļ��ж���һ��ͨѶ��Ϣ 
  	fscanf(fp,"%s\n%u\n%u\n%s\n",&name,&tel,&type,&email);
  	//�ö����ͨѶ��Ϣ���� 
  	add_addbook(name,tel,type,email);
    ++cnt;
  }
  printf("�ɹ���%s�ļ��е���%u�����ݡ�\n",filename,cnt);
  //�ر��ļ� 
  fclose(fp);  
};

//����ͨѶ��Ϣ  ��import_addbook���� 
void export_addbook(char *filename){
	FILE *fp;  
	int i=0;
  if((fp=fopen(filename,"w"))==NULL){printf("Cannot open this file.");exit(1);}    
  //��һ��ͨѶ��Ϣд�뵽�ļ� 
  for(;i<count;++i) fprintf(fp,"%s\n%u\n%u\n%s\n",all_addbooks[i].name,all_addbooks[i].tel,all_addbooks[i].type,all_addbooks[i].email);
  printf("�ɹ�����%u�����ݵ�%s�ļ��С�\n",i,filename);
  fclose(fp); 
};
