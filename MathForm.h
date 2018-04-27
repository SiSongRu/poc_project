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
/* ���Զ��� */
#define ERROR				-1		// ����
// �ս��(˳������)
#define TERMINATOR_START	 0		// �ս����ʼ���
#define ID					 0		// ��ʶ��id
#define DIGIT				 1		// ����
#define BLANK				 2		// �ո����\blank��' '���Ϸ�
#define LEFT_BRACKET		 3		// ������'('
#define RIGHT_BRACKET		 4		// ������')'
#define INT_OPRATOR			 5		// ���������\int
#define SUM_OPRATOR			 6		// �ۼ������\sum
#define SUBSCRIPT			 7		// �±���ţ����»���'_'
#define SUPERSCRIPT			 8		// �ϱ���ţ����˷���'^'
#define LEFT_BIG_BRACKET	 9		// �������'{'
#define RIGHT_BIG_BRACKET	 10		// �Ҵ�����'}'
#define START_END			 11		// ��ʼ��������ţ���'$'
#define NULL_STR			 12		// �մ�'#'
// ����
#define SLASH				 13		// б��'\'����
#define LINE_BREAKS			 14		// ���з�'\n'

// ���ս��(˳������)
#define NONTERMINATOR_START	 20		// ���ս����ʼ���
#define S					 20		// S -> $ B $
#define B					 21		// B -> T B1
#define B1					 22		// B1 -> T B1 | #	#��ʾ�մ�
#define T					 23		// T -> (id | num | \blank | (B) | \int{B}{B}{B} | \sum{B}{B}{B}) T1
#define T1					 24		// T1 -> _T2 | ^{B} | #
#define T2					 25		// T2 -> {B} | ^{B}{B}

#define IsLetter(c)		(((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))					// ����ĸ
#define IsDigit(c)			((c) >= '0' && (c) <= '9')
#define IS_TERMINATOR(x)	(((x) >= TERMINATOR_START) && ((x) < NONTERMINATOR_START))					// ���ս��
#define IS_PROPERTY_NODE(x)	((ID == (x)) || (DIGIT == (x)) || (LEFT_BRACKET == (x)) || (RIGHT_BRACKET == (x))\
							 || (INT_OPRATOR == (x)) || (SUM_OPRATOR == (x)) || (NULL_STR == (x)))		// �����Լ�����ս�����
												// ������
#define BASE_TOP			 300	// ��׼topֵ
#define BASE_LEFT			 200	// ��׼leftֵ
#define BASE_RATIO			 1		// ��׼������С
#define BASE_FONT_SIZE		 100	// ��׼�����С
#define RATIO_SHRINK		 0.5	// ÿ�α�������С
#define LEFT_UP_DOWN_OFFSET	 0.75	// ���±��leftֵƫ��
#define ID_DIGIT_RATIO_IN	 0.6
#define ID_DIGIT_RATIO_OUT	 0.9

typedef struct LexicalNode
{
	bool isTerminator;	// �Ƿ����ս��������Ϊtrue
	unsigned int type;	// ����
	string val;			// ֵ

	double ratio;		// ������С(�̳�)
	int top;			// ���붥�˴�С(�̳�)
	int left;			// ������ߴ�С(�̳�)
	int width;			// ����(�ۺ�)

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
}LexicalNode;		// �ʷ����

typedef struct PropertyNode
{
	int productionState;		// ����ʽ���
	int productionPos;			// λ����һ������ʽ�Ҳ�λ�ã���B->T B1 ����TΪ0
	LexicalNode node;

	PropertyNode *parent;
	PropertyNode *child;
	PropertyNode *preBrother;
	PropertyNode *brother;

	PropertyNode(){ productionState = -1; productionPos = 0; parent = NULL; child = NULL; brother = NULL; };
	~PropertyNode(){};
}PropertyNode;		// ���Խ��


/*LexicalNode m_head;
exicalNode *m_tail;*/
#endif // MATHFORM_H_INCLUDED