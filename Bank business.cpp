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

//普通用户id为4位，Vip为5位

int winNum1=3;//类型一窗口数量;
int bankMoney=1000000;//银行余额
int number;//普通用户进入顺序
int numberVip;//VIP用户进入顺序
int startTime[N];//客户进入银行时间
int finished[N];//客户处理完成时间
map<string,int>pass;//帐户和密码

void go();//加载界面
int eder();//加密密码
int Error(int x,int d);//判断输入流是否正确
void error();//打印错误
void welcome(); //初始界面
void welcomeCom();//普通界面
void welcomeVip();//Vip界面
void welcomeAdmin(); //管理员界面
void AdminQuery();  //管理员查询界面
void init(int num); //人物信息初始化
void QueryAll(); //管理员查询并打印所有用户信息
void QueryOne();   //管理员查询某位用户
void saveMoney(int id,int money); //存款
void getMoney(int id,int money); //取款
void lendMoney(int id,int money); //借款
void restoreMoney(int id,int money); //还款
void add(int time); //增加人数
void newID(int id); //开户
void Query(int id); //查询余额
void fillWindows(); //在类型一和VIP窗口排队
void SimulateWin2(int time,struct Window &win2); //模拟类型二窗口过程
void SimulateWin1(); //模拟类型一窗口过程
void SimulateWinvip(); //模拟VIP窗口
double getAverage(); //获取平均逗留时间
void initAdmin();   //初始管理员操作

struct User{ //存储用户信息
    string name;//用户姓名
    int type;//存取款类型
    int money;//存取款数目
    int arrivalTime;//到达时间
    int costMinute;//花费时间
    int loans;//贷款
    int balance;//余额
    bool isVip;//判断是否为VIP
    bool isOpen=false;//判断此用户账户是否开通
};

struct Window{ //窗口状态
    queue<int> line;//窗口队列
    int popTime;//处理完成时间
}windows[N],windows2,vip,vipWindows2;//类型一/二窗口/VIP窗口

map<int,User>users;//存储用户信息


void go() {//加载界面
    std::cout << "\n请稍后...... ";
    for (int i = 0; i <= 100; i++)  // 打印百分比
    {
        std::cout.width(3);  // i的输出为3位宽
        cout << i << "%";
        Sleep(8);
        std::cout << "\b\b\b\b";  //回删三个字符，使数字在原地变化
    }
    std::cout << "\t\t\t\t\t\t\t\t" << "\n\n";
    cout << "加载完成！";
    Sleep(500);
    system("cls");
}

void welcome(){//初始界面
    printf(
        "\t\t\t\t\t\t\t\t  *                        <银行储蓄管理>                    *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <欢迎使用银行储蓄管理系统>            *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                     <您可以使用以下模式>                 *\n");
printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                                                          *\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                  管理员模式          请按0               *\n");
printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
printf(
        "\t\t\t\t\t\t\t\t  *                                                          *\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                  用户模式            请按1               *\n");
printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
printf(
        "\t\t\t\t\t\t\t\t  *                                                          *\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                  退出程序            请按2               *\n");
printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                                                          *\n");
    printf(
        "\t\t\t\t\t\t\t\t   **********************************************************\n\n");
}

void welcomeAdmin(){//管理员界面
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <欢迎使用管理员模式>                  *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
        printf(
        "\t\t\t\t\t\t\t\t  *                    <您可以使用以下功能>                  *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                银行账户的录入        请按0             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                银行用户队列排序          请按1             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                查询银行用户信息         请按2             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                退出                      请按3             *\n");
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
}

void AdminQuery(){//管理员查询界面
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <欢迎使用管理员模式>                  *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
        printf(
        "\t\t\t\t\t\t\t\t  *                    <您可以使用以下功能>                  *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                打印所有用户信息        请按0             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                查询制定用户信息        请按1             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                退出                    请按2             *\n");
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
}

void welcomeCom()//一般界面
{
        printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <欢迎使用普通用户模式>                  *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
        printf(
        "\t\t\t\t\t\t\t\t  *                    <您可以使用以下功能>                  *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                开户                      请按0             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                存款                      请按1             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                取款                      请按2             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                借款                      请按3             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                还款                      请按4             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                查询                      请按5             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                退出                      请按6             *\n");
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
}

void welcomeVip()//Vip界面
{
        printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <欢迎使用VIP用户模式>                  *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                    <您可以享受优先取款等特权>                *\n");
        printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
        printf(
        "\t\t\t\t\t\t\t\t  *                    <您可以使用以下功能>                  *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                开户                      请按0             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                存款                      请按1             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                取款                      请按2             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                借款                      请按3             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                还款                      请按4             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                查询                      请按5             *\n");
    printf("\t\t\t\t\t\t\t\t  *----------------------------------------------------------*\n");
    printf(
        "\t\t\t\t\t\t\t\t  *                退出                      请按6             *\n");
    printf("\t\t\t\t\t\t\t\t   **********************************************************\n");
}

void error()  //打印操作错误
{
    printf("\n");
    printf("\t\t\t  操作错误，请重新选择操作选项！！\n\n");
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

void init(int num){ //人物信息初始化
    string name,ID;
    string id,balance,loans,password;
    int id1,balance1,loans1,password1;
    cout<<"\t\t\t\t\t\t\t\t 现在是银行账户初始化进程"<<endl;
    for(int i=0;i<num;i++){
        cout<<"\t\t\t\t\t\t\t\t 请依次输入id,姓名,余额,贷款,账号,密码"<<endl;
        while(true){
            int flag=0;
            int num=0;
            cout<<"\t\t\t\t\t\t\t\t ";
            cin>>id>>name>>balance>>loans>>ID>>password;
            for(int i=0;i<id.size();i++){
                if(id[i]<'0'||id[i]>'9'){
                    cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
                    flag=1;
                    break;
                }else num=num*10+id[i]-'0';
            }
            if(flag==1) continue;
            else id1=num;
            num=0;
            for(int i=0;i<balance.size();i++){
                if(balance[i]<'0'||balance[i]>'9'){
                    cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
                    flag=1;
                    break;
                }else num=num*10+balance[i]-'0';
            }
            if(flag==1) continue;
            else balance1=num;
            num=0;
            for(int i=0;i<loans.size();i++){
                if(loans[i]<'0'||loans[i]>'9'){
                    cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
                    flag=1;
                    break;
                }else num=num*10+loans[i]-'0';
            }
            if(flag==1) continue;
            else loans1=num;
            num=0;
            for(int i=0;i<password.size();i++){
                if(password[i]<'0'||password[i]>'9'){
                    cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
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
        if(balance1>=200000) users[id1].isVip=true;//存款大于20万为VIP
        else users[id1].isVip=false;//
        users[id1].name=name;
        users[id1].arrivalTime=0;
        users[id1].balance=balance1;
        users[id1].loans=loans1;
        users[id1].isOpen=true;
        pass[ID]=password1;
    }
}

//获取costMinute
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

//存款
void saveMoney(int id,int money){
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t 该账户不存在"<<endl;
        cout<<"\t\t\t\t\t\t\t\t 开户请输入1,退出请输入0"<<endl;
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
            cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
        }
    }
    users[id].balance+=money;
    bankMoney+=money;
    if(users[id].balance>=500000) users[id].isVip=true;//是否可以成为VIP
    else users[id].isVip=false;
    cout<<"\t\t\t\t\t\t\t\t 存款成功"<<endl;
}

//取款
void getMoney(int id,int money){
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t 该账户不存在"<<endl;
        cout<<"\t\t\t\t\t\t\t\t 开户请输入1,否则请输入0"<<endl;
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
            cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
        }
    }
    if(users[id].balance<money){
        cout<<"\t\t\t\t\t\t\t\t 余额不足,取款失败"<<endl;
        cout<<"\t\t\t\t\t\t\t\t 重新输入请按1,否则请按0"<<endl;
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
            cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
        }
    }
    else if(bankMoney<money){
        cout<<"\t\t\t\t\t\t\t\t 取款失败,银行余额不足,请到二型窗口等侯"<<endl;
        windows2.line.push(id);
        return ;
    }else{
        users[id].balance-=money;
        bankMoney-=money;
    }
    cout<<"\t\t\t\t\t\t\t\t 取款成功"<<endl;
    return ;
}

//借款
void lendMoney(int id,int money){
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t 该账户不存在"<<endl;
        cout<<"\t\t\t\t\t\t\t\t 开户请输入1,否则请输入0"<<endl;
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
            cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
        }
    }
    if(bankMoney<money){
        cout<<"\t\t\t\t\t\t\t\t 借款失败,银行余额不足,请到二型窗口等侯"<<endl;
        windows2.line.push(id);
        return ;
    }else{
        users[id].loans+=money;
        bankMoney-=money;
        cout<<"\t\t\t\t\t\t\t\t 借款成功"<<endl;
    }
    return ;
}

//还款
void restoreMoney(int id,int money){
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t 该账户不存在"<<endl;
        cout<<"\t\t\t\t\t\t\t\t 开户请输入1,否则请输入0"<<endl;
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
            cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
        }
    }
    if(users[id].loans<money){
        cout<<"\t\t\t\t\t\t\t\t 还款失败,您缴纳的金额超出贷款，请重新输入"<<endl;
        while(true){
            printf("\t\t\t\t\t\t\t\t ");
            cin>>money;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
            }else break;
            cout<<"\t\t\t\t\t\t\t\t 输入错误，请重新输入"<<endl;
        }
        restoreMoney(id,money);
    }
    else{
        bankMoney+=money;
        users[id].loans-=money;
        cout<<"\t\t\t\t\t\t\t\t 还款成功"<<endl;
        cout<<"\t\t\t\t\t\t\t\t 您现在的贷款额为:"<<users[id].loans<<endl;
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
		cout << "\t\t\t\t\t\t\t\t 输入错误，请重新输入。" << endl;
	}
	return x;
}

void add(int time){//增加人数
    if(time>=540){
        cout<<"\t\t\t\t\t\t\t\t 今日营业时间已结束"<<endl;
        return ;
    }
    cout<<"\t\t\t\t\t\t\t\t 现在是新人排队时间"<<endl;
    string name="";
    int id=0,money=-1,type=-1,costMinute=0;
    cout<<"\t\t\t\t\t\t\t\t 请输入id"<<endl;
    id=Error(id,0);
    cout<<"\t\t\t\t\t\t\t\t 请输入name"<<endl;
    cout<<"\t\t\t\t\t\t\t\t ";
    cin>>name;
    cout<<"\t\t\t\t\t\t\t\t 请输入type"<<endl;
    cout<<"\t\t\t\t\t\t\t\t (0:开户 1:存款 2:取款  3:借款  4:还款 5:查询)"<<endl;
    type=Error(type,1);
    if(type==1||type==2||type==3||type==4){
        cout<<"\t\t\t\t\t\t\t\t 请输入money"<<endl;
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

void newID(int id){ //开户
    cout<<"\t\t\t\t\t\t\t\t 现在是开户进程"<<endl;
    cout<<"\t\t\t\t\t\t\t\t 请输入账号"<<endl;
    string ID;
    int password;
    printf("\t\t\t\t\t\t\t\t ");
    cin>>ID;
    if(pass.count(ID)!=0){
        cout<<"\t\t\t\t\t\t\t\t 账号已存在，请重新输入"<<endl;
        newID(id);
    }else{
        cout<<"\t\t\t\t\t\t\t\t 请输入密码"<<endl;
        password=eder();
        pass[ID]=password;
        users[id].isOpen=true;
        cout<<endl;
        cout<<"\t\t\t\t\t\t\t\t 开户成功"<<endl;
    }
}

void QueryAll(){//查询所有用户信息
    printf(
        "\t\t\t\t\t\t\t\t  *           用户            余额               贷款              *\n");
    for(int i=1;i<100000;i++){
        if(users[i].isOpen){
            printf(
                "\t\t\t\t\t\t\t\t  *            %s              %d                 %d               *\n",users[i].name.c_str(),users[i].balance,users[i].loans);
        }
    }
}

void QueryOne(){//管理员查询某位用户
    cout<<"\t\t\t\t\t\t\t\t 请输入id:"<<endl;
    int id;
    id=Error(id,0);
    if(!users[id].isOpen){
        cout<<"\t\t\t\t\t\t\t\t 该用户不存在"<<endl;
        cout<<"\t\t\t\t\t\t\t\t 请重新输入  "<<endl;
        cin.get();
        system("cls");
        QueryOne();
    }else{
        printf(
            "\t\t\t\t\t\t\t\t  *           用户            余额               贷款              *\n");
        printf(
                "\t\t\t\t\t\t\t\t  *            %s              %d                 %d               *\n",users[id].name.c_str(),users[id].balance,users[id].loans);
    }
}
void Query(int id){//查询余额
    cout<<"\t\t\t\t\t\t\t\t 请输入帐户和密码:"<<endl;
    cout<<"\t\t\t\t\t\t\t\t ";
    string ID;
    int password;
    cin>>ID;
    password=eder();
    cout<<endl;
    if(!pass.count(ID)){
        cout<<"\t\t\t\t\t\t\t\t 该用户不存在"<<endl;
        cout<<"\t\t\t\t\t\t\t\t 重新输入请按1,开户请按0"<<endl;
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
            cout<<"\t\t\t\t\t\t\t\t 帐户或密码错误,请重新输入"<<endl;
            Query(id);
        }else{
            cout<<"\t\t\t\t\t\t\t\t 您的帐户余额为:"<<users[id].balance<<endl;
            cout<<"\t\t\t\t\t\t\t\t 您的贷款为:"<<users[id].loans<<endl;
            //可增加其他查询
        }
    }
}

int eder()//加密密码
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
				cout << "\b \b";//密码支持退格的实现
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

void fillWindows(){//在类型一窗口排队
    string name;
    int id,money,costMinute=0;//costMinute为不超过100的随机数
    cout<<"\t\t\t\t\t\t\t\t 现在是排队时间"<<endl;
    cout<<"\t\t\t\t\t\t\t\t 请输入id,name"<<endl;
    id=Error(id,0);
    cin>>name;
    while(costMinute==0)
        costMinute=rand()%100;
    users[id].costMinute=costMinute;
    users[id].arrivalTime=0;
    if(!users[id].isVip){//判断是否为VIP用户
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


void SimulateWinvip(int t){//模拟VIP窗口
    if(vip.popTime!=t||vip.line.empty()) return ;
    go();
    welcome();//初始界面
    int num;
    num=Error(num,0);
    if(num==0){
        system("cls");
        printf("\t\t\t  当前是用户时间！！\n");
        error();
        SimulateWinvip(t);
    }
    else if(num==1){
        int flag=0;
        int type,money;
        int id=vip.line.front();

        while(1){
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t 当前"<<users[id].name<<"用户正在办理业务"<<endl;
            if(!users[id].isVip) welcomeCom();
            else welcomeVip();
            cout<<"\t\t\t\t\t\t\t\t 请选择您要办理的业务类型"<<endl;
            type=Error(type,0);
            if(type==1||type==2||type==3||type==4){
                cout<<"\t\t\t\t\t\t\t\t 请输入money"<<endl;
                money=Error(money,0);
                users[id].type=type;
                users[id].money=money;
            }
            if(type==0) newID(id);
            else if(type==1){//存款
                saveMoney(id,money);
            }else if(type==2){//取款
                getMoney(id,money);
            }else if(type==3){//借款
                lendMoney(id,money);
            }else if(type==4){//还款
                restoreMoney(id,money);
            }else if(type==5){
                Query(id);
            }else if(type==6){
                system("cls");
                break;
            }else{
                cout<<"\t\t\t\t\t\t\t\t 请正确选择"<<endl;
                continue;
            }
            cin.get();
            cin.get();
            if(type==1||type==4){
                SimulateWin2(t,vipWindows2);
                SimulateWin2(t,windows2);
            }
        }
        finished[id]=t;//记录完成时间
        vip.line.pop();//出队
        if(vip.line.size() > 0){
            // 更新出列时间
                vip.popTime=t+users[vip.line.front()].costMinute;
        }
        cout<<endl;
    }else if(num==2){
        cout <<"\t\t\t\t\t\t\t\t 感谢您的使用" << endl;
        cin.get();
        system("cls");
    }else{
        system("cls");
        error();
        SimulateWinvip(t);
    }
}


//模拟类型二窗口过程
void SimulateWin2(int time,struct Window &win2){
    int num=0;
    while(!win2.line.empty()&&num<=win2.line.size()){
        num++;
        int id=win2.line.front();
        if(users[id].type==2){//取款
            if(bankMoney>=users[id].money){//满足条件
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
        }else if(users[id].type==3){//借款
            if(bankMoney>=users[id].money){//满足条件
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

//模拟类型一窗口过程
void SimulateWin1(){
    for(int t=0;t<540;t++){//从9:00---17:00
        if(t==60||t==360) add(t);
        SimulateWinvip(t);
        for(int i=1;i<=winNum1;i++){ //遍历窗口
            if(windows[i].popTime!=t||windows[i].line.empty()) continue;
            go();
            welcome();//初始界面
            cout<<"\t\t\t\t\t\t\t\t 请选择您要办理的业务类型"<<endl;
            int num;
            num=Error(num,0);
            if(num==0){
                system("cls");
                printf("\t\t\t  当前是用户时间！！\n");
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
                    cout<<"\t\t\t\t\t\t\t\t 当前"<<users[id].name<<"用户正在办理业务"<<endl;
                    if(!users[id].isVip) welcomeCom();
                    else welcomeVip();
                    cout<<"\t\t\t\t\t\t\t\t 请选择您要办理的业务类型"<<endl;

                    type=Error(type,0);
                    if(type==1||type==2||type==3||type==4){
                        cout<<"\t\t\t\t\t\t\t\t 请输入money"<<endl;
                        money=Error(money,0);
                        users[id].type=type;
                        users[id].money=money;
                    }
                    if(type==0) newID(id);
                    else if(type==1){//存款
                        saveMoney(id,money);
                    }else if(type==2){//取款
                        getMoney(id,money);
                    }else if(type==3){//借款
                        lendMoney(id,money);
                    }else if(type==4){//还款
                        restoreMoney(id,money);
                    }else if(type==5){
                        Query(id);
                    }else if(type==6){
                        system("cls");
                        break;
                    }else{
                        cout<<"\t\t\t\t\t\t\t\t 请正确选择"<<endl;
                        continue;
                    }
                    cin.get();
                    cin.get();
                    if(type==1||type==4){
                        SimulateWin2(t,vipWindows2);
                        SimulateWin2(t,windows2);
                    }
                }
                finished[id]=t;//记录完成时间
                windows[i].line.pop();//出队
                if(windows[i].line.size() > 0){
                    // 更新出列时间
                        windows[i].popTime=t+users[windows[i].line.front()].costMinute;
                }
                cout<<endl;
            }else if(num==2){
                cout <<"\t\t\t\t\t\t\t\t 感谢您的使用" << endl;
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

double getAverage(){ //获取平均逗留时间
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

void initAdmin(){//初始管理员操作
    printf("\t\t\t\t\t\t\t\t 请输入您选择的模式\n");
    cout<<endl;
    int num;
    num=Error(num,0);
    if(num==0){
        while(1){
            system("cls");
            welcomeAdmin();
            cout<<"\t\t\t\t\t\t\t\t 请输入您的服务类型"<<endl;
            num=Error(num,0);
            int numa;
            if(num==0){
                cout<<"\t\t\t\t\t\t\t\t 请输入录入账户数目"<<endl;
                numa=Error(numa,0);
                init(numa);
            }else if(num==1){
                for(int i=0;i<numa;i++)//窗口一排队
                    fillWindows();
            }else if(num==2){
                while(1){
                    system("cls");
                    AdminQuery();
                    cout<<"\t\t\t\t\t\t\t\t 请输入您的服务类型"<<endl;
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
        cout << "\t\t\t\t\t\t\t\t 输入错误，请重新输入。" << endl;
        initAdmin();
    }
    return ;
}

int main()
{
    memset(finished,0,sizeof(finished));
    memset(startTime,0,sizeof(startTime));
    system("mode con cols=240 lines=55");
    welcome();//初始界面
    initAdmin();//管理员操作
    SimulateWin1();//模拟过程
    cout<<"银行余额为:  "<<bankMoney<<endl;
    cout<<"每位用户的滞留时间为(ID:时间):"<<endl;
    for(int i=1;i<100000;i++){//遍历每位用户的滞留时间,可删去,测试用
        if(finished[i]>0)
            cout<<i<<" : "<<finished[i]-startTime[i]<<" 分钟 "<<endl;
    }
    cout<<"平均滞留时间为:";
    double average=getAverage();//平均时间
    printf("%.2f 分钟\n",average);
    return 0;
}
