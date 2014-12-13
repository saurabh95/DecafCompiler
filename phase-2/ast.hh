#include <list>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class   Fiemeth{
    public:
        virtual void print(){
               cout << "FIEMETH\n";
           }
};

class Variable{
    public:
        virtual void print(){}
};

class Statement
{
    public:
        virtual void print(){}
};

class Callarg{
    public:
       virtual void print(){}
};


class Expression:public Callarg
{ 
public:
    virtual void print(){}
};

class Location:public Expression{
    public:
        virtual void print(){}
};

class Identifier:public Location,public Variable{
    public:
        char * id_;
        Identifier(char * id)
        {
            id_=id;
        }
        Identifier()
        {
        }
        void print()
        {
//            cout << "Identifier: ";
            printf(" %s ", id_);
        }
};

class Vardec{
    public:
        char* type_;
        vector < Identifier* > * var_;
        Vardec(char* type,vector < Identifier* > * var)
        {
            type_=type;
            var_=var;
        }
        Vardec()
        {
        }
        void print()
        {
  //          cout << "Vaedec" << endl;
            printf("%s ",type_);
        //   reverse(var_->begin(), var_->end());
            for(int i=0;i<var_->size();i++)
            {
                (*var_)[i]->print();
                cout << " ";
            }
            cout << endl;
        //   reverse(var_->begin(), var_->end());
        }
};

class Block{
    public:
    vector < Vardec* >  * var_;
    vector < Statement* >  * stat_;
    Block(vector < Vardec* > *  var,vector <  Statement*> *  stat)
    {
        var_=var;
        stat_=stat;
    }
    Block()
    {
    }
    void print()
    {
    //    cout << "BLOCK" << endl;
     //   reverse(var_->begin(), var_->end());
        for(int i=0;i<var_->size();i++)
             (*var_)[i]->print();
     //   reverse(var_->begin(), var_->end());
     //   reverse(stat_->begin(), stat_->end());
     //   cout << "STAT" << stat_->size() << endl;
        fflush(stdout);
        for(int i=0;i<stat_->size();i++)
        {
             (*stat_)[i]->print();
             cout << endl;
        }
     //   reverse(stat_->begin(), stat_->end());
    }
};


class ASTProgram{
    public:
        Identifier * id_;
        vector< Fiemeth* > * fieldmore_;
        ASTProgram(Identifier * s,vector < Fiemeth* > *  fieldmore)
        {
            id_=s;
            fieldmore_=fieldmore;
        }
        ASTProgram()
        {
        }
        void print()
        {
            cout << "CLASS ";
            id_->print();
            cout << endl;
          //  reverse(fieldmore_->begin(), fieldmore_->end());
            for(int i=0;i<fieldmore_->size();i++)
            {
                (*fieldmore_)[i]->print();
                cout << endl;
            }
          //  reverse(fieldmore_->begin(), fieldmore_->end());
        }
};



class Field:public Fiemeth
{
    public:
        char* type_;
        vector< Variable* >  * var_;
        Field(char* type,vector < Variable* > *  var)
        {
            type_=type;
            var_=var;
        }
        Field()
        {
        }

        void print()
        {
    //        cout << "FIELD\n";
            printf("%s ", type_);
     //       reverse(var_->begin(), var_->end());
            for(int i=0;i<var_->size();i++)
                (*var_)[i]->print();
       //     reverse(var_->begin(), var_->end());
        }

};






class Binaryexp:public Expression{
    public:
        Expression* lhs_;
        Expression* rhs_;
        char* biop_;

        Binaryexp(Expression* lhs,char* biop,Expression* rhs)
        {
            lhs_=lhs;
            rhs_=rhs;
            biop_=biop;
        }
        Binaryexp()
        {
        }
        void print() 
        {
            lhs_->print();
            printf("%s ", biop_);
            rhs_->print();
        }
};


class   Unaryexp:public Expression{
    public:
        char* op_;
        Expression* exp_;
        Unaryexp(char* op,Expression* exp)
        {
            op_=op;
            exp_=exp;
        }
        Unaryexp()
        {
        }
        void print() {
            printf("%s ",op_);
            exp_->print();
        }

};

class Literal:public Expression{
    public:
        virtual void print(){}
};

class Intlit:public Literal{
    public:
        virtual void print(){}
};

class Number:public Intlit{
    public :
        int val_;
        Number(int val)
        {
            val_=val;
        }
        Number()
        {
        }
        void print()
        {
            cout << val_ << " ";
        }
};


class Hexit:public Intlit{
    public :
        int val_;
        Hexit(int val)
        {
            val_=val;
        }
        Hexit()
        {
        }
        void print()
        {
            cout << val_ << endl;
        }
};

class Charlit:public Literal{
    public:
        char* c_;
        Charlit(char* c)
        {
            c_=c;
        }
        Charlit()
        {
        }
        void print()
        {
            printf("%s\n",c_);
        }

};

class Boollit:public Literal{
    public:
        bool b_;
        Boollit(bool b)
        {
            b_=b;
        }
        Boollit()
        {
        }
        void print()
        {
      //      cout << "BOOL";
            cout << b_ << endl;
        }
};


class Strlit:public Callarg{
    public:
        char * s_;
        Strlit(char * s)
        {
            s_=s;
        }
        Strlit()
        {
        }
        void print()
        {
            printf(" %s ",s_);
        }
};



class Arrayacc:public Location{
    public:
        Expression* expr_;
        Identifier* id_;
        Arrayacc(Identifier* id, Expression* expr)
        {
            id_=id;
            expr_=expr;
        }
        Arrayacc()
        {
        }
        void print()
        {
            id_->print();
            cout << "[";
            expr_->print();
            cout << "] ";
        }
};

class Methodcall:public Expression,public Statement
{
    public:
        virtual void print(){}
};

class Methodcall1:public Methodcall{
    public:
        Identifier* mname_;
        vector < Expression* >* explist_;
        Methodcall1(Identifier* mname,vector < Expression* >* explist)
        {
            mname_=mname;
            explist_=explist;
        }
        Methodcall1()
        {
        }
        void print()
        {
            mname_->print();
      //    reverse(explist_->begin(), (explist_->end()));
          for(int i=0;i<explist_->size();i++)
            (*explist_)[i]->print();
        //  reverse(explist_->begin(), (explist_->end()));
        }
};


class Methodcall2:public Methodcall{
    public:
        Strlit* mname_;
        vector < Callarg* >*  list_;
        Methodcall2(Strlit* mname,vector < Callarg* >*  list)
        {
            mname_=mname;
            list_=list;
        }
        Methodcall2()
        {
        }
        void print()
        {
            mname_->print();
       //     reverse(list_->begin(), (list_->end()));
          for(int i=0;i<list_->size();i++)
                (*list_)[i]->print();
         //   reverse(list_->begin(), (list_->end()));
        }
};


class Assignst:public Statement{
    public:
        Expression * loc_;
        char* asop_;
        Expression* exp_;
        Assignst(Expression * loc,char* asop, Expression* exp)
        {
            asop_ = asop;
            loc_=loc;
            exp_=exp;
        }
        Assignst()
        {
        }
        void print()
        {
            loc_->print();
            printf(" %s ",asop_);
            exp_->print();
            cout << endl;
        }

};
 
class Ifst:public Statement{
    public:
        Expression* exp_;
        Block* bloc_;
        Ifst(Expression* exp, Block* bloc)
        {
            bloc_=bloc;
            exp_=exp;
        }
        Ifst()
        {
        }
        void print()
        {
            exp_->print();
            bloc_->print();
        }
};


class Ifelsest:public Statement{
    public:
        Expression* exp_;
        Block* bloc1_;
        Block* bloc2_;
        Ifelsest(Expression* exp,Block* bloc1, Block* bloc2)
        {
            bloc1_=bloc1;
            bloc2_=bloc2;
            exp_=exp;
        }
       Ifelsest()
       {
       }
        void print()
        {
            cout << "IF" << endl;
            exp_->print();
            cout << endl;
          //  cout << "THEN\n";
            bloc1_->print();
            cout << endl;
            cout << "ELSE\n";
            bloc2_->print();
            cout << endl;
        }
};


class Forst:public Statement{
    public:
        Block* bloc_;
        Expression* init_;
        Expression* exp_;
        Identifier* id_;
        Forst(Identifier* id,Expression* init,Expression* exp,Block* bloc)
        {
            id_=id;
            init_=init;
            exp_=exp;
            bloc_=bloc;

        }
        Forst()
        {
        }
        void print()
        {
            cout << "FOR ";
            id_->print();
            cout << "=";
            init_->print();
            exp_->print();
            cout << endl;
            bloc_->print();
        }
};

class Returnst:public Statement{
    public:
        void print()
        {
            cout << "RETURN";
        }
};
class Breakst:public Statement{
    public:
        virtual void print(){}
};

class Retvalst:public Statement{
    public:
        Expression* exp_;
        Retvalst(Expression* exp)
        {
            exp_=exp;
        }
        Retvalst()
        {
        }
        void print()
        {
            cout << "RETURN ";
            exp_->print();
        }
};

class Contst:public Statement{
public:
    virtual void print(){
        cout << "CONTINUE";
    }
};






class Metharg{
    public:
        vector < pair< char* , Identifier* > >*  arg_;
        Metharg(vector < pair < char* ,Identifier* > > *  arg)
        {
         //   cout << "THIS IS IT" << endl;
            arg_=arg;
        }
        Metharg()
        {
         //   cout << "THIS IadaS IT" << endl;
            arg_ = new vector<pair<char*, Identifier* > >;
        }
        void print()
        {
            cout << "( ";
                for(int i=0;i<arg_->size();i++)
                {
                    printf("%s ",(*arg_)[i].first);
                    (*arg_)[i].second->print();
                    cout << " ";
                }
                cout << ")";
        }
};

class Method:public Fiemeth{
    public:
        char* retype_;
        Identifier * id_;
        Metharg*   arg_;
        Block* bloc_;
        Method(char* retype,Identifier* id,Metharg* arg,Block* bloc )
        {
            retype_=retype;
            id_=id;
            arg_=arg;
            bloc_=bloc;
        }
        Method()
        {
        }
        void print()
        {
            printf("%s ", retype_);
            id_->print();
            cout << " ";
            arg_->print();
            cout << "\n";
            bloc_->print();
        }
};


class Arraydec:public Variable{
    public:
    Identifier* name_;
    int alloc_;
    Arraydec(Identifier* name,int alloc)
    {
        name_=name;
        alloc_=alloc;
    }
    Arraydec()
    {
    }
    void print()
    {
        name_->print();
        cout << "[";
        cout << alloc_;
        cout << "]";
    }
};







