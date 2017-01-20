#ifndef TREE_HH
#define TREE_HH
//容器实现
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
typedef unsigned char byte;
struct Node
{
    char c;//此节点代表的字符 或者 字节本身
    char *content;//此节点与父节点组成的
    //压缩数组法
    byte *nexts;//可以为NULL

};
//定义压缩数组setter getter 不安全
//压缩数据格式  [startof 1][null length 1][data length 1][...]
//由于空白和数据总是间隔分布 因此无需有记录位
Node *zip_get(byte *data,int index)
{
    int ptr=1;
    byte startof=*data;
    bool isnull=startof==0;//startof表示开始的块是否为空块
    for(;;)
    {
        byte size=data[ptr++];//得到当前块大小
        if(size==0) break;//如果当前块大小为0则为结束
        if(size>index)
        {
            //范围内 返回
            if(isnull) return NULL;
            else return (Node *)(data+index);
        }
        else
        {
            //范围外 跳过范围
            index-=size;
            if(!isnull)
            {
                //实体需要跳过数据区
                ptr+=size;
                //数据区跳过后再次到达记录块上
            }
        }
        isnull=!isnull;//空白块和实体块间隔分布
    }
    return NULL;//超界 返回NULL
}
void zip_set(byte *data,int index,Node *val)
{

}
void zip_zip(byte **dptr)
{
    //压缩函数 自动重设数据区指针 对压缩数据区有zip_set 即可
    //这个函数是把普通数据区压缩为压缩数据区的函数
    int lsum=0;//连续区间记录
    bool isnull=true;//连续区块类型
    byte *data=*dptr;//获取数据指针
    byte *temp=malloc(sizeof(Node *)*512);//压缩数据缓冲区
    int nowp=0;//压缩数据长度记录 同时也是当前写入指针
    //处理开始块
    temp[nowp++]=data[0]==NULL? 0:1;
    for(int i=0;i<256;++i)
    {
        Node *now=data[i];//得到当前数据
        if(now)
        {
            if(lsum==0) isnull=false;
            else if(isnull)
            {
                //执行从记录空到记录实体的转换
                temp[nowp++]=lsum;//记录上一个块的长度
                lsum=1;
                (temp+nowp)[lsum]=now;
                isnull=false;//转换为记录实体
            }
            else
            {
                //正在记录实体
                (temp+nowp)[++lsum]=now;//从记录块开始便宜lsum个位置记录具体数据
            }
        }
        else
        {
            //遇到空块
            if(lsum==0) isnull=true;
            else if(!isnull)
            {
                //正在记录实体 转换为记录空块

                temp[nowp]=lsum;
                nowp+=lsum+1;
                lsum=1;
                isnull=true;
            }
            else
            {
                //正在记录空块
                lsum++;
            }
        }
    }
    temp[nowp++]=0;//记录结束标记
    byte *ndata=malloc(sizeof(Node *)*nowp);
    free(*dptr);
    *dptr=ndata;
    free(temp);
}
void zip_foreach(byte *data,void (*func)(Node *))
{
    //压缩遍历函数 遍历所有有效节点（非空非NULL）
    bool isnull=*data==0;
    int now=1;
    for(;;)
    {
        byte size=data[now++];
        if(size==0) break;
        if(isnull)
        {
            now+=size;
            continue;
        }
        Node *ptr=((Node *)data)[now++];
        if(ptr) func(ptr);
    }
}

//这里先实现英到中 通用版 需要使用二重列表
Node *NewNode()
{
    //Node的构造函数…………
    Node *ret=(Node *)malloc(sizeof(Node));
    ret->c=0; //0代表head节点
    ret->content=NULL;//NULL代表没有这个单词 也就是value为空
    ret->nexts=NULL;  //非预分配模式
//    ret->nexts=(Node *)malloc(sizeof(Node *)*256);//预分配模式
    return ret;
}
///
/// \brief Node_Insert
/// \param head 树的头节点
/// \param key 键
/// \param value 值
/// \param isreset 是否允许替换
///
void Node_Insert(Node *head,const char *key,char *value,bool isreset)
{
    //约定传常指针代表不交付所有权
    //为了快速 value的指针会被直接保存
    if(head->c!=0) return;//不是head拒绝插入
    Node *now=head;//当前节点
    int ptr=0;//当前字符指针
    for(char c=key[ptr++];c!=0;c=key[ptr++])
    {
        //产生查找序
        int cptr;
        char tc;

        tc=c;
        cptr=c;

        //处理NULL的情况 分配空间
        if(now->nexts==NULL)
        {
            //采用非压缩模式分配空间
            now->nexts=(byte *)malloc(sizeof(Node *)*256);
            memset(now->nexts,NULL,sizeof(Node *)*256);
        }
        Node **nextptr=(Node **)now->nexts;
        if(nextptr[cptr]==NULL) nextptr[cptr]=NewNode();
        now=nextptr[cptr];
        now->c=tc;
    }
    //now此时为最后一个字符对应的节点
    if(now->content==NULL||isreset) now->content=value;
}
const char * Node_Search(Node *head,const char *key)
{
    //返回value 不可修改
    if(head->c!=0) return NULL;
    Node *now=head;
    int ptr=0;
    for(char c=key[ptr++];c!=0;c=key[ptr++])
    {
        //搜索
        //产生查找序
        int cptr;
        //
        cptr=c;


        //此时now指向上一个字符节点
        if(now->nexts==NULL) return NULL;//没找到

        Node **nexptr=(Node **)now->nexts;
        Node *nptr=nextptr[cptr];
        if(nptr==NULL) return NULL;//如果上级直接没有 就没找到
        now=nptr;//指向下一级
    }
    return now->content;//如果content没有 那就返回的是NULL 也就是没找到
}

void Node_Zip(Node *head)
{
    //树压缩函数 使用zip_zip压缩
    //注意 执行此函数后 树将只能用Node_ZSearch 和Node_ZInsert 执行插入和查询
    //而这两个函数相对较慢
    //深度优先搜索
    //非递归方式
    typedef struct Item
    {
        Node *ptr;
        int cptr;//当前节点的子节点的当前读取位置
    }Item;
    Item *items=malloc(sizeof(Item)*8192);//支持8192级树
    int now=0;//当前栈指针
    Item ti={head,0};//压入头
    for(;;)
    {
        Item nowitem=items[now];//
        if(nowitem.ptr->nexts==NULL)
        {
            //如果取到一个叶子节点或者一个已经递归扫描完成的节点就继续循环
            //叶子节点无需压缩
            now--;//出栈
        }
        else if(nowitem.cptr==256)
        {
            zip_zip(&nowitem.ptr->nexts);
            now--;
        }
        else
        {
            Node *child=NULL;
            for(;;)
            {
                child=nowitem.ptr->nexts[nowitem.cptr++];//得到当前子节点
                if(child)
                {
                    //取到一个可用的子节点
                    //就把子节点加入栈
                    Item titem={child,0};
                    items[now++]=titem;//入栈
                    break;
                }
            }
        }
    }
}
const char * Node_ZSearch(Node *head,const char key)
{

    //基本与search代码一样
    //返回value 不可修改
    if(head->c!=0) return NULL;
    Node *now=head;
    int ptr=0;
    for(char c=key[ptr++];c!=0;c=key[ptr++])
    {
        //搜索
        //产生查找序
        int cptr;
        //
        cptr=c;


        //此时now指向上一个字符节点
        if(now->nexts==NULL) return NULL;//没找到

        Node *nptr=zip_get(now->nexts,cptr);//通过压缩读取函数读取
        if(nptr==NULL) return NULL;//如果上级直接没有 就没找到
        now=nptr;//指向下一级
    }
    return now->content;//如果content没有 那就返回的是NULL 也就是没找到
}

void Node_Save(Node *head)
{
    //保存一个树
    if(head->c==0) return;//必须是头 因为这里没有提供插入子树的方法
    //尚未实现 敬请期待……
}
void Node_Free(Node *head)
{

    //尚未实现 所以现在不能释放树
}

#endif // TREE_HH
