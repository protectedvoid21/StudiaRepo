object zad4 {
  def main(args: Array[String]): Unit = {
    println(sqrList(List(1, 3, -9, 4)))
  }
  
  def sqrList(list: List[Int]): List[Int] = {
    list match {
      case head :: tail => head * head :: sqrList(tail)
      case Nil => Nil
    }
  }
  
  def cursedSqrList(list: List[Int]): List[Int] = {
    list.map(x => x * x)
  }
}
