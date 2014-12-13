
%{
    #include<cstdio>
    #include "ast.hh"
    #include<vector>
    #include<iostream>
    #include "codegen.cpp"
    extern "C" int yylex();
    void yyerror(const char * s ){printf("ERROR: %s\n",s);
    abort();}
ASTProgram* MAIN;
%}





%start program
%glr-parser

%left NOT
%left MULTIPLY DIVIDE REMAINDER
%left ADD MINUS
%left ROP
%left EOP
%left ANDAND OROR



%union
{
    char* string;
    int   integer;
    float val;
    char char_val_;
    Expression* expr_;
    ASTProgram* ast_;
  //  Field* field_;
    Method* method_;
    Variable* var_;
    vector <Variable*> *  variable_list_;
    vector <Expression*> *  expr_list_;
    vector<Fiemeth*> * fiemeth_list_;
    Statement* stmt_;
    vector<Statement*> * stmt_list_;
    Location* location_;
    Metharg* metharg_;
    Block* block_;
    vector<Vardec*> * var_decl_list_;
    Vardec* var_decl_;
    vector<Identifier*> * mvariables_;
    Literal* literal_;
    Methodcall* method_call_;
    Callarg* callout_arg_;
    vector <Callarg*> *  callout_arg_list_;
    vector <Expression*> *  method_call_arguments_;
    Intlit* int_literal_;
    Fiemeth* fiemeth_;
   // ASTProgram* MAIN;
}


%token CLASS PROGRAM LC RC LP RP LS RS WHILE FOR IF ELSE BREAK CONTINUE COMMA  

%token  SEMICOLON RETURN CALLOUT 

%token < string >  ANDAND OROR


%token < string > NOT EQUAL CHARACTER STRINGIT ID BOOLIT TYPE VOID ROP EOP  ADD MINUS MULTIPLY DIVIDE MINUSEQUAL PLUSEQUAL REMAINDER
%token < integer >  HEXIT NUMBER 

%type <ast_> program
%type <fiemeth_list_> fieldmore
%type <fiemeth_> field
%type <fiemeth_> method
%type <variable_list_> variables
%type <var_> variable
%type <metharg_> method_arguments
%type <block_> block
%type <var_decl_list_> var_declmore
%type <stmt_list_> statementmore
%type <var_decl_> var_decl
%type <stmt_> statement
%type <string> asop
%type <mvariables_> mvariables
%type <method_call_> method_call
%type <callout_arg_> callout_arg
%type <callout_arg_list_> callout_argmore


%type <expr_> expr
%type <location_> location


%type <expr_> literal
%type <int_literal_> int_literal
%type <method_call_arguments_> method_call_arguments

%%


program: CLASS ID LC fieldmore RC {
       Identifier * id = new Identifier($2);
       reverse($4->begin(), $4->end());
       MAIN = new ASTProgram(id, $4);
       }


fieldmore: {$$ = new vector< Fiemeth* >; } 
         | field fieldmore {
             $$ = $2;
             $$->push_back($1);
           }
           | method fieldmore {
             $$ = $2;
             $$->push_back($1);
           }


field: TYPE variables SEMICOLON {
  //   cout << "\n\n\nPARSER\n\n\n";
  //   cout << $1 << endl;
  //   cout << "\n\n\nPARSER\n\n\n";

     $$ = new Field($1, $2);
     printf("%s\n",$1);
     }


variables: variable {
         $$ = new vector<Variable*>;
         $$->push_back($1);
         }
          | variables COMMA variable {
          $$ = $1;
          $$->push_back($3);
          }

variable: ID {
        //id = new Identifier(yylval.string)
        $$ = new Identifier($1);
        }
        | ID LS NUMBER RS {
        Identifier* id = new Identifier($1);
        $$ = new Arraydec(id, $3);
        }

method: VOID ID LP method_arguments RP block {  
      Identifier * id = new Identifier($2);
      $$ = new Method($1, id, $4, $6);
      }
       |TYPE ID LP method_arguments RP block {
       Identifier* id = new Identifier($2);
       $$ = new Method($1, id , $4, $6);
       }    

method_arguments: { $$ = new Metharg;  } 
                | TYPE ID {
                $$ = new Metharg; 
                    Identifier *id = new Identifier($2);
               //     x.push_back(make_pair($1, id));
                   // cout << "PRINTING\n";
                 //   $$ = new Metharg(&x);
                 //   cout << $2 << endl;
                    ($$->arg_)->push_back(make_pair($1, id));
                }
                | method_arguments COMMA TYPE ID {
                    $$ = $1;
                    Identifier* id = new Identifier($4);
                    ($$->arg_)->push_back(make_pair($3,id));
                }

block: LC var_declmore statementmore RC {
     reverse($2->begin(), $2->end());
     reverse($3->begin(), $3->end());
 //  for(int i=0;i<$2->size();i++)
   //     (*$2)[i]->print();
     $$ = new Block($2, $3);
     }

var_declmore: { $$ = new vector<Vardec*>;} 
            | var_decl var_declmore {
                $$ = $2;
                $$->push_back($1);
            }

statementmore: { $$ = new vector<Statement*>; }
             | statement statementmore {
                $$ = $2;
                $$->push_back($1);
             }

var_decl: TYPE mvariables SEMICOLON {$$ = new Vardec($1, $2);}

mvariables: ID { 
             $$ = new vector<Identifier*>;
             Identifier *id = new Identifier($1);
             $$->push_back(id);
           }
          | mvariables COMMA ID {
            $$ = $1;
            Identifier* id = new Identifier($3);
            $$->push_back(id);
          }

statement: location asop expr SEMICOLON { $$ = new Assignst($1,$2,$3); }
          | method_call SEMICOLON{ $$ = new Methodcall(); $$ = $1; }
          | IF LP expr  RP block{ $$ = new Ifst($3, $5); }
          | IF LP expr  RP block ELSE block{ $$ = new Ifelsest($3, $5, $7); }
          | FOR ID EQUAL expr COMMA expr block{ 
            Identifier * id = new Identifier($2);
           // cout<< "BLOCK SIZE " <<  $7->stat_->size() << endl;
            //$7->print();
            $$ = new Forst(id, $4, $6, $7);
            }
          | RETURN expr SEMICOLON{ $$ = new Retvalst($2);}
          | RETURN SEMICOLON{ $$ = new Returnst(); }
          | BREAK SEMICOLON{ $$ = new Breakst(); }
          | CONTINUE SEMICOLON{ $$ = new Contst(); }


method_call: ID LP  method_call_arguments RP {
                Identifier * id = new Identifier($1);
                $$ = new Methodcall1(id, $3);
           }
            | CALLOUT  LP STRINGIT  RP {
                vector<Callarg*> *  empty_list;
                Strlit* mname= new Strlit($3);
                $$ = new Methodcall2(mname, empty_list);
            }
            | CALLOUT LP STRINGIT COMMA callout_argmore  RP {
                Strlit* mname= new Strlit($3);
                $$ = new Methodcall2(mname, $5);
            }

callout_argmore: callout_arg  { $$ = new vector <Callarg*>; $$->push_back($1); }
               | callout_argmore COMMA callout_arg { $$ = $1; $$->push_back($3); }


location: ID { 
        $$ = new Identifier($1); 
        }
        | ID LS expr  RS {
            Identifier * id = new Identifier($1);
            $$ = new Arrayacc(id, $3);
        }

expr: location { $$ = new Location(); $$ = $1; 
    }
    | method_call { $$ = new Methodcall(); $$ = $1; 
    }
    | literal { 
    $$ = new Literal(); $$ = $1; 
   }
    | MINUS expr { $$ = new Unaryexp($1, $2);  
    }
    | NOT expr  { $$ = new Unaryexp($1, $2); 
    }
    | LP expr  RP { $$ = $2; 
    }
    | expr ADD expr { $$ = new Binaryexp($1, $2, $3);
    }
    | expr MINUS expr { $$ = new Binaryexp($1, $2, $3);
    }
    | expr MULTIPLY expr { $$ = new Binaryexp($1, $2, $3);
    }
    | expr DIVIDE expr { $$ = new Binaryexp($1, $2, $3);
    }
    | expr REMAINDER expr { $$ = new Binaryexp($1, $2, $3); 
    }
    | expr  ROP expr { $$ = new Binaryexp($1, $2, $3); 
    }
    | expr EOP expr { $$ = new Binaryexp($1, $2, $3);  
    }
    | expr ANDAND expr { $$ = new Binaryexp($1, $2, $3); 
    }
    | expr OROR expr { $$ = new Binaryexp($1, $2, $3);  
    }

method_call_arguments: { $$ = new vector <Expression*>;  } 
                     | expr { $$ = new vector <Expression*>; $$->push_back($1);  }
                     | method_call_arguments COMMA expr {
                        $$ = $1;
                        $$->push_back($3);
                     }

callout_arg: expr { $$ = new Expression(); $$ = $1;  }
            | STRINGIT { $$ = new Strlit($1);  }

literal: int_literal {  $$ = new Number(); $$ = $1;   }
        | CHARACTER {
            $$ = new Charlit($1);
            cout << "PRINTING...\n";
            cout << $1 << endl;
        }
        | BOOLIT {
            if(strcmp($1, "true")==0)
                $$ = new Boollit(1);
            else
                $$ = new Boollit(0);
        }

asop: EQUAL { $$=$1; }
    |PLUSEQUAL {$$=$1;}
    |MINUSEQUAL {$$=$1;}


int_literal: NUMBER {
           $$ = new Number($1);  } 
           | HEXIT
           {
                $$ = new Number($1);
           }




%%

int main()
{
    while(yyparse());
    //MAIN->print();
    CodeGenContext context;
    context.generateCode(MAIN);

    return 0;
}
