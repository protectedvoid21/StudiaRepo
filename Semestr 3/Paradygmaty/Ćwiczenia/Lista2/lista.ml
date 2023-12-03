(*Zadanie 2*)

let rec fib n = match n with
    | 0 -> 0
    | 1 -> 1
    | _ -> fib (n - 1) + fib (n - 2)
;;

let fibTail n = 
  let rec aux x a b =
    match x with
      | 0 -> a
      | 1 -> b
      | _ -> aux (x - 1) b (a + b)
  in
  aux n 0 1
;;

fib 10;;
fib 20;;
fib 30;;

fibTail 10;;
fibTail 20;;
fibTail 30;;


(*Zadanie 3*)

let root3 a =
  let approx = 1.0e-15 *. abs_float a in

  let rec root_helper root_approx = 
    if abs_float (root_approx ** 3. -. a) <= approx then
      root_approx
    else
      root_helper (root_approx +. (a /. (root_approx ** 2.) -. root_approx) /. 3.)
  in
  root_helper (if a > 1. then a /. 3. else a)
;;

root3 27.;;
root3 9.65;;
root3 60.;;


(*Zadanie 4*)

let [_; _; x; _; _] = [-2;-1;0;1;2];;
x;;

let [(_, _); (x, _)] = [(1, 2); (0, 4)];;
x;;

(*Zadanie 5*)
let rec initSegment firstList secondList = 
  match firstList, secondList with
      | [], _ -> true
      | _, [] -> false
      | xHead :: xTail, yHead :: yTail -> match xHead = yHead with
        | true -> initSegment xTail yTail 
        | false -> false
;;

initSegment [1;2;3] [1;2;3;4;5];;
initSegment [1;2;3] [1;2;4;5];;
initSegment [1;2;3] [1;2;3];;
initSegment [] [1; 2;];;
initSegment [1; 2;] [10; 11; 1; 2; 3;];;

(*Zadanie 6*)

let rec replaceNth list index element = 
  match list, index with
    | [], _ -> []
    | head :: tail, 0 -> element :: tail 
    | head :: tail, _ -> head :: replaceNth tail (index - 1) element
;;

replaceNth [1;2;3;4;5] 2 10;;
replaceNth [1;2;3;4;5] 0 10;;
replaceNth [1;2;3;4;5] 4 10;;
replaceNth [1;2;3;4;5] 5 10;; 
replaceNth [1;2;3;4;5] 6 10;;
replaceNth [] 0 10;;
replaceNth [1;2;3;4;5] (-1) 10;;