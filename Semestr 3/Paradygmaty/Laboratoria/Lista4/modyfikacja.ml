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


let insert disk path file =
  let rec helper file_list files_checked rest_path = match file_list with
    | (File file_name) :: tail ->
      helper tail (files_checked @ [File file_name]) rest_path

    | (Directory (dir_name, subdirs)) :: tail ->
      if dir_name = List.hd rest_path then
        files_checked @ [Directory (dir_name, helper subdirs [] (List.tl rest_path))] @ tail
      else
        files_checked @ [Directory (dir_name, subdirs)] @ helper tail files_checked rest_path

    | [] -> match rest_path with
      | [] -> files_checked @ [file]
      | _ -> files_checked @ [Directory (List.hd rest_path, helper [] [] (List.tl rest_path))]
  in
  match disk with
  | Disk (drive_letter, file_list) -> Disk (drive_letter, helper file_list [] path)
;;

insert sample_system ["Program Files"; "D#"; "G#";] (File "TEST.txt");;
insert sample_system ["Program Files"; "D#"; "G#"] (Directory ("FOLDER", []));;
insert sample_system [""] (File "Plik.txt");;