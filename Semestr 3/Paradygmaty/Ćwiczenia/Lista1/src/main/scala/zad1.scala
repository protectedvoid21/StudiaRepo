object zad1 {
  def main(args: Array[String]): Unit = {
    val firstList = List(2, 1)
    val secondList = List(3, 6)

    val flattened = flatten(List(firstList, secondList))
    println(flattened)
  }
  
  
  def flatten[A](lists: List[List[A]]): List[A] = {
    def flatten(result: List[A], remainingLists: List[List[A]]): List[A] = {
      remainingLists match {
        case Nil => result
        case headList :: tailLists =>
          flatten(result ::: headList, tailLists)
      }
    }

    flatten(Nil, lists)
  }
}