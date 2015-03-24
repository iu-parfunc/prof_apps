

module Main where


import System.Environment


import Data.List.Split (splitOn) 

-- ----
-- MAIN
usage = "\n*****************************************\n" ++ 
        "prep filename #series [#rebucket-factor] \n" ++
        "*****************************************\n" 

main :: IO () 
main = do

  args <- getArgs

  let (fn,run,reb) =
        case args of
          [x,y] -> (x, read y :: Int, Nothing)
          [x,y,z] -> (x, read y :: Int, Just (read z :: Int)) 
          _  -> error usage

  rawData <- readFile fn

  let  lineData :: [String]
       lineData = filter (/= ">>") (lines rawData)
      
  putStrLn $ "Number of data lines: " ++ show (length lineData)

  let intData :: [[Integer]]
      intData = map (map read . splitOn ",") lineData
  
      lineData' :: [[(Integer,Integer)]]
      lineData' =  rebucket reb $ map (zip [0..]) intData
      
      pro = run * 3 + 1
      epi = run * 3 + 1    
      tot = run * 3 + 2
  
      genGPL :: Bool -> String -> String ->  String
      genGPL b ofn s = "set title 'Total Probe Overhead'\n" ++
                       "set ylabel 'Number of probes'\n"    ++
                       "set xlabel 'Overhead Interval'\n"   ++
                       "set grid\n"                         ++
                       "set term png\n"                     ++ 
                       "set logscale y 2\n"                 ++ 
                       "set datafile separator \",\"\n"     ++ 
                       "set output '"++ofn++".png'\n"        ++ 
                       case b of
                         False -> "plot 'tot_"++fn++".csv', 'pro_"++fn++".csv', 'epi_"++fn++".csv'"
                         True  -> "plot '"++s++"_"++fn++".csv'"
  
  writeFile ("pro_"++fn++".csv") $ toCSV $ lineData' !! pro
  writeFile ("epi_"++fn++".csv") $ toCSV $ lineData' !! epi
  writeFile ("tot_"++fn++".csv") $ toCSV $ lineData' !! tot

  writeFile ("pro_"++fn++".gpl") $ genGPL True ("pro_" ++ fn) "pro"
  writeFile ("epi_"++fn++".gpl") $ genGPL True ("epi_" ++ fn) "epi"
  writeFile ("tot_"++fn++".gpl") $ genGPL True ("tot_" ++ fn) "tot" 

  
  writeFile ("all_"++fn++".gpl") $ genGPL False ("all_" ++ fn) ""


  let sumIt n ix = (s1,s2)
        where 
          s1 = sum (map snd (take n (lineData' !! ix)))
          s2 = sum (map snd (drop n (lineData' !! ix)))

      (pro_1,pro_2) = sumIt 599 pro
      (epi_1,epi_2) = sumIt 599 epi
      (tot_1,tot_2) = sumIt 599 tot

  putStrLn "Prolog" 
  putStrLn $ "Bucket 0 - 599: " ++ show pro_1
  putStrLn $ "Bucket 600 -  : " ++ show pro_2 

  putStrLn "Epilog" 
  putStrLn $ "Bucket 0 - 599: " ++ show epi_1
  putStrLn $ "Bucket 600 -  : " ++ show epi_2 

  putStrLn "Total" 
  putStrLn $ "Bucket 0 - 599: " ++ show tot_1
  putStrLn $ "Bucket 600 -  : " ++ show tot_2 

  

toCSV :: [(Integer,Integer)] -> String 
toCSV [] = []
toCSV ((i,s):xs) = show i ++ "," ++ show s ++ "\n" ++
                   toCSV xs 
  




rebucket :: Maybe Int -> [[(Integer,Integer)]] -> [[(Integer,Integer)]]
rebucket Nothing xs = xs
rebucket (Just n) xs = map (go n) xs
  where
    go :: Int -> [(Integer,Integer)] -> [(Integer,Integer)]
    go n xs | length xs < n  = [bucket xs]
    go n xs = bucket (take n xs) : go n (drop n xs)

    bucket :: [(Integer,Integer)] -> (Integer,Integer)
    bucket xs = (buck, numProbes)
       where
         buck = minimum (map fst xs)
         numProbes = sum (map snd xs) 
    
