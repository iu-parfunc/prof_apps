

module Main where

import System.Process
import System.IO 
import System.Environment
import System.Directory

main = do

   curEnv <- getEnvironment
   curDir <- getCurrentDirectory
   
   (Just _hin, Just hout, Just herr, ph) <-
     createProcess (CreateProcess { cmdspec = ShellCommand "make build",
                               cwd = Just curDir,
                               env = Just ([ ("CC","gcc")
                                          , ("OPTLEVEL","-O2")] ++ curEnv),
--                                        
                               std_in = CreatePipe,
                               std_out = CreatePipe,
                               std_err = CreatePipe,
                               close_fds = False,
                               create_group = False,
                               delegate_ctlc = False
                                               })

   out <- hGetContents hout
   err <- hGetContents herr

   _ <- waitForProcess ph
   
   putStrLn out

   putStrLn err
