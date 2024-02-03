module type QUEUE_FUN = sig
  type 'a t

  exception Empty of string

  val empty : unit -> 'a t
  val enqueue : 'a * 'a t -> 'a t
  val dequeue : 'a t -> 'a t
  val first : 'a t -> 'a
  val isEmpty : 'a t -> bool
end

module Queue : QUEUE_FUN = struct
  type 'a t = 'a list

  exception Empty of string

  let empty () = []
  let enqueue (x, q) = q @ [ x ]
  let dequeue = function [] -> raise (Empty "dequeue") | _ :: q -> q
  let first = function [] -> raise (Empty "first") | x :: _ -> x
  let isEmpty q = q = []
end

let () = print_endline "Queue module"
