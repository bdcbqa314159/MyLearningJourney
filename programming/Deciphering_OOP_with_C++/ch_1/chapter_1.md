# nodiscard feature

The specifier [[nodiscard]] can optionally be added to precede the return type of a function. This specifier is used to indicate that the return value from a function must not be ignored – that is, it must be captured in a variable or utilized in an expression. Should the function’s return value consequently be ignored, a compiler warning will be issued. Note that the nodiscard qualifier can be added to the function prototype and optionally to the definition (or required in a definition if there is no prototype). Ideally, nodiscard should appear in both locations.

# creating aliases

Two single examples:
typedef float dollars;
using money = float;