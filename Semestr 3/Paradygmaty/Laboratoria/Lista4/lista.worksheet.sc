//Zadanie 1

sealed trait Tree3
    case class Node3(value: Int, left: Tree3, middle: Tree3, right: Tree3) extends Tree3
    case object Empty extends Tree3

def mapTree3(func: Int => Int)(tree: Tree3): Tree3 = tree match {
    case Node3(value, left, middle, right) => Node3(func(value), mapTree3(func)(left), mapTree3(func)(middle), mapTree3(func)(right))
    case Empty => Empty
}

val sampleTree3 = Node3(1, Node3(2, Empty, Empty, Empty), Node3(3, Empty, Empty, Empty), Node3(4, Empty, Empty, Empty))

mapTree3((x: Int) => x * 5)(sampleTree3)

//Zadanie 2

case class Disk(name: Char, children: List[FileSystem])

sealed trait FileSystem
    case class Directory(name: String, children: List[FileSystem]) extends FileSystem
    case class File(name: String) extends FileSystem
    
val disk = Disk('C', List(
    Directory("Program Files", List(
        Directory("Azure", List(
            File("azure.exe"),
            File("microsoft.dotnet8.dll"))),
        Directory("Big folder", List(
            Directory("Inside folder", List(
                Directory("Inside inside folder", List())))))
        ))
    ))