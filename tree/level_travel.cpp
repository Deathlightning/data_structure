/*********************************
层序递归遍历树节点
含树操作、队操作
code by kingsword
date 2020-10-08
*********************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Tree
{
    char data;
    struct Tree *l_child, *r_child;
} Tree;

typedef struct Queue_node
{
    Tree *data;
    struct Queue_node *next;
} Queue;

//创建树节点，递归实现
Tree *insert_tree_node();
//中序遍历，栈实现
void in_order_travel(Tree *root);
//先序遍历，由递归实现，用于检验其他函数的正确性
void pre_order_travel(Tree *root);

void push(Queue *s, Tree *data);
Tree *pop(Queue *s);
Tree *top(Queue *s);
int queue_is_empty(Queue *s);

int main()
{
    freopen("in.txt", "r", stdin);
    //初始化树和栈
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->next = NULL;
    Tree *root = insert_tree_node();
    //临时节点
    Tree *p;
    //根节点进队
    push(queue, root);
    while (!queue_is_empty(queue))
    {
        p = pop(queue);
        printf("%c ", p->data);
        if (p->l_child != NULL)
        {
            push(queue, p->l_child);
        }
        if (p->r_child != NULL)
        {
            push(queue, p->r_child);
        }
    }
}
//以下是树操作
Tree *insert_tree_node()
{

    char val;
    Tree *root = NULL;
    scanf("%c", &val);
    if (val == '#')
    {
        return NULL;
    }
    root = (Tree *)malloc(sizeof(Tree));
    root->data = val;
    root->l_child = insert_tree_node();
    root->r_child = insert_tree_node();
    return root;
}

void pre_order_travel(Tree *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%c ", root->data);
    pre_order_travel(root->l_child);
    pre_order_travel(root->r_child);
}

//*******************************************************
//以下是栈操作
/* PUSH 操作 */
void push(Queue *s, Tree *data)
{
    while (s->next != NULL)
    {
        s = s->next;
    }
    // 新建一个结点，用于存放压入栈内的元素，即新的栈顶
    Queue *node = (Queue *)malloc(sizeof(Queue));

    node->data = data; // 添加数据
    node->next = NULL;
    s->next = node;
}

/* POP 操作 */
Tree *pop(Queue *s)
{
    // 先判断栈是否为空，若栈为空，则不能再进行出栈操作，报错
    if (queue_is_empty(s))
    {
        printf("Error! Queue is empty!\n");
        return NULL;
    }
    else
    {
        //取队首元素
        Queue *queue_node = s->next;
        //取栈顶中存的树节点地址
        Tree *tree_node = s->next->data;
        //将头节点与第二个节点相连
        s->next = queue_node->next;
        // 释放原来栈顶元素所占的内存
        free(queue_node);
        return tree_node;
    }
}

/* 查看栈顶元素 */
Tree *top_Queue(Queue *s)
{
    if (queue_is_empty(s))
    {
        printf("Error! Queue is empty!\n");
        return 0;
    }
    else
    {
        return s->next->data;
    }
}

/* 判断栈是否为空 */
int queue_is_empty(Queue *s)
{
    return s->next == NULL;
}
