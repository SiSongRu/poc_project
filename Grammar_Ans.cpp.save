#include "MathForm.h"

extern vector<LexicalNode> m_lexicalNodes;
vector<vector<LexicalNode>> m_productions;	// 产生式
vector<vector<LexicalNode>> m_showProductions;
string m_idDigitVal;			// 语法分析遇到id或者数字时记录下其值
int m_nonterminator[6];			// 非终结符
int m_terminator[13];			// 终结符
int m_analysisTable[6][13];

PropertyNode *m_grammerTree;				// 语法树
stack<PropertyNode *> m_propertyNodeStack;	// 只放非终结符的栈

void ShowProduction();
void Production();
void ShowProduction();
void AnalysisTable();

void Error(string errorInfo)
{
	cout << "输入表达式错误,在字符串\"" << errorInfo << "\"之后出错." << endl << endl;
	exit(0);

	return;
}

void Grammar_Analysis()
{
    Production();
    AnalysisTable();
 	stack<LexicalNode> analysisStack;
	LexicalNode tmpNode;
	m_showProductions.clear();

	//#结束符结点，语法标志分析的结束
	//#S标志语法推导开始，然后将它们进栈，使用非递归的分析方法
    tmpNode.isTerminator = true;
	tmpNode.type = NULL_STR;
	tmpNode.val = "NULL";
	analysisStack.push(tmpNode);

	m_lexicalNodes.push_back(tmpNode);
	tmpNode.isTerminator = false;
	tmpNode.type = S;
	tmpNode.val = "S";
	analysisStack.push(tmpNode);

	int m_pos = 0;
	int size = m_lexicalNodes.size();
	if (size < 3)
	{
		cout << "输入表达词法分析结果少于3个." << endl;
		exit(0);
	}
    //cout<<size<<endl;
	int state;
	LexicalNode topStack;
	while (!analysisStack.empty())
	{
	    //cout<<m_pos<<endl;
		topStack = analysisStack.top();
		//cout<<topStack.val<<endl;
		if (m_pos >= size)
		{
			Error(m_lexicalNodes[size - 1].val);
		}
		if (ID == m_lexicalNodes[m_pos].type || DIGIT == m_lexicalNodes[m_pos].type)
		{
			m_idDigitVal = m_lexicalNodes[m_pos].val;
		}
		// 栈顶为终结符,匹配则出栈
		if (topStack.isTerminator)
		{
			if (topStack.type == m_lexicalNodes[m_pos].type)
			{
				analysisStack.pop();
				m_pos ++;
				continue;
			}
			else    //不匹配则回溯处理错误
			{
				int i = 0;
				for (i = m_pos - 1; i >= 0; i --)
				{
					if (NULL_STR != m_lexicalNodes[i].type)break;
				}
				Error(m_lexicalNodes[i].val);
			}
		}
		// 栈顶为非终结符

		state = m_analysisTable[topStack.type - NONTERMINATOR_START][m_lexicalNodes[m_pos].type - TERMINATOR_START];
		//cout<<state<<endl;
		if (ERROR == state)
		{
			int i = 0;
			for (i = m_pos - 1; i >= 0; i --)
			{
				if (NULL_STR != m_lexicalNodes[i].type)break;
			}
			Error(m_lexicalNodes[i].val);
		}
		// 栈顶非终结符出栈
		analysisStack.pop();
		// 逆序入栈
		for (int i = m_productions[state].size() - 1; i > 0; i --)	// 注意m_productions[state]中第0个节点为产生式左部，不入栈
		{
			if (NULL_STR == m_productions[state][i].type)
			{
				break;
			}
			//cout<<i<<endl;
			analysisStack.push(m_productions[state][i]);
		}
		// 产生式规约
		//TopRatioCacul(state);
		m_showProductions.push_back(m_productions[state]);
//		ShowProduction(m_productions[state]);
	}
	// 两边不一致
	if (m_pos != size)
	{
		Error(m_lexicalNodes[size - 1].val);
	}
	// 输入产生式
	cout << "--------------------------------------------------------------------------" << endl;
	ShowProduction();
	// width属性计算
	//WidthCacul();
	// left属性计算
	//LeftCacul();

	// 输出属性计算结果
	//cout << "--------------------------------------------------------------------------" << endl;
	//ShowProperty(m_grammerTree);
	cout << "--------------------------------------------------------------------------" << endl;

	//Output();

	return;
}

void Production()
{
	/*

	各产生式编号

	0 S -> $ B $
	1 B -> T B1
	2 B1 -> T B1
	3 B1 -> #	#表示空串
	4 T -> id T1
	5 T -> num T1
	6 T -> \blank T1
	7 T -> (B) T1
	8 T -> \int{B}{B}{B} T1
	9 T -> \sum{B}{B}{B} T1
	10 T1 -> _T2
	11 T1 -> ^{B}
	12 T1 -> #
	13 T2 -> {B}
	14 T2 -> ^{B}{B}

	 */
	LexicalNode s, b, b1, t, t1, t2;
	LexicalNode startEnd, _null, id, num, blank, _int, _sum,
		sub, sup, lbracket, rbracket, lbigbracket, rbigbracket;
	s.type = S;		s.val = "S";	s.isTerminator = false;
	b.type = B;		b.val = "B";	b.isTerminator = false;
	b1.type = B1;	b1.val = "B1";	b1.isTerminator = false;
	t.type = T;		t.val = "T";	t.isTerminator = false;
	t1.type = T1;	t1.val = "T1";	t1.isTerminator = false;
	t2.type = T2;	t2.val = "T2";	t2.isTerminator = false;

	startEnd.type = START_END;	startEnd.val = "$";		startEnd.isTerminator = true;
	_null.type = NULL_STR;		_null.val = "NULL";			_null.isTerminator = true;
	id.type = ID;				id.val = "id";			id.isTerminator = true;
	num.type = DIGIT;			num.val = "num";		num.isTerminator = true;
	blank.type = BLANK;			blank.val = "\\blank";	blank.isTerminator = true;
	_int.type = INT_OPRATOR;	_int.val = "∫";		_int.isTerminator = true;
	_sum.type = SUM_OPRATOR;	_sum.val = "∑";		_sum.isTerminator = true;
	sub.type = SUBSCRIPT;		sub.val = "_";			sub.isTerminator = true;
	sup.type = SUPERSCRIPT;		sup.val = "^";			sup.isTerminator = true;
	lbracket.type = LEFT_BRACKET;			lbracket.val = "(";		lbracket.isTerminator = true;
	rbracket.type = RIGHT_BRACKET;			rbracket.val = ")";		rbracket.isTerminator = true;
	lbigbracket.type = LEFT_BIG_BRACKET;	lbigbracket.val = "{";	lbigbracket.isTerminator = true;
	rbigbracket.type = RIGHT_BIG_BRACKET;	rbigbracket.val = "}";	rbigbracket.isTerminator = true;

	m_productions.resize(15);
	int i = 0;
	// 0
	m_productions[i].push_back(s);
	m_productions[i].push_back(startEnd);
	m_productions[i].push_back(b);
	m_productions[i].push_back(startEnd);
	i ++;
	// 1
	m_productions[i].push_back(b);
	m_productions[i].push_back(t);
	m_productions[i].push_back(b1);
	i ++;
	// 2
	m_productions[i].push_back(b1);
	m_productions[i].push_back(t);
	m_productions[i].push_back(b1);
	i ++;
	// 3
	m_productions[i].push_back(b1);
	m_productions[i].push_back(_null);
	i ++;
	// 4
	m_productions[i].push_back(t);
	m_productions[i].push_back(id);
	m_productions[i].push_back(t1);
	i ++;
	// 5
	m_productions[i].push_back(t);
	m_productions[i].push_back(num);
	m_productions[i].push_back(t1);
	i ++;
	// 6
	m_productions[i].push_back(t);
	m_productions[i].push_back(blank);
	m_productions[i].push_back(t1);
	i ++;
	// 7
	m_productions[i].push_back(t);
	m_productions[i].push_back(lbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbracket);
	m_productions[i].push_back(t1);
	i ++;
	// 8
	m_productions[i].push_back(t);
	m_productions[i].push_back(_int);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	m_productions[i].push_back(t1);
	i ++;
	// 9
	m_productions[i].push_back(t);
	m_productions[i].push_back(_sum);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	m_productions[i].push_back(t1);
	i ++;
	// 10
	m_productions[i].push_back(t1);
	m_productions[i].push_back(sub);
	m_productions[i].push_back(t2);
	i ++;
	// 11
	m_productions[i].push_back(t1);
	m_productions[i].push_back(sup);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	i ++;
	// 12
	m_productions[i].push_back(t1);
	m_productions[i].push_back(_null);
	i ++;
	// 13
	m_productions[i].push_back(t2);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	i ++;
	// 14
	m_productions[i].push_back(t2);
	m_productions[i].push_back(sup);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	m_productions[i].push_back(lbigbracket);
	m_productions[i].push_back(b);
	m_productions[i].push_back(rbigbracket);
	i ++;

	return;
}

void AnalysisTable()
{
	/*
	m_analysisTable[6][13]

			0		1		2		3		4		5		6		7		8		9		10		11		12
			id		num		\blank	(		)		\int	\sum	_		^		{		}		$		#

	0 S																								0
	1 B		1		1		1		1		1		1		1
	2 B1	2		2		2		2		3		2		2								3		3
	3 T		4		5		6		7				8		9
	4 T1	12		12		12		12		12		12		12		10		11				12		12
	5 T2																	14		13

	表中存放产生式编号，或者错误ERROR

	*/

	for (int i = 0; i < 6; i ++)
	{
		for (int j = 0; j < 13; j ++)
		{
			m_analysisTable[i][j] = ERROR;
		}
	}
	// 0
	m_analysisTable[0][11] = 0;
	// 1
	for (int i = 0; i <= 6; i ++)
		m_analysisTable[1][i] = 1;
	m_analysisTable[1][4] = ERROR;
	// 2
	for (int i = 0; i <= 6; i ++)
		m_analysisTable[2][i] = 2;
	m_analysisTable[2][4] = 3;
	m_analysisTable[2][10] = 3;
	m_analysisTable[2][11] = 3;
	// 3
	for (int i = 0; i <= 3; i ++)
		m_analysisTable[3][i] = i + 4;
	m_analysisTable[3][5] = 8;
	m_analysisTable[3][6] = 9;
	// 4
	for (int i = 0; i <= 11; i ++)
		m_analysisTable[4][i] = 12;
	m_analysisTable[4][9] = ERROR;
	m_analysisTable[4][7] = 10;
	m_analysisTable[4][8] = 11;
	// 5
	m_analysisTable[5][9] = 13;
	m_analysisTable[5][8] = 14;

	int k = 0;
	m_nonterminator[k ++] = S;
	m_nonterminator[k ++] = B;
	m_nonterminator[k ++] = B1;
	m_nonterminator[k ++] = T;
	m_nonterminator[k ++] = T1;
	m_nonterminator[k ++] = T2;

	k = 0;
	m_terminator[k ++] = ID;
	m_terminator[k ++] = DIGIT;
	m_terminator[k ++] = BLANK;
	m_terminator[k ++] = LEFT_BRACKET;
	m_terminator[k ++] = RIGHT_BRACKET;
	m_terminator[k ++] = INT_OPRATOR;
	m_terminator[k ++] = SUM_OPRATOR;
	m_terminator[k ++] = SUBSCRIPT;
	m_terminator[k ++] = SUPERSCRIPT;
	m_terminator[k ++] = LEFT_BIG_BRACKET;
	m_terminator[k ++] = RIGHT_BIG_BRACKET;
	m_terminator[k ++] = START_END;
	m_terminator[k ++] = NULL_STR;

	return;
}

void ShowProduction()
{
	int iSize = m_showProductions.size();
	int jSize = 0;

	for (int i = 0; i < iSize; i ++)
	{
		cout << m_showProductions[i][0].val << " -> ";
		jSize = m_showProductions[i].size();
		for (int j = 1; j < jSize; j ++)
		{
			if (SUM_OPRATOR == m_showProductions[i][j].type)
			{
				cout << "\\sum ";
			}
			else if (INT_OPRATOR == m_showProductions[i][j].type)
			{
				cout << "\\int ";
			}
			else cout << m_showProductions[i][j].val << " ";
		}
		cout << endl;
	}

	return;
}
