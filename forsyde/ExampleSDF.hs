{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use camelCase" #-}

module Examples where
import ForSyDe.Shallow

--------------------------
-- Example SDF
--------------------------
a_1 = actor11SDF 1 1 times
a_2 = actor22SDF (2,1) (1,1) plusN
d_1 = delaySDF [0]

plusN :: [Int] -> [Int] -> ([Int],[Int])
plusN [x1,x2] [y] = ([x1 + x2 - y],[x1 + x2 - y])
times :: [Int] -> [Int]
times [x] = [x * 10]

sdf s_in = a2_out1 where
  a2_in2 = d_1 a2_out2
  a1_out = a_1 s_in
  (a2_out1, a2_out2) = a_2 a1_out a2_in2

s_test :: Signal Int
s_test = signal [0..9]

{-
ghci> sdf s_test
{10,40,50,80,90}
-}
