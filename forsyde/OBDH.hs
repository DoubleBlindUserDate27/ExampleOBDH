{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use camelCase" #-}

module OBDH where
import ForSyDe.Shallow

--------------------------
-- Example OBDH
--------------------------
a_1 = actor11SDF 1 1 times1
a_2 = actor11SDF 1 1 times2
a_3 = actor11SDF 1 1 times3

times1 :: [Int] -> [Int]
times1 [x] = [x * 1]

times2 :: [Int] -> [Int]
times2 [x] = [x * 2]

times3 :: [Int] -> [Int]
times3 [x] = [x * 3]

k = kernel13SADF

dispatchAllTC :: [Int] -> ([Int],[Int],[Int])
dispatchAllTC [x1,x2,x3] = ([x1],[x2],[x3])

dispatchTwoTC :: [Int] -> ([Int],[Int],[Int])
dispatchTwoTC [x1,x2,x3] = ([x1],[x2],[])

dispatchOneTC :: [Int] -> ([Int],[Int],[Int])
dispatchOneTC [x1,x2,x3] = ([x1],[],[])

ns _ [x] = if x > 0 && x < 4 then x
           else 1

scenario1 = (3,(1,1,1), dispatchAllTC)
scenario2 = (3,(1,1,0), dispatchTwoTC)
scenario3 = (3,(1,0,0), dispatchOneTC)

selScenarios 1 = (1, [scenario1])
selScenarios 2 = (1, [scenario2])
selScenarios 3 = (1, [scenario3])

d = detector11SADF consume_rate ns selScenarios initial_state where
    consume_rate = 1
    initial_state = 1

obdh :: Signal Int -> Signal Int -> (Signal Int, Signal Int, Signal Int)
obdh i_tc i_ev = (o_a1,o_a2,o_a3) where
    s_sc = d i_ev
    (s_a1,s_a2,s_a3) = k s_sc i_tc
    o_a1 = a_1 s_a1
    o_a2 = a_2 s_a2
    o_a3 = a_3 s_a3

-- testing signals
s_tc :: Signal Int
s_tc = signal [1..12]
s_ev :: Signal Int
s_ev = signal [1,1,3,3]
s_ev1 :: Signal Int
s_ev1 = signal [1,1,1,1]
s_ev2 :: Signal Int
s_ev2 = signal [3,3,3,3]

{-
ghci> obdh s_tc s_ev
({1,4,7,10},{4,10},{9,18})
ghci> obdh s_tc s_ev1
({1,4,7,10},{4,10,16,22},{9,18,27,36})
ghci> obdh s_tc s_ev2
({1,4,7,10},{},{})
-}
