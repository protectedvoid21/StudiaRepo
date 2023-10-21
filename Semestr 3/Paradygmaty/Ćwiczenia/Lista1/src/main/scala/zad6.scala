object zad6 {
  def main(args: Array[String]): Unit = {
    println(listLength(List(1, 2, 3, 4, 5, 6, 7)))
  }
  
  def listLength[A](list: List[A]): Int = {
    def getLengthHelper(restList: List[A], length: Int): Int = {
      restList match {
        case head :: tail => getLengthHelper(tail, length + 1)
        case Nil => length
      }
    }
    
    getLengthHelper(list, 0)
  }
}
