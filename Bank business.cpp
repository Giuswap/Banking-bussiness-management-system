#include<bits/stdc++.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define N 1000005
typedef long long ll;

//��ͨ�û�idΪ4λ��VipΪ5λ

int winNum1=3;//����һ��������;
int bankMoney=1000000;//�������
int number;//��ͨ�û�����˳��
int numberVip;//VIP�û�����˳��
int startTime[N];//�ͻ���������ʱ��
int finished[N];//�ͻ��������ʱ��
map<string,int>pass;//�ʻ�������

void go();//���ؽ���
int eder();//��������
int Error(int x,int d);//�ж��������Ƿ���ȷ
void error();//��ӡ����
void welcome(); //��ʼ����
void welcomeCom();//��ͨ����
void welcomeVip();//Vip����
void welcomeAdmin(); //����Ա����
void AdminQuery();  //����Ա��ѯ����
void init(int num); //������Ϣ��ʼ��
void QueryAll(); //����Ա��ѯ����ӡ�����û���Ϣ
void QueryOne();   //����Ա��ѯĳλ�û�
void saveMoney(int id,int money); //���
void getMoney(int id,int money); //ȡ��
void lendMoney(int id,int money); //���
void restoreMoney(int id,int money); //����
void add(int time); //��������
void newID(int id); //����
void Query(int id); //��ѯ���
void fillWindows(); //������һ��VIP�����Ŷ�
void SimulateWin2(int time,struct Window &win2); //ģ�����Ͷ����ڹ���
void SimulateWin1(); //ģ������һ���ڹ���
void SimulateWinvip(); //ģ��VIP����
double getAverage(); //��ȡƽ������ʱ��
void initAdmin();   //��ʼ����Ա����

struct User{ //�洢�û���Ϣ
    string name;//�û�����
    int type;//��ȡ������
    int money;//��ȡ����Ŀ
    int arrivalTime;//����ʱ��
    int costMinute;//����ʱ��
    int loans;//����
    int balance;//���
    bool isVip;//�ж��Ƿ�ΪVIP
    bool isOpen=false;//�жϴ��û��˻��Ƿ�ͨ
};

struct Window{ //����״̬
    queue<int> line;//���ڶ���
    int popTime;//�������ʱ��
}windows[N],windows2,vip,vipWindows2;//����һ/������/VIP����

map<int,User>users;//�洢�û���Ϣ


void go() {//���ؽ���
    std::cout << "\n���Ժ�...... ";
    for (int i = 0; i <= 100; i++)  // ��ӡ�ٷֱ�
    {
        std::cout.width(3);  // i�����Ϊ3λ��
        cout << i << "%";
        Sleep(8);
        std::cout << "\b\b\b\b";  //��ɾ�����ַ���ʹ������ԭ�ر仯
    }
    std::cout << "\t\t\t\t\t\t\t\t" << "\n\n";
    cout << "������ɣ�";
    Sleep(500);
    system("cls");
}

void welcome(){//��ʼ����
    printf(
        "\t\t\t\t\t\t\t\t  *                        <���д������>                    *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <��ӭʹ�����д������ϵͳ>            *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                     <������ʹ������ģʽ>                 *\n");
printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                                                          *\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                  ����Աģʽ          �밴0               *\n");
printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
printf(
        "\t\t\t\t\t\t\t\t  *                                                          *\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                  �û�ģʽ            �밴1               *\n");
printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
printf(
        "\t\t\t\t\t\t\t\t  *                                                          *\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                  �˳�����            �밴2               *\n");
printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                                                          *\n");
    printf(
        "\t\t\t\t\t\t\t\t   **********************************************************\n\n");
}

void welcomeAdmin(){//����Ա����
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <��ӭʹ�ù���Աģʽ>                  *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
        printf(
        "\t\t\t\t\t\t\t\t  *                    <������ʹ�����¹���>                  *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                �����˻���¼��        �밴0             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                �����û���������          �밴1             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ��ѯ�����û���Ϣ         �밴2             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                �˳�                      �밴3             *\n");
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
}

void AdminQuery(){//����Ա��ѯ����
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <��ӭʹ�ù���Աģʽ>                  *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
        printf(
        "\t\t\t\t\t\t\t\t  *                    <������ʹ�����¹���>                  *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ��ӡ�����û���Ϣ        �밴0             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ��ѯ�ƶ��û���Ϣ        �밴1             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                �˳�                    �밴2             *\n");
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
}

void welcomeCom()//һ�����
{
        printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <��ӭʹ����ͨ�û�ģʽ>                  *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
        printf(
        "\t\t\t\t\t\t\t\t  *                    <������ʹ�����¹���>                  *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ����                      �밴0             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ���                      �밴1             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ȡ��                      �밴2             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ���                      �밴3             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ����                      �밴4             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ��ѯ                      �밴5             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                �˳�                      �밴6             *\n");
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
}

void welcomeVip()//Vip����
{
        printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <��ӭʹ��VIP�û�ģʽ>                  *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <��������������ȡ�����Ȩ>                *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
        printf(
        "\t\t\t\t\t\t\t\t  *                    <������ʹ�����¹���>                  *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ����                      �밴0             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ���                      �밴1             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ȡ��                      �밴2             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ���                      �밴3             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ����                      �밴4             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                ��ѯ                      �밴5             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                �˳�                      �밴6             *\n");
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
}

void error()  //��ӡ��������
{
    printf("\n");
    printf("\t\t\t  ��������������ѡ�����ѡ���\n\n");
    system("PAUSE");
}

void Borrow(int id){
    while (1) {
        system("cls");
        welcome();
        string p;
        cout << "\t\t\t\t\t\t\t\t";
        cin >> p;
        if (p == "0")
            welcomeAdmin();
        else if (p == "1"){
            if(!users[id].isVip) welcomeCom();
            else welcomeVip();
        }
        else if (p == "2") {
            system("cls");
            return;
        } else {
            system("cls");
            error();
        }
    }
}

void init(int num){ //������Ϣ��ʼ��
    string name,ID;
    string id,balance,loans,password;
    int id1,balance1,loans1,password1;
    cout<<"\t\t\t\t\t\t\t\t �����������˻���ʼ������"<<endl;
    for(int i=0;i<num;i++){
        cout<<"\t\t\t\t\t\t\t\t ����������id,����,���,����,�˺�,����"<<endl;
        while(true){
            int flag=0;
            int num=0;
            cout<<"\t\t\t\t\t\t\t\t ";
            cin>>id>>name>>balance>>loans>>ID>>password;
            for(int i=0;i<id.size();i++){
                if(id[i]<'0'||id[i]>'9'){
                    cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
                    flag=1;
                    break;
                }else num=num*10+id[i]-'0';
            }
            if(flag==1) continue;
            else id1=num;
            num=0;
            for(int i=0;i<balance.size();i++){
                if(balance[i]<'0'||balance[i]>'9'){
                    cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
                    flag=1;
                    break;
                }else num=num*10+balance[i]-'0';
            }
            if(flag==1) continue;
            else balance1=num;
            num=0;
            for(int i=0;i<loans.size();i++){
                if(loans[i]<'0'||loans[i]>'9'){
                    cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
                    flag=1;
                    break;
                }else num=num*10+loans[i]-'0';
            }
            if(flag==1) continue;
            else loans1=num;
            num=0;
            for(int i=0;i<password.size();i++){
                if(password[i]<'0'||password[i]>'9'){
                    cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
                    flag=1;
                    break;
                }else num=num*10+password[i]-'0';
            }
            if(flag==1) continue;
            else {
                password1=num;
                break;
            }
        }
        bankMoney+=balance1;
        if(balance1>=200000) users[id1].isVip=true;//������20��ΪVIP
        else users[id1].isVip=false;//
        users[id1].name=name;
        users[id1].arrivalTime=0;
        users[id1].balance=balance1;
        users[id1].loans=loans1;
        users[id1].isOpen=true;
        pass[ID]=password1;
    }
}

//��ȡcostMinute
/*int getCostminute(int money){
    getm[money]=1;
    map<int,int>::iterator it;
    int num=0;
    for(it=getm.begin();it!=getm.end();it++){
        if(it->first!=money){
            num++;
            getm[it->first]=num;
        }
        else break;
    }
    return num+1;
}*/

//���
void saveMoney(int id,int money){
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t ���˻�������"<<endl;
        cout<<"\t\t\t\t\t\t\t\t ����������1,�˳�������0"<<endl;
        while(true){
            printf("\t\t\t\t\t\t\t\t ");
            int num;
            cin>>num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }
            else if(num==1){
                newID(id);
                break;
            }
            else if(num==0)return ;
            cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
        }
    }
    users[id].balance+=money;
    bankMoney+=money;
    if(users[id].balance>=500000) users[id].isVip=true;//�Ƿ���Գ�ΪVIP
    else users[id].isVip=false;
    cout<<"\t\t\t\t\t\t\t\t ���ɹ�"<<endl;
}

//ȡ��
void getMoney(int id,int money){
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t ���˻�������"<<endl;
        cout<<"\t\t\t\t\t\t\t\t ����������1,����������0"<<endl;
        int num;
        while(true){
            printf("\t\t\t\t\t\t\t\t ");
            cin>>num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }
            else if(num==1){
                newID(id);
                break;
            }
            else if(num==0) return ;
            cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
        }
    }
    if(users[id].balance<money){
        cout<<"\t\t\t\t\t\t\t\t ����,ȡ��ʧ��"<<endl;
        cout<<"\t\t\t\t\t\t\t\t ���������밴1,�����밴0"<<endl;
        int flag;
        while(true){
            printf("\t\t\t\t\t\t\t\t ");
            cin>>flag;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }
            else if(!flag) return ;
            else if(flag==1){
                printf("\t\t\t\t\t\t\t\t ");
                cin>>money;
                getMoney(id,money);
                break;
            }
            cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
        }
    }
    else if(bankMoney<money){
        cout<<"\t\t\t\t\t\t\t\t ȡ��ʧ��,��������,�뵽���ʹ��ڵȺ�"<<endl;
        windows2.line.push(id);
        return ;
    }else{
        users[id].balance-=money;
        bankMoney-=money;
    }
    cout<<"\t\t\t\t\t\t\t\t ȡ��ɹ�"<<endl;
    return ;
}

//���
void lendMoney(int id,int money){
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t ���˻�������"<<endl;
        cout<<"\t\t\t\t\t\t\t\t ����������1,����������0"<<endl;
        int num;
        while(true){
            printf("\t\t\t\t\t\t\t\t ");
            cin>>num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }
            else if(num==1){
                newID(id);
                break;
            }
            else if(num==0) return ;
            cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
        }
    }
    if(bankMoney<money){
        cout<<"\t\t\t\t\t\t\t\t ���ʧ��,��������,�뵽���ʹ��ڵȺ�"<<endl;
        windows2.line.push(id);
        return ;
    }else{
        users[id].loans+=money;
        bankMoney-=money;
        cout<<"\t\t\t\t\t\t\t\t ���ɹ�"<<endl;
    }
    return ;
}

//����
void restoreMoney(int id,int money){
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t ���˻�������"<<endl;
        cout<<"\t\t\t\t\t\t\t\t ����������1,����������0"<<endl;
        int num;
        while(true){
            printf("\t\t\t\t\t\t\t\t ");
            cin>>num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }
            else if(num==1){
                newID(id);
                break;
            }
            else if(num==0) return ;
            cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
        }
    }
    if(users[id].loans<money){
        cout<<"\t\t\t\t\t\t\t\t ����ʧ��,�����ɵĽ����������������"<<endl;
        while(true){
            printf("\t\t\t\t\t\t\t\t ");
            cin>>money;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }else break;
            cout<<"\t\t\t\t\t\t\t\t �����������������"<<endl;
        }
        restoreMoney(id,money);
    }
    else{
        bankMoney+=money;
        users[id].loans-=money;
        cout<<"\t\t\t\t\t\t\t\t ����ɹ�"<<endl;
        cout<<"\t\t\t\t\t\t\t\t �����ڵĴ����Ϊ:"<<users[id].loans<<endl;
    }
}

int Error(int x,int d){
	while (true) {
        printf("\t\t\t\t\t\t\t\t ");
        cin>>x;
        if(d==0){
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }else break;
        }else{
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }else if(x>=0&&x<=5 ) break;
        }
        cout<<endl;
		cout << "\t\t\t\t\t\t\t\t ����������������롣" << endl;
	}
	return x;
}

void add(int time){//��������
    if(time>=540){
        cout<<"\t\t\t\t\t\t\t\t ����Ӫҵʱ���ѽ���"<<endl;
        return ;
    }
    cout<<"\t\t\t\t\t\t\t\t �����������Ŷ�ʱ��"<<endl;
    string name="";
    int id=0,money=-1,type=-1,costMinute=0;
    cout<<"\t\t\t\t\t\t\t\t ������id"<<endl;
    id=Error(id,0);
    cout<<"\t\t\t\t\t\t\t\t ������name"<<endl;
    cout<<"\t\t\t\t\t\t\t\t ";
    cin>>name;
    cout<<"\t\t\t\t\t\t\t\t ������type"<<endl;
    cout<<"\t\t\t\t\t\t\t\t (0:���� 1:��� 2:ȡ��  3:���  4:���� 5:��ѯ)"<<endl;
    type=Error(type,1);
    if(type==1||type==2||type==3||type==4){
        cout<<"\t\t\t\t\t\t\t\t ������money"<<endl;
        money=Error(money,0);
    }
    while(costMinute==0)
        costMinute=rand()%100;
    users[id].name=name;
    users[id].type=type;
    users[id].costMinute=costMinute;
    startTime[id]=time;
    if(users[id].isVip==false){
        number++;
        if(number%winNum1==0){
            if(windows[winNum1].line.empty())
                windows[winNum1].popTime=time+costMinute;
            windows[winNum1].line.push(id);
        }
        else{
            if(windows[number%winNum1].line.empty())
                windows[number%winNum1].popTime=time+costMinute;
            windows[number%winNum1].line.push(id);
        }
    }else{
        numberVip++;
        if(vip.line.empty())
            vip.popTime=time;
        vip.line.push(id);
    }
}

void newID(int id){ //����
    cout<<"\t\t\t\t\t\t\t\t �����ǿ�������"<<endl;
    cout<<"\t\t\t\t\t\t\t\t �������˺�"<<endl;
    string ID;
    int password;
    printf("\t\t\t\t\t\t\t\t ");
    cin>>ID;
    if(pass.count(ID)!=0){
        cout<<"\t\t\t\t\t\t\t\t �˺��Ѵ��ڣ�����������"<<endl;
        newID(id);
    }else{
        cout<<"\t\t\t\t\t\t\t\t ����������"<<endl;
        password=eder();
        pass[ID]=password;
        users[id].isOpen=true;
        cout<<endl;
        cout<<"\t\t\t\t\t\t\t\t �����ɹ�"<<endl;
    }
}

void QueryAll(){//��ѯ�����û���Ϣ
    printf(
        "\t\t\t\t\t\t\t\t  *           �û�            ���               ����              *\n");
    for(int i=1;i<100000;i++){
        if(users[i].isOpen){
            printf(
                "\t\t\t\t\t\t\t\t  *            %s              %d                 %d               *\n",users[i].name.c_str(),users[i].balance,users[i].loans);
        }
    }
}

void QueryOne(){//����Ա��ѯĳλ�û�
    cout<<"\t\t\t\t\t\t\t\t ������id:"<<endl;
    int id;
    id=Error(id,0);
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t ���û�������"<<endl;
        cout<<"\t\t\t\t\t\t\t\t ����������  "<<endl;
        cin.get();
        system("cls");
        QueryOne();
    }else{
        printf(
            "\t\t\t\t\t\t\t\t  *           �û�            ���               ����              *\n");
        printf(
                "\t\t\t\t\t\t\t\t  *            %s              %d                 %d               *\n",users[id].name.c_str(),users[id].balance,users[id].loans);
    }
}
void Query(int id){//��ѯ���
    cout<<"\t\t\t\t\t\t\t\t �������ʻ�������:"<<endl;
    cout<<"\t\t\t\t\t\t\t\t ";
    string ID;
    int password;
    cin>>ID;
    password=eder();
    cout<<endl;
    if(!pass.count(ID)){
        cout<<"\t\t\t\t\t\t\t\t ���û�������"<<endl;
        cout<<"\t\t\t\t\t\t\t\t ���������밴1,�����밴0"<<endl;
        int num;
        num=Error(num,0);
        system("cls");
        if(!users[id].isVip) welcomeCom();
        else welcomeVip();
        if(num==1){
            Query(id);
        }else{
            newID(id);
        }
    }else{
        int pass0;
        map<string,int>::iterator it;
        for(it=pass.begin();it!=pass.end();it++){
            if(it->first==ID){
                pass0=it->second;
                break;
            }
        }
        if(pass0!=password){
            cout<<"\t\t\t\t\t\t\t\t �ʻ����������,����������"<<endl;
            Query(id);
        }else{
            cout<<"\t\t\t\t\t\t\t\t �����ʻ����Ϊ:"<<users[id].balance<<endl;
            cout<<"\t\t\t\t\t\t\t\t ���Ĵ���Ϊ:"<<users[id].loans<<endl;
            //������������ѯ
        }
    }
}

int eder()//��������
{

	char ch, passwords0[20];
	int x = 0;
	string pword1;
	char ch1, passwords1[20];
	int x1 = 0;
	here:
    cout<<"\t\t\t\t\t\t\t\t ";
	while ((ch = _getch()) != '\r' && x <= 20)
	{
		if (ch == '\b')
		{
			if (x > 0)
			{
				x--;
				cout << "\b \b";//����֧���˸��ʵ��
			}
			else
				putchar(7);
		}
		else
		{
			passwords0[x++] = ch;
			printf("*");
		}
	}
	string str="";
    for(int i=0;i<x;i++)
        str+=passwords0[i];
    int num=atol(str.c_str());
    return num;
}

void fillWindows(){//������һ�����Ŷ�
    string name;
    int id,money,costMinute=0;//costMinuteΪ������100�������
    cout<<"\t\t\t\t\t\t\t\t �������Ŷ�ʱ��"<<endl;
    cout<<"\t\t\t\t\t\t\t\t ������id,name"<<endl;
    id=Error(id,0);
    cin>>name;
    while(costMinute==0)
        costMinute=rand()%100;
    users[id].costMinute=costMinute;
    users[id].arrivalTime=0;
    if(!users[id].isVip){//�ж��Ƿ�ΪVIP�û�
        number++;
        if(number<=winNum1){
            windows[number].popTime=costMinute;
            windows[number].line.push(id);
        }else{
            if(number%winNum1!=0)
                windows[number%winNum1].line.push(id);
            else windows[winNum1].line.push(id);
        }
    }else{
        numberVip++;
        vip.line.push(id);
        if(numberVip==1) vip.popTime=users[id].costMinute;
    }
}


void SimulateWinvip(int t){//ģ��VIP����
    if(vip.popTime!=t||vip.line.empty()) return ;
    go();
    welcome();//��ʼ����
    int num;
    num=Error(num,0);
    if(num==0){
        system("cls");
        printf("\t\t\t  ��ǰ���û�ʱ�䣡��\n");
        error();
        SimulateWinvip(t);
    }
    else if(num==1){
        int flag=0;
        int type,money;
        int id=vip.line.front();

        while(1){
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t ��ǰ"<<users[id].name<<"�û����ڰ���ҵ��"<<endl;
            if(!users[id].isVip) welcomeCom();
            else welcomeVip();
            cout<<"\t\t\t\t\t\t\t\t ��ѡ����Ҫ�����ҵ������"<<endl;
            type=Error(type,0);
            if(type==1||type==2||type==3||type==4){
                cout<<"\t\t\t\t\t\t\t\t ������money"<<endl;
                money=Error(money,0);
                users[id].type=type;
                users[id].money=money;
            }
            if(type==0) newID(id);
            else if(type==1){//���
                saveMoney(id,money);
            }else if(type==2){//ȡ��
                getMoney(id,money);
            }else if(type==3){//���
                lendMoney(id,money);
            }else if(type==4){//����
                restoreMoney(id,money);
            }else if(type==5){
                Query(id);
            }else if(type==6){
                system("cls");
                break;
            }else{
                cout<<"\t\t\t\t\t\t\t\t ����ȷѡ��"<<endl;
                continue;
            }
            cin.get();
            cin.get();
            if(type==1||type==4){
                SimulateWin2(t,vipWindows2);
                SimulateWin2(t,windows2);
            }
        }
        finished[id]=t;//��¼���ʱ��
        vip.line.pop();//����
        if(vip.line.size() > 0){
            // ���³���ʱ��
                vip.popTime=t+users[vip.line.front()].costMinute;
        }
        cout<<endl;
    }else if(num==2){
        cout <<"\t\t\t\t\t\t\t\t ��л����ʹ��" << endl;
        cin.get();
        system("cls");
    }else{
        system("cls");
        error();
        SimulateWinvip(t);
    }
}


//ģ�����Ͷ����ڹ���
void SimulateWin2(int time,struct Window &win2){
    int num=0;
    while(!win2.line.empty()&&num<=win2.line.size()){
        num++;
        int id=win2.line.front();
        if(users[id].type==2){//ȡ��
            if(bankMoney>=users[id].money){//��������
                bankMoney-=users[id].money;
                users[id].balance-=users[id].money;
                users[id].money=0;
                finished[id]=time+users[id].costMinute;
                users[id].costMinute=0;
                win2.line.pop();
            }else{
                win2.line.pop();
                win2.line.push(id);
            }
        }else if(users[id].type==3){//���
            if(bankMoney>=users[id].money){//��������
                bankMoney-=users[id].money;
                users[id].loans+=users[id].money;
                users[id].money=0;
                finished[id]=time+users[id].costMinute;
                users[id].costMinute=0;
                win2.line.pop();
            }else{
                win2.line.pop();
                win2.line.push(id);
            }
        }
    }
}

//ģ������һ���ڹ���
void SimulateWin1(){
    for(int t=0;t<540;t++){//��9:00---17:00
        if(t==60||t==360) add(t);
        SimulateWinvip(t);
        for(int i=1;i<=winNum1;i++){ //��������
            if(windows[i].popTime!=t||windows[i].line.empty()) continue;
            go();
            welcome();//��ʼ����
            cout<<"\t\t\t\t\t\t\t\t ��ѡ����Ҫ�����ҵ������"<<endl;
            int num;
            num=Error(num,0);
            if(num==0){
                system("cls");
                printf("\t\t\t  ��ǰ���û�ʱ�䣡��\n");
                error();
                i--;
                continue;
            }
            else if(num==1){
                int flag=0;
                int type,money;
                int id=windows[i].line.front();

                while(1){
                    system("cls");
                    cout<<"\t\t\t\t\t\t\t\t ��ǰ"<<users[id].name<<"�û����ڰ���ҵ��"<<endl;
                    if(!users[id].isVip) welcomeCom();
                    else welcomeVip();
                    cout<<"\t\t\t\t\t\t\t\t ��ѡ����Ҫ�����ҵ������"<<endl;

                    type=Error(type,0);
                    if(type==1||type==2||type==3||type==4){
                        cout<<"\t\t\t\t\t\t\t\t ������money"<<endl;
                        money=Error(money,0);
                        users[id].type=type;
                        users[id].money=money;
                    }
                    if(type==0) newID(id);
                    else if(type==1){//���
                        saveMoney(id,money);
                    }else if(type==2){//ȡ��
                        getMoney(id,money);
                    }else if(type==3){//���
                        lendMoney(id,money);
                    }else if(type==4){//����
                        restoreMoney(id,money);
                    }else if(type==5){
                        Query(id);
                    }else if(type==6){
                        system("cls");
                        break;
                    }else{
                        cout<<"\t\t\t\t\t\t\t\t ����ȷѡ��"<<endl;
                        continue;
                    }
                    cin.get();
                    cin.get();
                    if(type==1||type==4){
                        SimulateWin2(t,vipWindows2);
                        SimulateWin2(t,windows2);
                    }
                }
                finished[id]=t;//��¼���ʱ��
                windows[i].line.pop();//����
                if(windows[i].line.size() > 0){
                    // ���³���ʱ��
                        windows[i].popTime=t+users[windows[i].line.front()].costMinute;
                }
                cout<<endl;
            }else if(num==2){
                cout <<"\t\t\t\t\t\t\t\t ��л����ʹ��" << endl;
                cin.get();
                system("cls");
                i--;
            }else{
                system("cls");
                error();
            }
        }
    }
    while(!vip.line.empty()){
        int id=vip.line.front();
        if(vip.popTime<540)
            finished[id]=vip.popTime+users[id].costMinute;
    }
    for(int i=1;i<=winNum1;i++){
        int id=windows[i].line.front();
        if(windows[i].popTime<540)
            finished[id]=windows[i].popTime+users[id].costMinute;
    }
    while(!windows2.line.empty()){
        int id=windows2.line.front();
        finished[id]=540;
        windows2.line.pop();
    }
}

double getAverage(){ //��ȡƽ������ʱ��
    double average;
    int sumTime=0;
    for(int i=1;i<100000;i++){
        if(finished[i]>0){
            sumTime+=finished[i]-startTime[i];
        }
    }
    average=1.0*sumTime/(number+numberVip);
    return average;
}

void initAdmin(){//��ʼ����Ա����
    printf("\t\t\t\t\t\t\t\t ��������ѡ���ģʽ\n");
    cout<<endl;
    int num;
    num=Error(num,0);
    if(num==0){
        while(1){
            system("cls");
            welcomeAdmin();
            cout<<"\t\t\t\t\t\t\t\t ���������ķ�������"<<endl;
            num=Error(num,0);
            int numa;
            if(num==0){
                cout<<"\t\t\t\t\t\t\t\t ������¼���˻���Ŀ"<<endl;
                numa=Error(numa,0);
                init(numa);
            }else if(num==1){
                for(int i=0;i<numa;i++)//����һ�Ŷ�
                    fillWindows();
            }else if(num==2){
                while(1){
                    system("cls");
                    AdminQuery();
                    cout<<"\t\t\t\t\t\t\t\t ���������ķ�������"<<endl;
                    int type;
                    type=Error(type,0);
                    if(type==0){
                        system("cls");
                        QueryAll();
                        cin.get();
                        cin.get();
                    }else if(type==1){
                        system("cls");
                        QueryOne();
                        cin.get();
                        cin.get();
                    }else if(type==2) break;
                }
            }else if(num==3){
                system("cls");
                break;
            }
        }
    }else if(num==2) system("cls");
    else{
        cout << "\t\t\t\t\t\t\t\t ����������������롣" << endl;
        initAdmin();
    }
    return ;
}

int main()
{
    memset(finished,0,sizeof(finished));
    memset(startTime,0,sizeof(startTime));
    system("mode con cols=240 lines=55");
    welcome();//��ʼ����
    initAdmin();//����Ա����
    SimulateWin1();//ģ�����
    cout<<"�������Ϊ:  "<<bankMoney<<endl;
    cout<<"ÿλ�û�������ʱ��Ϊ(ID:ʱ��):"<<endl;
    for(int i=1;i<100000;i++){//����ÿλ�û�������ʱ��,��ɾȥ,������
        if(finished[i]>0)
            cout<<i<<" : "<<finished[i]-startTime[i]<<" ���� "<<endl;
    }
    cout<<"ƽ������ʱ��Ϊ:";
    double average=getAverage();//ƽ��ʱ��
    printf("%.2f ����\n",average);
    return 0;
}
