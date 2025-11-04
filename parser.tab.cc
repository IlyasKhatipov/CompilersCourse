// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 7 "parser.y"

/* C++ includes and AST definitions */
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <cstring> /* strdup, free */
using namespace std;

/* --- AST classes (C++ style) --- */
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void print(int indent=0) const = 0;
};

using ASTNodePtr = unique_ptr<ASTNode>;

static string indentStr(int n) { return string(n, ' '); }

struct ProgramNode : ASTNode {
    vector<ASTNodePtr> decls;
    void print(int indent=0) const override {
        cout << indentStr(indent) << "Program\n";
        for (auto &d : decls) d->print(indent+2);
    }
};

struct ClassNode : ASTNode {
    string name;
    string extendsName;
    vector<ASTNodePtr> members;
    ClassNode(const string &n="") : name(n) {}
    void print(int indent=0) const override {
        cout << indentStr(indent) << "Class: " << name;
        if (!extendsName.empty()) cout << " extends " << extendsName;
        cout << "\n";
        for (auto &m : members) m->print(indent+2);
    }
};

struct VarNode : ASTNode {
    string name;
    string type;
    VarNode(const string &n="", const string &t="") : name(n), type(t) {}
    void print(int indent=0) const override {
        cout << indentStr(indent) << "Var: " << name;
        if (!type.empty()) cout << " : " << type;
        cout << "\n";
    }
};

struct MethodNode : ASTNode {
    string name;
    vector<string> params;
    vector<ASTNodePtr> body;
    MethodNode(const string &n="") : name(n) {}
    void print(int indent=0) const override {
        cout << indentStr(indent) << "Method: " << name << "\n";
        for (auto &b : body) b->print(indent+2);
    }
};

/* глобальный root AST (используется в main.cpp) */
std::unique_ptr<ProgramNode> g_program = nullptr;

/* Forward: лексер предоставляет этот тип и вектор simpleTokens */
struct SimpleToken { std::string kind; std::string text; int line; int startCol; int endCol; };
extern std::vector<SimpleToken> simpleTokens; /* defined in lexer.l */

/* индекс для доступа к simpleTokens из yylex() */
static size_t parserTokIndex = 0;


#line 115 "parser.tab.cc"


#include "parser.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 193 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: top_list
#line 106 "parser.y"
    {
        /* $1 = std::vector<ASTNode*>* */
        g_program.reset(new ProgramNode());
        if ((yystack_[0].value.vec)) {
            for (ASTNode* p : *(yystack_[0].value.vec)) {
                g_program->decls.emplace_back( std::unique_ptr<ASTNode>(p) );
            }
            delete (yystack_[0].value.vec);
        }
    }
#line 658 "parser.tab.cc"
    break;

  case 3: // top_list: %empty
#line 120 "parser.y"
    { (yylhs.value.vec) = new std::vector<ASTNode*>(); }
#line 664 "parser.tab.cc"
    break;

  case 4: // top_list: top_list top_item
#line 122 "parser.y"
    {
        /* $1 = vector*, $2 = ASTNode* */
        (yylhs.value.vec) = (yystack_[1].value.vec);
        if ((yystack_[0].value.node)) (yylhs.value.vec)->push_back((yystack_[0].value.node));
    }
#line 674 "parser.tab.cc"
    break;

  case 5: // top_item: class_decl
#line 130 "parser.y"
                  { (yylhs.value.node) = (yystack_[0].value.node); }
#line 680 "parser.tab.cc"
    break;

  case 6: // top_item: var_decl
#line 131 "parser.y"
                  { (yylhs.value.node) = (yystack_[0].value.node); }
#line 686 "parser.tab.cc"
    break;

  case 7: // top_item: method_decl
#line 132 "parser.y"
                  { (yylhs.value.node) = (yystack_[0].value.node); }
#line 692 "parser.tab.cc"
    break;

  case 8: // class_decl: CLASS IDENTIFIER class_opt_ext IS class_body END
#line 137 "parser.y"
    {
        /* $2 = char* (name), $3 = char* (extends or NULL), $5 = vector* members */
        ClassNode* cn = new ClassNode((yystack_[4].value.str) ? string((yystack_[4].value.str)) : string());
        if ((yystack_[3].value.str)) cn->extendsName = string((yystack_[3].value.str));
        if ((yystack_[1].value.vec)) {
            for (ASTNode* m : *(yystack_[1].value.vec)) cn->members.emplace_back( std::unique_ptr<ASTNode>(m) );
            delete (yystack_[1].value.vec);
        }
        if ((yystack_[4].value.str)) free((yystack_[4].value.str));
        if ((yystack_[3].value.str)) free((yystack_[3].value.str));
        (yylhs.value.node) = cn;
    }
#line 709 "parser.tab.cc"
    break;

  case 9: // class_opt_ext: %empty
#line 152 "parser.y"
                     { (yylhs.value.str) = nullptr; }
#line 715 "parser.tab.cc"
    break;

  case 10: // class_opt_ext: EXTENDS IDENTIFIER
#line 153 "parser.y"
                       { (yylhs.value.str) = (yystack_[0].value.str); }
#line 721 "parser.tab.cc"
    break;

  case 11: // class_body: %empty
#line 157 "parser.y"
                     { (yylhs.value.vec) = new std::vector<ASTNode*>(); }
#line 727 "parser.tab.cc"
    break;

  case 12: // class_body: class_body class_member
#line 159 "parser.y"
    {
        (yylhs.value.vec) = (yystack_[1].value.vec);
        if ((yystack_[0].value.node)) (yylhs.value.vec)->push_back((yystack_[0].value.node));
    }
#line 736 "parser.tab.cc"
    break;

  case 13: // class_member: var_decl
#line 166 "parser.y"
             { (yylhs.value.node) = (yystack_[0].value.node); }
#line 742 "parser.tab.cc"
    break;

  case 14: // class_member: method_decl
#line 167 "parser.y"
                { (yylhs.value.node) = (yystack_[0].value.node); }
#line 748 "parser.tab.cc"
    break;

  case 15: // var_decl: VAR IDENTIFIER maybe_type SEMI
#line 172 "parser.y"
    {
        /* $2 = name (char*), $3 = type (char* or nullptr) */
        VarNode* vn = new VarNode((yystack_[2].value.str) ? string((yystack_[2].value.str)) : string(), (yystack_[1].value.str) ? string((yystack_[1].value.str)) : string());
        if ((yystack_[2].value.str)) free((yystack_[2].value.str));
        if ((yystack_[1].value.str)) free((yystack_[1].value.str));
        (yylhs.value.node) = vn;
    }
#line 760 "parser.tab.cc"
    break;

  case 16: // maybe_type: %empty
#line 182 "parser.y"
                     { (yylhs.value.str) = nullptr; }
#line 766 "parser.tab.cc"
    break;

  case 17: // maybe_type: COLON IDENTIFIER
#line 183 "parser.y"
                     { (yylhs.value.str) = (yystack_[0].value.str); }
#line 772 "parser.tab.cc"
    break;

  case 18: // method_decl: METHOD IDENTIFIER LPAREN RPAREN IS method_body END
#line 188 "parser.y"
    {
        /* $2 = name, $6 = vector* body */
        MethodNode* mn = new MethodNode((yystack_[5].value.str) ? string((yystack_[5].value.str)) : string());
        if ((yystack_[1].value.vec)) {
            for (ASTNode* b : *(yystack_[1].value.vec)) mn->body.emplace_back( std::unique_ptr<ASTNode>(b) );
            delete (yystack_[1].value.vec);
        }
        if ((yystack_[5].value.str)) free((yystack_[5].value.str));
        (yylhs.value.node) = mn;
    }
#line 787 "parser.tab.cc"
    break;

  case 19: // method_body: %empty
#line 201 "parser.y"
                     { (yylhs.value.vec) = new std::vector<ASTNode*>(); }
#line 793 "parser.tab.cc"
    break;

  case 20: // method_body: method_body method_member
#line 203 "parser.y"
    {
        (yylhs.value.vec) = (yystack_[1].value.vec);
        if ((yystack_[0].value.node)) (yylhs.value.vec)->push_back((yystack_[0].value.node));
    }
#line 802 "parser.tab.cc"
    break;

  case 21: // method_member: var_decl
#line 210 "parser.y"
             { (yylhs.value.node) = (yystack_[0].value.node); }
#line 808 "parser.tab.cc"
    break;

  case 22: // method_member: %empty
#line 212 "parser.y"
    { (yylhs.value.node) = new VarNode("__dummy__", ""); }
#line 814 "parser.tab.cc"
    break;


#line 818 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char parser::yypact_ninf_ = -25;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
     -25,     4,     0,   -25,   -13,    -6,    -4,   -25,   -25,   -25,
     -25,     9,    -9,   -10,    -1,    13,     1,    -3,    -7,   -25,
     -25,   -25,   -25,    16,     3,   -25,   -25,   -25,   -25,   -25,
      -5,   -25,   -25,   -25
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     2,     1,     0,     0,     0,     4,     5,     6,
       7,     9,    16,     0,     0,     0,     0,     0,     0,    10,
      11,    17,    15,     0,     0,    19,     8,    12,    13,    14,
       0,    18,    21,    20
  };

  const signed char
  parser::yypgoto_[] =
  {
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -24,   -25,
       2,   -25,   -25
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     7,     8,    15,    24,    27,     9,    17,
      10,    30,    33
  };

  const signed char
  parser::yytable_[] =
  {
      28,    31,     5,     4,     3,    11,    32,     5,     6,    26,
       5,     6,    12,    14,    13,    16,    18,    19,    20,    21,
      23,    25,    22,     0,     0,     0,    29
  };

  const signed char
  parser::yycheck_[] =
  {
      24,     6,     7,     3,     0,    18,    30,     7,     8,     6,
       7,     8,    18,     4,    18,    24,    26,    18,     5,    18,
      27,     5,    25,    -1,    -1,    -1,    24
  };

  const signed char
  parser::yystos_[] =
  {
       0,    33,    34,     0,     3,     7,     8,    35,    36,    40,
      42,    18,    18,    18,     4,    37,    24,    41,    26,    18,
       5,    18,    25,    27,    38,     5,     6,    39,    40,    42,
      43,     6,    40,    44
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    32,    33,    34,    34,    35,    35,    35,    36,    37,
      37,    38,    38,    39,    39,    40,    41,    41,    42,    43,
      43,    44,    44
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     1,     1,     1,     6,     0,
       2,     0,     2,     1,     1,     4,     0,     2,     7,     0,
       2,     1,     0
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "EXTENDS",
  "IS", "END", "VAR", "METHOD", "THIS", "RETURN", "IF", "THEN", "ELSE",
  "WHILE", "LOOP", "TRUE", "FALSE", "IDENTIFIER", "INTEGER", "REAL",
  "STRING", "SYMBOL", "UNKNOWN", "COLON", "SEMI", "LPAREN", "RPAREN",
  "COMMA", "DOT", "ASSIGN", "ARROW", "$accept", "program", "top_list",
  "top_item", "class_decl", "class_opt_ext", "class_body", "class_member",
  "var_decl", "maybe_type", "method_decl", "method_body", "method_member", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   105,   105,   120,   121,   130,   131,   132,   136,   152,
     153,   157,   158,   166,   167,   171,   182,   183,   187,   201,
     202,   210,   212
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
    };
    // Last valid token kind.
    const int code_max = 286;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1189 "parser.tab.cc"

#line 215 "parser.y"


/* ---- C/C++ вспомогательный код: yylex() и yyerror() ---- */
%{

/* Реализация yylex() читает из simpleTokens, который создаёт lexer.l (flex) */
/* simpleTokens: vector<SimpleToken> (SimpleToken defined in lexer.l) */
#include <iostream>

/* Прототип extern из lexer.l:
   extern std::vector<SimpleToken> simpleTokens;
   (SimpleToken = { std::string kind, text; int line,startCol,endCol })
*/
extern std::vector<SimpleToken> simpleTokens;

int yylex(void) {
    if (parserTokIndex >= simpleTokens.size()) return 0; /* EOF */

    const SimpleToken &t = simpleTokens[parserTokIndex++];

    /* Ключевые слова и идентификаторы:
       Лексер ранее помечал ключевые слова kind == "KEYWORD" и booleans etc.
       Здесь сопоставляем текст. При необходимости можно погружать в нижний регистр.
    */

    if (t.kind == "KEYWORD") {
        if (t.text == "class") return CLASS;
        if (t.text == "extends") return EXTENDS;
        if (t.text == "is") return IS;
        if (t.text == "end") return END;
        if (t.text == "var") return VAR;
        if (t.text == "method") return METHOD;
        if (t.text == "this") return THIS;
        if (t.text == "return") return RETURN;
        if (t.text == "if") return IF;
        if (t.text == "then") return THEN;
        if (t.text == "else") return ELSE;
        if (t.text == "while") return WHILE;
        if (t.text == "loop") return LOOP;
        if (t.text == "true") {
            yylval.str = strdup(t.text.c_str());
            return TRUE;
        }
        if (t.text == "false") {
            yylval.str = strdup(t.text.c_str());
            return FALSE;
        }
        /* если flex пометил как KEYWORD, но текст не совпал, отдаём как IDENTIFIER */
        yylval.str = strdup(t.text.c_str());
        return IDENTIFIER;
    } else if (t.kind == "IDENTIFIER") {
        yylval.str = strdup(t.text.c_str());
        return IDENTIFIER;
    } else if (t.kind == "INTEGER") {
        yylval.str = strdup(t.text.c_str());
        return INTEGER;
    } else if (t.kind == "REAL") {
        yylval.str = strdup(t.text.c_str());
        return REAL;
    } else if (t.kind == "STRING") {
        yylval.str = strdup(t.text.c_str());
        return STRING;
    } else if (t.kind == "SYMBOL") {
        if (t.text == ":") { return COLON; }
        if (t.text == ";") { return SEMI; }
        if (t.text == "(") { return LPAREN; }
        if (t.text == ")") { return RPAREN; }
        if (t.text == ",") { return COMMA; }
        if (t.text == ".") { return DOT; }
        if (t.text == ":=") { return ASSIGN; }
        if (t.text == "=>") { return ARROW; }
        /* иначе отдаём как SYMBOL (несем семантику в yylval.str) */
        yylval.str = strdup(t.text.c_str());
        return SYMBOL;
    } else if (t.kind == "UNKNOWN") {
        yylval.str = strdup(t.text.c_str());
        return UNKNOWN;
    } else {
        /* fallback: ignore */
        return 0;
    }
}

/* Простая ошибка парсинга */
void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << "\n";
}

%}
