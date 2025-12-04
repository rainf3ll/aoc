main :: IO ()
toDigits :: String -> [Int]
toDigits = map (\c -> read [c] :: Int)

dropWhileInclusive :: (a -> Bool) -> [a] -> [a]
dropWhileInclusive _ [] = []
dropWhileInclusive p (val : rest)
  | p val = dropWhileInclusive p rest
  | otherwise = rest

dropWithMax :: String -> String
dropWithMax s =
  let m = maximum (toDigits s)
      rest = dropWhileInclusive (\c -> (read [c] :: Int) < m) s
   in rest

megaSolve :: String -> String -> Int -> Int
megaSolve _ _ 16 = 0
megaSolve orig s n = maximum (toDigits (take (length orig - (15 - n)) s)) * 10 ^ (15 - n) + megaSolve orig (dropWithMax (take (length orig - (15 - n)) s) ++ take 1 (drop (length orig - (15 - n)) orig)) (n + 1)

main = do
  content <- readFile "in.txt"
  let nums = lines content
  let silver = sum (map (\orig -> megaSolve orig (take (length orig - 1) orig) 14) nums)
  putStrLn ("silver: " ++ show silver)
  let gold = sum (map (\orig -> megaSolve orig (take (length orig - 11) orig) 4) nums)
  putStrLn ("gold: " ++ show gold)
