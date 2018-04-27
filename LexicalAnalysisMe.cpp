#include "MathForm.h"

static  char IDentifierTbl[1000][50] = { "" };//��ʶ����

void AddLexicalNode(int node_type, string value);

vector<LexicalNode> m_lexicalNodes;			// �ʷ��ڵ�
vector<vector<LexicalNode>> m_productions;	// ����ʽ
vector<vector<LexicalNode>> m_showProductions;
string m_idDigitVal;			// �﷨��������id��������ʱ��¼����ֵ
int m_nonterminator[6];			// ���ս��
int m_terminator[13];			// �ս��
int m_analysisTable[6][13];
PropertyNode *m_grammerTree;				// �﷨��
stack<PropertyNode *> m_propertyNodeStack;	// ֻ�ŷ��ս����ջ

int Match_String(char s[])
{
    if(s=="\\blank") return BLANK;
    else if(s=="\\int") return INT_OPRATOR;
    else if(s=="\\sum") return SUM_OPRATOR;
    else return -1;
}
void scanner(int &syn,char resourceProject[],char token[],int &pProject)
{
    int i, count_token=0;
    char ch;
    ch = resourceProject[pProject];
 /*   while(ch ==' ')
    {
        pProject++;
        ch = resourceProject[pProject];
    }*/
    for(i = 0;i<20;i++)
    {
        token[i]='\0';
    }
    //��λ����ĸ
    if(IsLetter(resourceProject[pProject]))
    {
        token[count_token++]=resourceProject[pProject];
        pProject++;
        while(IsLetter(resourceProject[pProject])||IsDigit(resourceProject[pProject]))
        {
            token[count_token++]=resourceProject[pProject];
            pProject++;
        }
        token[count_token]='\0';
        syn = ID;
        return;
    }
    else if(IsDigit(resourceProject[pProject]))
    {
        while(IsDigit(resourceProject[pProject]))
        {
            token[count_token++]=resourceProject[pProject];
            pProject++;
        }
        token[count_token]='\0';
        syn = DIGIT;
        return;
    }
    else if(resourceProject[pProject] =='\\')
    {
        token[count_token++]=ch;
        pProject++;
        while(IsLetter(resourceProject[pProject]))
        {
            token[count_token++] = resourceProject[pProject];
            pProject++;
        }
        token[count_token]='\0';
        syn = Match_String(token);
        return;
    }
    else if(ch=='_')
    {
        token[0]=resourceProject[pProject];
        token[1]='\0';
        pProject++;
        syn =  SUBSCRIPT;
        return;
    }
    else if(ch=='^')
    {
        token[0]=resourceProject[pProject];
        token[1]='\0';
        pProject++;
        syn = SUPERSCRIPT;
        return;
    }
    else if(ch=='{')
    {
        token[0]=resourceProject[pProject];
        token[1]='\0';
        pProject++;
        syn =  LEFT_BIG_BRACKET;
        return;
    }
    else if(ch=='}')
    {
        token[0]=resourceProject[pProject];
        token[1]='\0';
        pProject++;
        syn = RIGHT_BIG_BRACKET;
        return;
    }
    else if(ch=='(')
    {
        token[0]=resourceProject[pProject];
        token[1]='\0';
        pProject++;
        syn = LEFT_BRACKET;
        return;
    }
    else if(ch==')')
    {
        token[0]=resourceProject[pProject];
        token[1]='\0';
        pProject++;
        syn =RIGHT_BRACKET ;
        return;
    }
    else if(ch=='$')
    {
        token[0]=resourceProject[pProject];
        token[1]='\0';
        pProject++;
        syn = START_END;
        return;
    }
    else{
        printf("error!");
    }
}

int Lexical_Analysis(FILE *fp, FILE *fp_output)
{
    //fp Ϊ�ļ�ָ�룬ָ������ļ�
    char resourceProject[1000];//�������Ҫ�����ľ���
    char token[20]={0}; //��ŵ���
    int syn =-1,i;  //syn��־��������ʶ����
    int pProject=0; //��Ϊ�ļ�ָ��

    /*while(fgetc(fp)!='$')//ȥ���ļ���ͷ��'$'�������ٴζ�����'$'���ż�Ϊ������
    {
        //do nothing
    }
    AddLexicalNode(START_END, "$");
    printf("(--,static  char IDentifierTbl[1000][50] = { "" };//��ʶ����

    void AddLexicalNode(int node_type, string value);
    int Lexical_Analysis(FILE *fp, FILE *fp_output); '$')\n");
    fprintf(fp_output,"(--, '$')\n");*/

    resourceProject[pProject]=fgetc(fp);
    pProject++;
    while((resourceProject[pProject]=fgetc(fp))!='$')//���ļ������ݶ����ַ�����resourceProject��
    {
        pProject++;
    }
    resourceProject[++pProject]='\0';//���������Ϊ'\0'
    fclose(fp);

    pProject=0; //�ض�λָ��
    cout<<resourceProject<<endl;
    while(resourceProject[pProject]!='\0')//�����һ���ַ���Ϊ'\0'����������ѭ��
    {
        scanner(syn,resourceProject,token,pProject);
        //����ɨ������ִ����Ϻ�syn�д洢�Ÿõ�������Ӧ��ʶ����

        if(syn==ID)//����Ϊ��ʶ��
        {
            for(i=0;i<1000;i++)
            {
                //��ʶ�������Ѿ��洢�˸ñ�ʶ��
                if(strcmp(IDentifierTbl[i],token)==0)
                {
                    break;
                }
                //��ʶ�����пռ�
                if(strcmp(IDentifierTbl[i],"")==0)
                {
                    strcpy(IDentifierTbl[i],token);
                    break;
                }
            }
            AddLexicalNode(ID,token);
            printf("(��ʶ��, %s)\n",token);
            fprintf(fp_output,"(��ʶ��, %s)\n",token);
        }
        else if(syn==DIGIT) //��ǰ����Ϊ����
        {
            AddLexicalNode(DIGIT,token);
            printf("(����, %s)\n",token);
            fprintf(fp_output,"(����, %s)\n",token);
        }
        else if(2<=syn<=10)//��ǰ����Ϊ��Ӧ�������
        {
            /*switch(syn):
            {
            case 2:

            }*/
            printf("(--,%s)\n",token);
            fprintf(fp_output,"(--, %s)\n",token);
        }
        else if(syn==-1)//�޷�����������
        {
            break;
        }
    }
    for(i=0;i<100;i++)
    {
        if(strcmp(IDentifierTbl[i],"")!=0)
        {
            printf("��%d����ʶ��,%s\n",i+1,IDentifierTbl[i]);
            fprintf(fp_output,"��%d����ʶ��,%s\n",i+1,IDentifierTbl[i]);
        }
    }
    return 0;
}

void AddLexicalNode(int node_type, string value)
{
    LexicalNode tmp;
    tmp.type = node_type;
    tmp.val = value;
    // �ս��
	if (IS_TERMINATOR(node_type))
	{
		tmp.isTerminator = true;
	}
	else tmp.isTerminator = false;
	m_lexicalNodes.push_back(tmp);
	//m_pos += _val.size();

	return;

}
