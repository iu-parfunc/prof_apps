#!/usr/bin/env runghc-7.8.2

-- Prereqs:
--  cabal install csv

import Control.Monad 
import qualified Data.Map as M
import qualified Data.Set as S
import Data.List as L
import Data.Char
import Text.CSV
import System.IO
import System.Environment
import Debug.Trace
--------------------------------------------------------------------------------

schema = ["Function", "Rate_Hist", "Time_Hist", "Count", "Samples", "Min", "Max", "Avg", "Variance", "Leaf?"]

-- Exmaple line:
-- ["BZ2_bzDecompressInit","0 0 0 0 0 0 0 0 0 0 0","0 0 0 2 1 0 0 0 0 0 0","3","1","4521","28554","12572.0","0.0","FALSE"]
getHist :: [String] -> [Int]
getHist [name, _, timeHist, _cnt, _smpls, _min, _max, _avg, _var, _isLeaf ] = map read (words timeHist)
getHist oth = error ("couldn't parse: "++show oth)

getName = head

getMax :: [String] -> Int
getMax [name, _, timeHist, _cnt, _smpls, _min, max, _avg, _var, _isLeaf ] = read max

getCount :: [String] -> Int
getCount [name, _, timeHist, cnt, _smpls, _min, max, _avg, _var, _isLeaf ] = read cnt

getAvg :: [String] -> Double
getAvg [name, _, timeHist, _cnt, _smpls, _min, max, avg, _var, _isLeaf ] = read avg

-- likelyMulti = 

isMulti :: [Int] -> Bool
isMulti (fst : sec : rst) 
  | null rst                        = False
  | fst > sec && sec < maximum rst  = True
  | otherwise                       = isMulti (sec:rst)
isMulti _ = False 

readGprof :: String -> M.Map String Double
readGprof str = M.fromList pairs -- (trace (" pairs "++show pairs) pairs)
    --  18.65      4.51     4.51 328060278     0.00     0.00  mainGtU
  where
    pairs = [ (name, read secs) | [_, secs, _, _, _, _, name ] <- filtered ]
    filtered = filter (\ls -> isNum (ls!!1)) $
               -- trace ("rightlen "++show rightlen) $
              rightlen
    rightlen = filter ((==7) . length) $ 
               sec1 -- (trace ("sec1 "++show sec1) sec1)
    sec1 :: [[String]]
    sec1 = map words $ 
           takeWhile (not . isInfixOf "the percentage of the total") $ 
           lines str

isNum :: String -> Bool
isNum str = not (null (reads str :: [(Double,String)]))

main = do 
  args <- getArgs
  (csvfile,gprof) <- case args of 
                      [a,b] -> return (a,b)
                      _   -> error "Expects a .csv and .gprof file as command line argument!"
  putStrLn ("\nReading file "++csvfile)
  putStrLn "----------------------------------------"
  str  <- readFile csvfile

  let Right csv = parseCSV csvfile str
      csv' = filter (\r -> length r == length schema) $
             map (map trim) $ tail csv -- Drop the header line.

  str2 <- readFile gprof
  let gprofData = readGprof str2

  -- cheat, it's actually whitespace separtaed just fine:
  -- let recs = L.map (words . L.filter (/= ',')) $ lines f
  --     mp   = M.fromList [ (head l, tail l) | l <- recs ]

  let total  = length csv'
      multis = filter (isMulti . getHist) csv'
  putStrLn ("Found good data on "++show total++" functions.")
  putStrLn ("Found "++show (length multis)++" definitely multimodal functions:")
  forM_ multis $ \ dat -> 
    putStrLn (" * "++getName dat ++" "++ show(getHist dat))

--  mapM_ print $ map getHist csv' -- (M.toList mp)    

  putStrLn$ "Processing gprof data, found "++show (M.size gprofData)++" functions"

  let dynaOnly = filter (\x -> not (M.member (getName x) gprofData)) multis 
  putStrLn$ "DynaProf found "++show (length dynaOnly)++" functions gprof did not:"
  forM_ dynaOnly $ \ dat -> 
    putStrLn (" * "++concat (intersperse ", " dat))

  unless (null dynaOnly) $ do 
    let avgs   = (map getAvg dynaOnly)
        maxes  = (map getMax dynaOnly)
        counts = (map getCount dynaOnly)
        totals = zipWith (*) avgs (map fromIntegral counts)
    putStrLn$ "\n avg durations of gprof-missed: "++ show (sort avgs)
    putStrLn$ "                        median: "++ show (median avgs)
    putStrLn$ "\n max durations of gprof-missed: "++ show (sort maxes)
    putStrLn$ "                        median: "++ show (median maxes)
    putStrLn$ "\n        counts of gprof-missed: "++ show (sort counts)
    putStrLn$ "                        median: "++ show (median counts)
    putStrLn$ "\n  total cycles of gprof-missed: "++ show (sort totals)
    putStrLn$ "                        median: "++ show (median totals)
    putStrLn$ "\n Max duration of a function dynaprof missed: "++ show (maximum $ map getMax dynaOnly)

-- 303,984,903,830

median [] = error "No median of empty list"
median [a] = a
median ls = head $ drop (length ls `quot` 2) (sort ls)
  
trim s = dropWhile isSpace $ 
         reverse $ dropWhile isSpace $ 
         reverse s
