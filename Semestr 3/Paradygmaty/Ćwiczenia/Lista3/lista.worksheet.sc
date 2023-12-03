//zadanie 2
def curry3(f: (Int, Int, Int) => Int): Int => Int => Int => Int =
  x => y => z => f(x, y, z)
  
curry3((x, y, z) => x + y + z)(1)(2)(3)
  
def uncurry3(f: Int => Int => Int => Int): (Int, Int, Int) => Int =
  (x, y, z) => f(x)(y)(z)

uncurry3(x => y => z => x + y + z)(1, 2, 3)


def currySugared(f: (Int, Int, Int) => Int)(x: Int)(y: Int)(z: Int): Int =
    f(x, y, z)

currySugared((x, y, z) => x + y + z)(1)(2)(3)

def uncurrySugared(f: Int => Int => Int => Int):(Int, Int, Int) => Int =
    (x,y,z) => f(x)(y)(z)
    
uncurrySugared(x => y => z => x + y + z)(1, 2, 3)


//zadanie 3
def sumProd(xs: List[Int]): (Int,Int) = xs.foldLeft((0,1))((acc, x) => (acc._1 + x, acc._2 * x))

sumProd(List(1,2,3,4,5))


//zadanie 5
def insertionSort(list: List[Int]) =
    def insert(x: Int, restTail: List[Int]): List[Int] = restTail match
        case Nil => List(x)
        case head :: tail => if x < head then x :: head :: tail else head :: insert(x, tail)

    list.foldLeft(List[Int]())((acc, x) => insert(x, acc))

insertionSort(List(5, 1, -3, 10, 4, 2))    

def mergeSort(list: List[Int]): List[Int] =
    def merge(left: List[Int], right: List[Int]): List[Int] = (left, right) match
        case (Nil, _) => right
        case (_, Nil) => left
        case (leftHead :: leftTail, rightHead :: rightTail) =>
            if leftHead < rightHead then leftHead :: merge(leftTail, right)
            else rightHead :: merge(left, rightTail)

    def split(list: List[Int]): (List[Int], List[Int]) = list match
        case Nil => (Nil, Nil)
        case head :: Nil => (List(head), Nil)
        case head :: tail =>
            val (left, right) = split(tail)
            (head :: right, left)

    list match
        case Nil => Nil
        case head :: Nil => List(head)
        case _ =>
            val (left, right) = split(list)
            merge(mergeSort(left), mergeSort(right))

mergeSort(List(5, 1, -3, 10, 4, 2))            