module Problem4
where

digits :: Int -> [Int]
digits 0 = []
digits n = (mod n 10) : digits (div n 10)

isPalindrome :: Int -> Bool
isPalindrome n = (digits n) == (reverse.digits) n

palindromes = [n*m | n <- [999,998..100], m<-[999,998..100]]
maxPalindromes = map isPalindrome palindromes

palindromeList = maximum $ map (\(v,t) -> v) (filter (\(_,t) -> (t == True)) (zip palindromes maxPalindromes))

--Brute force attempt, no logic ; < 10 seconds
--906609