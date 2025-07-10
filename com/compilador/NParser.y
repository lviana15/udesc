{
module NParser where

import qualified Lexer as L
import Token
import AST
}

%name parse
%tokentype { Token }
%error { parseError }

%token
  "int"       { TTipo TInt }
  "double"    { TTipo TDouble }
  "string"    { TTipo TString }
  "void"      { TTipo TVoid }
  "if"        { TIf }
  "else"      { TElse }
  "while"     { TWhile }
  "return"    { TReturn }
  "print"     { TPrint }
  "read"      { TRead }
  "{"         { TLChave }
  "}"         { TRChave }
  "("         { TLPar }
  ")"         { TRPar }
  ";"         { TSemi }
  ","         { TComma }
  "+"         { TAdd }
  "-"         { TSub }
  "*"         { TMul }
  "/"         { TDiv }
  "="         { TAssign }
  "=="        { TEq }
  "/="        { TNotEq }
  "<"         { TLt }
  "<="        { TLte }
  ">"         { TGt }
  ">="        { TGte }
  "&&"        { TAnd }
  "||"        { TOr }
  "!"         { TNot }
  identifier  { TId $$ }
  intConst    { TCInt $$ }
  doubleConst { TCDouble $$ }
  stringLit   { TLit $$ }

%left ","
%left "||"
%left "&&"
%right "!"
%left "+" "-"
%left "*" "/"
%nonassoc "==" "!=" "<" "<=" ">" ">="

%%

Programa : ListaFuncoes BlocoPrincipal
            { (\(decl, cmds) -> Prog $1 [] (id decl) (id cmds)) $2 }
         | BlocoPrincipal
            { (\(decl, cmds) -> Prog [] [] (id decl) (id cmds)) $1 }

ListaFuncoes : ListaFuncoes Funcao       { [$2] ++ $1 }
             | Funcao                       { [$1] }

Funcao : TipoRetorno identifier "(" DeclParametros ")" BlocoPrincipal
            { $2 :->: ($4, $1) }
       | TipoRetorno identifier "(" ")" BlocoPrincipal
            { $2 :->: ([], $1) }

TipoRetorno : Tipo                          { $1 }
            | "void"                        { TVoid }

DeclParametros : DeclParametros "," Parametro       { [$2] ++ $1 }
               | Parametro                          { [$1] }

Parametro: Tipo identifier                  { $2 :#: ($1, 0) }

BlocoPrincipal: "{" Declaracoes ListaCmd "}"            { ($2, $3) }
              | "{" ListaCmd "}"                        { ([], $2) }

Declaracoes: Declaracoes Declaracao          { $2 ++ $1 }
           | Declaracao                     { $1 }

Declaracao: Tipo ListaId ";"
                    { map (\id -> id :#: ($1, 0)) $2 }

Tipo: "int"                                 { TInt }
    | "double"                              { TDouble }
    | "string"                              { TString }

ListaId : ListaId "," identifier            { [$3] ++ $1 }
        | identifier                        { [$1] }

Bloco
    : "{" ListaCmd "}"                      { $2 }

ListaCmd
    : ListaCmd  Comando                     { [$2] ++ $1 }
    | Comando                               { [$1] }

Comando
    : CmdSe                                 { $1 }
    | CmdEnquanto                           { $1 }
    | CmdAtrib                              { $1 }
    | CmdEscrita                            { $1 }
    | CmdLeitura                            { $1 }
    | ChamadaProc                           { $1 }
    | Retorno                               { $1 }

Retorno
    : "return" ExprA ";"                    { Ret (Just $2) }
    | "return" stringLit ";"                { Ret (Just (Lit $2)) }
    | "return" ";"                          { Ret Nothing }

CmdSe
    : "if" "(" ExprL ")" Bloco              { If $3 $5 [] }
    | "if" "(" ExprL ")" Bloco "else" Bloco { If $3 $5 $7 }

CmdEnquanto
    : "while" "(" ExprL ")" Bloco           { While $3 $5 }

CmdAtrib
    : identifier "=" ExprA ";"                   { Atrib $1 $3 }
    | identifier "=" stringLit ";"              { Atrib $1 (Lit $3) }

CmdEscrita
    : "print" "(" ExprA ")" ";"             { Imp $3 }
    | "print" "(" stringLit ")" ";"         { Imp (Lit $3) }

CmdLeitura
    : "read" "(" identifier ")" ";"         { Leitura $3 }

ChamadaProc
    : ChamadaFuncao ";"                       { Proc $1 }

ChamadaFuncao
    : identifier "(" ListaParametros ")"        { Chamada $1 $3 }
    | identifier "(" ")"                       { Chamada $1 [] }

ListaParametros
    : ExprA "," ListaParametros             { [$1] ++ $3 }
    | stringLit "," ListaParametros         { [(Lit $1)] ++ $3 }
    | ExprA                                 { [$1] }

ExprA
    : Term                                  { $1 }
    | ExprA "+" Term                        { Add $1 $3 }
    | ExprA "-" Term                        { Sub $1 $3 }

Term
    : Factor                                { $1 }
    | Term "*" Factor                       { Mul $1 $3 }
    | Term "/" Factor                       { Div $1 $3 }

Factor
    : "(" ExprA ")"                         { $2 }
    | identifier                            { IdVar $1 }
    | intConst                              { Const (CInt $1) }
    | doubleConst                           { Const (CDouble $1) }
    | "(" "int" ")" Factor                  { DoubleInt $4 }

ExprR
    : ExprA "<" ExprA                       { Rlt $1 $3 }
    | ExprA ">" ExprA                       { Rgt $1 $3 }
    | ExprA "<=" ExprA                      { Rle $1 $3 }
    | ExprA ">=" ExprA                      { Rge $1 $3 }
    | ExprA "==" ExprA                      { Req $1 $3 }
    | ExprA "/=" ExprA                      { Rdif $1 $3 }
    | ExprA                                 { Arit $1 }

ExprL
    : ExprR                                         { Rel $1 }
    | ExprL "&&" ExprR                              { And $1 (Rel $3) }
    | ExprL "||" ExprR                              { Or $1 (Rel $3) }
    | "!" ExprL                                     { Not $2 }

{
parseError :: [Token] -> a
parseError s = error ("Parse error " ++ show s)
}
