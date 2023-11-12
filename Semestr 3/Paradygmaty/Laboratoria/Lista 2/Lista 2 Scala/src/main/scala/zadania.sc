/*1) Napisać funkcję cutAndMend wycinającą z danej listy elementy o indeksach pomiędzy
pozycjami a <= b (włącznie z końcami). Funkcja ma być napisana w taki sposób, by za jej
pomocą można było wygenerować wiele funkcji wycinających wartości między danymi
pozycjami np. cutAndMend15, która wycina wartości o indeksach 1, 2, 3, 4 i 5. Wykorzystać
mechanizm dopasowania wzorca, ale bez wyrażenia if. (OCaml i Scala) (30pkt.)*/


def cutAndMend[A](start: Int, end: Int): List[A] => List[A] = (list: List[A]) => {
  def aux(remaining: List[A], index: Int): List[A] = {
    (index >= start && index <= end, remaining) match {
      case (false, head :: tail) => head :: aux(tail, index + 1)
      case (true, head :: tail) => aux(tail, index + 1)
      case (_, Nil) => Nil
    }
  }
  aux(list, 1)
}

val cutAndMend24: List[Int] => List[Int] = cutAndMend(2, 4)

cutAndMend24(List(1, 2, 3, 4, 5, 6, 7, 8))
cutAndMend24(List(1, 2, 3, 4))
cutAndMend24(List(1, 2, 3))
cutAndMend24(List())

/*Napisać funkcje rozdzielające daną listę na dwie równe listy: (OCaml i Scala)
a. split2Rec bazującą na zwykłej rekurencji, (10pkt.)*/

def split2Rec[A](list: List[A]): (List[A], List[A]) = {
  def aux(l: List[A]): (List[A], List[A]) = l match {
    case Nil => (Nil, Nil)
    case head :: Nil => (List(head), Nil)
    case first :: second :: tail =>
      val (firstList, secondList  ) = aux(tail)
      (first :: firstList, second :: secondList)
  }

  aux(list)
}

split2Rec(List(1, 2, 3, 4, 5, 6, 7, 8))
split2Rec(List(1, 2, 3, 4, 5))
split2Rec(List(1))
split2Rec(List())

//b. split2Tail bazującą na rekurencji ogonowej. (10pkt.)

def split2Tail[A](list: List[A]): (List[A], List[A]) = {
  def aux(remaining: List[A], firstList: List[A], secondList: List[A], firstTurn: Boolean): (List[A], List[A]) = {
    (firstTurn, remaining) match {
      case (true, head :: tail) => aux(tail, head :: firstList, secondList, false)
      case (false, head :: tail) => aux(tail, firstList, head :: secondList, true)
      case (_, Nil) => (firstList, secondList)
    }
  }
  
  aux(list, List(), List(), true)
}

split2Tail(List(1, 2, 3, 4, 5, 6, 7, 8))
split2Tail(List(1, 2, 3, 4, 5))
split2Tail(List(1))
split2Tail(List())