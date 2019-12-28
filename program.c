#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
# define LEN sizeof(struct Student)
struct Student {
char num[10]; /*学号*/
char name[20]; /*姓名*/
char sex[10];  /*性别*/
int age;       /*年龄*/
char phone[12];/*电话*/
char qq[12];   /*QQ号*/
float cscore;  /*C语言成绩*/
float escore;  /*英语成绩*/
struct Student *next;
};
char filename[30];//全局变量，用来保存要打开的文件名字 
/*生成链表*/
struct Student *Creat(int n) 
{	
    void menu_print_in(void);
struct Student *head;//结构型指针
struct Student *p1, *p2; 
	//向操作系统发送控制台命令行，清除屏幕
for(int i=1;i<n+1;i++) 
{		
    p1 = (struct Student*)malloc(LEN);		
    menu_print_in();//输入输出提示栏		
    scanf("%s%s%s%d%s%s%f%f",p1->num,p1->name,p1->sex,&p1->age,p1->phone,p1->qq,&p1->cscore,&p1->escore);		
    p1->next = NULL;
    if(i==1) 
    {
        head = p2 = p1;		
    }		
    else 
    {			
        p2->next = p1;
    	p2 = p1;		
                
    }	
}	
    return(head);
    
    } 
/*数据存盘(wb只写)*/
void WriteData_wb(struct Student *head)//此时返回的是文件的头指针 
{	FILE *fp;	
    struct Student *p;	
    if((fp = fopen(filename, "wb"))==NULL)//第一个参数是文件名，第二个参数是打开模式，若没有指定路径则默认本地工作路径	
    printf("\a error! Can not open the file!");	
    p = head;	
    while(p!=NULL) 
    {		
        if(fwrite(p,LEN,1,fp)!=1) 
        {			
            printf("写入数据出错\n");			
            fclose(fp);			
            return;
        }		
            p=p->next;	
        }	
            fclose(fp);
        } 
/*数据存盘(ab追加)*///追加时返回的指针是文件末尾的指针
void WriteData_ab(struct Student *head) 
{	
    FILE *fp;//据说这是一个文件类型指针？	
    struct Student *p;	
    if((fp = fopen(filename, "ab"))==NULL)	//试错
        printf("\a error! Can not open the file!");	
        p = head;	
     while(p!=NULL) 
        {	
            if(fwrite(p,LEN,1,fp)!=1) 
            {
                printf("写入数据出错\n");	
                fclose(fp);			
            return;		
            }		
            p=p->next;	
            }	
            fclose(fp);
            }  
/*读取数据*//*读取数据文件保存到链表中 ，返回指向此链表头指针*/
    struct Student *ReadData(void) 
    {	struct Student *head = NULL;	
    struct Student *p1, *p2;
    FILE *fp;	
    if((fp=fopen(filename,"rb+"))==NULL)	
    {		printf("打开文件出错\n");		exit(0);	}	
    while(!feof(fp)) 
    {		
        if((p1=(struct Student*)malloc(LEN))==NULL)
        {			
            printf("内存申请出错\n");			
            fclose(fp);			
            exit(0);		
            }		
        if(fread(p1,LEN,1,fp)!=1)
        {	
            free(p1);			
            break;		
        }		
        if(head==NULL)		
        head=p2=p1;		
        else{			
            p2->next=p1;			
            p2=p1;		}	}	
            fclose(fp);	
            return (head);} 
/*【1】全量查询*/
void Print_inquire_all(void) {	
    void menu_print_out(void);	
    struct Student *pt;	pt = ReadData();	
    menu_print_out();	
    do {		
    printf("%-10s%6s%8s%4d%13s%11s  %4.1f %4.1f %4.1f %4.1f\n",	pt->num,pt->name,pt->sex,pt->age,pt->phone,pt->qq,pt->cscore,		pt->escore,(pt->cscore+pt->escore)/2,pt->cscore+pt->escore);		
    pt = pt->next;	}
    while(pt!=NULL);	
    printf("\n\n");} 
/*【2】学号查询*/
    int Print_inquire_num() 
    {	
    void menu_print_out(void);	
    struct Student *pt;	
    char str_num[10];	
    printf("◎请输入您要查询的学号:");	
    scanf("%s", str_num);	
    pt = ReadData();	
    menu_print_out();	
    do {		
        if(strcmp(pt->num,str_num)==0) 
        {			
            printf("%-10s%6s%8s%4d%13s%11s  %4.1f %4.1f %4.1f %4.1f\n",			pt->num,pt->name,pt->sex,pt->age,pt->phone,pt->qq,pt->cscore,			pt->escore,(pt->cscore+pt->escore)/2,pt->cscore+pt->escore);			
            printf("\n\n");			
            return 0;		
            }		
            pt = pt->next;	
            }
            while(pt!=NULL);	
            printf("数据库中没有存储您要查询的数据！\n");	
            printf("\n\n");	return 0;} 
/*【3】姓名查询*/
            int Print_inquire_name() 
            {	
                void menu_print_out(void);	
                struct Student *pt;	
                char str_name[20];	
                printf("◎请输入您要查询的姓名:");	
                scanf("%s", str_name);	
                pt = ReadData();	
                menu_print_out();	
                do {		
                    if(strcmp(pt->name,str_name)==0) 
                    {			
                        printf("%-10s%6s%8s%4d%13s%11s  %4.1f %4.1f %4.1f %4.1f\n",			pt->num,pt->name,pt->sex,pt->age,pt->phone,pt->qq,pt->cscore,			pt->escore,(pt->cscore+pt->escore)/2,pt->cscore+pt->escore);			
                        printf("\n\n");			
                        return 0;		
                        }		
                        pt = pt->next;	
                        }
                        while(pt!=NULL);	
                        printf("数据库中没有存储您要查询的数据！\n");	
                        printf("\n\n");	
                        return 0;} 
/*【4】模糊查询*/
        int Print_inquire_fuzzy(void) 
            {	void menu_print_out(void);	
                struct Student *pt;	
                char str_find[20];	
                int m = 0;	
                printf("◎请输入您要查询的关键词:");	
                scanf("%s", str_find);	
                pt = ReadData();	
                menu_print_out();	
                do {		
                    if(strstr(pt->num,str_find)!=0||strstr(pt->name,str_find)!=0		||strstr(pt->sex,str_find)!=0||strstr(pt->phone,str_find)!=0		||strstr(pt->qq,str_find)!=0) 
                    {			
                    printf("%-10s%6s%8s%4d%13s%11s  %4.1f %4.1f %4.1f %4.1f\n",			pt->num,pt->name,pt->sex,pt->age,pt->phone,pt->qq,pt->cscore,			pt->escore,(pt->cscore+pt->escore)/2,pt->cscore+pt->escore);			
                    m = 1;		
                    }		
                pt = pt->next;	
                    }
                while(pt!=NULL);	
                if(!m)		
                printf("数据库中没有存储您要查询的数据！\n");	
                printf("\n\n");	return 0;
                } 
/*成绩统计*/
    int Print_inquire_stats(void) 
    {	struct Student *head, *p1;	float CMIN, CMAX, EMIN, EMAX, SMIN, SMAX;	
    head = ReadData();	
    p1 = head;	
    CMIN = CMAX = p1->cscore;	
    EMIN = EMAX = p1->escore;	
    SMIN = SMAX = p1->cscore + p1->escore;	
    while(p1->next!=NULL) 
    {		
        if(p1->cscore > CMAX) 
        {			CMAX = p1->cscore;		}		
        if(p1->cscore < CMIN) 
        {			CMIN = p1->cscore;		}		
        if(p1->escore > EMAX) 
        {			EMAX = p1->escore;		}		
        if(p1->escore < EMIN) 
        {			EMIN = p1->escore;		}		
        if((p1->cscore + p1->escore) > SMAX) 
        {			SMAX = (p1->cscore + p1->escore);		}		
        if((p1->cscore + p1->escore) < SMIN) 
        {			SMIN = (p1->cscore + p1->escore);		}		
        p1 = p1->next;	
        }	
        printf("\n");	
        printf("◎数据库中C语言最高分为:%4.1f \n", CMAX);	
        printf("◎数据库中C语言最低分为:%4.1f \n\n", CMIN);	
        printf("◎数据库中英语最高分为:%4.1f \n", EMAX);
        printf("◎数据库中英语最低分为:%4.1f \n\n", EMIN);	
        printf("◎数据库中总成绩最高分为:%4.1f \n", SMAX);	
        printf("◎数据库中总成绩最低分为:%4.1f \n\n", SMIN);	
        printf("\n");	
        printf("ps：更多功能正在开发中，敬请期待。\n（我也不清楚啥时候会有新功能上线)\n\n");	
        return 0;
        } 
/*【1】修改数据之删除记录*/
int Delete() 
{	
    struct Student *pt1, *pt2, *head;	
    char str_num[20];	              
    printf("\n◎请输入您要删除的学号信息:");	
    scanf("%s", str_num);	
    pt1 = ReadData();	
    pt2 = pt1->next;	
    head = pt1;	
    while(pt2!=NULL) 
    {if(strcmp(pt1->num,str_num)==0) 
    {WriteData_wb(pt2);		}		
    else if(strcmp(pt2->num,str_num)==0) 
    {	pt1->next = pt2->next;			
    WriteData_wb(head);		
    }		
    pt2 = pt2->next;		
    pt1 = pt1->next;	
    }	
    if(pt2!=NULL)	
    printf("数据库中没有存储您要删除的数据！\n");	
    printf("\n\n");	return 0;} 
/*【2】修改数据之修改记录*/        
    int Amend()
     {	void menu_print_in(void);
     	struct Student *pt1, *pt2, *head;
        char str_num[20];	
        printf("◎请输入您要修改的学号信息:");	
        scanf("%s", str_num);	
        pt1 = ReadData();	
        pt2 = pt1->next;	
        head = pt1;
    while(pt2!=NULL)
    {
    if(strcmp(pt1->num,str_num)==0) 
    {	
        menu_print_in();			
        scanf("%s%s%s%d%s%s%f%f",pt1->num,pt1->name,pt1->sex,			&pt1->age,pt1->phone,pt1->qq,&pt1->cscore,&pt1->escore);			
        WriteData_wb(head);		
        }		
    else if(strcmp(pt2->num,str_num)==0) 
    {	
        menu_print_in();			
        scanf("%s%s%s%d%s%s%f%f",pt2->num,pt2->name,pt2->sex,			&pt2->age,pt2->phone,pt2->qq,&pt2->cscore,&pt2->escore);			
        WriteData_wb(head);		
    }		
    pt2 = pt2->next;		
    pt1 = pt1->next;	
    }	
    if(pt2!=NULL)	
    printf("数据库中没有存储您要删除的数据！\n");	
    return 0;
    } 
    /*【3】修改数据之整理数据*/
    int Neaten() 
    {	struct Student *first;	
    struct Student *tail;	
    struct Student *p_min;	
    struct Student *min;	
    struct Student *p;	
    struct Student *head;		
    head = ReadData();	
    first = NULL;	
    while(head!=NULL) 
    {		for(p=head,min=head; p->next!=NULL; p=p->next)//指针版循环 
            {
                if(strcmp(p->next->num,min->num)<0) 
            {	
                p_min = p;	
                min = p->next;		
                    }	
            }		
        if(first==NULL) 
        {			
            first = min;//对头部指针和尾部指针进行初始化吗？
            tail = min;		}		
        else 
        {			
            tail->next = min;			
            tail = min;		
            }		
    if(min==head) 
    {			
        head = head->next;		
        }
    else 
    {     
        p_min->next = min->next;		
        }	
    }	
    if(first!=NULL) 
    {		
        tail->next = NULL;	
        }	
    head = first; 	
    WriteData_wb(head);
    return 0;
    } 
    /*输入写入数据的数量*/
    int Creat_num(void) 
    {	printf(" 	注意：由于技术落后，性别请使用“male”或者“female”进行输入\n");
        printf("    手机号与QQ号最多仅支持13位输入\n") ;
        printf("\n◎请输入您此次要添加的数据个数:");	
        int n;	
    if(scanf("%d", &n)!=1) 
    {		
        printf("\a error!");	
        }	
        return n;} 
    /*选择将要打开的文件*/
    int File_name() 
       {	
        printf("\n◎请输入您想要打开的文件:");	
        if(scanf("%s", filename)!=1)	
            printf("\a error!");	
            return 0;
            } 
        /*主菜单*/
        void menu(void) 
        {	
            void menu_add(void);	
            void menu_inquire(void);	
            void menu_amend(void);	
            printf("              ╭════════╮              \n");	
            printf("╭══════╣学生管理系统V1.2╠════════════════════╮\n");	
            printf("║            ╰════════╯                      ║\n");	
            printf("║   【1】添加数据           【3】修改数据    ║\n");	
            printf("║                                            ║\n");	
            printf("║   【2】查询数据           【4】退出系统    ║\n");	
            printf("║                                            ║\n");	
            printf("╰═══════════════════════════════════════════╯\n");	
            printf(" 	注意：由于技术落后，性别请使用“male”或者“female”进行输入\n");
            printf("    手机号与QQ号最多仅支持13位输入\n") ;
            printf("◎请输入功能前的序号进入相应的工具:【   】\b\b");
            
           int a = 0;	
           a = getchar(); 	
        while(a!='1'&&a!='2'&&a!='3'&&a!='4') 
        {		printf("error! please input the right number!\n");		
                putchar('\a');		
                getchar();
                printf("◎请重新输入功能前的序号进入相应的工具:【   】\b\b");		
                a = getchar();	
                }	
        switch(a) 
        {		
            case '1': File_name();menu_add();		break;		
            case '2': File_name();menu_inquire();		break;		
            case '3': File_name();menu_amend();		break;		
            case '4': exit(0);		break;	
            }	
        getchar();
        } 
            /*二级菜单之添加数据*/
            void menu_add(void) 
            {	
                	
                getchar();	
                printf("          ╭════════╮              \n");	
                printf("╭══════╣  添加数据方式  ╠══════════════════╮\n");	
                printf("║         ╰════════╯                      ║\n");	
                printf("║ 【1】新建文件 【2】增添数据 【3】返回菜单  ║\n");	
                printf("║                                         ║\n");	
                printf("╰════════════════════════════════════════╯\n");	
                printf("◎请输入功能前的序号进入相应的工具:【   】\b\b"); 	
                int a = 0;	
                a = getchar(); 	
                while(a!='1'&&a!='2'&&a!='3') 
                {		
                    printf("error! please input the right number!\n");		
                    putchar('\a');		
                    getchar();		
                    printf("◎请重新输入功能前的序号进入相应的工具:【   】\b\b");		
                    a = getchar();	}	
                switch(a) 
                {		
                    case '1': WriteData_wb(Creat(Creat_num()));		 
                    printf("\n◎新建文件成功且数据已成功保存◎\n");			 
                    system("pause");		 
                    		 
                    menu_add();		break;		
                    case '2': WriteData_ab(Creat(Creat_num()));			 
                    printf("\n◎数据已成功添加◎\n");			 
                    system("pause");		 
                    		 
                    menu_add();		break;		
                    case '3': 		 
                    getchar();		 
                    menu();		
                    break;	
                    }
                    } 
/*二级菜单之查询数据*/
    void menu_inquire(void) 
    {	
        	
        getchar();//难道这是要初始化?	
        while(1) 
        {	
            	
            printf("              ╭════════╮              \n");	
            printf("╭══════╣  查询数据方式  ╠════════════════════════╮\n");	
            printf("║            ╰════════╯                        ║\n");	
            printf("║    【1】全量查询         【4】模糊查询         ║\n");	
            printf("║                                              ║\n");	
            printf("║    【2】学号查询         【5】成绩统计         ║\n");	
            printf("║                                              ║\n");	
            printf("║    【3】姓名查询         【6】返回菜单         ║\n");	
            printf("╰══════════════════════════════════════════════╯\n");	
            printf("成功不是终点，失败也并非永恒，唯有前进的勇气永存！\n");	
            printf("制作人员预祝您有一个好成绩！\n");
            printf("◎请输入功能前的序号进入相应的工具:【   】\b\b");
            
            int a = 0;	
            a = getchar(); 	
            while(a!='1'&&a!='2'&&a!='3'&&a!='3'&&a!='4'&&a!='5'&&a!='6') 
            {			
                printf("error! please input the right number!\n");			
                putchar('\a');			
                getchar();			
                printf("◎请重新输入功能前的序号进入相应的工具:【   】\b\b");			
                a = getchar();		
                }		
            switch(a) 
            {			
                case '1': Print_inquire_all();system("pause");getchar();			break;			
                case '2': Print_inquire_num();system("pause");getchar();			break;			
                case '3': Print_inquire_name();system("pause");getchar();			break;			
                case '4': Print_inquire_fuzzy();system("pause");getchar();;			break;			
                case '5': Print_inquire_stats();system("pause");getchar();			break;			
                case '6': getchar();menu();			break;		}	}}
/*二级菜单之修改数据*/
    void menu_amend(void) 
        {	
            	
            getchar();	
            while(1) 
            {	
                	
                printf("              ╭════════╮              \n");	
                printf("╭══════╣  修改数据方式  ╠════════════════════╮\n");	
                printf("║            ╰════════╯                     ║\n");	
                printf("║    【1】删除记录          【3】整理数据      ║\n");	
                printf("║                                            ║\n");	
                printf("║    【2】修改记录          【4】返回菜单      ║\n");	
                printf("╰═══════════════════════════════════════════╯\n");	
                printf("◎请输入功能前的序号进入相应的工具:【   】\b\b"); 	
                int a = 0;	//将a进行初始化
                a = getchar(); 	//获取a的值
                while(a!='1'&&a!='2'&&a!='3'&&a!='4') //输入未给定值时，报错
                   {		
                    printf("error! please input the right number!\n");		
                    putchar('\a');		
                    getchar();		
                    printf("◎请重新输入功能前的序号进入相应的工具:【   】\b\b");		
                    a = getchar();		
                    }		
                switch(a) 
                {			
                    case '1': Delete();			 
                    printf("\n\n◎已成功删除指定数据◎\n");			 
                    system("pause");			 
                    getchar();			break;			
                    case '2': Amend();				 
                    printf("\n\n◎已成功修改指定数据◎\n");			 
                    system("pause");				 
                    getchar();			break;			
                    case '3': Neaten();			 
                    printf("\n\n◎数据已成功按照学号重新排列◎\n");			 
                    system("pause");			 
                    getchar();			break;			
                    case '4': 			 
                    getchar();			 
                    menu();			break;		
                    }	}} 
    /*输入输出提示栏*/
    void menu_print_in(void) 
    {	
        printf("------------------------------------------------------------------------\n");	
        printf("学号      姓名     性别  年龄    电话         QQ        C    E          \n");	
        printf("------------------------------------------------------------------------\n");
        }
    void menu_print_out(void) 
    {	
        printf("--------------------------------------------------------------------------\n");	
        printf("学号      姓名     性别  年龄    电话         QQ        C    E    A    S  \n");	
        printf("--------------------------------------------------------------------------\n");
        } 
    /*主函数*/
    int main(void) 
    {	SetConsoleTitle("C学生信息管理系统");	
        menu();	
        return 0; 
        }
