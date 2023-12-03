def append[T](list: List[T], element: T): List[T] = {
  list :+ element
}

append(List(1, 2, 3), 4)