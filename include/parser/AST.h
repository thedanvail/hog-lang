enum class NodeType
{
    EXPR,
    STATEMENT,
    LITERAL,
};

struct Node
{
    NodeType type;
    Node* lhs;
    Node* rhs;
};

// FIXME: How do I do a heterogenous AST?
// TODO: Arithmetic operator precedence
class AST
{
public:
    AST() = default;
    AST(Node aNode);
    ~AST();
};
