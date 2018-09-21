#ifndef CHAT_H
#define CHAT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
//#include<linux/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include<time.h>		 //for asctime() and time()
#include<ctype.h>    //for ispunct()
 

#define QUEUELEN     100  //max of  client
#define BUF_SIZE     256  
#define IP        "127.0.0.1"
#define PORT         1234             // port
#define FILENAME     "userinfo"       // file name for save users info��name:passwd:id:authority�� 
#define CLIENT_ID    1000    // client id 
//========================functions================================================
#define PUBLIC_CHAT        			1  //Ⱥ��
#define PRIVATE_CHAT       			2  //˽��
#define CLIENT_LOGIN       			3  //��½��֤
#define CLIENT_REGISTER    			4  //ע��
#define CLIENT_ONLINE      			5  //���õ������û�
#define CLIENT_EXIT        			6  //�˳�
#define ADMIN_KICK_CLIENT       7  //����Ա�߳�ĳ�û�
#define ADMIN_SHUTUP_CLIENT     8  //����Ա��ֹĳ�û�����
#define ADVANCED_CLIENT_TO_ADMIN   9  //����Ա����ĳ�û�Ϊ����Ա
#define DROP_CLIENT_TO_NORMAL    10  //����Ա��ĳ�û���Ϊ��ͨ�û�

//====================================================================
#define NORMAL_USER_LOGIN_FAILED  			 0 //��ͨ�û���¼ʧ��
#define NORMAL_USER_LOGIN_SUCCESS 			 1 //��ͨ�û���¼�ɹ�
#define NORMAL_USER_LOGIN_FAILED_ONLINE  2 //��ͨ�û��Ѿ�����
#define ADMIN_LOGIN_SUCCESS              3 //����Ա��¼�ɹ�
#define NORMAL_USER_LOGIN_PASSWD_ERROR   4 //��ͨ�û���¼�������

#define REGIST_FALIED   0   //ע��ʧ��
#define REGIST_EXITED   1   //ע����û��Ѿ�����
#define NORMAL_USER     0   //��ͨ�û�
#define ADMIN_USER      1   //����Ա

// ===========client attr==========================================
typedef struct{
	pthread_t tid;					//�̵߳�������,unsigned long int ,printf��%lu
	int  sockfd;  					//accept�ķ��صĿͻ��˵��µ��׽���������
	char client_name[25]; 	// �˺�
	char client_passwd[25]; //����
	int client_id;					//�û�ID
  	int is_online;					// ����״̬ 1 ���� 0 ������
  	int admin;              //�û�Ȩ�ޣ�1Ϊ����Ա��0Ϊ��ͨ�û�
}client_info;
client_info clients[QUEUELEN];

//===========�ͻ����͵����ݽṹ=====================================
 typedef struct send_info{
	int  type;						//����
	char id[25];  				//�Է�id
	char buf[BUF_SIZE]; 	//����
	char name[25];				//�û������ǳƣ�
	char passwd[25];			//����
	}send_info;
//================�������ܵ�Э��====================================
typedef struct {
     int  fun_flag; //function flag
     void (*fun)();// function pointer variable
}proto;
//====================debug============================

#define CHAT_DEBUG
#ifdef  CHAT_DEBUG
#define DEBUG(message...) fprintf(stderr, message)
#else
#define DEBUG(message...)
#endif

// ========fun=========client.c====================
void  print_err(char *msg);
void  reg_log();
void  register_client();
void  login();
void  inits();
void  writedata();
void  show_menu();
void  wait_minutes();
void  signHandler(int signNo);
void *pthread_fun(void *arg);

//  ======fun=======server.c======================
int 	 system_init();
void   connect_to_client(int socketfd );
void   err(char *err_msg);
int    init_clents(char  *tok_file[]);
void   register_new_client(send_info *send,int newfd);
void   server_check_login(send_info *send,int newfd);
void   client_exit(send_info *send,int newfd);
int    get_sockfd(char dest[]);
void   private_chat ( send_info *send,int newfd);
void   public_chat (send_info *send ,int newfd);
void   get_all_online_clients (send_info *send ,int newfd);
void   admin_kick_client (send_info *send,int newfd);
void   admin_shutup_client(send_info *send,int newfd);
void   advanced_client_to_admin (send_info *send,int newfd);
void   drop_client_to_normal (send_info *send,int newfd) ;
int    admin_is_opt_self(send_info *send,int newfd);
int    admin_opt_self(send_info *send,int newfd);

//void public_chatroom_fun(void *arg);
void public_chatroom_inits(int socketfd);
void public_chat_V2( send_info *send,int newfd);
#endif 
