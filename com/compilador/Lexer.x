{
module Lexer where

import Data.Array
import Token
import AST
}

%wrapper "basic"

$digit = [0-9]
@int = $digit+
@double = $digit+\.($digit+)?

tokens :-

<0> $white+ ;
<0> "int"                   { \_ -> TTipo TInt }
<0> "double"                { \_ -> TTipo TDouble }
<0> "string"                { \_ -> TTipo TString }
<0> "void"                  { \_ -> TTipo TVoid }
<0> "if"                    { \_ -> TIf }
<0> "while"                 { \_ -> TWhile }
<0> "else"                  { \_ -> TElse }
<0> "return"                { \_ -> TReturn }
<0> "print"                 { \_ -> TPrint }
<0> "read"                  { \_ -> TRead }
<0> [a-zA-Z][a-zA-Z0-9_]*   { \tok -> TId tok }
<0> @int                    { \tok -> TCInt (read tok) }
<0> @double                 { \tok -> TCDouble (read tok) }
<0> \"[^\"]*\"              { \tok -> TLit (init (tail tok)) }
<0> "{"                     { \_ -> TLChave }
<0> "}"                     { \_ -> TRChave }
<0> "("                     { \_ -> TLPar }
<0> ")"                     { \_ -> TRPar }
<0> ";"                     { \_ -> TSemi }
<0> ","                     { \_ -> TComma }
<0> "+"                     { \_ -> TAdd }
<0> "-"                     { \_ -> TSub }
<0> "*"                     { \_ -> TMul }
<0> "/"                     { \_ -> TDiv }
<0> "="                     { \_ -> TAssign }
<0> "=="                    { \_ -> TEq }
<0> "/="                    { \_ -> TNotEq }
<0> "<"                     { \_ -> TLt }
<0> "<="                    { \_ -> TLte }
<0> ">"                     { \_ -> TGt }
<0> ">="                    { \_ -> TGte }
<0> "&&"                    { \_ -> TAnd }
<0> "||"                    { \_ -> TOr }
<0> "!"                     { \_ -> TNot }

{
testLex = do token <- getLine
             print (alexScanTokens token)
}

