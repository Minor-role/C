/*
	2017年6月24日17:58:50
	顺序表实现哈夫曼编码树
	根据哈夫曼(Huffman)编码的原理，编写一个程序，在用户输入节点权重的基础 上建立它的哈夫曼编码
	知识相关：
		哈夫曼树：给定一组具有 确定权值的叶子结点，可以构造出不同的二叉树，将其中带权路径长度最小的二叉树 称为哈夫曼树。
	算法：
	1. 构建哈夫曼树
		1. 初始化数组，所有双亲结点、孩子结点置为-1，hCode置为空
		2. 数组 huffTree 的前 n 个元素的字符和权值置给定值； 
		3．进行 n-1 次合并 
			3.1 在二叉树集合中选取两个权值最小的根结点，其下标分别为 i1，i2； 
			3.2 将二叉树 i1，i2 合并为一棵新的二叉树 k
	2. 对哈夫曼树进行编码
		1. 针对每一个叶子节点，遍历其父结点，父父结点，一直到根节点
		2. 识别左孩子、右孩子，使用hc[hclen]存储遍历过程的编码
		3. 把hc[hclen]放到当前叶子节点的hCode上

*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define Max 10

typedef struct huffNode
{
	char ch; //结点字符A-Z
	int weight; //结点权值域 
	int lChild; //该结点左孩子结点在数组中的下标 
	int rChild; //该结点右孩子结点在数组中的下标 
	int parent; //该结点双亲结点在数组中的下标 
	char hCode[Max]; //该结点字符的哈夫曼编码
	int flag;
}huffNode;

// 找最小权重和次小权重，设置数组下标i就是为了避免错过权重值相等且最小的结点
typedef struct mini
{
	int data; // 保存权重
	int i; // 保存数组下标
}mini;

huffNode huffmanTree[2 * Max - 1]; // 申请所有可能用到的结点空间

// 构建哈夫曼树
int BuildhuffmanTree(int n)
{
	mini min1, min2;
	int i;
	int temp = 0;
	int count; // 控制循环次数，循环次数等于结点数-1
	for (count = 0; count<n - 1; count++)
	{
		/*
		选出最小和次小的结点，一定要把最小值先判断出，再判断次小值，因为次小值一定比最小值大
		这种方法是能想到的时间复杂度最低的方法
		*/
		min1.data = 10000;
		min2.data = 10000;
		for (i = 0; i<n+temp; i++)
			if (huffmanTree[i].weight < min1.data && huffmanTree[i].flag == 0) // 选出没有被标记过的最小值
			{
				min1.data = huffmanTree[i].weight;
				min1.i = i;
			}
		huffmanTree[min1.i].flag = 1; // 这一步至关重要，它标志着这个值已经被访问过且确定过，不能再被访问
		for (i = 0; i<n+temp; i++)
			if (huffmanTree[i].weight < min2.data && i != min1.i && huffmanTree[i].flag == 0)// 选出没有被标记过的次小值
			{
				min2.data = huffmanTree[i].weight;
				min2.i = i;
			}
		huffmanTree[min2.i].flag = 1;

		// 给父结点和子结点填充相应的信息
		for (i = 0; huffmanTree[i].weight != 0; i++); // 查找没有使用的哈夫曼结点
		huffmanTree[i].weight = huffmanTree[min1.i].weight + huffmanTree[min2.i].weight; // 子结点权值相加给父结点
		huffmanTree[i].lChild = min1.i; // 子结点的下标给父结点
		huffmanTree[i].rChild = min2.i;
		huffmanTree[min1.i].parent = i; // 父结点的下标给子结点
		huffmanTree[min2.i].parent = i;
		temp += 1; // 每增加一个结点，需要遍历的结点就要多一个
	}
	return 0;
}

// 哈夫曼树编码
void huffmanTreeCode(int n)
{
	char hc[Max];
	int hcLen;
	int i, j, k, parent, p;
	for (i = 0; i<n; i++)
	{
		hcLen = 0;
		parent = huffmanTree[i].parent;//待编码字符的双亲结点下标 
		p = i;
		while (parent != -1)//未到达根结点(只有根节点的parent是-1)
		{
			if (huffmanTree[parent].lChild == p)//是左孩子 
			{
				hc[hcLen] = '0';
				hcLen++;
			}
			else if (huffmanTree[parent].rChild == p)//是右孩子 
			{
				hc[hcLen] = '1';
				hcLen++;
			}
			p = parent;
			parent = huffmanTree[parent].parent;//继续向根结点查找
		}
		for (j = 0, k = hcLen - 1; j<hcLen; j++, k--)//将编码写入相应字符数组 
			huffmanTree[i].hCode[j] = hc[k];
		huffmanTree[i].hCode[j] = '\0';//加上字符串结束符 
	}
}

int main()
{
	int n, i;
	char letter; // 临时保存字母
	int weight; // 临时保存权重
	printf("请输入元素个数：");
	scanf("%d", &n);
	fflush(stdin); // 清除前面scanf语句的缓冲区内容
				   // 初始化数组
	for (i = 0; i<Max; i++)
	{
		huffmanTree[i].ch = '0';
		huffmanTree[i].weight = 0;
		huffmanTree[i].parent = -1;
		huffmanTree[i].lChild = -1;
		huffmanTree[i].rChild = -1;
		huffmanTree[i].hCode[i] = '\0';
		huffmanTree[i].flag = 0;
	}
	for (i = 0; i<n; i++)
	{
		printf("请输入第%d个结点的字符：", i + 1);
		scanf("%c", &letter);
		huffmanTree[i].ch = letter;
		printf("请输入第%d个结点的权重：", i + 1);
		scanf("%d", &weight);
		huffmanTree[i].weight = weight;
		fflush(stdin);// 清除前面scanf语句的缓冲区内容
	}
	BuildhuffmanTree(n);
	huffmanTreeCode(n);
	printf("结点6的weigit：%d,lChild:%d,rChild:%d\n", huffmanTree[6].weight, huffmanTree[6].lChild, huffmanTree[6].rChild);
	for (i = 0; i<n; i++)
		printf("结点%d的编码为：%s\n", i + 1, huffmanTree[i].hCode);
	system("pause");
	return 0;
}
