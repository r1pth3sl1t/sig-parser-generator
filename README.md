# SPG
Signal Parser Generator - simple parser generator for bnf-like grammar notation
## Usage
To avoid writing adapters for node and token objects, define them and their fields as it is shown in the example below. It is not neccesary to redefine them all as they have default value that is the same as their name
```
token_body=content;
node_name=rule_name;
node_children=children;
node_tokens=tokens;
token=token;
node=Node;
parser=parser;
parse=parse;
decl_header = struct_mapping;
root_rule = signal_program;
```

Define set of grammar rules for your language in following format:
```
<rule_name> --> <rule_definition>;
```

Specify your definition with the next components:

```
<rule_name> - recursive call to specific rule handler
<rule1> | <rule2> | ... - try to handle rule1, if current token doesn't fit to it, move to rule2 etc
'token' - check if the next token is equal to token1, if it doesn't - call the error() function
{ code } - run your custom rule handler
```

### Important

Your node and token structs MUST contain at least these fields and they MUST be public:

- Token: `std::string token_body`
- Node: `std::vector<std::shared_ptr<Node>> node_children, std::vector<std::shared_ptr<Token>> node_tokensб std::string node_name`

Note, that it is not neccesary for them to have these specific names as you can redefine them.  
Also you MUST declare and implement the function:  
  `void error(std::string expected, const std::shared_ptr<Token>& actual , std::string rule)`, 
which will be called every time the parser finds an error.

Your BNF grammar must follow these rules:
- It has to be LL(1)
- Any specific tokens **MUST** be wrapped with single quotes(`'`)
- **AVOID** leftside recursion
- if your rule has multiple definitions to parse, the first option in every definition **MUST** be a recursive call, for example the next rule is invalid for this generator:
```
<rule> --> 'token1' <rule1> | 'token2' <rule2> ;
```
But you can redefine this rule as this example:
```
<rule> --> <rule11> | <rule22> ;
<rule11> --> 'token' <rule1> ;
<rule22> --> 'token2' <rule2> ;
```
- Refedinition or override of any rules is denied. If you want to make multiple definitions to one rule, use pipe (|) construction:
```
Invalid:
<a> --> <b>;
<a> --> <c>;
```
```
Valid:
<a> --> <b> | <c>;
```

### Naming conventions

The parser generates code using your rules names, but some of combinations are not allowed:
- `tk`
- `node`
- `<empty>` rule

The rule name can contain letters, digits, `$`, `_`. The rule names are case-sensitive.

### Custom handlers

If you want to run your C++ code to handle the rule, you can specify it with:
```
<rule> --> {your code}
```
After generating your code gets injected in the if() statement, and if it is true, it returns a node of specified rule, and if it is not, it calls error() function.

To get access to current token use a `(*tk)` construction and access it's fields with `->`:
```
(*tk)->name
```

For example, if your tokens are being coded with specific values, you can create your custom handler to determine which group of tokens this one belongs to.
In this example the Token struct has extra `code` field that is assigned to tokens with the next rules:
- if token represents the identifier, it's base is 1000
- if token is a constant, it's base is 500
- if token is a keyword, it's base is 400
```
<identifier> --> { (*tk)->code > 1000 } // error when tk is a keyword or constant
<constant> --> { (*tk)->code > 500 && (*tk)->code < 1000 } // error when tk is a keyword or identifier
<specific_keyword> --> { (*tk)->code == 403 } // error when tk is not a specific keyword
```


