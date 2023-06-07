#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define CAPACITY 1e6 // Max Capacity of the stack

/*
 * Structure     : Stack
 * -------------------------------
 *   Structure defining our stack
 *
 *   int capacity: Max capacity of stack
 *   int top     : Top of the stack
 *   int* st     : Array storing the actual stack
 */
typedef struct Stack
{
    int capacity;
    int top;
    int *st;
} Stack;

/*
 * Function      : isFull
 * ---------------------------------
 * Checks if the stack is full or not
 *
 *   Stack* stack: Stack to be checked
 *
 *   returns     : true if stack is full else false
 */
bool isFull(Stack *stack)
{
    if (stack->top == (CAPACITY - 1))
        return true;
    return false;
}

/*
 * Function      : isEmpty()
 * ---------------------------------
 * Checks if the stack is empty or not
 *
 *   Stack* stack: Stack to be checked
 *
 *   returns     : true if stack is empty else false
 */
bool isEmpty(Stack *stack)
{
    if (stack->top == -1)
        return true;
    return false;
}

/*
 * Function      : push()
 * ---------------------------------
 * Pushes an item into the stack if it is not full
 *
 *   Stack* stack: Stack into which item is to be added
 *   int val     : Item to be added
 */
void push(Stack *stack, int val)
{
    if (isFull(stack))
        return;

    stack->st[++(stack->top)] = val;
}

/*
 * Function      : pop()
 * ---------------------------------
 * Pops an item into top of the stack and returns it if it is not empty else returns INT_MIN
 *
 *   Stack* stack: Stack which is to be popped
 *
 *   returns     : Popped item if non-empty stack else INT_MIN
 */
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("!\n");
        return INT_MIN;
    }
    return stack->st[(stack->top)--];
}

/*
 * Function      : top()
 * ---------------------------------
 * Gives top of the stack without popping if it is not empty else returns INT_MIN
 *
 *   Stack* stack: Stack whose top is to be returned
 *
 *   returns     : Top item if non-empty stack else INT_MIN
 */
int top(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("!\n");
        return INT_MIN;
    }
    return stack->st[stack->top];
}

/*
 * Function      : size()
 * ---------------------------------
 * Gives size of the stack
 *
 *   Stack* stack: Stack whose size is required
 *
 *   returns     : Size of the stack
 */
int size(Stack *stack)
{
    return (stack->top) + 1;
}

int evaluate(int expression[], int n)
{
    Stack *nStack = (Stack *)malloc(sizeof(Stack));                       // Create N-Stack
    int *st1 = (int *)malloc(sizeof(int) * (CAPACITY));
    *nStack = (Stack){.capacity = CAPACITY, .top = -1, .st = st1};

    Stack *oStack = (Stack *)malloc(sizeof(Stack));                       // Create O-Stack
    int *st2 = (int *)malloc(sizeof(int) * (CAPACITY));
    *oStack = (Stack){.capacity = CAPACITY, .top = -1, .st = st2};

    int ele1, ele2;          // These variables store the two popped items from N-Stack
    char op;                 // This variable stores the popped item from O-Stack
    
    for (int i = 0; i < n; i++)
    {
        if (expression[i] == '(')           // In case of left parenthesis, it will always enter the O-Stack
        {
            push(oStack, expression[i]);
        }
        else if (expression[i] == ')')      // If we encounter right parenthesis, this means that the expression so     
        {                                   // far can be evaluated
            while (!isEmpty(oStack) && top(oStack) != '(')
            {
                ele1 = pop(nStack);
                ele2 = pop(nStack);
                op = pop(oStack);

                switch (op)
                {
                case '+':
                {
                    push(nStack, ele1 + ele2);
                    break;
                }
                case '-':
                {
                    push(nStack, ele2 - ele1);
                    break;
                }
                case '*':
                {
                    push(nStack, ele1 * ele2);
                    break;
                }
                case '/':
                {
                    push(nStack, ele2 / ele1);
                    break;
                }
                case '^':
                {
                    push(nStack, (int)pow(ele2, ele1));
                    break;
                }
                default:
                    break;
                }
            }
            pop(oStack);         // After evaluating the expression so far, this step removes the stale left paranthesis
        }
        else if (expression[i] == '^')    // '^' operator will also always enter O-Stack
        {
            push(oStack, expression[i]);
        }
        else if (expression[i] == '/')    // For '/', evaluate the expression unless we encounter '/','*','+','-' on top of O-Stack
        {
            while (!isEmpty(oStack) && top(oStack) != '(' && top(oStack) == '^')
            {
                ele1 = pop(nStack);
                ele2 = pop(nStack);
                push(nStack, (int)pow(ele2, ele1));
            }
            push(oStack, expression[i]);
        }
        else if (expression[i] == '*')    // For '*', evaluate the expression unless we encounter '+','-' on top  of O-Stack
        {
            while (!isEmpty(oStack) && top(oStack) != '(' && top(oStack) != '+' && top(oStack) != '-')
            {
                ele1 = pop(nStack);
                ele2 = pop(nStack);
                op = pop(oStack);
                switch (op)
                {
                case '*':
                {
                    push(nStack, ele1 * ele2);
                    break;
                }
                case '/':
                {
                    push(nStack, ele2 / ele1);
                    break;
                }
                case '^':
                {
                    push(nStack, (int)pow(ele2, ele1));
                    break;
                }
                default:
                    break;
                }
            }
            push(oStack, expression[i]);
        }
        else if (expression[i] == '+')   //For '+', evaluate whole of the expression so far or till the left paranthesis
        {
            while (!isEmpty(oStack) && top(oStack) != '(')
            {
                ele1 = pop(nStack);
                ele2 = pop(nStack);
                op = pop(oStack);
                switch (op)
                {
                case '+':
                {
                    push(nStack, ele1 + ele2);
                    break;
                }
                case '-':
                {
                    push(nStack, ele2 - ele1);
                    break;
                }
                case '*':
                {
                    push(nStack, ele1 * ele2);
                    break;
                }
                case '/':
                {
                    push(nStack, ele2 / ele1);
                    break;
                }
                case '^':
                {
                    push(nStack, (int)pow(ele2, ele1));
                    break;
                }
                default:
                    break;
                }
            }
            push(oStack, expression[i]);
        }
        else if (expression[i] == '-')   //For '-', evaluate the expression unless we encounter '+','-' on top  of O-Stack
        {
            while (!isEmpty(oStack) && top(oStack) != '(' && top(oStack) != '+' && top(oStack) != '-')
            {
                ele1 = pop(nStack);
                ele2 = pop(nStack);
                op = pop(oStack);
                switch (op)
                {
                case '*':
                {
                    push(nStack, ele1 * ele2);
                    break;
                }
                case '/':
                {
                    push(nStack, ele2 / ele1);
                    break;
                }
                case '^':
                {
                    push(nStack, (int)pow(ele2, ele1));
                    break;
                }
                default:
                    break;
                }
            }
            push(oStack, expression[i]);
        }
        else
        {                     // If expression[i] is a numeric character, read the whole number(can be of multiple digits) and push to N-Stack
            char num[11];
            int k = 0;
            while(i < n && expression[i] >= 48 && expression[i] <= 57) {  // 48 & 57 are ASCII values of '0' and '9'
                num[k++] = expression[i++];
            }
            i--;
            num[k] = '\0';
            int val = atoi(num);    // Parse the numeric characters as an Intger
            push(nStack, val);
        }
    }

    while (!isEmpty(oStack))    // Evaluate rest of tbe operators in N-Stack
    {
        ele1 = pop(nStack);
        ele2 = pop(nStack);
        op = pop(oStack);
        switch (op)
        {
        case '+':
        {
            push(nStack, ele1 + ele2);
            break;
        }
        case '-':
        {
            push(nStack, ele2 - ele1);
            break;
        }
        case '*':
        {
            push(nStack, ele1 * ele2);
            break;
        }
        case '/':
        {
            push(nStack, ele2 / ele1);
            break;
        }
        case '^':
        {
            push(nStack, (int)pow(ele2, ele1));
            break;
        }
        default:
            break;
        }
    }

    return pop(nStack);
}

int main()
{
    int n;
    scanf("%d\n", &n);
    int expression[n];

    for (int i = 0; i < n; i++)
    {
        expression[i] = getchar();
    }

    printf("%d\n", evaluate(expression, n));
    return 0;
}