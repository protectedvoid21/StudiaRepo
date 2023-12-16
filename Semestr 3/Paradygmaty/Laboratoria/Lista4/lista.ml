type tree3 = 
  | Empty
  | Node of int * tree3 * tree3 * tree3;;
  
let tree = 
  Node(1, 
    Node(2, 
      Node(4, Empty, Empty, Empty), 
      Node(5, Empty, Empty, Empty), 
      Node(6, Empty, Empty, Empty)
    ), 
    Node(3, 
      Node(7, Empty, Empty, Empty), 
      Node(8, Empty, Empty, Empty), 
      Node(9, Empty, Empty, Empty)
    ), 
    Node(10, 
      Node(11, Empty, Empty, Empty), 
      Node(12, Empty, Empty, Empty), 
      Node(13, Empty, Empty, Empty)
    )
  );;

let mapTree3 f tree = 
  let rec aux = function
    | Empty -> Empty
    | Node (value, left, middle, right) -> 
      Node (f value, aux left, aux middle, aux right)
  in
  aux tree
;;

mapTree3 (fun x -> x * 1) tree;;

type file_type = 
  | Directory of string * file_type list
  | File of string
;;
type disk = Disk of char * file_type list;;

let sample_system = 
  Disk('C', [
    Directory("Program Files", [
      Directory("Java", [
        Directory("JDK", [File("java.exe");]);
        File("documentation.txt");
        File("alotofboilerplate.txt");
        File("publicstaticvoidmainstringargs.XD")
      ]);
      Directory("C#", [
        Directory("Roslyn", []);
        Directory("Folder of better languages", []);
        File("java.exe");
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
  | Directory (dir_name, subdirs) -> 
    let new_path = current_path ^ "\\" ^ dir_name in

    if dir_name = target_file 
      then new_path 
    else
      let rec helper = function
        | [] -> ""
        | head :: tail -> 
          let path = find_file_path head new_path target_file in
          if path <> "" then path else helper tail
      in
      helper subdirs
;;

let find_file_in_disk (Disk (drive_letter, file_system_list)) target_file = 
  let drive = String.make 1 drive_letter ^ ":" in
  
  let rec aux = function
    | [] -> ""
    | head :: tail -> 
      let path = find_file_path head drive target_file in
      if path <> "" then path else aux tail
  in

  let path = aux file_system_list in
  if path = "" then None else Some(path)
;;

find_file_in_disk sample_system "csharp.exe";;
find_file_in_disk sample_system "java.exe";;
find_file_in_disk sample_system "csharpcompiler.exe";;
find_file_in_disk sample_system "Roslyn";;
find_file_in_disk sample_system "ocaml.exe";;
find_file_in_disk sample_system "ddddd.exe";;