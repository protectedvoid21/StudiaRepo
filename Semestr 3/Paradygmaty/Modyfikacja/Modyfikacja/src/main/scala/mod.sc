def argmax(list: List[Int]): List[Int] = {
  def aux(lst: List[Int], maxLst: List[Int]): List[Int] = {
    if lst == Nil then
      maxLst
    else if lst.head > maxLst.head then
      aux(lst.tail, List(lst.head))
    else if lst.head == maxLst.head then
      aux(lst.tail, maxLst.head :: maxLst)
    else
      aux(lst.tail, maxLst)
  }

  if list == Nil then List()
  else aux(list.tail, List(list.head))
}

argmax(List(1, 2, 3, 4, 3, 2))
argmax(List(5, 3, 20, -1, 30, -5, 3))
argmax(List())
argmax(List(7, 2, 1, 3, 7, 0))
argmax(List(5, 4, 3, 2, 6, 5, 3))
argmax(List(5, 4, 7, 7, 7, 7, 5))