let reverse4 (x, y, z, w) = (w, z, y, x);;

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


let insert (lst, elem, pos) =
  let rec insertAtPosition list position =
    if position <= 0 then
      elem :: list
    else
      match list with
      | [] -> [elem]
      | head :: tail -> head :: insertAtPosition tail (position - 1)
  in
  if pos <= 0 then elem :: lst
  else insertAtPosition lst pos
;;