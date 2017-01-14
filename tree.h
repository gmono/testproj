#ifndef TREE_HH
#define TREE_HH
//����ʵ��
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
struct Node
{
    char c;//�˽ڵ������ַ�
    char *content;//�˽ڵ��븸�ڵ���ɵ�
    Node *nexts[30];//Сд��ĸ�Ĳ��ұ� . �ո� - ' ���⴦�� �ֱ��Ӧ 26 27 28 29λ
};
//������ʵ��Ӣ���� ͨ�ð� ��Ҫʹ�ö����б�
Node *NewNode()
{
    //Node�Ĺ��캯����������
    Node *ret=(Node *)malloc(sizeof(Node));
    ret->c=0; //0����head�ڵ�
    ret->content=NULL;//NULL����û��������� Ҳ����valueΪ��
    memset(ret->nexts,0,sizeof(Node *)*30);
    return ret;
}
///
/// \brief Node_Insert
/// \param head ����ͷ�ڵ�
/// \param key ��
/// \param value ֵ
/// \param isreset �Ƿ������滻
///
void Node_Insert(Node *head,const char *key,char *value,bool isreset)
{
    //Լ������ָ�������������Ȩ
    //Ϊ�˿��� value��ָ��ᱻֱ�ӱ���
    if(head->c!=0) return;//����head�ܾ�����
    Node *now=head;//��ǰ�ڵ�
    int ptr=0;//��ǰ�ַ�ָ��
    for(char c=key[ptr++];c!=0;c=key[ptr++])
    {
        //����������
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
            cptr=tc-'a';//ת��ΪСд�ٵõ���
            break;
        }


        if(now->nexts[cptr]==NULL) now->nexts[cptr]=NewNode();
        now=now->nexts[cptr];
        now->c=tc;
    }
    //now��ʱΪ���һ���ַ���Ӧ�Ľڵ�
    if(now->content==NULL||isreset) now->content=value;
}
const char * Node_Search(Node *head,const char *key)
{
    //����value �����޸�
    if(head->c!=0) return NULL;
    Node *now=head;
    int ptr=0;
    for(char c=key[ptr++];c!=0;c=key[ptr++])
    {
        //����
        //����������
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
        if(nptr==NULL) return NULL;//����ϼ�ֱ��û�� ��û�ҵ�
        now=nptr;//ָ����һ��
    }
    return now->content;//���contentû�� �Ǿͷ��ص���NULL Ҳ����û�ҵ�
}

void Node_Save(Node *head)
{
    //����һ����
    if(head->c==0) return;//������ͷ ��Ϊ����û���ṩ���������ķ���
    //��δʵ�� �����ڴ�����
}
void Node_Free(Node *head)
{

    //��δʵ�� �������ڲ����ͷ���
}

#endif // TREE_HH
