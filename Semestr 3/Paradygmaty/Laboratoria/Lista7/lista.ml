module StackMachine = struct
  exception Division_by_zero of string
  exception Missing_parameter of string

  type t = { mutable stack : float list }

  type instruction =
  | Load_float of float
  | Load_int of int
  | Reset
  | Copy
  | Add
  | Sub
  | Mul
  | Div

  let result state = match state.stack with
    | [] -> raise (Missing_parameter "Stack is empty")
    | x :: _ -> x

  let init () = { stack = [] }
  
  let load_float number state = { stack = number :: state.stack }
  
  let load_int number state = { stack = float_of_int number :: state.stack }

  let copy state =
    match state.stack with
    | [] -> raise (Missing_parameter "Stack is empty")
    | x :: xs -> { stack = x :: x :: xs }

  let reset state = { stack = [] }

  let add state =
    match state.stack with
    | [] -> raise (Missing_parameter "Stack is empty")
    | x :: [] -> raise (Missing_parameter "Stack has only one element")
    | x :: y :: xs -> { stack = (x +. y) :: xs }

  let sub state =
    match state.stack with
    | [] -> raise (Missing_parameter "Stack is empty")
    | x :: [] -> raise (Missing_parameter "Stack has only one element")
    | x :: y :: xs -> { stack = (x -. y) :: xs }

  let mul state =
    match state.stack with
    | [] -> raise (Missing_parameter "Stack is empty")
    | x :: [] -> raise (Missing_parameter "Stack has only one element")
    | x :: y :: xs -> { stack = (x *. y) :: xs }

  let div state =
    match state.stack with
    | [] -> raise (Missing_parameter "Stack is empty")
    | x :: [] -> raise (Missing_parameter "Stack has only one element")
    | x :: y :: xs ->
        if y = 0. then raise (Division_by_zero "Division by zero")
        else { stack = (x /. y) :: xs }

  let rec run state instructions =
    match instructions with
    | [] -> state
    | instruction :: rest_instructions ->
        let new_state =
          match instruction with
          | Load_float number -> load_float number state
          | Load_int number -> load_int number state
          | Copy -> copy state
          | Reset -> reset state
          | Add -> add state
          | Sub -> sub state
          | Mul -> mul state
          | Div -> div state
        in
        run new_state rest_instructions
end

module type COPROCESSOR = sig
  type t 

  exception Division_by_zero of string
  exception Missing_parameter of string

  type instruction(* =
  | Load_float of float
  | Load_int of int
  | Reset
  | Copy
  | Add
  | Sub
  | Mul
  | Div*)

  val init : unit -> t
  val run : t -> instruction list -> t
  val result : t -> float
end

module Coprocessor : COPROCESSOR with type instruction = StackMachine.instruction = StackMachine


let coprocessor = Coprocessor.init ()

let () =
  let final_state = Coprocessor.run coprocessor [
    Load_float 1.;
    Load_float 2.;
    Add;
    Load_float 3.;
    Mul;
    Load_float 4.;
    Div;
    Load_float 5.;
    Sub;
    Copy;
    Add;
  ] in
  Printf.printf "Result: %f\n" (Coprocessor.result final_state)
