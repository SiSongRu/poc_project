#include "MathForm.h"

static  char IDentifierTbl[1000][50] = { "" };//标识符表

void AddLexicalNode(int node_type, string value);

vector<LexicalNode> m_lexicalNodes;			// 词法节点
vector<vector<LexicalNode>> m_productions;	// 产生式
vector<vector<LexicalNode>> m_showProductions;
string m_idDigitVal;			// 语法分析遇到id或者数字时记录下其值
int m_nonterminator[6];			// 非终结符
int m_terminator[13];			// 终结符
int m_analysisTable[6][13];
PropertyNode *m_grammerTree;				// 语法树
stack<PropertyNode *> m_propertyNodeStack;	// 只放非终结符的栈

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
    //首位是字母
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
    //fp 为文件指针，指向测试文件
    char resourceProject[1000];//存放所需要分析的句子
    char token[20]={0}; //存放单词
    int syn =-1,i;  //syn标志单词种类识别码
    int pProject=0; //作为文件指针

    /*while(fgetc(fp)!='$')//去除文件开头的'$'，这样再次读到的'$'符号即为结束符
    {
        //do nothing
    }
    AddLexicalNode(START_END, "$");
    printf("(--,static  char IDentifierTbl[1000][50] = { "" };//标识符表

    void AddLexicalNode(int node_type, string value);
    int Lexical_Analysis(FILE *fp, FILE *fp_output); '$')\n");
    fprintf(fp_output,"(--, '$')\n");*/

    resourceProject[pProject]=fgetc(fp);
    pProject++;
    while((resourceProject[pProject]=fgetc(fp))!='$')//把文件的内容读到字符数组resourceProject中
    {
        pProject++;
    }
    resourceProject[++pProject]='\0';//数组结束符为'\0'
    fclose(fp);

    pProject=0; //重定位指针
    cout<<resourceProject<<endl;
    while(resourceProject[pProject]!='\0')//当最后一个字符不为'\0'，继续进入循环
    {
        scanner(syn,resourceProject,token,pProject);
        //启动扫描器，执行完毕后syn中存储着该单词所对应的识别码

        if(syn==ID)//单词为标识符
        {
            for(i=0;i<1000;i++)
            {
                //标识符表中已经存储了该标识符
                if(strcmp(IDentifierTbl[i],token)==0)
                {
                    break;
                }
                //标识符表还有空间
                if(strcmp(IDentifierTbl[i],"")==0)
                {
                    strcpy(IDentifierTbl[i],token);
                    break;
                }
            }
            AddLexicalNode(ID,token);
            printf("(标识符, %s)\n",token);
            fprintf(fp_output,"(标识符, %s)\n",token);
        }
        else if(syn==DIGIT) //当前单词为数字
        {
            AddLexicalNode(DIGIT,token);
            printf("(常数, %s)\n",token);
            fprintf(fp_output,"(常数, %s)\n",token);
        }
        else if(2<=syn<=10)//当前单词为对应特殊符号
        {
            /*switch(syn):
            {
            case 2:

            }*/
            printf("(--,%s)\n",token);
            fprintf(fp_output,"(--, %s)\n",token);
        }
        else if(syn==-1)//无法分析，错误
        {
            break;
        }
    }
    for(i=0;i<100;i++)
    {
        if(strcmp(IDentifierTbl[i],"")!=0)
        {
            printf("第%d个标识符,%s\n",i+1,IDentifierTbl[i]);
            fprintf(fp_output,"第%d个标识符,%s\n",i+1,IDentifierTbl[i]);
        }
    }
    return 0;
}

void AddLexicalNode(int node_type, string value)
{
    LexicalNode tmp;
    tmp.type = node_type;
    tmp.val = value;
    // 终结符
	if (IS_TERMINATOR(node_type))
	{
		tmp.isTerminator = true;
	}
	else tmp.isTerminator = false;
	m_lexicalNodes.push_back(tmp);
	//m_pos += _val.size();

	return;

}
