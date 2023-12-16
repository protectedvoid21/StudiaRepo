type prize =
  | Value of string
  | AdditionalTickets of ticket list
and
ticket = 
  | Unrevealed of prize Lazy.t 
  | Revealed of prize
;;

type table = ticket list;;

let rec buyTicket table ticketNumber =
  let rec helper table ticketNumber counter =
    match table with
    | [] -> []
    | head :: tail ->
      if counter >= ticketNumber then
        match head with
        | Unrevealed prizeFn -> (
            match Lazy.force prizeFn with
            | Value s -> Revealed (Value s) :: tail
            | AdditionalTickets n -> n @ tail
          )
        | Revealed prize -> head :: tail
      else
        head :: helper tail ticketNumber (counter + 1)
  in
  helper table ticketNumber 1
;;
  
let printTable table =
  let showPrize prize =
    match prize with
    | Value s -> s
    | AdditionalTickets n -> string_of_int (List.length n) ^ " losy"
  in
  let rec helper tab acc = match tab with
    | [] -> acc
    | head :: tail -> 
      match head with
      | Unrevealed _ -> acc ^ " ?" ^ helper tail acc
      | Revealed prize -> acc ^ " " ^ showPrize prize ^ "" ^ helper tail acc
    in
  let tableStr = helper table ""
  in
  "[" ^ tableStr ^ " ]"
;;


let exampleTable = [Unrevealed (lazy (AdditionalTickets [Unrevealed (lazy (Value "Bronx")); Unrevealed (lazy (Value "Biblia C++"))])); 
                    Unrevealed (lazy (Value "Samochod")); 
                    Unrevealed (lazy (Value "Telewizor")); 
                    Unrevealed (lazy (AdditionalTickets [Unrevealed (lazy (Value "Ksiazka")); Unrevealed (lazy (Value "Kubek"))])); 
                    Unrevealed (lazy (Value "Laptop"))]

;;

let table1 = buyTicket exampleTable 2;;
let table2 = buyTicket table1 4;;
let table3 = buyTicket table2 3;;
let table4 = buyTicket table3 0;;
let table5 = buyTicket table4 1;;

printTable exampleTable;;
printTable table1;;
printTable table2;;
printTable table3;;
printTable table4;;
printTable table5;;




let exampleTable = [Unrevealed (lazy (Value "Samochod"));  
                    Unrevealed (lazy (AdditionalTickets [Unrevealed (lazy (Value "Ksiazka")); Unrevealed (lazy (Value "Kubek"))])); 
                    Unrevealed (lazy (Value "Laptop"))]
;;
  
let table1 = buyTicket exampleTable 1;;
let table2 = buyTicket table1 1;;
let table3 = buyTicket table2 1;;
let table4 = buyTicket table3 1;;

printTable table1;;
printTable table2;;
printTable table3;;
printTable table4;;
