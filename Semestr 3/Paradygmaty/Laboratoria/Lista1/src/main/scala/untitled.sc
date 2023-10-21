def reverse4(tuple: (Int, Int, Int, Int)) = (tuple._4, tuple._3, tuple._2, tuple._1)

reverse4((3, 1, 2, 4))
reverse4((1, 2, 3, 4))
reverse4((1, 2, 3, 4))
reverse4((3, 3, 2, 5))

def sumProd(s: Int, e: Int): (Int, Int) = {
  def sumHelper(current: Int): (Int, Int) = {
    if current < e - 1 then
      val sumTuple = sumHelper(current + 1)
      (current + sumTuple._1, current * sumTuple._2)
    else
      (current, current)
  }

  sumHelper(s)
}

sumProd(1, 5)
sumProd(5, 5)
sumProd(-3, 10)

def isPerfect(n: Int): Boolean = {
  def perfectHelper(left: Int, num: Int): Boolean = {
    if num == 0 then
      left == 0
    else
      if n % num == 0 then
        perfectHelper(left - num, num - 1)
      else
        perfectHelper(left, num - 1)
  }
  
  perfectHelper(n, n / 2)
}

isPerfect(6)
isPerfect(12)
isPerfect(20)
isPerfect(28)
isPerfect(50)

def insert[T](lst: List[T], elem: T, pos: Int): List[T] = {
  def insertAtPosition(list: List[T], position: Int): List[T] = {
    if position <= 0 then elem :: list
    else 
      list match {
        case head :: tail =>
          if position == 1 then elem :: head :: tail
          else head :: insertAtPosition(tail, position - 1)
        case Nil => List(elem)
    }
  }

  if pos <= 0 then elem :: lst
  else insertAtPosition(lst, pos)
}

insert(List(1, 2, 3, 4, 5, 6), 2137, 4)
insert(List(1, 2, 3, 4, 5, 6), 2137, -3)
insert(List(1, 2, 3, 4, 5, 6), 2137, 1000)
insert(List(1, 2, 3, 4, 5, 6), 2137, 2)