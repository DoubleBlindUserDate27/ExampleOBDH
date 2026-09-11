{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use camelCase" #-}

module Examples where
import ForSyDe.Shallow

--------------------------
-- Example SADF
--------------------------
ns _ [x] = x

plus :: [Int] -> [Int]
plus [x1,x2] = [x1 + x2]

times :: [Int] -> [Int]
times [x] = [x * 10]

k = kernel11SADF 
scenario1 = (1,1, times)
scenario2 = (2,1, plus)

selScenarios 1 = (1, [scenario1])
selScenarios 2 = (1, [scenario2])

d = detector11SADF consume_rate ns selScenarios initial_state where
  consume_rate = 1
  initial_state = 1

sadf :: Signal Int -> Signal Int -> Signal Int
sadf i_c i = o where
  o = k s i
  s = d i_c

s_control :: Signal Int
s_control = signal [1,1,2]
s_in :: Signal Int
s_in = signal [1,2,3,4]

{-
ghci> sadf s_control s_in
{10,20,7}
-}
