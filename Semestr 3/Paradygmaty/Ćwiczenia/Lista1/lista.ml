(*Zadanie 1*)
let flatten lists = 
  let rec aux acc remaining =
    match remaining with
    | [] -> acc
    | head :: tail -> aux (acc @ head) tail
  in aux [] lists
;;

flatten [[1;2;3];[4;5;6];[7;8;9]];;
flatten [[1;2;3];[];[7;8;9]];;

(*Zadanie 2*)
let rec count (elem, list) =
  match list with
  | [] -> 0
  | head :: tail -> if head = elem then 1 + count (elem, tail) else count (elem, tail)
;;

count (1, [1;2;3;1;1;1;1;1;1;1;1;1;1;1;1;1;1]);;
count (1, []);;
count (1, [2;3;4;5;6;7;8;9]);;

  
(*Zadanie 3*)
let rec replicate (elem, count) =
  if count <= 0 then [] else elem :: replicate (elem, count - 1);;

replicate (1, 10);;
replicate (1, 0);;
replicate (1, -1);;

(*Zadanie 4*)
let rec sqrList list =
  match list with
  | [] -> []
  | head :: tail -> (head * head) :: sqrList tail
;;

sqrList [1;2;3;4;5;6;7;8;9];;
sqrList [];;
sqrList [0];;
  
(*Zadanie 5*)
let isPalindrome list = 
  let reverseList list =
    let rec aux acc remaining =
      match remaining with
      | [] -> acc
      | head :: tail -> aux (head :: acc) tail
    in aux [] list
  in list = reverseList list
;;

isPalindrome [1;2;3;4;5;6;7;8;9];;
isPalindrome [1;2;3;4;5;4;3;2;1];;
isPalindrome [1;2;3;4;5;5;4;3;2;1];;
  
(*Zadanie 6*)
let rec listLength list =
  match list with
  | [] -> 0
  | head :: tail -> 1 + listLength tail
;;

listLength [1;2;3;4;5;6;7;8;9];;
listLength [];;
listLength [1;2;3;4;5;6;7;8;9;10;11;12;13;14;15];;

(*Zadanie 7*)
let rec foo n c = if n = 1. then 1. else c *. log10 n +. foo (n /. 2.) c;;

foo 8. 3.;;
foo 1. 3.;;
foo 2. 3.;;