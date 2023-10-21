object zad3 {
  def main(args: Array[String]): Unit = {
    println(replicate('d', 5))
  }
  
  def replicate[A](element: A, count: Int): List[A] = {
    if count <= 0 then Nil
    else 
      element :: replicate(element, count - 1)
  }
}
