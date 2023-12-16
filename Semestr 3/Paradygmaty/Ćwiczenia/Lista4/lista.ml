(*Zadanie 3*)
type 'a bt = Empty | Node of 'a * 'a bt * 'a bt;;

let tree = Node(1, Node(2, Node(4, Empty, Empty), Empty), Node(3, Node(5, Empty, Node(6, Empty, Empty)), Empty));; 

let breadthBT tree =
  let rec breadth_first queue acc = match queue with
    | [] -> List.rev acc
    | Empty :: tl -> breadth_first tl acc
    | Node (value, left, right) :: tl ->
        let updated_queue = tl @ [left; right] in
        breadth_first updated_queue (value :: acc)
  in
  breadth_first [tree] []
;;

breadthBT tree;;

(*Zadanie 4*)
type 'a bt = Empty | Node of 'a * 'a bt * 'a bt

let rec internal_path_length tree =
  let rec helper depth = function
    | Empty -> 0
    | Node (_, left, right) ->
        depth + helper (depth + 1) left + helper (depth + 1) right
  in
  helper 0 tree
;;

let rec external_path_length tree =
  let rec helper depth = function
    | Empty -> depth
    | Node (_, left, right) ->
        helper (depth + 1) left + helper (depth + 1) right
  in
  helper 0 tree
;;

let example_tree =
  Node (1,
    Node (2,
      Node (4, Empty, Empty),
      Node (5, Empty, Empty)),
    Node (3,
      Node (6, Empty, Empty),
      Node (7, Empty, Empty))
  )
;;

internal_path_length example_tree;;
external_path_length example_tree;;