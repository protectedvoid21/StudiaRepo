(*Zadanie 3*)
type 'a bt = Empty | Node of 'a * 'a bt * 'a bt;;

let tree = Node(1, Node(2, Node(4, Empty, Empty), Empty), Node(3, Node(5, Empty, Node(6, Empty, Empty)), Empty));; 

let breadthBT tr =
  let rec aux acc = function
    | Empty -> []
    | Node(num, left, right) -> num :: aux left acc @ aux right acc
  in aux tr
;;

breadthBT tree;;