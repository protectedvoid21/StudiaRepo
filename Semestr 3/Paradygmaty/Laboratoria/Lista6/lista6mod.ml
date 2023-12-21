let composite n = 
  let arr = Array.make n 0 in
  for i = 2 to n do
    arr.(i - 1) <- i
  done;

  for i = 2 to n do
    if arr.(i - 1) <> 0 then
      for j = 2 to n do
        arr.(i * j - 1) <- 0;
      done;
    done;

  arr
;;

composite 10;;