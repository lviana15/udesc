module Table where

import AST

type SymbolTable = [Var]
type FunctionTable = [Funcao]

-- Tabela simbolos
insertVarTable :: Var -> SymbolTable -> Either String SymbolTable
insertVarTable var@(id :#: _) table
    | isVarDeclared id table = Left $ "Variavel " ++ id ++ " já declarada"
    | otherwise = Right $ var : table

isVarDeclared :: Id -> SymbolTable -> Bool
isVarDeclared id table = any (\(id :#: (t, _)) -> id == id) table


-- Tabela funcoes
insertFunction :: Funcao -> FunctionTable -> Either String FunctionTable
insertFunction func@(id :->: _) table
    | isFunctionDeclared id table = Left $ "Função " ++ id ++ " já declarada"
    | otherwise = Right (func : table)

isFunctionDeclared :: Id -> FunctionTable -> Bool
isFunctionDeclared id table = any (\(funcId :->: _) -> id == funcId) table


-- Travessia programa
buildTables :: Programa -> Either String (SymbolTable, FunctionTable)
buildTables (Prog funcs procs vars bloco) = do
  funcTable <- foldl processFunc (Right []) funcs

  symTable <- foldl processVar (Right []) vars

  (symTableFinal, _) <- foldl processProc (Right (symTable, funcTable)) procs

  (symTableMain, _) <- processBlock (symTableFinal, funcTable) bloco

  return (symTableMain, funcTable)
  where
    processFunc :: Either String FunctionTable -> Funcao -> Either String FunctionTable
    processFunc acc func = do
      table <- acc
      insertFunction func table

    processVar :: Either String SymbolTable -> Var -> Either String SymbolTable
    processVar acc var = do
      table <- acc
      insertVarTable var table

    processProc :: Either String (SymbolTable, FunctionTable) -> (Id, [Var], Bloco) -> Either String (SymbolTable, FunctionTable)
    processProc acc (id, params, bloco) = do
      (symTable, funcTable) <- acc
      symTableWithParams <- foldl processVar (Right symTable) params
      processBlock (symTableWithParams, funcTable) bloco

    processBlock :: (SymbolTable, FunctionTable) -> Bloco -> Either String (SymbolTable, FunctionTable)
    processBlock (symTable, funcTable) [] = Right (symTable, funcTable)
    processBlock (symTable, funcTable) (cmd:cmds) = do
      (newSymTable, newFuncTable) <- processCommand (symTable, funcTable) cmd
      processBlock (newSymTable, newFuncTable) cmds

    processCommand :: (SymbolTable, FunctionTable) -> Comando -> Either String (SymbolTable, FunctionTable)
    processCommand (symTable, funcTable) cmd = case cmd of
      If _ thenBlock elseBlock -> do
        (symTableThen, _) <- processBlock (symTable, funcTable) thenBlock
        processBlock (symTableThen, funcTable) elseBlock
      While _ body -> processBlock (symTable, funcTable) body
      Atrib id _ ->
        if isVarDeclared id symTable
          then Right (symTable, funcTable)
          else Left $ "Variável " ++ id ++ " não declarada"
      Leitura id ->
        if isVarDeclared id symTable
          then Right (symTable, funcTable)
          else Left $ "Variável " ++ id ++ " não declarada"
      Imp _ -> Right (symTable, funcTable)
      Ret _ -> Right (symTable, funcTable)
      Proc (Chamada id _) ->
        if isFunctionDeclared id funcTable
          then Right (symTable, funcTable)
          else Left $ "Função " ++ id ++ " não declarada"
      Proc _ -> Right (symTable, funcTable)

