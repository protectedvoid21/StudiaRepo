@main
def main(): Unit = {
  val rectangle1 = Rectangle(15, 10)
  val rectangle2 = Rectangle(7, 5)
  val rectangle3 = Rectangle(10, 2)
  val rectangle4 = Rectangle(10, 6)
  val square1 = Rectangle(10)
  val square2 = Rectangle(5)
  val square3 = Rectangle(2)
  
  val shapes = List(rectangle1, rectangle2, rectangle3, rectangle4, square1, square2, square3)
  
  val splitter = FineSplitter(20, 50)
  
  splitter(shapes)
  
  splitter.displaySmallFigures()
  splitter.displayMediumFigures()
  splitter.displayBigFigures()
}