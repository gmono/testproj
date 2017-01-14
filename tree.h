#ifndef TREE_HH
#define TREE_HH
//容器实现
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
struct Node
{
    char c;//此节点代表的字符
    char *content;//此节点与父节点组成的
    Node *nexts[30];//小写字母的查找表 . 空格 - ' 特殊处理 分别对应 26 27 28 29位
};
//这里先实现英到中 通用版 需要使用二重列表
Node *NewNode()
{
    //Node的构造函数…………
    Node *ret=(Node *)malloc(sizeof(Node));
    ret->c=0; //0代表head节点
    ret->content=NULL;//NULL代表没有这个单词 也就是value为空
    memset(ret->nexts,0,sizeof(Node *)*30);
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
        switch(c)
        {
        case '.':
            tc='.';
            cptr=26;
            break;
        case ' ':
            tc=' ';
            cptr=27;
            break;
        case '-':
            tc='-';
            cptr=28;
            break;
        case '\'':
            tc='\'';
            cptr=29;
            break;
        default:
            tc=(c|(1<<5));
            cptr=tc-'a';//转换为小写再得到序
            break;
        }


        if(now->nexts[cptr]==NULL) now->nexts[cptr]=NewNode();
        now=now->nexts[cptr];
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
        switch(c)
        {
        case '.':
            cptr=26;
            break;
        case ' ':
            cptr=27;
            break;
        case '-':
            cptr=28;
            break;
        case '\'':
            cptr=29;
            break;
        default:
            cptr=(c|(1<<5))-'a';
            break;
        }


        Node *nptr=now->nexts[cptr];
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
