//#include <iostream>
//#include <vector>
//#include <list>
//#include <map>
//#include <string>
//#include <functional>
//using namespace std;
//struct Fac
//{
//    bool isnumber=true;
//    int num=0;
//};
//typedef function<int(int,int)> SymFunc;
//map<string,int> symbolmap={{"+",0},{"-",1},{"*",2},{"÷",3},{"/",3}};//符号映射表
//map<int,SymFunc> calmap; //因为Func没有什么好的实现比较的方法 因此就存储指针了 //上次截止此处


//template<Cont>
//void regist(Cont &cont,int sign,SymFunc func)
//{
//    //注册函数
//    if(calmap.find(sign)!=calmap.end()) return;
//    if(cont.size()==0) return;
//    //添加sign注册
//    calmap[sign]=func;
//    //添加符号注册
//    for(auto t=cont.begin();t!=cont.end();++t)
//    {
//        symbolmap[*t]=sign;
//    }

//}
//template<>
//void regist<char *>(char *str,int sign,SymFunc func)
//{
//    //这是对C风格字符串的特化
//    if(calmap.find(sign)!=calmap.end()) return;
//    if(str[0]==0) return;
//    //添加sign注册
//    calmap[sign]=func;
//    //添加符号注册
//    for(int i=0;str[i]!=0;++i)
//    {
//        symbolmap[str[i]]=sign;
//    }
//}

//void initsym()
//{
//    //预设的初始化函数
//    regist("+",0,[](int a,int b){return a+b;});
//    regist("-",1,[](int a,int b){return a-b;});
//    regist("*",2,[](int a,int b){return a*b;});
//    regist("/÷",3,[](int a,int b){return a/b;});
//}
//vector<Fac> makeLine(const string &exp)
//{
//    //解析得到一个line
//    vector<Fac> ret;
//    int num=0;//数字缓冲
//    char buf[4096];
//    int top=0;//字符缓冲空位指针
//    bool isnum=exp[0]<='9'&&exp[0]>='0'? true:false;//这个标志 当遇到数字时置位 遇到符号时复位
//    for(int i=0;i<exp.length();++i)
//    {
//        for(;exp[i]==' '||exp[i]=='\t';++i);//跳过空格
//        //现在处理字符
//        char c=exp[i];
//        if(c>='0'&&c<='9')
//        {
//            if(!isnum)
//            {
//                //压入符号
//                buf[top]=0;//添加字符串结尾
//                auto ptr=symbolmap.find(string(buf));
//                if(ptr==symbolmap.end()) throw "符号错误！";
//                int sym=ptr->second;
//                //构造Fac
//                Fac fac;
//                fac.isnumber=false;
//                fac.num=sym;
//                ret.push_back(fac);
//                //重置数字缓冲
//                num=0;
//            }
//            isnum=true;
//            num*=10;
//            num+=c-'0';
//        }
//        else
//        {
//            //符号
//            if(isnum)
//            {
//                //放入数字
//                Fac fac;
//                fac.isnumber=true;
//                fac.num=num;
//                ret.push_back(fac);
//                //清空字符缓冲
//                top=0;
//            }
//            //处理当前字符
//            isnum=false;//设置为读取符号状态
//            buf[top++]=c;
//        }
//    }
//    return ret;
//}
//int str2int(char *str,int base)
//{
//    int sum=0;
//    for(int i=0;str[i]!=0;++i)
//    {
//        sum*=base;
//    }
//}

//int main(int argc,char *argv)
//{
//    //说明:这个程序里不试用任何技巧 而是直接对人类的思维过程进行表现
//    cout<<"symbols"<<endl;
//    for(auto ptr=symbolmap.begin();ptr!=symbolmap.end();ptr++)
//    {
//        cout<<ptr->first<<"\t"<<ptr->second<<endl;
//    }
//    start:
//    string exp;
//    cout<<"please enter a expression:";
//    cin>>exp;

//    //解析
//    vector<Fac> line=makeLine(exp);
//    for(int i=0;i<line.size();++i)
//    {
//        Fac fac=line[i];
//        cout<<"no."<<i<<":\t";
//        cout<<"type:"<<(fac.isnumber? "number":"symbol")<<"\t";
//        cout<<"contain:"<<fac.num<<endl;
//    }
//    //计算
//    int sum=0;
//    for(int i=0;i<line.size();++i)
//    {
//        Fac fac=line[i];
//        SymFunc func=calmap[fac.num];
//    }
//    goto start;
//    //解析开始
//    //第一要素：人类的思维基于“过程”的树状组合，结构上为递归
//    //第二要素：人类的思维基于“因子”而非原始数据
//    //第三要素：人类的思维基于“共享池”，解析过程中不丢失原始信息
//    //第四要素：人类解析表达式时，有“看”和“过”两个操作，而非只有“取”一个操作
//    //第五要素：人类解析思维中有“预览过程”，暂时过程记录一个起始点，并且预览过程不影响主过程
//    //          预览过程结束时，得到一个“预先结论”，思维重新回到起始点，并使用这个预先结论
//    //第六要素：人类解析思维中存在“等量代换”过程，等量代换确定一个范围并将其作为一个整体（更广泛的说是一个过滤器），并将
//                //任何访问这个整体的动作都被重定向到代换变量
//    //第七要素：人类思维基于“状态树”和“状态栈”，状态树为预先确定，状态栈为解析时使用
//    //第八要素：人类思维存在可以与主过程无关的“暂时过程”，暂时过程的产生由主过程 “require”开始，
//    //          并且这个暂时过程与主过程关联，主过程的所有数据保存在“活跃缓冲区”，可以被暂时过程使用但不能修改
//    //          暂时过程修改主过程的数据与“写时复制”机制类似，当暂时过程成功时，修改后的数据替换掉主过程的对应数据（类似
//    //            pull request，这也是个过程
//    //第九要素：人类思维的任何“过程”都是平等的,因此任何过程都可以作为主过程
//    //第十要素：人类思维的任何过程都是“有监视”的，也就是过程本身产生一系列描述这个过程的数据，
//    //          这些数据作为“触发因子”被投递到“关联网”
//    //第十一要素： 人类思维存在作为基本触发构造的“关联网”，其接受监视得到的数据并触发一个过程
//    //第十二要素：人类思维存在“记忆库”，任何监视得到的数据以时间为索引放到此记忆库中，任何过程都可访问，记忆库是分层的
//                   //层次越低的记忆库 “监视频率”越低
//    //第十三要素： 数据监视的结果就是数据本身
//    //第十四要素：一旦记忆库中某些数据被“注意到”，则相关数据都会被调动为活跃态，放入高速记忆库中
//    //第十五要素：人类记忆库为定时间序降级机制，数据会被迅速层层下降，只有不断被“注意”才会被
//    //              不断提升

//    //以下为解析过程

//}


//下面是新程序 用于测试字符串压缩
//所以说要sum>3因为必须要有一个“引导符” 所以说这样毫无意义……倒不如直接用缩位的方法
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define MAXZBUF  4096    //这是压缩缓冲区大小
#define MAXUBUF  32768    //这是解压缓冲区大小
int satoi(const char *str,int *nextptr,int start=0)
{
    //以任何非数字为结束
    //nextptr为‘后的位置
    //不考虑负数
    int sum=0;
    *nextptr=start;
    for(int i=start;str[i]<='9'&&str[i]>='0';++i,(*nextptr)++)
    {
        sum*=10;
        sum+=str[i]-'0';
    }
    return sum;
}

char *zip(const char *str)
{
    char *buf=(char *)malloc(sizeof(char)*4096);//通用缓冲区
    char *ret=(char *)calloc(MAXZBUF,sizeof(char));//用个calloc增加多样性……
    char *retptr=ret;
    int sum=0;//同字符计数器
    char c=str[0];//当前字符 初始化为第一个字符
    retptr+=sprintf(retptr,"%c",c);//先输出第一个字符 创造初始化环境
    for(int j=0;;++j)
    {
        if(str[j]==c) sum++;
        else
        {
            //遇到不同字符
            if(sum>3)
            {
                retptr+=sprintf(retptr,":%s'",itoa(sum,buf,10));
            }
            else
            {
                if(sum>1) for(int k=0;k<sum-1;++k) retptr+=sprintf(retptr,"%c",c);//填充sum-1个 加上下面一个正好sum个
            }
            //标准初始化过程：记录新字符 输出要计数的字符 然后初始化计数器为1
            c=str[j];
            retptr+=sprintf(retptr,"%c",c);
            sum=1;
            if(str[j]==0) break;//这里放跳出语句 的意思为 当遇到不同字符(\0总是不同字符)时处理 处理完了发现是结束符就跳出
        }
    }
    free(buf);
    return ret;
}
char *unzip(const char *zstr)
{
    //解压程序
    char *ret=(char *)calloc(MAXUBUF,sizeof(char));
    int rtop=0;//ret的当前空位指针
    for(int i=0;zstr[i]!=0;)
    {
//        if(zstr[i]=='\'') {i++;continue;} //跳过
        char c=zstr[i];
        ret[rtop++]=c;
        i++;//跳到后面的数字上去
//        if(c<='9'&&c>='0')
//        {
            if(zstr[i]==':') i++;//如果后面的符号是冒号就跳到数字上
            else continue;//否则继续
//        }
//        if(zstr[i]=='\'') {i++;continue;}//如果为’的话就继续下一个
        if(!(zstr[i]<='9'&&zstr[i]>='0'))
        {
            //如果不在数字范围内 说明要继续下一个
            continue;
        }
        //否则这里读取个数
        int sum=satoi(zstr,&i,i);//读取结束后satoi会直接把i设置为‘处
        i++;//跳过数字后的单引号
        for(int j=1;j<sum;++j)
        {
            ret[rtop++]=c;
        }
        ret[rtop]=0;//暂时把顶设置为结束
    }
    return ret;
}

int main(int argc,char **argv)
{
    if(argc>1)
    {
        for(int i=1;i<argc;++i)
        {
            char *zipstr=zip(argv[i]);
            char *unziped=unzip(zipstr);
            printf("ziped:%s\nraw  :%s\nunzip:%s\n",zipstr,argv[i],unziped);
            free(zipstr);
            free(unziped);
        }
    }
    getchar();
}
