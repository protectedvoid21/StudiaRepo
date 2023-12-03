(*1) Zdefiniuj:
a. Typ tree3 (drzewo trójkowe) o następujących cechach:
• Drzewo puste jest drzewem trójkowym,
• Węzeł drzewa składa się z elementu oraz 0 – 3 poddrzew.

b. Zdefiniuj funkcjonał mapTree3 w postaci rozwiniętej, wykonujący operację mapowania dla
drzewa trójkowego.*)

type tree3 = Empty | Node of int * tree3 * tree3 * tree3;;

let rec mapTree3 f t = match t with
  | Empty -> Empty
  | Node (x, t1, t2, t3) -> Node (f x, mapTree3 f t1, mapTree3 f t2, mapTree3 f t3)
;;

mapTree3(fun x -> x * 7) (Node(1, Node(2, Empty, Empty, Empty), Empty, Node(3, Empty, Empty, Empty)));;


(*Zadanie 2*)
type file_type = 
  | Directory of string * file_type list
  | File of string
;;
type disk = Disk of char * file_type list;;

let sample_system = 
  Disk('C', [
    Directory("Program Files", [
      Directory("Java", [
        File("java.exe");
        File("documentation.txt");
        File("alotofboilerplate.txt");
        File("publicstaticvoidmainstringargs.XD")
      ]);
      Directory("C#", [
        Directory("Roslyn", []);
        Directory("Folder of better languages", []);
        File("csharp.exe");
        File("csharpcompiler.exe");
        File("csharpinterpreter.exe");
        File("csharpdocumentation.txt");
      ]);
      Directory("OCaml", [
        File("ocaml.exe");
        File("ocamlc.exe");
        File("csharp.exe");
        File("ocamllex.exe");
    ]);
  ]);
]);;
    
let rec find_file_path current_dir current_path target_file = 
  match current_dir with
  | File file_name -> if file_name = target_file then current_path ^ "\\" ^ file_name else ""
  | Directory (dir_name, file_system_list) -> 
    let new_path = current_path ^ "\\" ^ dir_name in
    let rec helper files =
      match files with
      | [] -> ""
      | hd::tl -> 
        let path = find_file_path hd new_path target_file in
        if path <> "" then path else helper tl
    in
    helper file_system_list
;;

let find_file_in_disk (Disk (drive_letter, file_system_list)) target_file = 
  let drive = String.make 1 drive_letter ^ ":" in
  
  let rec aux = function
    | [] -> ""
    | head :: tail -> 
      let path = find_file_path head drive target_file in
      if path != "" then path else aux tail
  in

  let path = aux file_system_list in
  if path = "" then None else Some(path)
;;

find_file_in_disk sample_system "csharp.exe";;
find_file_in_disk sample_system "csharpcompiler.exe";;
find_file_in_disk sample_system "ocaml.exe";;
find_file_in_disk sample_system "ddddd.exe";;