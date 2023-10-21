object zad7 {
  def main(args: Array[String]): Unit = {
    println(foo(8, 3))
  }
  
  def foo(n: Int, c: Int): Double = {
    n match {
      case 1 => 1
      case _ => c * math.log10(n) + foo(n / 2, c)
    }
  } 
}
