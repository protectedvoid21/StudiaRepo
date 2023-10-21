object zad2 {
  def main(args: Array[String]): Unit = {
    val occurrencies = count('a', List('a', 'l', 'a', 'm', 'a', 'k', 'o', 't', 'a'))
    println(occurrencies)
  }
  
  def count[T](element: T, list: List[T]): Int = {
    def count(remainingElements: List[T], elementCount: Int): Int = {
      remainingElements match {
        case Nil => elementCount 
        case headList :: tailList =>
          if headList == element then 
            count(tailList, elementCount + 1)
          else 
            count(tailList, elementCount)
            
      }
    }
    
    count(list, 0)
  }
}
