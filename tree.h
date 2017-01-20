#ifndef TREE_HH
#define TREE_HH
//����ʵ��
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
typedef unsigned char byte;
struct Node
{
    char c;//�˽ڵ������ַ� ���� �ֽڱ���
    char *content;//�˽ڵ��븸�ڵ���ɵ�
    //ѹ�����鷨
    byte *nexts;//����ΪNULL

};
//����ѹ������setter getter ����ȫ
//ѹ�����ݸ�ʽ  [startof 1][null length 1][data length 1][...]
//���ڿհ׺��������Ǽ���ֲ� ��������м�¼λ
Node *zip_get(byte *data,int index)
{
    int ptr=1;
    byte startof=*data;
    bool isnull=startof==0;//startof��ʾ��ʼ�Ŀ��Ƿ�Ϊ�տ�
    for(;;)
    {
        byte size=data[ptr++];//�õ���ǰ���С
        if(size==0) break;//�����ǰ���СΪ0��Ϊ����
        if(size>index)
        {
            //��Χ�� ����
            if(isnull) return NULL;
            else return (Node *)(data+index);
        }
        else
        {
            //��Χ�� ������Χ
            index-=size;
            if(!isnull)
            {
                //ʵ����Ҫ����������
                ptr+=size;
                //�������������ٴε����¼����
            }
        }
        isnull=!isnull;//�հ׿��ʵ������ֲ�
    }
    return NULL;//���� ����NULL
}
void zip_set(byte *data,int index,Node *val)
{

}
void zip_zip(byte **dptr)
{
    //ѹ������ �Զ�����������ָ�� ��ѹ����������zip_set ����
    //��������ǰ���ͨ������ѹ��Ϊѹ���������ĺ���
    int lsum=0;//���������¼
    bool isnull=true;//������������
    byte *data=*dptr;//��ȡ����ָ��
    byte *temp=malloc(sizeof(Node *)*512);//ѹ�����ݻ�����
    int nowp=0;//ѹ�����ݳ��ȼ�¼ ͬʱҲ�ǵ�ǰд��ָ��
    //����ʼ��
    temp[nowp++]=data[0]==NULL? 0:1;
    for(int i=0;i<256;++i)
    {
        Node *now=data[i];//�õ���ǰ����
        if(now)
        {
            if(lsum==0) isnull=false;
            else if(isnull)
            {
                //ִ�дӼ�¼�յ���¼ʵ���ת��
                temp[nowp++]=lsum;//��¼��һ����ĳ���
                lsum=1;
                (temp+nowp)[lsum]=now;
                isnull=false;//ת��Ϊ��¼ʵ��
            }
            else
            {
                //���ڼ�¼ʵ��
                (temp+nowp)[++lsum]=now;//�Ӽ�¼�鿪ʼ����lsum��λ�ü�¼��������
            }
        }
        else
        {
            //�����տ�
            if(lsum==0) isnull=true;
            else if(!isnull)
            {
                //���ڼ�¼ʵ�� ת��Ϊ��¼�տ�

                temp[nowp]=lsum;
                nowp+=lsum+1;
                lsum=1;
                isnull=true;
            }
            else
            {
                //���ڼ�¼�տ�
                lsum++;
            }
        }
    }
    temp[nowp++]=0;//��¼�������
    byte *ndata=malloc(sizeof(Node *)*nowp);
    free(*dptr);
    *dptr=ndata;
    free(temp);
}
void zip_foreach(byte *data,void (*func)(Node *))
{
    //ѹ���������� ����������Ч�ڵ㣨�ǿշ�NULL��
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

//������ʵ��Ӣ���� ͨ�ð� ��Ҫʹ�ö����б�
Node *NewNode()
{
    //Node�Ĺ��캯����������
    Node *ret=(Node *)malloc(sizeof(Node));
    ret->c=0; //0����head�ڵ�
    ret->content=NULL;//NULL����û��������� Ҳ����valueΪ��
    ret->nexts=NULL;  //��Ԥ����ģʽ
//    ret->nexts=(Node *)malloc(sizeof(Node *)*256);//Ԥ����ģʽ
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

        tc=c;
        cptr=c;

        //����NULL����� ����ռ�
        if(now->nexts==NULL)
        {
            //���÷�ѹ��ģʽ����ռ�
            now->nexts=(byte *)malloc(sizeof(Node *)*256);
            memset(now->nexts,NULL,sizeof(Node *)*256);
        }
        Node **nextptr=(Node **)now->nexts;
        if(nextptr[cptr]==NULL) nextptr[cptr]=NewNode();
        now=nextptr[cptr];
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
        //
        cptr=c;


        //��ʱnowָ����һ���ַ��ڵ�
        if(now->nexts==NULL) return NULL;//û�ҵ�

        Node **nexptr=(Node **)now->nexts;
        Node *nptr=nextptr[cptr];
        if(nptr==NULL) return NULL;//����ϼ�ֱ��û�� ��û�ҵ�
        now=nptr;//ָ����һ��
    }
    return now->content;//���contentû�� �Ǿͷ��ص���NULL Ҳ����û�ҵ�
}

void Node_Zip(Node *head)
{
    //��ѹ������ ʹ��zip_zipѹ��
    //ע�� ִ�д˺����� ����ֻ����Node_ZSearch ��Node_ZInsert ִ�в���Ͳ�ѯ
    //��������������Խ���
    //�����������
    //�ǵݹ鷽ʽ
    typedef struct Item
    {
        Node *ptr;
        int cptr;//��ǰ�ڵ���ӽڵ�ĵ�ǰ��ȡλ��
    }Item;
    Item *items=malloc(sizeof(Item)*8192);//֧��8192����
    int now=0;//��ǰջָ��
    Item ti={head,0};//ѹ��ͷ
    for(;;)
    {
        Item nowitem=items[now];//
        if(nowitem.ptr->nexts==NULL)
        {
            //���ȡ��һ��Ҷ�ӽڵ����һ���Ѿ��ݹ�ɨ����ɵĽڵ�ͼ���ѭ��
            //Ҷ�ӽڵ�����ѹ��
            now--;//��ջ
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
                child=nowitem.ptr->nexts[nowitem.cptr++];//�õ���ǰ�ӽڵ�
                if(child)
                {
                    //ȡ��һ�����õ��ӽڵ�
                    //�Ͱ��ӽڵ����ջ
                    Item titem={child,0};
                    items[now++]=titem;//��ջ
                    break;
                }
            }
        }
    }
}
const char * Node_ZSearch(Node *head,const char key)
{

    //������search����һ��
    //����value �����޸�
    if(head->c!=0) return NULL;
    Node *now=head;
    int ptr=0;
    for(char c=key[ptr++];c!=0;c=key[ptr++])
    {
        //����
        //����������
        int cptr;
        //
        cptr=c;


        //��ʱnowָ����һ���ַ��ڵ�
        if(now->nexts==NULL) return NULL;//û�ҵ�

        Node *nptr=zip_get(now->nexts,cptr);//ͨ��ѹ����ȡ������ȡ
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
