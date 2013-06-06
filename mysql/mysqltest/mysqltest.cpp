#include <stdio.h>
#include <windows.h>
#include <mysql.h>
#include <conio.h>

#pragma  comment(lib,"libmysql.lib")

/*�������ݿ���ز�������*/
MYSQL mysql;          //
MYSQL_RES *result;    //������������
MYSQL_ROW row;        //�����б���
char ch[2];


void ShowAll();       /*��ʾ���е�ͼ����Ϣ*/
void AddBook();       /*���ͼ����Ϣ*/
void ModifyBook();    /*�޸�ͼ����Ϣ*/
void DeleteBook();    /*ɾ��ͼ����Ϣ*/
void QueryBook();     /*��ѯͼ����Ϣ*/


/*��ʾ�˵�*/
void showmenu()
{
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
    printf("\t�U            Welcome To Lemon Books System             �U\n");
    printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
    printf("\t�U\t 1 - ��ʾ����ͼ����Ϣ                           �U\n");
    printf("\t�U\t 2 - ���ͼ����Ϣ                               �U\n");
    printf("\t�U\t 3 - �޸�ͼ����Ϣ                               �U\n");
    printf("\t�U\t 4 - ɾ��ͼ����Ϣ                               �U\n");
    printf("\t�U\t 5 - ��ѯͼ����Ϣ                               �U\n");
    printf("\t�U\t 6 - �˳�                                       �U\n");
    printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
    printf("\n              ENTER YOUR CHOICE(1-6):");
    
}

void inquire()  /*ѯ���û��Ƿ���ʾ���˵�*/
{
    printf("\t ��ʾ���˵�?(y/n):");
    scanf("%s",ch);
    if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*�ж��Ƿ�Ҫ��ʾ���ҵ�����Ϣ*/
    {
        showmenu();   /*��ʾ�˵�*/ 
    }
    else
    {
        exit(0);
    }
}

/*��ʾ���˵����������ݿ�*/
int main()
{
    int n ;   //�������  �洢�û�����ı��
    
    mysql_init(&mysql);  //��ʼ��mysql�ṹ
    
    showmenu();   /*��ʾ�˵�*/ 
    
    scanf("%d",&n);/*����ѡ���ܵı��*/
    
    while(n)
    { 
        switch(n)
        {
            case 1: 
                ShowAll();    /*������ʾ����ͼ�����ݵĹ���*/
                break;
            case 2: 
                AddBook();   /*���ͼ����Ϣ*/
                break;
            case 3: 
                ModifyBook();     /*�޸�ͼ����Ϣ*/
                break;
            case 4:
                DeleteBook();   /*ɾ��ͼ����Ϣ*/
                break;
            case 5:
                QueryBook();   /*��ѯͼ����Ϣ*/
                break;
            case 6:
                exit(0);       /*�˳�*/
            default:break;
        }
        scanf("%d",&n);
    }
}



void ShowAll()    /*������ʾ����ͼ�����ݵĹ���*/
{
    /*�������ݿ�*/
    if(!mysql_real_connect(&mysql,"127.0.0.1","root","123","db_books",0,NULL,0))
    { 
        printf("\n\t �����������ݿ�!\n");
    }
    else
    {
        /*���ݿ����ӳɹ�*/
        if(mysql_query(&mysql,"select * from tb_book"))
        {   //�����ѯʧ��
            printf("\n\t ��ѯ tb_book ���ݱ�ʧ��!\n");
        }
        else
        {
            result=mysql_store_result(&mysql); //��ý����
            if(mysql_num_rows(result)!=NULL)
            {  //�м�¼�����,ֻ���м�¼ȡ���ݲ�������
                printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                printf("\t                 �� ʾ �� �� ͼ �� �� Ϣ                  \n");
                printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                printf("\tͼ����       ͼ����         ����        ������      \n");
                printf("\t -------------------------------------------------------- \n");
                while((row=mysql_fetch_row(result)))
                {   //ȡ��������м�¼
                    fprintf(stdout,"\t   %s             %s             %s          %s   \n",row[0],row[1],row[2],row[3]);  //������м�¼
                }
                printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
            }
            else
            {
                printf("\n\t û�м�¼��Ϣ !\n");
            }
            mysql_free_result(result);    //�ͷŽ����
        }
        mysql_close(&mysql);          //�ͷ�����
    }
    inquire();   /*ѯ���Ƿ���ʾ���˵�*/
}







void AddBook()    /*���ͼ����Ϣ*/
{
    int rowcount;   /*������е�����*/
    
    char id[10];       /*���*/
    char *bookname;
    char *author;
    char *bookconcern;
    
    char *sql;    
    char dest[500] ={"  "};    
    
    /*�������ݿ�*/
    if(!mysql_real_connect(&mysql,"127.0.0.1","root","123","db_books",0,NULL,0))
    { 
        printf("\n\t �����������ݿ�!\n");
    }
    else
    {
        /*���ݿ����ӳɹ�����������*/   
        printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
        printf("\t                     �� �� ͼ �� �� Ϣ                    \n");
        printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
        if(mysql_query(&mysql,"select * from tb_book"))
        {   //�����ѯʧ��
            printf("\n\t ��ѯ tb_book ���ݱ�ʧ��!\n");
        }
        else
        {
            result=mysql_store_result(&mysql); //��ý����
            rowcount=mysql_num_rows(result) ;  //�������
            row=mysql_fetch_row(result);       //��ȡ���������  
            
            printf("\t ͼ����:");
            scanf("%s",id);   /*����ͼ����*/    
            
            sql="insert into tb_book (ID,bookname,author,bookconcern) values (";
            strcat(dest,sql);
            strcat(dest,"'");
            strcat(dest,id);
            strcat(dest,"', '");


            if(mysql_num_rows(result)!=NULL)
            {                
                /*�ж�����ı���Ƿ����*/
                do
                {   //������ͬ���
                    if(!strcmp(id,row[0]))
                    {
                      //  printf("%s",row[0]);
                        printf("\n\t ��¼���ڣ������������!\n");
                        getch();
                        mysql_free_result(result);   /*�ͷŽ����*/ 
                        mysql_close(&mysql);         /*�ͷ�����*/  
                        inquire();   /*ѯ���Ƿ���ʾ���˵�*/
                        return;
                    }
                }while(row=mysql_fetch_row(result));  
            }
            
            bookname = (char*)malloc(50);
            author = (char*)malloc(50);
            bookconcern = (char*)malloc(50);

            
            //��������ͬ�ı��            
            printf("\t ͼ����:");
            scanf("%s",bookname);   /*����ͼ����*/
            strcat(dest,bookname);    /*��ͼ����׷�ӵ�sql������*/
            
            printf("\t ����:");
            scanf("%s",author);    /*��������*/
            strcat(dest,"', '");
            strcat(dest,author);
            
            printf("\t ������:");
            scanf("%s",bookconcern);    /*���������*/
            strcat(dest,"', '");
            strcat(dest,bookconcern);
            strcat(dest,"')");
            //printf("%s",dest);
            
            if ( mysql_query(&mysql,dest)!=0)   
            {
                fprintf(stderr,"\t ���ܲ����¼!",mysql_error(&mysql));
            }
            else
            {
                printf("\t ����ɹ�!\n");                
            }
            mysql_free_result(result);    //�ͷŽ����
        }
        mysql_close(&mysql);          //�ͷ�����
    }
    inquire();   /*ѯ���Ƿ���ʾ���˵�*/
}   




void ModifyBook()   /*�޸�ͼ����Ϣ*/
{
    char id[10];   /*������е�����*/
    char *sql;    
    char dest[500] ={"  "};
    char dest1[500] ={"  "};
    
    char *bookname;
    char *author;
    char *bookconcern;
    
    if (!mysql_real_connect(&mysql,"127.0.0.1","root","123","db_books",0,NULL,0))
    {
        printf("\t �����������ݿ�!\n");
    }
    else
    {
        /*���ݿ����ӳɹ�*/
        // printf("���ӳɹ�");
        printf("\t ����������Ҫ�޸ĵ�ͼ����.");
        
        scanf("%s",id);   /*����ͼ����*/
        sql = "select * from tb_book where id=";
        strcat(dest,sql);
        strcat(dest,id);    /*��ͼ����׷�ӵ�sql������*/
        
        //printf("%s\n",dest);
        
        /*��ѯ��ͼ����Ϣ�Ƿ����*/
        if(mysql_query(&mysql,dest))
        {   //�����ѯʧ��
            printf("\n  ��ѯ tb_book ���ݱ�ʧ��! \n");
        }
        else
        {
            result=mysql_store_result(&mysql); //��ý����
            if(mysql_num_rows(result)!=NULL)
            {
                //�м�¼�����,ֻ���м�¼ȡ���ݲ�������
                printf("\t ���ּ�¼��Ϣ,�Ƿ���ʾ?(y/n) ");
                scanf("%s",ch);
                if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*�ж��Ƿ�Ҫ��ʾ���ҵ�����Ϣ*/
                {
                    printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                    printf("\t               ***** ��ʾͼ����Ϣ *****                   \n");
                    printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                    printf("\tͼ����       ͼ����         ����        ������      \n");
                    printf("\t -------------------------------------------------------- \n");
                    while((row=mysql_fetch_row(result)))
                    {   //ȡ��������м�¼
                        fprintf(stdout,"\t   %s             %s             %s          %s   \n",row[0],row[1],row[2],row[3]);  //������м�¼
                    }
                    printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                }
                
                
                printf("\t Modify?(y/n)");
                scanf("%s",ch);
                if (strcmp(ch,"Y")==0||strcmp(ch,"y")==0)    /*�ж��Ƿ���Ҫ¼��*/
                {

 
                    sql = "update tb_book set bookname= '";
                    strcat(dest1,sql);
                    //   printf("%s",sql);
                    bookname = (char*)malloc(20);
                    author = (char*)malloc(20);
                    bookconcern = (char*)malloc(20);

                    printf("\t ͼ����:");
                    scanf("%s",bookname);   /*����ͼ����*/
                    
                    strcat(dest1,bookname); 
                    //  printf("%s",&bookname);

                    printf("\t ����:");
                    scanf("%s",author);    /*��������*/
                    strcat(dest1,"', author= '");
                    strcat(dest1,author);    /*׷��sql���*/                        
                    
                    printf("\t ������:");
                    scanf("%s",bookconcern);    /*���������*/
                    strcat(dest1,"', bookconcern = '");
                    strcat(dest1,bookconcern);    /*׷��sql���*/
                    
                    strcat(dest1,"' where id= ");
                    strcat(dest1,id);                        
                    
                    //printf("%s",dest1);

                    if(mysql_query(&mysql,dest1)!=0)
                    {   
                        fprintf(stderr,"\t �����޸ļ�¼!\n",mysql_error(&mysql));                            
                    }
                    else
                    {
                        printf("\t �޸ĳɹ�!\n");
                    }
                }
                
            }
            else
            {
                printf("\t û�з���Ҫ�޸ĵ���Ϣ!\n");
            }
        }
        mysql_free_result(result);          //�ͷŽ����
    }
    mysql_close(&mysql);     //�ͷ�����
    inquire();   /*ѯ���Ƿ���ʾ���˵�*/
}



void DeleteBook()   /*ɾ��ͼ����Ϣ*/
{
    char id[10];   /*������е�����*/
    char *sql;
    char dest[100] ={"  "};
    char dest1[100] ={"  "};
    if(!mysql_real_connect(&mysql,"127.0.0.1","root","123","db_books",0,NULL,0))
    {
        printf("\t �����������ݿ�!\n");
    }
    else
    {
        printf("\t ����������Ҫɾ����ͼ����. ");        
        scanf("%s",id);   /*����ͼ����*/
        sql = "select * from tb_book where id=";
        strcat(dest,sql);
        strcat(dest,id);    /*��ͼ����׷�ӵ�sql������*/        
        //printf("%s\n",dest);
        
        /*��ѯ��ͼ����Ϣ�Ƿ����*/
        if(mysql_query(&mysql,dest))
        {   //�����ѯʧ��
            printf("\n ��ѯ tb_book ���ݱ�ʧ��! \n");
        }
        else
        { 
            result=mysql_store_result(&mysql); //��ý����
            if(mysql_num_rows(result)!=NULL)
            {  //�м�¼�����,ֻ���м�¼ȡ���ݲ�������
                printf("\t ���ּ�¼��Ϣ,�Ƿ���ʾ?(y/n) ");
                scanf("%s",ch);
                if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*�ж��Ƿ�Ҫ��ʾ���ҵ�����Ϣ*/
                {
                    printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                    printf("\t               ***** ��ʾͼ����Ϣ *****                   \n");
                    printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                    printf("\tͼ����       ͼ����         ����        ������      \n");
                    printf("\t -------------------------------------------------------- \n");
                    while((row=mysql_fetch_row(result)))
                    {   //ȡ��������м�¼
                        fprintf(stdout,"\t   %s             %s             %s          %s   \n",row[0],row[1],row[2],row[3]);  //������м�¼
                    }
                    printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                }
                                    
                    printf("\t �Ƿ�ɾ��?(y/n) ");
                    scanf("%s",ch);
                    if (strcmp(ch,"Y")==0||strcmp(ch,"y")==0)    /*�ж��Ƿ���Ҫ¼��*/
                    {
                        sql = "delete from tb_book where ID= ";
                        printf("%s",dest1);
                        strcat(dest1,sql);
                        strcat(dest1,id);
                       // printf("%s",dest1);
                        
                        if(mysql_query(&mysql,dest1)!=0)
                        {
                            fprintf(stderr,"\t ����ɾ����¼! \n",mysql_error(&mysql));
                        }
                        else
                        {
                            printf("\t ɾ���ɹ�!\n");
                        }
                    }
            }
            else
            {
                printf("\t û�з���Ҫɾ������Ϣ!\n");
            }
        }
        mysql_free_result(result);    //�ͷŽ����
    }
    mysql_close(&mysql);
    inquire();   /*ѯ���Ƿ���ʾ���˵�*/
}



void QueryBook()   /*��ѯͼ����Ϣ*/
{     
    char id[10];   /*������е�����*/
    char *sql;
    char dest[100] ={"  "};
    
    if(!mysql_real_connect(&mysql,"127.0.0.1","root","123","db_books",0,NULL,0))
    {
        printf("\t �����������ݿ�!\n");
    }
    else
    {  
        printf("\t ����������Ҫ��ѯ��ͼ����:");        
        scanf("%s",id);   /*����ͼ����*/
        sql = "select * from tb_book where id=";
        strcat(dest,sql);
        strcat(dest,id);    /*��ͼ����׷�ӵ�sql������*/        
        
        if(mysql_query(&mysql,dest))
        {   //�����ѯʧ��
            printf("\n ��ѯ tb_book ���ݱ�ʧ��!\n");
        }
        else
        {
            result=mysql_store_result(&mysql); //��ý����
            if(mysql_num_rows(result)!=NULL)
            {  //�м�¼�����,ֻ���м�¼ȡ���ݲ�������
                printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                printf("\t                          ��ʾͼ����Ϣ                      \n");
                printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
                printf("\tͼ����       ͼ����         ����        ������      \n");
                printf("\t -------------------------------------------------------- \n");
                while((row=mysql_fetch_row(result)))
                {   //ȡ��������м�¼
                    fprintf(stdout,"\t   %s             %s             %s          %s   \n",row[0],row[1],row[2],row[3]);  //������м�¼
                }
                printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");                
            }
            else
            {
                printf("\t û�з���Ҫ��ѯ����Ϣ!\n");
            }
            mysql_free_result(result);    //�ͷŽ����
        }
        mysql_close(&mysql);          //�ͷ�����
    }
    inquire();   /*ѯ���Ƿ���ʾ���˵�*/
}
