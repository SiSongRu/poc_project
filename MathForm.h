#ifndef MATHFORM_H_INCLUDED
#define MATHFORM_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <stack>
#include <queue>
#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;
/* 词性定义 */
#define ERROR				-1		// 错误
// 终结符(顺序不能乱)
#define TERMINATOR_START	 0		// 终结符起始编号
#define ID					 0		// 标识符id
#define DIGIT				 1		// 数字
#define BLANK				 2		// 空格符号\blank，' '不合法
#define LEFT_BRACKET		 3		// 左括号'('
#define RIGHT_BRACKET		 4		// 右括号')'
#define INT_OPRATOR			 5		// 积分运算符\int
#define SUM_OPRATOR			 6		// 累加运算符\sum
#define SUBSCRIPT			 7		// 下标符号，即下划线'_'
#define SUPERSCRIPT			 8		// 上标符号，即乘方号'^'
#define LEFT_BIG_BRACKET	 9		// 左大括号'{'
#define RIGHT_BIG_BRACKET	 10		// 右大括号'}'
#define START_END			 11		// 开始或结束符号，即'$'
#define NULL_STR			 12		// 空串'#'
// 其它
#define SLASH				 13		// 斜杠'\'符号
#define LINE_BREAKS			 14		// 换行符'\n'

// 非终结符(顺序不能乱)
#define NONTERMINATOR_START	 20		// 非终结符起始编号
#define S					 20		// S -> $ B $
#define B					 21		// B -> T B1
#define B1					 22		// B1 -> T B1 | #	#表示空串
#define T					 23		// T -> (id | num | \blank | (B) | \int{B}{B}{B} | \sum{B}{B}{B}) T1
#define T1					 24		// T1 -> _T2 | ^{B} | #
#define T2					 25		// T2 -> {B} | ^{B}{B}

#define IsLetter(c)		(((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))					// 是字母
#define IsDigit(c)			((c) >= '0' && (c) <= '9')
#define IS_TERMINATOR(x)	(((x) >= TERMINATOR_START) && ((x) < NONTERMINATOR_START))					// 是终结符
#define IS_PROPERTY_NODE(x)	((ID == (x)) || (DIGIT == (x)) || (LEFT_BRACKET == (x)) || (RIGHT_BRACKET == (x))\
							 || (INT_OPRATOR == (x)) || (SUM_OPRATOR == (x)) || (NULL_STR == (x)))		// 是属性计算的终结符结点
												// 是数字
#define BASE_TOP			 300	// 基准top值
#define BASE_LEFT			 200	// 基准left值
#define BASE_RATIO			 1		// 基准比例大小
#define BASE_FONT_SIZE		 100	// 基准字体大小
#define RATIO_SHRINK		 0.5	// 每次比例的缩小
#define LEFT_UP_DOWN_OFFSET	 0.75	// 上下标的left值偏移
#define ID_DIGIT_RATIO_IN	 0.6
#define ID_DIGIT_RATIO_OUT	 0.9

typedef struct LexicalNode
{
	bool isTerminator;	// 是否是终结符，是则为true
	unsigned int type;	// 类型
	string val;			// 值

	double ratio;		// 比例大小(继承)
	int top;			// 距离顶端大小(继承)
	int left;			// 距离左边大小(继承)
	int width;			// 宽度(综合)

	LexicalNode(){ isTerminator = false; type = -2; ratio = 0; top = 0; left = 0; width = 0; };
	~LexicalNode(){};
	LexicalNode &operator=(const LexicalNode &l)
	{
		this->isTerminator = l.isTerminator;
		this->type = l.type;
		this->val = l.val;
		this->ratio = l.ratio;
		this->top = l.top;
		this->left = l.left;
		this->width = l.width;

		return *this;
	};

//	LexicalNode *next;
}LexicalNode;		// 词法结点

typedef struct PropertyNode
{
	int productionState;		// 产生式编号
	int productionPos;			// 位于上一个产生式右部位置，如B->T B1 ，则T为0
	LexicalNode node;

	PropertyNode *parent;
	PropertyNode *child;
	PropertyNode *preBrother;
	PropertyNode *brother;

	PropertyNode(){ productionState = -1; productionPos = 0; parent = NULL; child = NULL; brother = NULL; };
	~PropertyNode(){};
}PropertyNode;		// 属性结点



/*void Error(char errorInfo)
{
	cout << "输入表达式错误,在字符\'" << errorInfo << "\'之后出错." << endl << endl;
	exit(0);

	return;
}*/
/*LexicalNode m_head;
exicalNode *m_tail;*/
#endif // MATHFORM_H_INCLUDED
