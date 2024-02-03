class TimeMidnight(private var minutes: Int) {
  if (minutes < 0 || minutes > 24 * 60) throw new IllegalArgumentException("Minutes must be between 0 and 24 * 60")
  
  def before(other: TimeMidnight): Boolean = minutes < other.minutes

  def changeTime(newHour: Int, newMinute: Int): Unit =
    if (newHour < 0 || newHour > 23)
      throw new IllegalArgumentException("hour must be between 0 and 23")
    else if (newMinute < 0 || newMinute > 59)
      throw new IllegalArgumentException("minute must be between 0 and 59")
    else
      minutes = newHour * 60 + newMinute
}


object TimeMidnightTest extends App {
  val t1 = new TimeMidnight(605)

  val t2 = new TimeMidnight(504)

  println(t1.before(t2))

  val t3 = new TimeMidnight(133004)
  val t4 = new TimeMidnight(-3)
}