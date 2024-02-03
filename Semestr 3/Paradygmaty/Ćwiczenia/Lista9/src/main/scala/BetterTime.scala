class BetterTime(private var hour: Int, private var minute: Int) {
  if (hour < 0 || hour > 23) {
    throw new IllegalArgumentException("hour must be between 0 and 23")
  }

  if (minute < 0 || minute > 59) {
    throw new IllegalArgumentException("minute must be between 0 and 59")
  }

  private def minutes = hour * 60 + minute

  def before(other: BetterTime): Boolean = minutes < other.minutes

  def changeTime(newHour: Int, newMinute: Int): Unit =
    if (newHour < 0 || newHour > 23)
      throw new IllegalArgumentException("hour must be between 0 and 23")
    else if (newMinute < 0 || newMinute > 59)
      throw new IllegalArgumentException("minute must be between 0 and 59")
    else
      hour = newHour
      minute = newMinute
}

//write a demo

object BetterTimeTest extends App {
  val t1 = new BetterTime(11, 50)

  val t2 = new BetterTime(12, 45)

  println(t1.before(t2))

  val t3 = new BetterTime(-3, 30)
  val t4 = new BetterTime(3, 60)
}