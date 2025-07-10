{-# LANGUAGE GADTs #-}
module Token where

import AST

data Token where
  TTipo :: Tipo -> Token
  TId :: String -> Token
  TCInt :: Int -> Token
  TCDouble :: Double -> Token
  TLit :: String -> Token
  TIf :: Token
  TElse :: Token
  TWhile :: Token
  TReturn :: Token
  TPrint :: Token
  TRead :: Token
  TLChave :: Token
  TRChave :: Token
  TLPar :: Token
  TRPar :: Token
  TSemi :: Token
  TComma :: Token
  TAdd :: Token
  TSub :: Token
  TMul :: Token
  TDiv :: Token
  TAssign :: Token
  TEq :: Token
  TNotEq :: Token
  TLt :: Token
  TLte :: Token
  TGt :: Token
  TGte :: Token
  TAnd :: Token
  TOr :: Token
  TNot :: Token
  deriving (Show, Eq)
