let f1 x = x 2 2;; 

let f2 x y z = x ( y ^ z );;

(*Zadanie 2*)
let curry3 f x y z = f (x, y, z);;
let addun (x, y, z) = x + y + z;;

curry3 addun 3 5 8;;


let uncurry3 f (x, y, z) = f x y z;;
let addcu x y z = x + y + z;;

uncurry3 addcu (4, 6, 9);;

(*Zadanie 3*)
let sumProd = List.fold_left (fun (s, p) x -> (s + x, p * x)) (0, 1);;

sumProd [1; 2; 3; 4; 5];;

(*Zadanie 4*)
(*Przekazywana była ta sama lista gdzie porównywano głowę. W wyniku tego przekazywana była 'niżej' ta sama lista a głowa nie odpadała.*)
let rec quicksort = function
    [] -> []
  | head::tail -> let small = List.filter (fun y -> y < head ) tail
                  and large = List.filter (fun y -> y > head ) tail
  in quicksort small @ (head :: quicksort large)
;;

quicksort [5; 3; 1; 2; 4];;

(*Druga funkcja była poprawna xd*)

let rec quicksort' = function
    [] -> []
  | head::tail -> let small = List.filter (fun y -> y < head ) tail
                  and large = List.filter (fun y -> y > head ) tail
  in quicksort' small @ (head :: quicksort' large)
;;

quicksort' [5; 3; 1; 2; 4; 10; -3];;

(*Zadanie 5*)
let insertionsort lst = 
  let rec insert x = function
    | [] -> [x]
    | h::t -> if x < h then x::h::t else h::insert x t
  in List.fold_left (fun acc x -> insert x acc) [] lst
;;

insertionsort [5; 3; 1; 2; 4];;


(*Write mergesort*)
let rec mergesort list =
  let rec merge left right =
    match left, right with
    | [], _ -> right
    | _, [] -> left
    | h1::t1, h2::t2 -> if h1 < h2 then h1::merge t1 right else h2::merge left t2
  in
  let rec split = function
    | [] -> [], []
    | [x] -> [x], []
    | h1::h2::t -> let left, right = split t in h1::left, h2::right
  in
  match list with
  | [] -> []
  | [x] -> [x]
  | _ -> let left, right = split list in merge (mergesort left) (mergesort right)
;;

mergesort [5; 3; 1; 2; 4];;