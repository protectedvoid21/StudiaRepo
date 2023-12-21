let fib_decl n first_term second_term = 
  let rec helper a b m = 
    if m = n then [a]
    else a :: helper b (a + b) (m + 1)
  in
  helper first_term second_term 1;;
;;

let fib_tuple_decl n = 
  let rec helper a b m = 
    if m >= n then (a, b)
    else helper b (a + b) (m + 1)
  in
  helper 1 1 2
;;

let declaracci m n = 
  if n < 1 then []
  else
    let fib_tuple = fib_tuple_decl (m * 2)
    in
    if n <= 2 then if n = 1 then [fst fib_tuple] else [fst fib_tuple; snd fib_tuple]
    else fib_decl n (fst fib_tuple) (snd fib_tuple)
;;



let fib_imper n first_term second_term =
  let arr = Array.make n first_term
in
  if n >= 2 then arr.(1) <- second_term;
  for i = 2 to n - 1 do
    arr.(i) <- arr.(i - 1) + arr.(i - 2)
  done;
  arr
;;

let fib_tuple_imper n =
  let a = ref 1 in
  let b = ref 1 in
  for i = 3 to n do
    let c = !a + !b in
    a := !b;
    b := c
  done;
  (!a, !b)
;;

let imperacci m n = 
  if n < 1 then Array.make 0 0
  else
    let fib_tuple = fib_tuple_imper (m * 2)
    in
    if n <= 2 then 
      if n = 1 then Array.make 1 (fst fib_tuple) 
      else let arr = Array.make 2 0 in arr.(0) <- fst fib_tuple; arr.(1) <- snd fib_tuple; arr
    else fib_imper n (fst fib_tuple) (snd fib_tuple)
;;


(*Tests*)
for m = 1 to 10 do
  let elements = declaracci m 10 in
    List.iter (fun x -> print_int x; print_string "\t") elements;
    print_newline ()
done;;

for m = 1 to 10 do
  let elements = imperacci m 10 in
    Array.iter (fun x -> print_int x; print_string "\t") elements;
    print_newline ()
done;;