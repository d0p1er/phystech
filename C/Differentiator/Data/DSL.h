#define DATA node->data
#define L node->left
#define R node->right
#define dL Differentation(L, tree, file)
#define dR Differentation(R, tree, file)
#define cL CopyNode(L)
#define cR CopyNode(R)

#define DO_OPER(oper) Eval(L) oper Eval(R)
#define CREATE_NUM_NODE(val)	CreateNode(NUMBER, val, NULL, NULL)
#define ADDITION(l, r)			CreateNode(OPERATION, ADD, l, r)
#define SUBTRACT(l, r)			CreateNode(OPERATION, SUB, l, r)
#define MULTIPLY(l, r)			CreateNode(OPERATION, MUL, l, r)
#define DIVISION(l, r)			CreateNode(OPERATION, DIV, l, r)
#define POWER(l, r)				CreateNode(OPERATION, POW, l, r)
#define COSINUS(r)				CreateNode(FUNCTION, 1000, NULL, r)
#define SINUS(r)				CreateNode(FUNCTION, 1001, NULL, r)
#define LOGN(r)					CreateNode(FUNCTION, 1010, NULL, r)


#define RETNODE(n) return PrintEqual(node, n, tree, file);