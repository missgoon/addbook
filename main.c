#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXNUM 100

//定义通讯信息结构体  保存：名称name，电话号tel，类型代码type，电邮email 
struct AddBook{
	char name[15];
	unsigned int tel;
	unsigned int type;	
	char email[30];
};

//定义一个为空的通讯录信息的全局变量 
struct AddBook nil_addbook={"",0,0,""};
//定义一个用来存放所有通讯信息的数据 
struct AddBook all_addbooks[MAXNUM]={{"",0,0,""}};
//count用来记录当前通讯录中保存的信息的条数 
unsigned int count=0;
//类型代码对应的类型名称 
char *typecode[]={"fellow","friend","business","ordinary"};

//添加通讯信息的方法 
void add_addbook(char *name,unsigned int tel,unsigned int type,char *email);
//按名称查找通讯信息的方法 
void find_addbook_by_name(struct AddBook *target,struct AddBook *result,char *name);
//按类型查找通讯信息的方法 
void find_addbook_by_type(struct AddBook *target,struct AddBook *result,unsigned int type);
//删除通讯信息的方法 
void delete_addbook(struct AddBook *target);
//从文件导入通讯信息的方法 
void import_addbook(char *filename);
//导出通讯信息到文件的方法 
void export_addbook(char *filename);

int main(int argc, char const *argv[])
{
    //用while循环一直执行 知道输入的comman等于'E' 结束程序 
	char command=' ';
	while(1){
		printf("请输入命令：\n\t输入A:增加一条通讯信息。\n\t输入N:按名称查找通讯信息。\n\t输入T:按类型查找通讯信息。\n\t输入D:删除一条通讯信息。\n\t输入I:将通讯录文件导入。\n\t输入O:将通讯信息导出到文件\n\t输入E:退出程序。\n");
		scanf("%c",&command);
		char name[15],email[30],filename[50];
		unsigned int tel=0,type=0,i=0;
		struct AddBook infos[MAXNUM]={{"",0,0,""}};
		system("cls");
		switch(command){
			case 'A':
				printf("请依次输入通讯信息的名称、电话、类型代码、电邮(如：安妮 15761673823 0 annie@email.com):\n");
				printf("类型代码：0=fellow,1=friend,2=business,3=ordinary.\n");
				scanf("%s %u %u %s",&name,&tel,&type,&email);
				//根据录入的信息 新建一条通讯信息 
				add_addbook(name,tel,type,email);
				break;
			case 'N':
				printf("请输入名称:\n");
				fflush(stdin);
				scanf("%s",&name);
				find_addbook_by_name(all_addbooks,infos,name);
				//将按名称找到的通讯信息打印出来 
				for(i=0;strcmp(infos[i].name,"")!=0;++i)
				  printf("通讯信息：\n\t名称：%s\n\t电话：%u\n\t类型：%s\n\t电邮：%s\n\t**********\n",infos[i].name,infos[i].tel,typecode[infos[i].type],infos[i].email);
				break;
			case 'T':
				printf("请输入类型代码(0=fellow,1=friend,2=business,3=ordinary):\n");
				scanf("%u",&type);
				find_addbook_by_type(all_addbooks,infos,type);
				//将按类型找到的通讯信息打印出来 
				for(i=0;strcmp(infos[i].name,"")!=0;++i)
					printf("通讯信息：\n\t名称：%s\n\t电话：%u\n\t类型：%s\n\t电邮：%s\n\t**********\n",infos[i].name,infos[i].tel,typecode[infos[i].type],infos[i].email);
				break;
			case 'D':
				printf("请输入名称:\n");
				scanf("%s",&name);
				//按名称找到要删除的通讯信息 
                find_addbook_by_name(all_addbooks,infos,name);
                //将找到的通讯信息删除 
			    delete_addbook(infos);
				break;
			case 'I':
				printf("请输入文件地址：\n");
				scanf("%s",&filename);
				//根据输入的文件地址  导入通讯信息 
				import_addbook(filename);
				break;
			case 'O':
				printf("请输入文件地址：\n");
				scanf("%s",&filename);
				//根据输入的文件地址  导出通讯信息 
				export_addbook(filename);
				break;
			case 'E':
                 // 如果输入的命令为E 则结束程勋 
				return 0;
			//若输入不为以上命令 则重新输入 
			default: printf("输入无效命令，请重新输入！\n");
		}
		system("pause");
		system("cls");
		//刷新缓冲区 
		fflush(stdin);
	}
	return 0;
}

//新增通讯信息，若同类型已有此人则询问是否覆盖。 依次传入新建的name,tel,type,email 
void add_addbook(char *name,unsigned int tel,unsigned int type,char *email){
	struct AddBook info_t[MAXNUM]={{"",0,0,""}},info_n[MAXNUM]={{"",0,0,""}};
	char flag='N';
	//查找该类型的是否有通讯信息 
	find_addbook_by_type(all_addbooks,info_t,type);
	if(strcmp(info_t[0].name,"")!=0){
        //若该类型有通讯信息  则按名称查找 
		find_addbook_by_name(info_t,info_n,name);
		//若没有则直接添加  若有则询问是添加还是覆盖 
		if(strcmp(info_n[0].name,"")!=0){
			printf("该类型已有此人，是否覆盖(Y/N):\n");
			fflush(stdin);
			scanf("%c",&flag);
		}
	}
	//覆盖就是把 相同的都删了 再新建 
	if(flag=='Y') delete_addbook(info_n);
	//新建通讯信息 
	struct AddBook new_add;
	strcpy(new_add.name,name);new_add.tel=tel;new_add.type=type;strcpy(new_add.email,email);
	//这两行  找到在all_addbooks中可以存放新建通讯信息的位置save_num 
	int save_num=0;
	for(;strcmp(all_addbooks[save_num].name,"")!=0;++save_num);
	//将新建的通讯信息放到all_addbooks中 
	all_addbooks[save_num]=new_add;
	//将count加1 
	++count;
	printf("名称为：%s的通讯信息添加成功。\n",name);
}

//按名称查找通讯信息  该方法先传入一个查找范围target，再传入一个存放输出结果的result，最后一个参数是要查询的名称name 
void find_addbook_by_name(struct AddBook *target,struct AddBook *result,char *name){
	unsigned int cnt=0,i=0,j=0;
  for(i=0;cnt<count;++i){
    //若target[i].name不为空则将cnt加1  当cnt等于当前信息总条数时，表明查询结束 
  	if(strcmp(target[i].name,"")!=0) ++cnt;
  	//如果target[i].name与name相等  则表明找到一条通讯信息  将该条信息放到result中 
  	if(strcmp(name,target[i].name)==0){ result[j]=target[i];++j;}
  }
  printf("该名称共找到%d条通讯信息。\n",j);
}

//按类型查找通讯信息  与find_addbook_by_name相似 
void find_addbook_by_type(struct AddBook *target,struct AddBook *result,unsigned int type){
	unsigned int cnt=0,i=0,j=0;
	for(i=0;cnt<count;++i){
        //若target[i].name不为空则将cnt加1  当cnt等于当前信息总条数时，表明查询结束                  
		if(strcmp(target[i].name,"")!=0) ++cnt;
		//若target[i].type与type相等  则表明找到一条通讯信息  将该条信息放到result中 
		if(type==target[i].type){result[j]=target[i];++j;}
	}
	printf("该类型共找到%d条通讯信息。\n",j);
}

//删除通讯信息   传入一个将要删除的通讯信息的集合  该方法将依次把它们删除
//删除  即把该位置的信息重置为空nil_addbook 
void delete_addbook(struct AddBook *target){
	unsigned int cnt=0;
	//删除后将count的值减1 
	for(;strcmp(target[cnt].name,"")!=0;++cnt){target[cnt]=nil_addbook;--count;}
	printf("共删除%d条通讯信息。\n",cnt);
}

//导入通讯信息  传入导入的文件的文件名 
void import_addbook(char *filename){
    //定义文件指针 
	FILE *fp;  
	unsigned int save_num=0,tel=0,type=0,cnt=0;
	char name[15],email[30];
  //打开文件 
  if((fp=fopen(filename,"r"))==NULL){printf("Cannot open this file.");exit(1);}    
  while(!feof(fp)){
    //从文件中读入一条通讯信息 
  	fscanf(fp,"%s\n%u\n%u\n%s\n",&name,&tel,&type,&email);
  	//用读入的通讯信息创建 
  	add_addbook(name,tel,type,email);
    ++cnt;
  }
  printf("成功从%s文件中导入%u条数据。\n",filename,cnt);
  //关闭文件 
  fclose(fp);  
};

//导出通讯信息  与import_addbook相似 
void export_addbook(char *filename){
	FILE *fp;  
	int i=0;
  if((fp=fopen(filename,"w"))==NULL){printf("Cannot open this file.");exit(1);}    
  //将一条通讯信息写入到文件 
  for(;i<count;++i) fprintf(fp,"%s\n%u\n%u\n%s\n",all_addbooks[i].name,all_addbooks[i].tel,all_addbooks[i].type,all_addbooks[i].email);
  printf("成功导出%u条数据到%s文件中。\n",i,filename);
  fclose(fp); 
};
