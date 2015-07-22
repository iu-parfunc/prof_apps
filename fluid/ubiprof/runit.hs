

module Main where

import System.Process
import System.IO 
import System.Environment
import System.Directory
import qualified Data.ByteString.Char8 as B

main = do

   curEnv <- getEnvironment
   curDir <- getCurrentDirectory
   
   (Just _hin, Just hout, Just herr, ph) <-
     createProcess (CreateProcess { cmdspec = ShellCommand "make run",
                               cwd = Just curDir,
                               env = Just ([ ("PROFILER_TYPE","MINIMAL_ADAPTIVE")
                                          , ("ADAPTIVE_STRATEGY","SLOW_RAMP_UP")
                                          , ("TARGET_OVERHEAD","3")] ++ curEnv),
--                                           , ("LD_LIBRARY_PATH","/opt/gcc/4.9.2/lib64:/opt/papi/5.4.1/lib/::/u/crest-team/opt/lib:/lib/x86_64-linux-gnu/")],
                               std_in = CreatePipe,
                               std_out = CreatePipe,
                               std_err = CreatePipe,
                               close_fds = False,
                               create_group = False,
                               delegate_ctlc = False
                                               })

   out <- B.hGetContents hout
   err <- B.hGetContents herr

   _ <- waitForProcess ph

   B.putStrLn out

   B.putStrLn err
