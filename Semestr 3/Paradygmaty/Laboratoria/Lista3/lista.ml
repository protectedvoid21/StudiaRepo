let (>>) f n =
  let rec applyMultipleTimes x count acc =
    if count = 0 then acc
    else let result = f (x - 1) in applyMultipleTimes result (count - 1) (result :: acc)
  in
  if n <= 0 then fun x -> [x - 1] 
  else fun x -> applyMultipleTimes x (n - 1) ((x - 1) :: [])
;;

(>>) (fun x -> x) 10 5;;
(>>) (fun x -> 2 * x) 5 2;;

(>>) (fun x -> x * 4) 4 2;;

(>>) (fun x -> x + 1) 5 3;;
(>>) (fun x -> x + 1) 5 0;;
(>>) (fun x -> x + 1) 5 (-1);;
(>>) (fun x -> x / 2) 16 65536;;
(>>) (fun x -> x * 2) 16 2;;

let rec fib = function
  | 0 -> 0
  | 1 -> 1
  | n -> fib (n - 1) + fib (n - 2)
;;

(fib >> 4) 6;;