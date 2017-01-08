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
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <string.h>
//#define MAXZBUF  4096    //这是压缩缓冲区大小
//#define MAXUBUF  32768    //这是解压缓冲区大小
//int satoi(const char *str,int *nextptr,int start=0)
//{
//    //以任何非数字为结束
//    //nextptr为‘后的位置
//    //不考虑负数
//    int sum=0;
//    *nextptr=start;
//    for(int i=start;str[i]<='9'&&str[i]>='0';++i,(*nextptr)++)
//    {
//        sum*=10;
//        sum+=str[i]-'0';
//    }
//    return sum;
//}

//char *zip(const char *str)
//{
//    char *buf=(char *)malloc(sizeof(char)*4096);//通用缓冲区
//    char *ret=(char *)calloc(MAXZBUF,sizeof(char));//用个calloc增加多样性……
//    char *retptr=ret;
//    int sum=0;//同字符计数器
//    char c=str[0];//当前字符 初始化为第一个字符
//    retptr+=sprintf(retptr,"%c",c);//先输出第一个字符 创造初始化环境
//    for(int j=0;;++j)
//    {
//        if(str[j]==c) sum++;
//        else
//        {
//            //遇到不同字符
//            if(sum>3)
//            {
//                retptr+=sprintf(retptr,":%s'",itoa(sum,buf,10));
//            }
//            else
//            {
//                if(sum>1) for(int k=0;k<sum-1;++k) retptr+=sprintf(retptr,"%c",c);//填充sum-1个 加上下面一个正好sum个
//            }
//            //标准初始化过程：记录新字符 输出要计数的字符 然后初始化计数器为1
//            c=str[j];
//            retptr+=sprintf(retptr,"%c",c);
//            sum=1;
//            if(str[j]==0) break;//这里放跳出语句 的意思为 当遇到不同字符(\0总是不同字符)时处理 处理完了发现是结束符就跳出
//        }
//    }
//    free(buf);
//    return ret;
//}
//char *unzip(const char *zstr)
//{
//    //解压程序
//    char *ret=(char *)calloc(MAXUBUF,sizeof(char));
//    int rtop=0;//ret的当前空位指针
//    for(int i=0;zstr[i]!=0;)
//    {
////        if(zstr[i]=='\'') {i++;continue;} //跳过
//        char c=zstr[i];
//        ret[rtop++]=c;
//        i++;//跳到后面的数字上去
////        if(c<='9'&&c>='0')
////        {
//            if(zstr[i]==':') i++;//如果后面的符号是冒号就跳到数字上
//            else continue;//否则继续
////        }
////        if(zstr[i]=='\'') {i++;continue;}//如果为’的话就继续下一个
//        if(!(zstr[i]<='9'&&zstr[i]>='0'))
//        {
//            //如果不在数字范围内 说明要继续下一个
//            continue;
//        }
//        //否则这里读取个数
//        int sum=satoi(zstr,&i,i);//读取结束后satoi会直接把i设置为‘处
//        i++;//跳过数字后的单引号
//        for(int j=1;j<sum;++j)
//        {
//            ret[rtop++]=c;
//        }
//        ret[rtop]=0;//暂时把顶设置为结束
//    }
//    return ret;
//}

//int main(int argc,char **argv)
//{
//    if(argc>1)
//    {
//        for(int i=1;i<argc;++i)
//        {
//            char *zipstr=zip(argv[i]);
//            char *unziped=unzip(zipstr);
//            printf("ziped:%s\nraw  :%s\nunzip:%s\n",zipstr,argv[i],unziped);
//            free(zipstr);
//            free(unziped);
//        }
//    }
//    getchar();
//}



//#include <stdio.h>
//#include <math.h>
//#include <thread>
//#include <fstream>
//int f(int a)
//{
//    int i;
//    for(i=2;i<=sqrt(a);i+=2)
//        if(a%i==0)break;
//    if(i>=sqrt(a))return 1;
//    else return 0;
//}
//// primes[i]是递增的素数序列: 2, 3, 5, 7, ...
//// 更准确地说primes[i]序列包含1->sqrt(n)范围内的所有素数
//bool isPrime(int primes[], int n)
//{
// if(n < 2) return false;
// for(int i = 0; primes[i]*primes[i] <= n; ++i)
//  if(n%primes[i] == 0) return false;
// return true;
//}
//bool isPrime_ml(int n)
//{
//    if(n < 2) return false;
//    if(n == 2) return true;
//    if(n%2 == 0) return false;
//    int foo = (int)sqrt(n);
//    for(int i = 3; i <= foo; i += 2)
//        if(n%i == 0) return false;
//    return true;
//}
//int main(void)
//{

////    int n,a,i,b;
////    while(scanf("%d",&n)!=EOF)
////    {
////        for(i=3,b=0;i<=n/2;i+=2)
////        {
////            if(f(i)==1)
////            {
////                a=n-i;
////                if(f(a)==1)b++;
////            }
////        }
////        printf("%d\n",b);
////    }
////    return 0;

//    auto fun=[](int start,int end,int *nums){
//        int tsum=0;
//        int p=0;
//        for(int i=start;i<end;++i)
//        {
//            if(isPrime_ml(i))
//            {
//                nums[p++]=i;
//                tsum++;
//            }
//        }
//        printf("done");
//    };

//    int max=pow(2,23);
//    //4线程素数表生成
//    int *nums1=new int[4*1024*1024]{0};//就不信不够
//    int *nums2=new int[4*1024*1024]{0};
//    int *nums3=new int[4*1024*1024]{0};
//    int *nums4=new int[4*1024*1024]{0};

//    std::thread th1([&fun,max,nums1](){fun(2,max/4,nums1);});
//    std::thread th2([&fun,max,nums2](){fun(max/4+1,max/4*2,nums2);});
//    std::thread th3([&fun,max,nums3](){fun(max/4*2+1,max/4*3,nums3);});
//    std::thread th4([&fun,max,nums4](){fun(max/4*3+1,max,nums4);});
//    th1.detach();
//    th2.detach();
//    th3.detach();
//    th4.detach();
//    getchar();
//    //写入文件
//    std::ofstream fout;
//    fout.open("table.c");
//    fout<<"int stable[]={";
//    int *nums[]={nums1,nums2,nums3,nums4};
//    int sum=0;
//    for(int i=0;i<4;++i)
//    {
//        int *ns=nums[i];
//        for(int j=0;ns[j]!=0;++j)
//        {
//            fout<<ns[j];
//            if(!(i==3&&ns[j+1]==0)) fout<<',';
//            sum++;
//        }
//        }
//        fout<<"};\n";
//        fout<<"int s_sum="<<sum<<";";
//        fout.close();

    //单线程版本 似乎有些问题
//    auto fun=[](int start,int end,int *nums){
//        int tsum=0;
//        int p=0;
//        for(int i=start;i<end;++i)
//        {
//            if(isPrime(nums,i))
//            {
//                nums[p++]=i;
//                tsum++;
//            }
//        }
//        printf("done");
//    };
//    int *nums1=new int[8*1024*1024]{0};
//    nums1[0]=2;
//    fun(2,max,nums1);
//    std::ofstream fout;
//    fout.open("table.c");
//    fout<<"int stable[]={";
//    int *nums[]={nums1};
//    for(int i=0;i<4;++i)
//    {
//        int *ns=nums[i];
//        for(int j=0;ns[j]!=0;++j)
//        {
//            fout<<ns[j];
//            if(!(i==3&&ns[j+1]==0)) fout<<',';
//        }
//    }
//    fout<<"};";
//    fout.close();
    //程序结束不用释放内存
//}

//#include<iostream>
//#include <math.h>
//using namespace std;
//int main()
//{int CompositeNumFilterV3(int);
// int m=pow(2,23),c;
//// cin>>m;
// c=CompositeNumFilterV3(m);
// cout<<c<<endl;
//return 0;
//}//求素数的程序
//int CompositeNumFilterV3(int n)
//{
// int i, j;
// //素数数量统计
// int count = 0;
// // 分配素数标记空间，明白+1原因了吧，因为浪费了一个flag[0]
// char* flag = (char*)malloc( n+1 );
// // 干嘛用的，请仔细研究下文
// int mpLen = 2*3*5*7*11*13;
// char magicPattern[2*3*5*7*11*13]; // 奇怪的代码，why，思考无法代劳，想！
// for (i=0; i<mpLen; i++)
// {
//  magicPattern[i++] = 1;
//  magicPattern[i++] = 0;
//  magicPattern[i++] = 0;
//  magicPattern[i++] = 0;
//  magicPattern[i++] = 1;
//  magicPattern[i] = 0;
// }
// for (i=4; i<=mpLen; i+=5)
//  magicPattern[i] = 0;
// for (i=6; i<=mpLen; i+=7)
//  magicPattern[i] = 0;
// for (i=10; i<=mpLen; i+=11)
//  magicPattern[i] = 0;
// for (i=12; i<=mpLen; i+=13)
//  magicPattern[i] = 0;  // 新的初始化方法,将2,3,5,7,11,13的倍数全干掉
//  // 而且采用memcpy以mpLen长的magicPattern来批量处理
// int remainder = n%mpLen;
// char* p = flag+1;
// char* pstop = p+n-remainder;
// while (p < pstop)
// {
//  memcpy(p, magicPattern, mpLen);
//  p += mpLen;
// }
//  if (remainder > 0)
//  {
//   memcpy(p, magicPattern, remainder);
//  }
//  flag[2] = 1;
//  flag[3] = 1;
//  flag[5] = 1;
//  flag[7] = 1;
//  flag[11] = 1;
//  flag[13] = 1;    // 从17开始filter，因为2,3,5,7,11,13的倍数早被kill了
//  // 到n/13止的，哈哈，少了好多吧
//  int stop = n/13;
//  for (i=17; i <= stop; i++)
//  {
//   // i是合数，请歇着吧，因为您的工作早有您的质因子代劳了
//  if (0 == flag[i]) continue;
//  // 从i的17倍开始过滤
//  int step = i*2;
//  for (j=i*17; j <= n; j+=step)
//  {
//  flag[j] = 0;
//  }
//  }

//  // 统计素数个数
//  for (i=2; i<=n; i++)
//  {
//   if (flag[i]) count++;
//  }

//  // 因输出费时，且和算法核心相关不大，故略
//  // 释放内存，别忘了传说中的内存泄漏
//  free(flag);

//  return count;
//}

//C语言读取
#include <stdio.h>
#include <stdbool.h>
int read(FILE *f)
{
    //这里f的文件指针应该指向数字
    bool isf=false;//负数标志
    char c=0;
    if((c=fgetc(f))=='-') {isf=true;c=fgetc(f);}//自动seek
    int sum=0;
    for(;c>='0'&&c<='9';c=fgetc(f))
    {
        sum=sum*10+(c-'0');
    }
    //文件指针指向 第一个非空格的后面 根据此函数的逻辑语义
    //应该在数字后面结束因此减一 如果直接在main里写代码
    //就不用这么麻烦
    fseek(f,-1,SEEK_CUR);
    if(isf) sum=-sum;
    return sum;
}

int main()
{
    char buf[4096];
    FILE *write=fopen("test.txt","wt");
    int raw[]={1,2,3,4,5,6,1111,2222,123,124};
    int len=sizeof(raw)/sizeof(int);
    for(int i=0;i<len;++i) fprintf(write,"%d ",raw[i]);
    fclose(write);

    FILE *rfile=fopen("test.txt","rt");
    int nums[4096]={0};
//    FILE *f=rfile;
//    int nums[4096]={0};
//    int nptr=0;
//    bool isin=false;
//    for(char c=fgetc(f);c!=EOF;c=fgetc(f))
//    {
//        if(c==' ')
//        {
//            if(!isin)
//                continue;
//            else
//            {
//                nptr++;
//                isin=false;
//            }
//        }
//        if(c>='0'&&c<='9')
//        {
//            if(!isin) isin=true;
//            nums[nptr]*=10;
//            nums[nptr]+=c-'0';
//        }
//    }
//    int sum=0;
//    char c=fgetc(rfile);
//    for(;c!=EOF&&c!=0;c=fgetc(rfile))
//    {

//        if(c==' '||c=='\t') continue;
//        fseek(rfile,-1,SEEK_CUR);//文件指针复位
//        int num=read(rfile);//结束后指向数字最后一个字符后面
//        nums[sum++]=num;
//    }
//    int sum=nptr;

    //以上注释部分为不分割结构的版本
    for(int i=0;i<sum;++i)
    {
        printf("%d\n",nums[i]);
    }
    fclose(rfile);
    getchar();
}
