(*Zadanie 1*)

type 'a llist = LNil | LCons of 'a * 'a llist Lazy.t;;

let lRepeat k list =
  let rec helper counter acc rest_list = match counter < k, rest_list with
    | true, LCons(head, tail)-> LCons(head, lazy (helper (counter + 1) acc rest_list))
    | false, LCons(head, tail) -> helper 0 acc (Lazy.force tail)
    | _, LNil -> acc
  in
  helper 0 LNil list
;;

let rec unlazy = function
  | LCons(head, tail) -> head :: unlazy (Lazy.force tail)
  | LNil -> []
;;

let lz_list = LCons(1, lazy (LCons(4, lazy (LCons(3, lazy LNil)))));;

let repeated = unlazy (lRepeat 3 lz_list);;

(*Zadanie 2*)

let fib n = 
  let rec helper a b =
    