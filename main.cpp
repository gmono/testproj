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
//map<string,int> symbolmap={{"+",0},{"-",1},{"*",2},{"��",3},{"/",3}};//����ӳ���
//map<int,SymFunc> calmap; //��ΪFuncû��ʲô�õ�ʵ�ֱȽϵķ��� ��˾ʹ洢ָ���� //�ϴν�ֹ�˴�


//template<Cont>
//void regist(Cont &cont,int sign,SymFunc func)
//{
//    //ע�ắ��
//    if(calmap.find(sign)!=calmap.end()) return;
//    if(cont.size()==0) return;
//    //���signע��
//    calmap[sign]=func;
//    //��ӷ���ע��
//    for(auto t=cont.begin();t!=cont.end();++t)
//    {
//        symbolmap[*t]=sign;
//    }

//}
//template<>
//void regist<char *>(char *str,int sign,SymFunc func)
//{
//    //���Ƕ�C����ַ������ػ�
//    if(calmap.find(sign)!=calmap.end()) return;
//    if(str[0]==0) return;
//    //���signע��
//    calmap[sign]=func;
//    //��ӷ���ע��
//    for(int i=0;str[i]!=0;++i)
//    {
//        symbolmap[str[i]]=sign;
//    }
//}

//void initsym()
//{
//    //Ԥ��ĳ�ʼ������
//    regist("+",0,[](int a,int b){return a+b;});
//    regist("-",1,[](int a,int b){return a-b;});
//    regist("*",2,[](int a,int b){return a*b;});
//    regist("/��",3,[](int a,int b){return a/b;});
//}
//vector<Fac> makeLine(const string &exp)
//{
//    //�����õ�һ��line
//    vector<Fac> ret;
//    int num=0;//���ֻ���
//    char buf[4096];
//    int top=0;//�ַ������λָ��
//    bool isnum=exp[0]<='9'&&exp[0]>='0'? true:false;//�����־ ����������ʱ��λ ��������ʱ��λ
//    for(int i=0;i<exp.length();++i)
//    {
//        for(;exp[i]==' '||exp[i]=='\t';++i);//�����ո�
//        //���ڴ����ַ�
//        char c=exp[i];
//        if(c>='0'&&c<='9')
//        {
//            if(!isnum)
//            {
//                //ѹ�����
//                buf[top]=0;//����ַ�����β
//                auto ptr=symbolmap.find(string(buf));
//                if(ptr==symbolmap.end()) throw "���Ŵ���";
//                int sym=ptr->second;
//                //����Fac
//                Fac fac;
//                fac.isnumber=false;
//                fac.num=sym;
//                ret.push_back(fac);
//                //�������ֻ���
//                num=0;
//            }
//            isnum=true;
//            num*=10;
//            num+=c-'0';
//        }
//        else
//        {
//            //����
//            if(isnum)
//            {
//                //��������
//                Fac fac;
//                fac.isnumber=true;
//                fac.num=num;
//                ret.push_back(fac);
//                //����ַ�����
//                top=0;
//            }
//            //����ǰ�ַ�
//            isnum=false;//����Ϊ��ȡ����״̬
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
//    //˵��:��������ﲻ�����κμ��� ����ֱ�Ӷ������˼ά���̽��б���
//    cout<<"symbols"<<endl;
//    for(auto ptr=symbolmap.begin();ptr!=symbolmap.end();ptr++)
//    {
//        cout<<ptr->first<<"\t"<<ptr->second<<endl;
//    }
//    start:
//    string exp;
//    cout<<"please enter a expression:";
//    cin>>exp;

//    //����
//    vector<Fac> line=makeLine(exp);
//    for(int i=0;i<line.size();++i)
//    {
//        Fac fac=line[i];
//        cout<<"no."<<i<<":\t";
//        cout<<"type:"<<(fac.isnumber? "number":"symbol")<<"\t";
//        cout<<"contain:"<<fac.num<<endl;
//    }
//    //����
//    int sum=0;
//    for(int i=0;i<line.size();++i)
//    {
//        Fac fac=line[i];
//        SymFunc func=calmap[fac.num];
//    }
//    goto start;
//    //������ʼ
//    //��һҪ�أ������˼ά���ڡ����̡�����״��ϣ��ṹ��Ϊ�ݹ�
//    //�ڶ�Ҫ�أ������˼ά���ڡ����ӡ�����ԭʼ����
//    //����Ҫ�أ������˼ά���ڡ�����ء������������в���ʧԭʼ��Ϣ
//    //����Ҫ�أ�����������ʽʱ���С������͡�������������������ֻ�С�ȡ��һ������
//    //����Ҫ�أ��������˼ά���С�Ԥ�����̡�����ʱ���̼�¼һ����ʼ�㣬����Ԥ�����̲�Ӱ��������
//    //          Ԥ�����̽���ʱ���õ�һ����Ԥ�Ƚ��ۡ���˼ά���»ص���ʼ�㣬��ʹ�����Ԥ�Ƚ���
//    //����Ҫ�أ��������˼ά�д��ڡ��������������̣���������ȷ��һ����Χ��������Ϊһ�����壨���㷺��˵��һ����������������
//                //�κη����������Ķ��������ض��򵽴�������
//    //����Ҫ�أ�����˼ά���ڡ�״̬�����͡�״̬ջ����״̬��ΪԤ��ȷ����״̬ջΪ����ʱʹ��
//    //�ڰ�Ҫ�أ�����˼ά���ڿ������������޹صġ���ʱ���̡�����ʱ���̵Ĳ����������� ��require����ʼ��
//    //          ���������ʱ�����������̹����������̵��������ݱ����ڡ���Ծ�������������Ա���ʱ����ʹ�õ������޸�
//    //          ��ʱ�����޸������̵������롰дʱ���ơ��������ƣ�����ʱ���̳ɹ�ʱ���޸ĺ�������滻�������̵Ķ�Ӧ���ݣ�����
//    //            pull request����Ҳ�Ǹ�����
//    //�ھ�Ҫ�أ�����˼ά���κΡ����̡�����ƽ�ȵ�,����κι��̶�������Ϊ������
//    //��ʮҪ�أ�����˼ά���κι��̶��ǡ��м��ӡ��ģ�Ҳ���ǹ��̱������һϵ������������̵����ݣ�
//    //          ��Щ������Ϊ���������ӡ���Ͷ�ݵ�����������
//    //��ʮһҪ�أ� ����˼ά������Ϊ������������ġ���������������ܼ��ӵõ������ݲ�����һ������
//    //��ʮ��Ҫ�أ�����˼ά���ڡ�����⡱���κμ��ӵõ���������ʱ��Ϊ�����ŵ��˼�����У��κι��̶��ɷ��ʣ�������Ƿֲ��
//                   //���Խ�͵ļ���� ������Ƶ�ʡ�Խ��
//    //��ʮ��Ҫ�أ� ���ݼ��ӵĽ���������ݱ���
//    //��ʮ��Ҫ�أ�һ���������ĳЩ���ݱ���ע�⵽������������ݶ��ᱻ����Ϊ��Ծ̬��������ټ������
//    //��ʮ��Ҫ�أ���������Ϊ��ʱ���򽵼����ƣ����ݻᱻѸ�ٲ���½���ֻ�в��ϱ���ע�⡱�Żᱻ
//    //              ��������

//    //����Ϊ��������

//}


//�������³��� ���ڲ����ַ���ѹ��
//����˵Ҫsum>3��Ϊ����Ҫ��һ������������ ����˵�����������塭��������ֱ������λ�ķ���
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <string.h>
//#define MAXZBUF  4096    //����ѹ����������С
//#define MAXUBUF  32768    //���ǽ�ѹ��������С
//int satoi(const char *str,int *nextptr,int start=0)
//{
//    //���κη�����Ϊ����
//    //nextptrΪ�����λ��
//    //�����Ǹ���
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
//    char *buf=(char *)malloc(sizeof(char)*4096);//ͨ�û�����
//    char *ret=(char *)calloc(MAXZBUF,sizeof(char));//�ø�calloc���Ӷ����ԡ���
//    char *retptr=ret;
//    int sum=0;//ͬ�ַ�������
//    char c=str[0];//��ǰ�ַ� ��ʼ��Ϊ��һ���ַ�
//    retptr+=sprintf(retptr,"%c",c);//�������һ���ַ� �����ʼ������
//    for(int j=0;;++j)
//    {
//        if(str[j]==c) sum++;
//        else
//        {
//            //������ͬ�ַ�
//            if(sum>3)
//            {
//                retptr+=sprintf(retptr,":%s'",itoa(sum,buf,10));
//            }
//            else
//            {
//                if(sum>1) for(int k=0;k<sum-1;++k) retptr+=sprintf(retptr,"%c",c);//���sum-1�� ��������һ������sum��
//            }
//            //��׼��ʼ�����̣���¼���ַ� ���Ҫ�������ַ� Ȼ���ʼ��������Ϊ1
//            c=str[j];
//            retptr+=sprintf(retptr,"%c",c);
//            sum=1;
//            if(str[j]==0) break;//������������ ����˼Ϊ ��������ͬ�ַ�(\0���ǲ�ͬ�ַ�)ʱ���� �������˷����ǽ�����������
//        }
//    }
//    free(buf);
//    return ret;
//}
//char *unzip(const char *zstr)
//{
//    //��ѹ����
//    char *ret=(char *)calloc(MAXUBUF,sizeof(char));
//    int rtop=0;//ret�ĵ�ǰ��λָ��
//    for(int i=0;zstr[i]!=0;)
//    {
////        if(zstr[i]=='\'') {i++;continue;} //����
//        char c=zstr[i];
//        ret[rtop++]=c;
//        i++;//���������������ȥ
////        if(c<='9'&&c>='0')
////        {
//            if(zstr[i]==':') i++;//�������ķ�����ð�ž�����������
//            else continue;//�������
////        }
////        if(zstr[i]=='\'') {i++;continue;}//���Ϊ���Ļ��ͼ�����һ��
//        if(!(zstr[i]<='9'&&zstr[i]>='0'))
//        {
//            //����������ַ�Χ�� ˵��Ҫ������һ��
//            continue;
//        }
//        //���������ȡ����
//        int sum=satoi(zstr,&i,i);//��ȡ������satoi��ֱ�Ӱ�i����Ϊ����
//        i++;//�������ֺ�ĵ�����
//        for(int j=1;j<sum;++j)
//        {
//            ret[rtop++]=c;
//        }
//        ret[rtop]=0;//��ʱ�Ѷ�����Ϊ����
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
//// primes[i]�ǵ�������������: 2, 3, 5, 7, ...
//// ��׼ȷ��˵primes[i]���а���1->sqrt(n)��Χ�ڵ���������
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
//    //4�߳�����������
//    int *nums1=new int[4*1024*1024]{0};//�Ͳ��Ų���
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
//    //д���ļ�
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

    //���̰߳汾 �ƺ���Щ����
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
    //������������ͷ��ڴ�
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
//}//�������ĳ���
//int CompositeNumFilterV3(int n)
//{
// int i, j;
// //��������ͳ��
// int count = 0;
// // ����������ǿռ䣬����+1ԭ���˰ɣ���Ϊ�˷���һ��flag[0]
// char* flag = (char*)malloc( n+1 );
// // �����õģ�����ϸ�о�����
// int mpLen = 2*3*5*7*11*13;
// char magicPattern[2*3*5*7*11*13]; // ��ֵĴ��룬why��˼���޷����ͣ��룡
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
//  magicPattern[i] = 0;  // �µĳ�ʼ������,��2,3,5,7,11,13�ı���ȫ�ɵ�
//  // ���Ҳ���memcpy��mpLen����magicPattern����������
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
//  flag[13] = 1;    // ��17��ʼfilter����Ϊ2,3,5,7,11,13�ı����类kill��
//  // ��n/13ֹ�ģ����������˺ö��
//  int stop = n/13;
//  for (i=17; i <= stop; i++)
//  {
//   // i�Ǻ�������Ъ�Űɣ���Ϊ���Ĺ����������������Ӵ�����
//  if (0 == flag[i]) continue;
//  // ��i��17����ʼ����
//  int step = i*2;
//  for (j=i*17; j <= n; j+=step)
//  {
//  flag[j] = 0;
//  }
//  }

//  // ͳ����������
//  for (i=2; i<=n; i++)
//  {
//   if (flag[i]) count++;
//  }

//  // �������ʱ���Һ��㷨������ز��󣬹���
//  // �ͷ��ڴ棬�����˴�˵�е��ڴ�й©
//  free(flag);

//  return count;
//}

//C���Զ�ȡ
//#include <stdio.h>
//#include <stdbool.h>
//int read(FILE *f)
//{
//    //����f���ļ�ָ��Ӧ��ָ������
//    bool isf=false;//������־
//    char c=0;
//    if((c=fgetc(f))=='-') {isf=true;c=fgetc(f);}//�Զ�seek
//    int sum=0;
//    for(;c>='0'&&c<='9';c=fgetc(f))
//    {
//        sum=sum*10+(c-'0');
//    }
//    //�ļ�ָ��ָ�� ��һ���ǿո�ĺ��� ���ݴ˺������߼�����
//    //Ӧ�������ֺ��������˼�һ ���ֱ����main��д����
//    //�Ͳ�����ô�鷳
//    fseek(f,-1,SEEK_CUR);
//    if(isf) sum=-sum;
//    return sum;
//}

//int main()
//{
//    char buf[4096];
//    FILE *write=fopen("test.txt","wt");
//    int raw[]={1,2,3,4,5,6,1111,2222,123,124};
//    int len=sizeof(raw)/sizeof(int);
//    for(int i=0;i<len;++i) fprintf(write,"%d ",raw[i]);
//    fclose(write);

//    FILE *rfile=fopen("test.txt","rt");
//    int nums[4096]={0};
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
//        fseek(rfile,-1,SEEK_CUR);//�ļ�ָ�븴λ
//        int num=read(rfile);//������ָ���������һ���ַ�����
//        nums[sum++]=num;
//    }
//    int sum=nptr;

    //����ע�Ͳ���Ϊ���ָ�ṹ�İ汾
//    for(int i=0;i<sum;++i)
//    {
//        printf("%d\n",nums[i]);
//    }
//    fclose(rfile);
//    getchar();
//}

    //�����Ǵʵ������� ��C

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <time.h>
#include "tree.h"
char buf[8192]={0};//ͨ���ַ���������
struct Word
{
    char *english;
    char *chinese;
};
//��ȡ����ѭ����ԭ�� ��Ҫ�ļ�ָ�븴λ
inline Word GetWordFromFile(FILE *file)
{
    //�ļ���ȡ
    //key��ȡ
    //=Ϊ�Ǻ�
    int ptr=0;
    for(char c=fgetc(file);c!='=';c=fgetc(file))
    {
        buf[ptr++]=c;
    }
    char *english=(char *)malloc(ptr+1);
    memcpy(english,buf,ptr);
    english[ptr]=0;
    //�ļ�ָ��ָ��=����һλ
    ptr=0;
    for(char c=fgetc(file);c!='\n';c=fgetc(file))
    {
        //��Ҫ����\r
        if(c=='\r') continue;
        buf[ptr++]=c;
    }
    //��ʱ�ļ�ָ������ָ����һ�е�һ���ַ�
    char *chinese=(char *)malloc(ptr+1);
    memcpy(chinese,buf,ptr);
    chinese[ptr]=0;
    Word ret;
    ret.chinese=chinese;
    ret.english=english;
    return ret;
}
inline Word GetWord(const char *str,int *sptr)
{
    //�ַ�����ȡ
    int bptr=0;
    for(char c=str[*(sptr++)];c!='=';c=str[*(sptr++)])
    {
        buf[bptr++]=c;
    }
    char *english=(char *)malloc(bptr+1);
    memcpy(english,buf,bptr);
    english[bptr]=0;
    //�ļ�ָ��ָ��=����һλ
    bptr=0;
    for(char c=str[*(sptr++)];c!='\n';c=str[*(sptr++)])
    {
        //��Ҫ����\r
        if(c=='\r') continue;
        buf[bptr++]=c;
    }
    //��ʱ�ļ�ָ������ָ����һ�е�һ���ַ�
    char *chinese=(char *)malloc(bptr+1);
    memcpy(chinese,buf,bptr);
    chinese[bptr]=0;
    Word ret;
    ret.chinese=chinese;
    ret.english=english;
    return ret;
}
Node *head=NULL;
///
/// \brief loadfile
/// \param path �ļ�·��
/// \param isfromfile �Ƿ�ʹ��fromfile����������ļ����ȡ
///
void loadfile(FILE *file,bool isfromfile)
{
    if(head!=NULL) Node_Free(head);
    head=NewNode();
    //��ȡ����
    if(isfromfile)
    {
        for(;;)
        {
            char c=fgetc(file);
            if(c==EOF) break;
            if(c==' '||c=='\t'||c=='\r'||c=='\n') continue;//������Զ���հ�
            fseek(file,-1,SEEK_CUR);
            Word w=GetWordFromFile(file);
            Node_Insert(head,w.english,w.chinese,false);//�������滻
        }
    }
    else
    {
        //��δʵ��
    }
}
const char *search(const char *str)
{
    //��������
    const char *val=Node_Search(head,str);
    return val;
}


int main()
{
    printf("������Ҫ������ļ���");
    scanf("%s",buf);
    getchar();
    FILE *file=fopen(buf,"r");
    printf("�����Ƿ�����ļ�����ȡģʽ(Y,N):");
    char t;
    scanf("%c",&t);
    bool isfromfile=t=='Y';
    printf("lodong....\n");
    clock_t start=clock();
    loadfile(file,isfromfile);
    //����
    clock_t end=clock();
    printf("��ʱ%ld\n",end-start);
    fclose(file);
    //����
    //
    printf("100000000�β�ѯ���� ��������Եĵ��ʣ�\n");
    scanf("%s",buf);
    int len=strlen(buf);
    char *test=(char *)malloc(len+1);
    strcpy(test,buf);
    clock_t tests=clock();
    for(int i=0;i<100000000;++i)
    {
        search(test);
    }
    clock_t teste=clock();
    printf("��ʱ��%ld\n",teste-tests);
    for(;;)
    {
        //��ѯѭ��
        printf("�������ѯ�����ݣ�");
        scanf("%s",buf);
        const char *str=search(buf);
        if(str!=NULL)
        {
            //���
            printf("%s\n",str);
        }
        else
        {
            printf("û���ҵ�ָ�����ݣ�\n");

        }
    }
}

