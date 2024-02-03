class Time(private var hours: Int) {
  if (hours < 0) hours = 0
  
  def setHours (h: Int): Unit = {
    if (h < 0) hours = 0
    else hours = h
  }
  
  def getHours: Int = hours
}

object TimeTest extends App {
  val t = new Time(10)
  
  println(t.getHours)
  
  t.setHours(-1)
  println(t.getHours)
}