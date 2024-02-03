class Pojazd(val producent: String, val model: String, val rokProdukcji: Int = -1, var numerRejestracyjny: String = "") {
  override def toString: String = s"Pojazd(Producent: $producent, Model: $model, Rok produkcji: $rokProdukcji, Numer rejestracyjny: $numerRejestracyjny)"
}

object PojazdExample extends App {
  val pojazd1 = new Pojazd("Toyota", "Camry")
  val pojazd2 = new Pojazd("Ford", "Focus", 2020)
  val pojazd3 = new Pojazd("Honda", "Civic", 2018, "ABC123")
  val pojazd4 = new Pojazd("Chevrolet", "Malibu", numerRejestracyjny = "XYZ789")
  
  println(pojazd1)
  println(pojazd2)
  println(pojazd3)
  println(pojazd4)
}