module Main where

import System.IO
import System.Environment
import Lexer
import NParser
import AST

main :: IO ()
main = do
    args <- getArgs
    case args of
        [filename] -> do
            content <- readFile filename
            let tokens = alexScanTokens content
            let ast = parse tokens
            putStrLn $ show ast
        _ -> putStrLn "Usage: ./Main <filename>"
