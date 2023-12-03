let reverse4 (x, y, z, w) = (w, z, y, x);;

reverse4 (1, 2, 3, 4);;
reverse4 (3, 2, 1, 4);;


let sumProd (s, e) = 
  let rec sumHelper current = 
    if current < e - 1 then
      let sumTuple = sumHelper (current + 1) in
      (current + fst sumTuple, current * snd sumTuple)
    else 
      (current, current)
  in
  sumHelper s
;;

sumProd (-2, 3);;
sumProd (2, 5);;
sumProd (10, 12);;

let isPerfect n = 
  let rec perfectDivider (left, num) =
    if num = 0 then
      left = 0
    else
      if n mod num = 0 then
        perfectDivider (left - num, num - 1)
      else
        perfectDivider (left, num - 1)
      in
  perfectDivider (n, n / 2)
;;

isPerfect 2;;
isPerfect 6;;
isPerfect 12;;
isPerfect 24;;
isPerfect 28;;

let insert (lst, elem, pos) =
  let rec insertAtPosition (list, position) =
    if list == [] then [elem]
    else
      if position = 0 then elem :: List.hd list :: List.tl list
      else List.hd list :: insertAtPosition (List.tl list, position - 1)
  in
  if pos < 0 then elem :: lst
  else insertAtPosition (lst, pos)
;;

insert ([1; 2; 3], 4, 0);;
insert ([1; 2; 3], 4, 1);;
insert ([1; 2; 3], 4, 2);;
insert ([1; 2; 3], 4, 3);;
insert ([1; 2; 3], 4, 4);;
insert ([1; 2; 3], 4, 5);;
insert ([1; 2; 3], 4, 6);;
insert ([1; 2; 3], 4, -1);;
insert ([1; 2; 3], 4, -2);;
insert ([], 'e', 3);;
insert ([], 'e', 0);;
insert ([], 'e', -1);;


let argmax list = 
  let rec aux lst maxLst = 
    if lst = [] then
      maxLst
    else if List.hd lst > List.hd maxLst then
      aux (List.tl lst) [List.hd lst]
    else if List.hd lst = List.hd maxLst then
      aux (List.tl lst) (List.hd maxLst :: maxLst)
    else 
      aux (List.tl lst) maxLst
    
    in
    
      if list = [] then []
      else aux(List.tl list) [List.hd list]
    ;;

argmax [1; 30; 5; 0; -3; 2; 10; 7];;
argmax [1; 20; 3; 4; 3; 2] ;;
argmax [5; 30; 20; -1; 30; -5; 3];;
argmax [];;
argmax [5; 4; 3; 2; 6; 5; 3];;