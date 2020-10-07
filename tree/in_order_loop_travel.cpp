/*********************************
中序非递归遍历树节点
含树操作、栈操作
code by kingsword
date 2020-10-07
*********************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Tree
{
    char data;
    struct Tree *l_child, *r_child;
} Tree;

typedef struct stack_node
{
    Tree *data;
    struct stack_node *next;
} Stack;

//创建树节点，递归实现
Tree *insert_tree_node();
//中序遍历，栈实现
void in_order_travel(Tree *root);
//先序遍历，由递归实现，用于检验其他函数的正确性
void pre_order_travel(Tree *root);

void push_stack(Stack *s, Tree *data);
Tree *pop_stack(Stack *s);
Tree *top_stack(Stack *s);
int stack_is_empty(Stack *s);

int main()
{
    freopen("in.txt", "r", stdin);
    //初始化树和栈
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->next=NULL;
    Tree *root = insert_tree_node();
    //临时节点
    Tree *p = root;
    //根节点进栈
    while (p!=NULL||!stack_is_empty(stack))
    {
        //左节点连续进栈，结束后p指向最左的叶子节点
        if (p!= NULL)
        {
            push_stack(stack, p);
            p = p->l_child;
        }
        //左节点访问完毕后，读取当前节点，弹出，将右节点进栈，程序继续
        else
        {
            p = pop_stack(stack);
            printf("%c ", p->data);
            p=p->r_child;
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
void push_stack(Stack *s, Tree *data)
{
    // 新建一个结点，用于存放压入栈内的元素，即新的栈顶
    Stack *head_node = (Stack *)malloc(sizeof(Stack));

    head_node->data = data;    // 添加数据
    head_node->next = s->next; // 新的栈顶 head_node 的 next 指针指向原来的栈顶 s->next
    s->next = head_node;       // s->next 现在指向新的栈顶
}

/* POP 操作 */
Tree *pop_stack(Stack *s)
{
    // 先判断栈是否为空，若栈为空，则不能再进行出栈操作，报错
    if (stack_is_empty(s))
    {
        printf("Error! Stack is empty!\n");
        return NULL;
    }
    else
    {
        //取栈顶元素
        Stack *stack_node = s->next;
        //取栈顶中存的树节点地址
        Tree *node = s->next->data;
        //将头节点与第二个节点相连
        s->next = stack_node->next;
        // 释放原来栈顶元素所占的内存
        free(stack_node);
        return node;
    }
}

/* 查看栈顶元素 */
Tree *top_stack(Stack *s)
{
    if (stack_is_empty(s))
    {
        printf("Error! Stack is empty!\n");
        return 0;
    }
    else
    {
        return s->next->data;
    }
}

/* 判断栈是否为空 */
int stack_is_empty(Stack *s)
{
    return s->next == NULL;
}
