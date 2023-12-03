let cutAndMend a b list = 
  let rec aux remaining index = 
    match (index >= a && index <= b, remaining) with
      | (false, head :: tail) -> head :: aux tail (index + 1)
      | (true, head :: tail) -> aux tail (index + 1)
      | (_, []) -> []
  in
  aux list 1
;;

let cutAndMend24 = cutAndMend 2 4;;

cutAndMend24 [1; 2; 3; 4; 5; 6; 7; 8];;
cutAndMend24 [1; 2; 3];;
cutAndMend24 [1];;
cutAndMend24 [];;


let split2Rec list = 
  let rec aux lst = 
    match lst with
      | [] -> ([], [])
      | head :: [] -> (head :: [], [])
      | first :: second :: tail ->  let (firstList, secondList) = aux tail 
                                    in (first :: firstList, second :: secondList) 
    in
  aux list
;;

split2Rec [1; 2; 3; 4; 5; 6; 7; 8; 9];;
split2Rec [1; 2; 3; 4];;
split2Rec [1];;
split2Rec [];;


let split2Tail list =
  let rec aux remaining firstList secondList firstTurn =
    match (firstTurn, remaining) with
    | (true, head :: tail) -> aux tail (head :: firstList) secondList false
    | (false, head :: tail) -> aux tail firstList (head :: secondList) true
    | (_, []) -> (firstList, secondList)
  in
  
  aux list [] [] true
;;

split2Tail [1; 2; 3; 4; 5; 6; 7; 8; 9];;
split2Tail [1; 2; 3; 4];;
split2Tail [1];;
split2Tail [];;