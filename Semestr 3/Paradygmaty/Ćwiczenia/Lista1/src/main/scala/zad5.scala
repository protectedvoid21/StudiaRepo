object zad5 {
  def main(args: Array[String]): Unit = {
    println(isPalindrome(List(1, 2, 3, 1)))
  }

  def isPalindrome[A](list: List[A]): Boolean = {
    list == reverseList(list)
  }
  
  def reverseList[A](list: List[A]): List[A] = {
    def reverseHelper(inputList: List[A], reversedList: List[A]): List[A] = {
      inputList match {
        case head :: tail => reverseHelper(tail, head :: reversedList)
        case Nil => reversedList
      }
    }
    
    reverseHelper(list, List())
  }
}
