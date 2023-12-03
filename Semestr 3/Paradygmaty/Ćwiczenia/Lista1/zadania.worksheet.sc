//Zadanie 1
def flatten[A](lists: List[List[A]]): List[A] = {
  def flatten(result: List[A], remainingLists: List[List[A]]): List[A] = 
    remainingLists match
      case Nil => result 
      case headList :: tailLists => flatten(result ::: headList, tailLists)
  
  flatten(Nil, lists)
}

flatten(List(List(1, 2), List(3, 4)))
flatten(List(List(1, 2), List(3, 4), List(5, 6)))
flatten(List(List(1, 2), List(3, 4), List(5, 6), List(7, 8)))
flatten(List(List(List(1, 2, 3), List(4, 5, 6)), List(List(7, 8, 9), List(10, 11, 12))))

//Zadanie 2
def count[T](element: T, list: List[T]): Int = {
  def count(remainingElements: List[T], elementCount: Int): Int =
    remainingElements match
      case Nil => elementCount 
      case headList :: tailList =>
        if headList == element then count(tailList, elementCount + 1)
        else count(tailList, elementCount)
    
  count(list, 0)
}

count('a', List('a', 'l', 'a', 'm', 'a', 'k', 'o', 't', 'a'))
count('a', List('a', 'l', 'a', 'm', 'a', 'k', 'o', 't', 'a', 'a'))
count(3, List(1, 2, 3, 4, 5, 4, 3, 2, 3, 2, -1))
count(-1, List())

//Zadanie 3
def replicate[A](element: A, count: Int): List[A] = count <= 0 match
  case true => Nil
  case false => element :: replicate(element, count - 1)
  
replicate('d', 5)
replicate('d', 0)
replicate('d', -1)
replicate(2137, 4)

//Zadanie 4
def sqrList(list: List[Int]): List[Int] = list match 
  case head :: tail => head * head :: sqrList(tail)
  case Nil => Nil

sqrList(List(1, 3, -9, 4))
sqrList(List(1, 3, -9, 4, 0))
sqrList(List())
  
//Zadanie 5
def isPalindrome(list: List[Int]): Boolean = {
  def reverseList(list: List[Int]): List[Int] = {
    def reverseHelper(inputList: List[Int], reversedList: List[Int]): List[Int] = inputList match
        case head :: tail => reverseHelper(tail, head :: reversedList)
        case Nil => reversedList
    
    reverseHelper(list, List())
  }
  
  list == reverseList(list)
}

isPalindrome(List(1, 2, 3, 1))
isPalindrome(List(1, 2, 3, 2, 1))
isPalindrome(List(1, 2, 3, 2, 1, 0))
isPalindrome(List(1, 2, 2, 1))

//Zadanie 6
def listLength[A](list: List[A]): Int = {
    def getLengthHelper(restList: List[A], length: Int): Int = 
      restList match 
        case head :: tail => getLengthHelper(tail, length + 1) 
        case Nil => length
    
  getLengthHelper(list, 0)
}

listLength(List(1, 2, 3, 4, 5))
listLength(List(1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
listLength(List())
listLength(List(1))

//Zadanie 7
def foo(n: Int, c: Int): Double = n match 
  case 1 => 1
  case _ => c * math.log10(n) + foo(n / 2, c)

foo(8, 3)
foo(1, 3)
foo(2, 3)
  