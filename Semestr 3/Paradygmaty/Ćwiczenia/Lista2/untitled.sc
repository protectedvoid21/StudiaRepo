//Zadanie 2

def fib(n: Int): Int = n match {
  case 0 => 0
  case 1 => 1
  case _ => fib(n - 1) + fib(n - 2)
}

def fibTail(n: Int) = {
  def aux(x: Int, a: Int, b: Int): Int = x match {
    case 0 => a
    case 1 => b
    case _ => aux(x - 1, b, a + b)
  } 
  aux(n, 0, 1)
}

//Zadanie 3

def root3(a: Double): Double = {
  val approx = 1.0e-15 * math.abs(a);
  
  def rootHelper(rootApprox: Double): Double = 
    if math.abs(math.pow(rootApprox, 3) - a) <= approx then
      rootApprox
    else
      rootHelper(rootApprox + (a / math.pow(rootApprox, 2) - rootApprox) / 3)
      
  rootHelper(if a > 1 then a / 3 else a)
}

//Zadanie 4

val List(_, _, x, _, _) = List(-2, -1, 0, 1, 2)
val List((_, _), (y, _)) = List((1, 2), (0, 1))

//Zadanie 5

def initSegment[A](firstList: List[A], secondList: List[A]): Boolean = (firstList, secondList) match {
  case (Nil, _) => true
  case (_, Nil) => false
  case (xHead :: xTail, yHead :: yTail) => xHead == yHead match {
    case true => initSegment(xTail, yTail)
    case false => false
  }
}

initSegment(List(1, 2, 3), List(1, 2, 3, 4, 5))
initSegment(List(1, 2, 3), List(1, 2, 3))
initSegment(List(1, 2, 3), List(1, 2, 3, 4, 5, 6))
initSegment(List(1, 2, 3), Nil)
initSegment(Nil, List(1, 2, 3))
initSegment(Nil, Nil)

//Zadanie 6

def replaceNth[A](list: List[A], n: Int, elem: A): List[A] = (list, n) match {
  case (Nil, _) => Nil
  case (head :: tail, 0) => elem :: tail
  case (head :: tail, _) => head :: replaceNth(tail, n - 1, elem)
}

replaceNth(List(1, 2, 3, 4, 5), 2, 0)
replaceNth(List(1, 2, 3, 4, 5), 0, 0)
replaceNth(List(1, 2, 3, 4, 5), 4, 0)
replaceNth(List(1, 2, 3, 4, 5), 5, 0)
replaceNth(List(1, 2, 3, 4, 5), 6, 0)
replaceNth(Nil, 0, 0)
