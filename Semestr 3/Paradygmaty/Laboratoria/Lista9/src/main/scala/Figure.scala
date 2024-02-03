trait Figure {
  def area: Double
}

class Rectangle(private var width: Double, private var height: Double) extends Figure {
  def this(width: Double) = this(width, width)
  
  if width <= 0 then 
    throw new IllegalArgumentException("Width must be positive")
  if height <= 0 then
    throw new IllegalArgumentException("Height must be positive")
  
  override def area: Double = width * height
  
  def setWidth(newWidth: Double): Unit = 
    if newWidth <= 0 then 
      throw new IllegalArgumentException("Width must be positive")
    else
      width = newWidth
  
  def setHeight(newHeight: Double): Unit = 
    if newHeight <= 0 then 
      throw new IllegalArgumentException("Height must be positive")
    else
      height = newHeight
}

class Splitter(private val areaSplit: Double) {
  if areaSplit <= 0 then
    throw new IllegalArgumentException("Area split must be positive")
  
  protected var smallFigures: List[Figure] = List[Figure]()
  protected var bigFigures: List[Figure] = List[Figure]()
  
  def apply(figures: List[Figure]): Unit =
    figures.foreach(f => 
      if f.area <= areaSplit then
        smallFigures = smallFigures :+ f
      else
        bigFigures = bigFigures :+ f
    )
      
  protected def displayFigures(text: String, figureList: List[Figure]): Unit =
    println(text)
    figureList.foreach(figure => println(s"- ${figure.getClass.getSimpleName}, Area: ${figure.area}"))
  
  def displaySmallFigures(): Unit = displayFigures("Small figures", smallFigures)
  
  def displayBigFigures(): Unit = displayFigures("Big figures", bigFigures)
}

class FineSplitter(private val smallAreaMax: Double, private val bigAreaMin: Double) extends Splitter(smallAreaMax) {
  if smallAreaMax <= 0 then
    throw new IllegalArgumentException("Small area max must be positive")
  if bigAreaMin <= 0 then
    throw new IllegalArgumentException("Big area min must be positive")
  if bigAreaMin <= smallAreaMax then
    throw new IllegalArgumentException("Big area min must be greater than small area max")
  
  protected var mediumFigures: List[Figure] = List[Figure]()

  override def apply(figures: List[Figure]): Unit = {
    super.apply(figures.filter(f => f.area < smallAreaMax || f.area > bigAreaMin))
    mediumFigures = figures.filter(f => f.area >= smallAreaMax && f.area <= bigAreaMin)
  }
      
  def displayMediumFigures(): Unit = displayFigures("Medium figures", mediumFigures)
}